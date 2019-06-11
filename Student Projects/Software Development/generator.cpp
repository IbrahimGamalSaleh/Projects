#include <iostream>
#include <cstring>
#include <string>
using namespace std;

int main() {
	string station[] = {"Assyut", "Cairo", "Qena", "Luxor", "Sohag", "Alexandria", "Aswan", "Giza", "Beni-Suef", "Minia", "Helwan" };
	string taymfrom[] = {"00:30 AM", "06:00 AM", "08:00 PM", "07:30 PM"};
	string taymto[] = {"03:50 AM", "10:30 AM", "01:00 AM", "11:45 PM"};
	string clss[] = {"Express", "Distinctive", "VIP", "SLEEPING", "Conditioned", "Upgraded"};
	string price1[] = {"05.00", "04.00", "100.00", "300.00", "50.00", "05.00"};
	string price2[] = {"05.00", "04.00", "200.00", "600.00", "1000.00", "05.00"};

	for (int t=0; t<2; ++t)
	for (int k=0 ; k<6 ; ++k)
    	for (int i=0 ; i<11;++i)
    		for (int j=0 ; j<11;++j)
    				if (i!=j)
    		    printf("(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"1st: %s\",\"2nd: %s\"),\n",
			station[i].c_str(),
			taymfrom[(i+j)%4].c_str(),
			station[j].c_str(),
			taymto[(i+j)%4].c_str(),
			clss[k].c_str(),
			price1[k].c_str(),
			price2[k].c_str());

	return 0;
}
