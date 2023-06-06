<!--
 * @Author: yao fanghao
 * @Date: 2023-04-14 22:13:52
 * @LastEditTime: 2023-04-23 11:08:03
 * @LastEditors: yao fanghao
-->
  
# TCP基本认识

* ![1](_img/TCP/1.png "TCP报文格式")
* 序列号：解决网络包乱序问题
* 确认应答号：解决丢包问题
* 控制位：
  * ACK
  * RST
  * SYN
  * FIN
* ![2](_img/TCP/2.png "UDP报文格式")

# TCP三次握手

* ![3](_img/TCP/3.png "")
* ![4](_img/TCP/3-1.png "")
* ![5](_img/TCP/3-2.png "")
* ![6](_img/TCP/3-3.png "")
* 第三次握手可以携带数据，前两次握手不可以携带数据
* netstat -napt 命令查看TCP连接状态
* 三次握手才可以阻止重复历史连接的初始化（主要原因）
* ![7](_img/TCP/3-4.png "")
* 三次握手才可以同步双方的初始序列号
* 三次握手才可以避免资源浪费

# Socket编程

* ![8](_img/TCP/4.png "")
