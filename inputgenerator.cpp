#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){
	if(argc != 2) cout<<"ERROR: wrong input format\n";
	ofstream file(argv[1]);
	file.is_open();
	int i = 0;
	while(i<10){
		int n = rand() % 20 + (-10); 
		file<<n<<endl;
		i++;
	}

	file.close();

	return 0;
}
