/**************************************************************
* File Name   : mkcpp.go
* Author      : ThreeDog
* Date        : 2019-12-23 20:02:00
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
)

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

/**
 检查错误
 */
func checkErr(err error){
	if err!=nil{
		log.Fatal(err)
	}
}

func main()  {
	// 命令行参数获取
	if len(os.Args) != 2 {
		fmt.Printf("arguement error: 命令mkc需要有且只有一个参数 \n")
		return 
	}
	
	res,_ := PathExists(os.Args[1])
	// 如果文件已经存在，替换一下文件名 
	if res {
		fmt.Printf("文件%s已存在，是否覆盖创建？（旧文件将被重命名为：%s.bak ）Y/N ",os.Args[1],os.Args[1])
		var ok string
		fmt.Scanln(&ok)
		if ok == "Y"{
			err := os.Rename(os.Args[1],os.Args[1]+".bak")
			if err != nil{
				fmt.Printf("文件%q已存在，将文件重命名为%q.bak时失败 \n",os.Args[1],os.Args[1])
				return 
			}
		}else{
			return 
		}
	}
	
	// 打开文件
	file,err:=os.OpenFile(os.Args[1],os.O_CREATE|os.O_APPEND|os.O_WRONLY,0644)
	checkErr(err)
	var buffer bytes.Buffer
	buffer.WriteString("/**************************************************************\n")
	buffer.WriteString("* File Name   : " + os.Args[1] + "\n")
	buffer.WriteString("* Author      : ThreeDog\n")
	buffer.WriteString("* Date        : "+time.Now().Format("2006-01-02 15:04:05")+"\n")
	buffer.WriteString("* Description : \n")
	buffer.WriteString("*\n")
	buffer.WriteString("**************************************************************/\n\n")
	buffer.WriteString("#include <iostream>\n\n")
	buffer.WriteString("using namespace std;\n\n")
	buffer.WriteString("int main (int argc , char** argv)\n")
	buffer.WriteString("{\n")
	buffer.WriteString("\treturn 0;\n")
	buffer.WriteString("}\n")

	file.Write([]byte(buffer.String()))
	file.Close()
}
