<!--
 * @Author: yao fanghao
 * @Date: 2023-04-20 22:20:30
 * @LastEditTime: 2023-04-21 22:04:11
 * @LastEditors: yao fanghao
-->
# 文件I/O 基础知识

# 参考资料

* UNP 第4、5章 文件I/O
* **APUE 第3-6章** 文件I/O、文件和目录、标准I/O库、系统数据文件和信息
* 李慧琴网课 p124-141

# 学习进度

* UNP 4.1
* APUE 3.1
* 李慧琴网课 P136

# 简要记录

* io操作非常重要且常用，一切皆文件
* **需用到时多查man手册**

## 系统I/O 参考代码-- 1_1_sysio.c

* 通常都需要包含的头文件:

```C
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
int main(int argc, char **argv)
{
    // ....
    exit(0);  // 0 正常退出，1异常退出
}
```

* stream-流的概念
  * 0: stdin
  * 1: stdout
  * 2: stderr

* ```fopen();```
  * 结合 ```strerror(errno) / perror()``` 使用
  * "r" 只读
  * "w" 只写

  ```C
  if(fps == NULL)
  {
      fprintf(stderr, "fopen() failed, errno = %d \n", errno);
      fprintf(stderr, "fopen() failed, %s \n", strerror(errno)); 
      perror("fopen()");
      exit(1);
  }
  ```

* ```fclose();```

* ```fputc();```
* ```fgetc();```
* ```fgets();```
  * 结合 ```char buf[BUFSIZE]``` 使用
* ```fputs();```

    ```C
    // 方法1
    // 按字符并写入    
    while(1)
    {
        ch = fgetc(fps);
        if (ch == EOF)
        {
            break;  // 读到文件末尾即退出
        }
        fputc(ch, fpd);
    }

    // 方法2
    // 按符串并写入
    while(fgets(buf, BUFSIZE, fps) != NULL)
    {
        fputs(buf, fpd);
    }
    ```

* ```fread();```
* ```fwrite();```
  
* ```printf();```  
* ```fprintf();```
  * 可以把信息输出到指定的stream中
* ```sprintf();```
* ```scanf();```
* ```fscanf();```

* ```fseek();```
  * 可以设置偏移量offset
  * 可以设置位置pos: ```SEEK_SET / SEEK_CUR / SEEK_END```
* ```ftell();```
  * 找出文件当前位置指针
* ```fseek``` 和 ```ftell``` 二者结合可以统计文件长度

  ```C
  fseek(fps, 0, SEEK_END);
  printf("length of file is %ld \n", ftell(fps));
  ```

* ```rewind();```
  * 回到文件起始位置
  * 等同于 fseek(stream, 0, SEEK_SET)

* ```fseeko();```
* ```ftello();```

* ```fflush();```
  * 刷新流，空表示对所有流操作

* ```getline();```

* 使用```malloc```要包含stdlib头文件，否则会报警告或产生可怕的错误
  
* ```ulimit -a ``` 命令
  * 一个进程能打开的文件个数最多为1024个

* 临时文件
  * 如何不冲突、及时销毁
  * ```tmpnam```
  * ```tmpfile```

## 标准I/O 参考代码-- 1_2_stdio.c

* 文件描述符 fd
  * 整型数
  * 存在于某个进程空间中
  * 