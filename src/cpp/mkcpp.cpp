/**************************************************************
 * File Name   : mkcpp.cpp
 * Author      : ThreeDog
 * Date        : Thu Nov  3 11:05:14 2016
 * Description : 快捷命令 制作.cpp文件
 *
 **************************************************************/


#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc,char **argv){

	int size = 20;

	ofstream output_file(argv[1],ios::trunc);
	if(argc < 2){
		cerr << "arguement error: 命令mkcpp需要包含一个参数 " << endl;
		return 1;
	}
	else if(argc > 2){
		cerr << "arguement error: 命令mkcpp只能包含一个参数 " << endl;
		return 1;
	}

	if(!output_file){
		cerr << "open file " << argv[1] << "fail" << endl;
		return 3;
	}
	time_t now_time;
	now_time = time(NULL);
	output_file << "/**************************************************************"<<endl;
	output_file << " * File Name   : " << argv[1] << endl;
	output_file << " * Author      : ThreeDog "<<endl;
	output_file << " * Date        : " << ctime(&now_time);
	output_file << " * Description : " << endl << " *" << endl;
	output_file << " **************************************************************/"<<endl;

	output_file << endl;
	output_file << "#include <iostream>" << endl;
	output_file << endl;
	output_file << "using namespace std;" << endl;
	output_file << endl;
	output_file << "int main (int argc, char **argv){" << endl;
	output_file << endl;
	output_file << endl;
	output_file << endl;
	output_file << endl;
	output_file << "return 0;" << endl;
	output_file << "}" << endl;

	char *a = new char[size];
	char *name = new char[size];
	strcpy(name,argv[1]);
	strcpy(a,"vi ");
	char *n = strtok(argv[1],".");

	while(strlen(n) > size){
		char *r = new char[size+10];
		strcpy(r,a);
		delete[] a;
		a = r;
		size += 10;
		}

	strcat(a,name);
	system(a);

	return 0;
}
