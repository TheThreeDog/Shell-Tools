/**************************************************************
 * File Name   : mkhead.cpp
 * Author      : ThreeDog
 * Date        : Thu Nov  3 11:05:14 2016
 * Description : 快捷命令 制作.h文件
 *
 **************************************************************/

#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
using namespace std;

int main(int argc,char **argv){
	int size = 20;
	if(argc < 2){
		cerr << "arguement error: 命令mkhead需要包含一个参数 " << endl;
		return 1;
	}
	else if(argc > 2){
		cerr << "arguement error: 命令mkhead只能包含一个参数 " << endl;
		return 1;
	}


	ofstream output_file(argv[1],ios::trunc);
	if(!output_file){
		cerr << "open file " << argv[1] << "fail" << endl;
		return 3;
		}
	char *p = new char[size];
	char *a = new char[size];
	char *name = new char[size];
	strcpy(name,argv[1]);
	strcpy(a,"vi ");
	char *n = strtok(argv[1],".");

	while(strlen(n) > size){
		char *q = new char[size+10];
		delete[] p;
		p = q;
		char *r = new char[size+10];
		strcpy(r,a);
		delete[] a;
		a = r;
		size += 10;
		}
	strcpy(p,n);
	strcat(a,name);
	for(int i = 0; i < size; i++)
		*(p+i) = toupper(*(p+i));
	char buff[size+50];
	memset(buff,0,sizeof(buff));
	strcat(buff,"#ifndef _");
	strcat(buff,p);
	strcat(buff,"_H_ \n");
	strcat(buff,"#define _");
	strcat(buff,p);
	strcat(buff,"_H_ \n\n\n\n\n\n\n");
	strcat(buff,"#endif");

	time_t now_time;
    now_time = time(NULL);
	output_file << "/**************************************************************"<<endl;
	output_file << " * File Name   : " << argv[1] << ".h" << endl;
	output_file << " * Author      : ThreeDog"<<endl;
	output_file << " * Date        : " << ctime(&now_time);
	output_file << " * Description : " << endl << " *" << endl;
	output_file << " **************************************************************/"<<endl;

	output_file.write(buff,strlen(buff));
	output_file.close();
	system(a);
	delete[] name;
	return 0;
}
