/**************************************************************
* File Name   : mkclass.go
* Author      : ThreeDog
* Date        : 2019-12-24 09:54:44
* Description : 
*
**************************************************************/

package main

import (
	"fmt"
	"os"
	"log"
	"bytes"
	"time"
	"strings"
)

/**
 检查错误
 */
 func checkErr(err error){
	if err!=nil{
		log.Fatal(err)
	}
}

func PathExists(path string) (bool, error) {
	_, err := os.Stat(path)
	if err == nil {
		return true, nil
	}
	if os.IsNotExist(err) {
		return false, nil
	}
	return false, err
}

//文件校验处理，如果文件已经存在，询问替换， 如果文件不存在则直接创建
func CheckFile(path string)(bool, error){
	res,_ := PathExists(path)
	// 如果文件已经存在，替换一下文件名 
	if res {
		fmt.Printf("文件%s已存在，是否覆盖创建？（旧文件将被重命名为：%s.bak ）Y/N ",path,path)
		var ok string
		fmt.Scanln(&ok)
		if ok == "Y"{
			err := os.Rename(path,path+".bak")
			if err != nil{
				fmt.Printf("文件%q已存在，将文件重命名为%q.bak时失败 \n",os.Args[1],os.Args[1])
				return false ,err
			}
			return true,nil
		}else{
			return  false, nil
		}
	}
	return true , nil
}

func main()  {
	// 命令行参数获取
	if len(os.Args) != 2 {
		fmt.Printf("arguement error: 命令mkc需要有且只有一个参数 \n")
		return 
	}
	classname := os.Args[1]
	name := strings.ToLower(os.Args[1])
	cppfilename := name + ".cpp"
	headfilename :=  name + ".h"
	headname := strings.ToUpper(headfilename)
	headname = strings.Replace(headname, ".", "_", -1 )

	res1,_ := CheckFile(cppfilename)
	res2,_ := CheckFile(headfilename)
	if !res1 || !res2 {
		return 
	} 

	// cpp文件
	cppfile,err:=os.OpenFile(cppfilename,os.O_CREATE|os.O_APPEND|os.O_WRONLY,0644)
	checkErr(err)
	var buffer bytes.Buffer
	buffer.WriteString("/**************************************************************\n")
	buffer.WriteString("* File Name   : " + cppfilename + "\n")
	buffer.WriteString("* Author      : ThreeDog\n")
	buffer.WriteString("* Date        : "+time.Now().Format("2006-01-02 15:04:05")+"\n")
	buffer.WriteString("* Description : \n")
	buffer.WriteString("*\n")
	buffer.WriteString("**************************************************************/\n\n")
	buffer.WriteString("#include \""+headfilename+"\"\n\n")
	buffer.WriteString(classname+"::"+classname+"()\n")
	buffer.WriteString("{\n\n")
	buffer.WriteString("}\n\n")
	buffer.WriteString(classname+"::~"+classname+"()\n")
	buffer.WriteString("{\n\n")
	buffer.WriteString("}\n\n")

	cppfile.Write([]byte(buffer.String()))
	cppfile.Close()


	// 头文件
	headfile,err:=os.OpenFile(headfilename,os.O_CREATE|os.O_APPEND|os.O_WRONLY,0644)
	checkErr(err)
	var buffer2 bytes.Buffer
	buffer2.WriteString("/**************************************************************\n")
	buffer2.WriteString("* File Name   : " + headfilename + "\n")
	buffer2.WriteString("* Author      : ThreeDog\n")
	buffer2.WriteString("* Date        : "+time.Now().Format("2006-01-02 15:04:05")+"\n")
	buffer2.WriteString("* Description : \n")
	buffer2.WriteString("*\n")
	buffer2.WriteString("**************************************************************/\n\n")
	buffer2.WriteString("#ifndef __"+headname+"__\n")
	buffer2.WriteString("#define __"+headname+"__\n\n\n")
	buffer2.WriteString("class "+classname+"\n")
	buffer2.WriteString("{\n")
	buffer2.WriteString("public:\n")
	buffer2.WriteString("\t"+classname+"();\n")
	buffer2.WriteString("\t~"+classname+"();\n")
	buffer2.WriteString("};\n\n")
	buffer2.WriteString("#endif  // __"+headname+"__\n")

	headfile.Write([]byte(buffer2.String()))
	headfile.Close()

}
