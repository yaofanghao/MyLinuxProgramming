<!--
 * @Author: yao fanghao
 * @Date: 2023-06-06 16:31:04
 * @LastEditTime: 2023-06-06 22:09:20
 * @LastEditors: yao fanghao
-->
# 参考资料

* **计算机网络-自顶向下方法**
* **计算机网络-谢希仁** √
* **UNP**
* 王道-计算机网络 √
* 网络是怎样连接的 √
* 小林coding-图解网络
* https://xiaolincoding.com
* 图解TCP/IP √
* 嵌入式软件开发笔试面试指南
* [【计算机网络微课堂】](https://www.bilibili.com/video/BV1c4411d7jb/)
* [【中科大郑烇《计算机网络（自顶向下方法 第7版》】](https://www.bilibili.com/video/BV1JV411t7ow/)
* [【史上最强最细腻的linux嵌入式C语言学习教程【李慧芹老师】】](https://www.bilibili.com/video/BV18p4y167Md/)
* [【黑马程序员-Linux网络编程】](https://www.bilibili.com/video/BV1iJ411S7UA/)

# 2.1 TCP/IP 网络模型有哪几层？

* OSI七层协议： 物理层--数据链路层--网络层--传输层--会话层--表示层--应用程序层
* 五层协议：**物理层--数据链路层--网络层--传输层--应用层**
* **下面的协议对上面的实体是透明的**
  |  层   | 分组  | 协议  | 有关概念 |
  |  ----  | ----  | ---- | --- |
  | 应用层  | 报文 message | HTTP、SMTP、FTP等  | DNS、WWW、DHCP |
  | 传输层  | 报文段 segment | **TCP、UDP**  | TCP三次握手四次挥手、流量控制、超时重传、拥塞控制、最大报文段长度MSS、滑动窗口、端口 |
  | 网络层  | IP数据报 datagram | **IP、ICMP、ARP**等  | 网络号、主机号、子网掩码、路由、MAC头部、路由器 |
  | 链路层  | 帧 frame | PPP等  | 最大传输单元MTU、差错检测、后退N帧协议、CSMA/CD、网桥 |
  | 物理层  | 比特 byte |   | HUB集线器 |

  ![1](_img/ComputerNetworking/4layers.png " ")

# 2.2 键入网址到网页显示，期间发生了什么？

|  步骤   | 有关概念  |
|  ----  | ----  |
|  1、浏览器解析URL  | URI 统一资源标识符。相当于身份证号； URL 统一资源定位符。包括hhtp: ftp: 等。相当于身份证住址姓名等  |
| 2、生成HTTP请求消息 | **GET** **POST** 等方法 |
| 3、DNS域名解析 | DNS相当于电话本； DNS的存放是树状结构：顶级域名、二级域名、子域名 |
| 4、委托协议栈发送消息 | **ICMP**协议告知网络包传送过程中产生的错误以及各种控制信息； **ARP**协议根据 IP 地址查询相应的以太网 MAC 地址。 |
| 4.1 可靠传输TCP | TCP报文生成 |
| 4.2 委托IP封装成网络包 |  |
| 4.3 加上MAC头部 | ARP协议， arp -a |
| 5、通过网卡发送数据 | 数字信息转为电信号 |
| 6、交换机 | 二层网络设备 |
| 7、路由器 | 路由表查询转发； **子网掩码 & IP地址**，与目标地址匹配 |
| 8、服务器端解析包 | |

* 网络包的报文段组成：
  ![1](_img/ComputerNetworking/IP_TCP_HTTP.png "TCP报文格式")

# HTTP

## -基本概念

* 超文本传输协议
  ![1](_img/ComputerNetworking/HTTPcode.png " ")

* HTTP 常见字段
  * Host： 客户端发送请求时，用来指定服务器的域名
    * ```Host: www.xxx.com```
  * Content-Length： 服务器返回数据时表明回应的数据长度
  * Connection： 客户端要求服务端长连接
    * 只要任意一端没有提出断开连接，则保持TCP连接状态
    * ```Connection: Keep-Alive```
  * Content-Type： 服务器回应时告诉客户端，数据是什么格式
  * Accpet: 表明客户端接受的数据格式
    * ```Accept: */*```

* **GET**
  * 从服务器获取指定的资源
* **POST**
  * 根据请求符合对指定资源处理

* HTTP缓存技术
  * 强制缓存和协商缓存技术

## -技术

* **cookie**
  * 允许站点对用户标识跟踪

* HTTP/1.0
  * 短连接
* HTTP/1.1
  * 长连接
  * 管道网络传输
* HTTP/2
  * 相比HTTP/1.1的改进：头部压缩、二进制格式、并发传输、服务器主动推送资源
* HTTP/3
  * 把下层TCP改成了UDP，且实现了新的协议QUIC
* HTTPS
  * **HTTPS 在 HTTP 与 TCP 层之间加入了 SSL/TLS 协议**
  * 信息加密、校验机制、身份证书
  * HTTPS协议本身到目前为止还是没有任何漏洞的
* HTTP的优化对比：
  ![1](_img/ComputerNetworking/HTTP.png " ")

## -这里小林coding关于HTTP一章写得比较详细，没有仔细读，后续再看

# TCP