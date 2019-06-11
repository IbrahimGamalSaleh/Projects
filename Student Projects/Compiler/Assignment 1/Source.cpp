#define _CRT_SECURE_NO_WARNINGS
#include <bits\stdc++.h>

#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define endl '\n'

#define lpi(i,j,s) for(int i=s;i<j;++i)
#define lpd(i,j,s) for(int i=s;i>=j;i--)
#define all(i,n) (i).begin(),(i).end()
#define sz(x) (int)(x).size()

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

#define MAXI (int)0x7fffffff
#define MINI (int)0x80000000
#define MAXL (long long)0x7fffffffffffffff
#define MINL (long long)0x8000000000000000

#ifdef ONLINE_JUDGE
#define whats(i) //whats()
#define file ;
#else
#define whats(i) cout<<#i<<" = "<<i<<endl;
#define file freopen("file.in", "r", stdin);freopen("file.out", "w", stdout);
#endif

// /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ \\
// || || || || || || || || || || || || || || || || || || || || || || || || || || || || || \\
// ||	 ||			 ||												 ||			 ||	   || \\
// ||	 ||			 ||		 	 nothing .... goes ....			 	 ||	 		 ||	   || \\
// ||	 ||			 ||			       here .... at all ....		 ||		  	 ||	   || \\
// ||	 ||			 ||												 ||			 ||	   || \\
// || || || || || || || || || || || || || || || || || || || || || || || || || || || || || \\
// \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \\


using namespace std;

int state = 0;

// [0] => for language alphabet
// [1] => for identifiers
// [3] => for numbers
// [4] => for operators
set<char> grmr[4];

vector<string> identifiers;
vector<int> numbers;
vector<char> opertors;


void initialize() {

	grmr[1].insert('_');

	for (int i = 0; i < 26; ++i)
		grmr[1].insert(i + 'a'), grmr[1].insert(i + 'A');

	for (int i = 0; i < 10; ++i)
		grmr[1].insert(i + '0'), grmr[2].insert(i + '0');

	grmr[3].insert('+'); grmr[3].insert('-'); grmr[3].insert('=');
	grmr[3].insert('*'); grmr[3].insert('/'); grmr[3].insert('!');
	grmr[3].insert('%'); grmr[3].insert('^'); grmr[3].insert('&');
	
	grmr[0].insert(grmr[1].begin(), grmr[1].end());
	grmr[0].insert(grmr[3].begin(), grmr[3].end());

}

int main() {

	fast file;

	initialize();



	string s;
	while (getline(cin, s)) {

		string identifier = "";
		int number = 0;
		char opertor = '\0';

		for (int i = 0; i < s.size(); ++i) {
			if (grmr[2].count(s[i]))
				if (state != 1)
					number = number * 10 + (s[i] - '0'), state = 2;
				else
					identifier += s[i];
			else if (grmr[1].count(s[i])) {
				if (state == 2) {
					numbers.push_back(number);
					number = 0;
				}
				identifier += s[i];
				state = 1;
			}
			else if (grmr[3].count(s[i])) {
				opertors.push_back(s[i]);
				if (state == 1) {
					identifiers.push_back(identifier);
					identifier = "";
					state = 0;
				}
				else if (state == 2) {
					numbers.push_back(number);
					number = 0;
					state = 0;
				}
			}
			else {
				if (state == 1) {
					identifiers.push_back(identifier);
					identifier = "";
					state = 0;
				}
				else if (state == 2) {
					numbers.push_back(number);
					number = 0;
					state = 0;
				}
			}
		}

		if (state == 1) {
			identifiers.push_back(identifier);
			identifier = "";
			state = 0;
		}
		else if (state == 2) {
			numbers.push_back(number);
			number = 0;
			state = 0;
		}
	}

	cout << "Identifiers: " << endl;
	if (identifiers.empty()) cout << "none" << endl;
	for (auto itr : identifiers)
		cout << itr << endl;
	cout << endl;

	cout << "Numbers: " << endl;
	if (numbers.empty()) cout << "none" << endl;
	for (auto itr : numbers)
		cout << itr << endl;
	cout << endl;

	cout << "Operators: " << endl;
	if (opertors.empty()) cout << "none" << endl;
	for (auto itr : opertors)
		cout << itr << endl;

	return 0;
}