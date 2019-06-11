/* 
This code simulates, in simple form, 'tasklist' command implemented in Windows CMD.
*/

//console application.
//#include "console.h"
#include <iostream>
#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <Windows.h>
#include <iomanip>
#include <psapi.h>

#define MODULES 7
#define PROCESSES 777
#pragma pack(16)
#pragma comment( lib, "psapi.lib" )

typedef struct tagPROCESSTIMES {
	__int64 m_kernel;
	__int64 m_user;
} PROCESSTIMES[PROCESSES];
PROCESSTIMES ptm;

#define WAIT_FOR_PROCESS 5// In seconds

BOOL GetCurrentProcessCreateTime(LPSTR lpszString) {
	FILETIME createTime;
	FILETIME exitTime;
	FILETIME kernelTimeProcess;
	FILETIME userTimeProcess;
	FILETIME ftLocal;
	HANDLE hProcess = GetCurrentProcess();
	SYSTEMTIME stCreate;

	if (hProcess) {
		if (!GetProcessTimes(hProcess, &createTime, &exitTime, &kernelTimeProcess, &userTimeProcess))
			return FALSE;

		if (!FileTimeToLocalFileTime(&createTime, &ftLocal))
			return FALSE;

		FileTimeToSystemTime(&ftLocal, &stCreate);

		wsprintfA(lpszString, "%02d/%02d/%d %02d:%02d:%02d",
			stCreate.wMonth, stCreate.wDay, stCreate.wYear,
			stCreate.wHour, stCreate.wMinute, stCreate.wSecond);
		return TRUE;
	}
	return FALSE;
}

void GetTimes(DWORD processID, UINT index) {
	FILETIME m_createTime;
	FILETIME m_exitTime;
	FILETIME m_kernelTimeProcess;
	FILETIME m_userTimeProcess;
	__int64 m_kernel = 0;
	__int64 m_user = 0;

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
	if (hProcess)
	{
		GetProcessTimes(hProcess, &m_createTime, &m_exitTime, &m_kernelTimeProcess, &m_userTimeProcess);
		m_kernel = m_kernelTimeProcess.dwHighDateTime;
		m_kernel = m_kernel << 32;
		m_kernel += m_kernelTimeProcess.dwLowDateTime;
		m_user = m_userTimeProcess.dwHighDateTime;
		m_user = m_user << 32;
		m_user += m_userTimeProcess.dwLowDateTime;
	}
	ptm[index].m_kernel = m_kernel;
	ptm[index].m_user = m_user;
}

ULONG PrintProcessNameAndID(DWORD processID, UINT index) {

	char szProcessName[MAX_PATH] = "unknown";

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

	FILETIME createTime;
	FILETIME exitTime;
	FILETIME kernelTimeProcess;
	FILETIME userTimeProcess;
	__int64 kernel = 0;
	__int64 user = 0;
	ULONG kresult = 0;
	ULONG uresult = 0;
	ULONG cpuusage = 0;
	__int64 divisor = 156250;

	HMODULE hMod[MODULES];
	char szModuleName[MAX_PATH] = "unknown";
	DWORD cbNeeded;
	int num;

	// we put a condition at 'GetTimes' function to get the times at which processes start, 
	// thus, we should do this here again, we can't get times for null-handle process
	// and also it has no old time in the arry 'ptm'
	if (hProcess)
	{
		GetProcessTimes(hProcess, &createTime, &exitTime, &kernelTimeProcess, &userTimeProcess);

		kernel = kernelTimeProcess.dwHighDateTime;
		kernel = kernel << 32;
		kernel += kernelTimeProcess.dwLowDateTime;
		kernel -= ptm[index].m_kernel;
		kresult = (ULONG)(kernel / divisor);

		user = userTimeProcess.dwHighDateTime;
		user = user << 32;
		user += userTimeProcess.dwLowDateTime;
		user -= ptm[index].m_user;
		uresult = (ULONG)(user / divisor);

		cpuusage += kresult + uresult;
	}

	
	// if we ignore the condition here, we may get '?nknown', which has no meaning
	if (EnumProcessModules(hProcess, hMod, sizeof(hMod), &cbNeeded))
	GetModuleBaseNameA(hProcess, hMod[0], szProcessName, sizeof(szProcessName));


	// ignoring the condition and printing all processes; to see details of the processes, pid, user and kernel time
	//if (strcmp(szProcessName, "unknown") != 0)
	{
	//if ((kresult != 0) || (uresult != 0))
	printf("%s", szProcessName);

	if (strlen(szProcessName) < 8)
	printf("\t\t\t(PID: %u)", processID);
	else if (strlen(szProcessName) > 16)
	printf("\t(PID: %u)", processID);
	else
	printf("\t\t(PID: %u)", processID);

	printf("\tKernel [%lu]\t User [%lu]\n", kresult, uresult);

	// limited to print only 7, if there's enough, modules
	num = cbNeeded / sizeof(HMODULE);
	for (int i = 1; i < num && i < MODULES; ++i) {

	//Only for the 'unknown' processes, if we ignored the condition and called function 'GetModuleBaseName' directly and print the module,
	//we then get a '?nknown', meaningless answer.

	if (GetModuleBaseNameA(hProcess, hMod[i], szModuleName, sizeof(szModuleName)))
	printf("\t\t%s\n", szModuleName);
	}
	}
	

	CloseHandle(hProcess);
	return cpuusage;
}

void maain() {

	char String[32];
	LPSTR lpszString;
	lpszString = String;

	if (GetCurrentProcessCreateTime(lpszString)) {
		printf("This Process Created: %s\n", lpszString);
		printf("Processing, PLEASE wait");
	}

	DWORD aProcesses[1024], cbNeeded, cProcesses;
	ULONG lCpuusage = 0;
	UINT index;
	double percent;

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
		return;

	cProcesses = cbNeeded / sizeof(DWORD);

	if (cProcesses > PROCESSES) {
		printf("\nProgram Error, %ld is too many, see PROCESSTIMES structure!\n", cProcesses);
		printf("\nPress any key to exit ");
		while (!_kbhit());
		exit(1);
	}

	for (index = 0; index < cProcesses; index++)
		GetTimes(aProcesses[index], index);

	for (int wait = 0; wait < WAIT_FOR_PROCESS; wait++) {
		printf(".");
		Sleep(1000);
	}

	printf("\n|Process Name \t\t| PID  \t|      | Kernel    |\t| User   |\n");
	printf("------------------------------------------------------------------\n");

	for (index = 0; index < cProcesses; index++)
		lCpuusage += PrintProcessNameAndID(aProcesses[index], index);

	printf("------------------------------------------------------------------\n");
	percent = (double)(lCpuusage / (2.0*(double)WAIT_FOR_PROCESS));
	printf("Processes: %ld\t\t CPU Usage: %3.2f%% Per/Sec\n", cProcesses, percent);
	printf("Press any key to exit ");

	while (!_kbhit());
}
