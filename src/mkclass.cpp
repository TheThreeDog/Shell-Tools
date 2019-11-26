/**************************************************************
 * File Name   : mkclass.cpp
 * Author      : ThreeDog
 * Date        : Mon Jan 02 15:52:38 2017
 * Description : 快捷命令，制作一个类的.h和.cpp文件
 *
 **************************************************************/

#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main (int argc, char **argv){
    //创建一个类，以类名为基础制作头文件和cpp文件
    if(argc < 2){
        cerr << "arguement error: Command 'mkclass' needs an arguement! " << endl;
        return 1;
    }
    else if(argc > 2){
        cerr << "arguement error: Command 'mkclass' only have one arguement!" << endl;
        return 1;
    }

    int size = 20;//初始化扩展区域的大小

    //先用一个字符串存储传入的参数，并保存为小写形式
    char *arg_lower = new char[size];
    while(strlen(argv[1]) > size){  //如果参数长度大于20，则扩展大小
        char *q = new char[size+10];
        delete[] arg_lower;
        arg_lower = q;
        size += 10;
        delete[] q;
        }
    strcpy(arg_lower,argv[1]);              //ClassName
    for(int i = 0; i < size; i++)//全部转换成小写
		*(arg_lower+i) = tolower(*(arg_lower+i));           //classname

    //创建头文件
    //先判断文件是否存在，询问用户
    fstream file;
    char *file_head = new char[size+5];
    strcpy(file_head,arg_lower);            //classname
    strcat(file_head,".h");                 //classname.h
    file.open(file_head,ios::in);
    if(!file){
    //cout<<FILENAME<<"没有被创建";
    }
    else{
        while(1){
            cout<<file_head<<" already exits ! Would you like to recreate it ? Y/N" << endl;
            char is_create;
            cin >> is_create;
            if('Y' == is_create)
                break;
            else if('N' == is_create)
                return 2;
            //如果输入正确  不会执行到这一步
            cout <<"input error!"<<endl;
            cerr << "open file " << file_head << " fail" << endl;
            return 2;
        }
    }
    file.close();

    ofstream output_file(file_head,ios::trunc);

	if(!output_file){
  		cerr << "open file " << file_head << "fail" << endl;
		return 3;
	}

	char *arg_upper = new char[size];

	strcpy(arg_upper,arg_lower);
	//转化为大写
	for(int i = 0; i < size; i++)              //CLASSNAME
		*(arg_upper+i) = toupper(*(arg_upper+i));

	time_t now_time;
    now_time = time(NULL);
	output_file << "/**************************************************************"<<endl;
	output_file << " * File Name   : " << arg_lower << ".h" << endl;
	output_file << " * Author      : ThreeDog"<<endl;
	output_file << " * Date        : " << ctime(&now_time);
	output_file << " * Description : " << endl << " *" << endl;
	output_file << " **************************************************************/"<<endl;

    output_file << "#ifndef _" << arg_upper << "_H_ "<<endl;    //#ifnedf CLASSNAME_H_
    output_file << "#define _" << arg_upper << "_H_ "<<endl;    //#define CLASSNAME_H_
    output_file << endl << endl;
    output_file << "class " << argv[1] << endl;                 //class ClassName
    output_file << "{" << endl;                                 //{
    output_file << "public:" <<endl;                            //public:
    output_file << "    "<<argv[1]<<"();" << endl;              //    ClassName();
    output_file << "    ~"<<argv[1]<<"();" << endl;             //    ClassName();
    output_file << "};"<<endl;                                  //};
    output_file << endl;
    output_file << "#endif  //" << arg_upper <<endl;             //#endif  //CLASSNAME_H_

	output_file.close();
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    //创建头文件完毕
    //创建cpp文件
    //先判断文件是否存在，询问用户
    char *file_cpp = new char[size+5];
    strcpy(file_cpp,arg_lower);            //classname
    strcat(file_cpp,".cpp");                 //classname.pp
    file.open(file_cpp,ios::in);
    if(!file){
    //cout<<FILENAME<<"没有被创建";
    }
    else{
        while(1){
            cout<<file_cpp<<" already exits ! Would you like to recreate it ? Y/N" << endl;
            char is_create;
            cin >> is_create;
            if('Y' == is_create)
                break;
            else if('N' == is_create)
                return 2;
            //如果输入正确  不会执行到这一步
            cout <<"input error!"<<endl;
            cerr << "open file " << file_head << " fail" << endl;
            return 2;
        }
    }
    file.close();

    output_file.open(file_cpp,ios::trunc);

	if(!output_file){
		cerr << "open file " << argv[1] << "fail" << endl;
		return 3;
	}
	output_file << "/**************************************************************"<<endl;
	output_file << " * File Name   : " << file_cpp << endl;
	output_file << " * Author      : ThreeDog "<<endl;
	output_file << " * Date        : " << ctime(&now_time);
	output_file << " * Description : " << endl << " *" << endl;
	output_file << " **************************************************************/"<<endl;

	output_file << endl;
	output_file << "#include \"" <<file_head <<"\""<< endl;                             //#include "classname.h"
	output_file << endl;
    output_file << argv[1] <<"::"<<argv[1]<<"()" << endl;                               //ClassName::ClassName()
    output_file << "{" << endl;                                                         //{
    output_file << endl;
    output_file << "}" << endl;                                                         //}
    output_file << endl;
    output_file << argv[1] <<"::~"<<argv[1]<<"()" << endl;                              //ClassName::~ClassName()
    output_file << "{" << endl;                                                         //{
    output_file << endl;
    output_file << "}" << endl;                                                         //}

	output_file.close();

    //释放内存
    delete[] arg_lower;
    delete[] arg_upper;
    delete[] file_head;
    delete[] file_cpp;

return 0;
}
