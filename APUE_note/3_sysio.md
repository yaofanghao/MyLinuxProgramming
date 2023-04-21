<!--
 * @Author: yao fanghao
 * @Date: 2023-04-20 22:20:30
 * @LastEditTime: 2023-04-21 14:49:58
 * @LastEditors: yao fanghao
-->
# 文件I/O 基础知识

# 参考书

* UNP 第4章 文件I/O
* APUE 第3章 文件I/O
* 李慧琴网课 p124-141

# 学习进度

* UNP 4.1
* APUE 3.1
* 李慧琴网课 P125

# 代码参考3_sysio.c

* 通常都需要包含的头文件:

```C
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
int main(int argc, char **argv)
{
    // ....
    exit(0);
}
```

* stdio标准库
  * fopen();
  * fclose();
  * fputc();
  * fgetc();
  * fgets();
  * fputs();
  * fread();
  * fwrite();


* "r" 只读
* "w" 只写

* 使用malloc要包含stdlib头文件，否则会报警告
  
* ulimit -a 命令
  * 一个进程能打开的文件个数最多为1024个

* exit(0) 正常退出
* exit(1) 异常退出
