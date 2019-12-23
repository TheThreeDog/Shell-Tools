/**************************************************************
* File Name   : mkhead.go
* Author      : ThreeDog
* Date        : 2019-12-23 20:04:41
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
		err := os.Rename(os.Args[1],os.Args[1]+".bak")
		if err != nil{
			fmt.Printf("文件%q已存在，将文件重命名为%q.bak时失败 \n",os.Args[1],os.Args[1])
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
	
	var name string;
	name = strings.ToUpper(os.Args[1])
	name = strings.Replace(name, ".", "_", -1 )

	buffer.WriteString("#ifndef __"+name+"__\n")
	buffer.WriteString("#define __"+name+"__\n\n\n\n\n\n\n\n\n\n")
	buffer.WriteString("#endif  // __"+name+"__\n")

	file.Write([]byte(buffer.String()))
	file.Close()
}
