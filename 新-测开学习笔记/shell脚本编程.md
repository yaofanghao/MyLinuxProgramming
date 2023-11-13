<!--
 * @Author: yao fanghao
 * @Date: 2023-10-27 10:51:33
 * @LastEditTime: 2023-11-02 09:36:39
 * @LastEditors: yao fanghao
-->

# 测试开发自学记录

* 2023.10.27起

# 参考资料

* CSAPP
* Linux命令行与shell编程脚本大全
* 鸟哥的Linux私房菜
* bash shell 脚本编程经典案例
* https://www.bilibili.com/video/BV1WY4y1H7d3

# 学习进度

## 已学习

* 鸟哥 第10章
* Linux命令行与shell编程脚本大全 第5，6，11，12，13章

## 学习中

* 鸟哥 第11章
* Linux命令行与shell编程脚本大全 第14章
* 尚硅谷网课 p67

## 认识bash

* 通过shell实现指令与kernel的沟通，控制硬件

* type 测试是否为内建指令

* env 列出所有shell环境变量
* echo $[变量] 查看某变量值
* set 列出所有环境变量和自定义变量
* unset 删除环境变量
* export 自定义变量转换成环境变量

* echo $? 查看最后一个执行命令的状态码

* alias 起别名

* 数据流重定向 stdin:0 stdout:1 stderr:2 >覆盖 >>追加
* 黑洞装置  2> /dev/null
  
* | 管道命令
* cut grep
* sort wc uniq
* 双向重定向 tee

## 结构化命令

* if语句

```shell
if command 
    then commands 
else
    commands
fi
```

```shell
if command1
then
   commands
elif command2
then
    more commands
fi
```

* test语句
  * 测试condition语句，如果返回非0状态码，则if-then语句不被执行

```shell
test condition
```

```shell
if test condition
    then commands 
fi
```

```shell
if [ condition ]
    then commands 
fi
```

* case语句

```shell
case variable in
pattern1 | pattern2) 
    commands1;;
pattern3) 
    commands2;;
*) default 
    commands;;
esac
```

* for语句
  * 用空格划分list列表内的每个值
  * 可以临时更改环境变量IFS，更改字段分隔符

```shell
IFS.OLD=$IFS
IFS=$'\n'
for var in list
do
    commands
done
IFS=$IFS.OLD
```

* C语言风格的for语句

```shell
for (( i=1; i <= 10; i++ ))
do
    echo "The next number is $i"
done
```

* while语句

```shell
while test command
do
    other commands
done
```

* until语句

```shell
until test commands
do
   other commands
done
```

* break命令
  
* continue命令

* 文件名通配符匹配

```shell
for file in /home/rich/test/*
do
    if [ -d "$file" ]
    then
      echo "$file is a directory"
    elif [ -f "$file" ]
    then
      echo "$file is a file"
    fi
done
```

* 数值比较
  * -eq -ge -gt -le -lt -ne
* 字符串比较
  * = != < >
  * -n -z

* 文件比较
    语句     | 作用
    -------- | -----
    -d file  | 检测是否存在且为目录
    -e file  | 检测是否存在
    -f file  | 检测是否存在且为文件
    -r file  | 检测是否存在且可读
    -s file  | 检测是否存在且非空
    -w file  | 检测是否存在且可写
    -x file  | 检测是否存在且可执行
    -O file  | 检测是否存在且属当前用户
    file1 -nt file2  | 检测file1是否比file2新
    file1 -ot file2  | 检测file1是否比file2旧

* 复合条件 && ||
* 双括号实现计算数学表达式 (( expression ))
* 双方括号实现字符串模式匹配 [[ expression]]

## 处理用户输入

* 位置参数
  * $0脚本名 $1第一个命令行参数 ...

* $* 将所有命令行参数视为一个单词
* $@ 将各个命令行参数视为独立单词

* getopt
  * 定义了有效的命令行选项字母
  * -q 忽略错误信息

```shell
getopt optstring parameters
```

* getopts

* read 获取用户输入
  * -t 超时等待的计时器

## 正则表达式
