<!--
 * @Author: yao fanghao
 * @Date: 2023-06-06 16:31:04
 * @LastEditTime: 2023-06-14 18:05:44
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
  | 物理层  | 比特 bit |   | HUB集线器 |

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

## -报文格式

![8](_img/ComputerNetworking/TCP_message.png)

* **序列号**
  * 解决网络包乱序问题
* **确认应答号**
  * 解决丢包问题
  * **若确认号为N，表明到序号N-1为止所有数据已正确收到**
* 控制位
  * **ACK** 为1时确认号有效
  * RST 为1时需重连
  * **SYN** 为1时表明连接请求或连接接受
    * SYN=1 ACK=0 连接请求
    * SYN=1 ACK=1 对方已同意建立连接
  * FIN 为1时表明发送完毕
  
* 建立一个 TCP 连接是需要客户端与服务端达成三个信息的共识
  * Socket：由 IP 地址和端口号组成
  * 序列号：用来解决乱序问题等
  * 窗口大小：用来做流量控制

## -TCP和UDP的区别

| |  TCP   | UDP  |
| --- | ----  | ----  |
| 连接 | 面向连接，需要先建立连接 | 不需要连接，即刻传输 |
| 服务对象 | 一对一 | 一对一、一对一、一对多 |
| 可靠性 | 可靠交付，无差错，不丢失，不重复，按序到达 | 尽最大努力交付，不保证可靠交付 （新技术：**QUIC**实现了可靠传输）|
| 拥塞控制、流量控制 | 有 | 无 |
| 传输方式 | **流式传输**，没有边界，保证顺序和可靠 | 按包发送，有边界，但可能会丢包和乱序 |
| 分片不同 | MSS | MTU |
| 应用 | SMTP、TELNET、HTTP、FTP | DNS、SNMP |

## -连接建立-三次握手

![10](_img/ComputerNetworking/TCP_connect.png "TCP_connect")

* 第三次握手可以携带数据，前两次握手不可以携带数据
* netstat -napt 命令查看TCP连接状态
* 三次握手才可以阻止重复历史连接的初始化（主要原因）:
  ![7](_img/TCP/3-4.png " ")

* 三次握手才可以同步双方的初始序列号
* 三次握手才可以避免资源浪费

* 每次建立TCP连接时，初始化序列号不一样

* MTU和MSS：
  * 为了达到最佳的传输效能，建立TCP连接的时候通常要协商双方的 MSS 值
  * 当 TCP 层发现数据超过 MSS 时，则就先会进行分片
  ![7](_img/TCP/MTU.png " ")

* 第一次握手丢失了，会发生什么？
  * 客户端触发超时重传，重传SYN报文
  * 重传次数由内核参数tcp_syn_retries控制
* 第二次握手丢失了，会发生什么？
  * **客户端和服务端都会重传**
  * 客户端触发超时重传，重传SYN报文
  * 服务端触发超时重传，重发SYN-ACK报文
* 第三次握手丢失了，会发生什么？
  * 服务端触发超时重传，重发SYN-ACK报文

* SYN攻击
  * 攻击者伪造SYN报文，服务端每收到便发出SYN-ACK报文
  * 久而久之占满服务端的半连接队列
  * 避免SYN攻击：调大 netdevmaxbacklog；增大 TCP 半连接队列；开启 tcp_syncookies；减少 SYN+ACK 重传次数

## -连接释放-四次挥手

![11](_img/ComputerNetworking/TCP_disconnect.png "TCP_disconnect")

* 每个方向都需要一个 FIN 和一个 ACK

* TEAM_WAIT 状态
  * 足以让两个方向上的数据包都被丢弃，使得原来连接的数据包在网络中都自然消失，再出现的数据包一定都是新建立连接所产生的

* 保活计时器

## -有限状态机FSM

  ![12](_img/ComputerNetworking/TCP_FSM.png "TCP_FSM")

## -重传

* **RTT** 往返时延
  * 数据发送时刻到接收到确认的时刻的差值
  * 指数加权移动平均估计RTT
* RTO 超时重传时间
  * RTO较长：网络空隙时间增大，降低传输效率
  * RTO较短：网络负荷增大，有不必要的重传
* RTO 应略大于 RTT
  
* 超时重传
  * 每遇到一次超时重传，都会将下一次超时时间间隔设为先前值的两倍
  * tcp_synack_retries
  
* 快速重传

* SACK
  * 只重传丢失的数据
  * 在 TCP 头部字段加一个 SACK ，可以将已收到数据的信息发送给发送方
  
* D-SACK
  * 使用了 SACK 告诉发送方有哪些数据被重复接收了

## -滑动窗口

* 窗口大小就是指无需等待确认应答，而可以继续发送数据的最大值

* 发送方的滑动窗口swnd：
  ![12](_img/TCP/window.png " ")
  ![12](_img/TCP/window2.png " ")

* 指针实现：
  * SND.WND
  * SND.UNA
  * SND.NXT

* 接收方的滑动窗口rwnd：
  ![12](_img/TCP/window3.png " ")

## -流量控制

![12](_img/TCP/control.png " ")

* 窗口探测报文
  * 防止窗口关闭时潜在的死锁现象
* 糊涂窗口综合症
* Nagle算法

## -拥塞控制

* 避免发送方数据填满整个网络
* **拥塞窗口 cwnd**
  * swnd = min(cwnd, rwnd)
  * ![12](_img/TCP/cwnd.png " ")
* 拥塞控制的四个算法
  * 慢启动
    * 当发送方每收到一个 ACK，拥塞窗口 cwnd 的大小就会加 1
    * 指数型增长
  * 拥塞避免
    * 慢启动门限 ssthresh 
    * cwnd < ssthresh 时，使用慢启动算法
    * cwnd >= ssthresh 时，使用拥塞避免算法
    * 每当收到一个 ACK 时，cwnd 增加 1/cwnd
  * 拥塞发生
    * 当发生超时重传时，就会使用拥塞避免算法
    * ssthresh 设置为 cwnd/2
  * 快速恢复

## -半连接队列和全连接队列

* **半连接队列（SYN Queue）**：服务端收到 SYN 后，连接处于 SYN_RCVD 状态，放入半连接队列
* **全连接队列（Accept Queue）**：三次握手完成后，连接转入 ESTABLISHED 状态，移入全连接队列
* `ss -lnt` 查看：`Recv-Q` 表示全连接队列大小，`Send-Q` 表示最大长度
* 全连接队列满时，内核行为由 `tcp_abort_on_overflow` 控制

# 扩展补充

## HTTP 深入

### HTTP 请求方法对比

| 方法 | 幂等 | 安全 | 说明 |
|------|:----:|:----:|------|
| GET | 是 | 是 | 获取资源，不应改变状态 |
| HEAD | 是 | 是 | 类似 GET 但不返回 body |
| POST | 否 | 否 | 创建/提交资源 |
| PUT | 是 | 否 | 替换/更新资源（完整替换） |
| PATCH | 否 | 否 | 部分更新资源 |
| DELETE | 是 | 否 | 删除资源 |
| OPTIONS | 是 | 是 | 查询服务器支持的 HTTP 方法 |

### HTTP 状态码

| 范围 | 分类 | 常见状态码 |
|------|------|-----------|
| 1xx | 信息 | 101 Switching Protocols（WebSocket 升级） |
| 2xx | 成功 | 200 OK、201 Created、204 No Content |
| 3xx | 重定向 | 301 Moved Permanently、302 Found、304 Not Modified |
| 4xx | 客户端错误 | 400 Bad Request、401 Unauthorized、403 Forbidden、404 Not Found、429 Too Many Requests |
| 5xx | 服务端错误 | 500 Internal Server Error、502 Bad Gateway、503 Service Unavailable、504 Gateway Timeout |

### HTTP 缓存策略

```
强制缓存（不请求服务器）:
  Cache-Control: max-age=3600
  Expires: Wed, 21 Oct 2025 07:28:00 GMT

协商缓存（请求服务器验证）:
  Last-Modified / If-Modified-Since（时间戳）
  ETag / If-None-Match（内容哈希）
```

* 优先级：`Cache-Control` > `Expires` > `ETag` > `Last-Modified`
* `Cache-Control: no-cache` 每次请求服务器验证；`no-store` 完全禁止缓存

### HTTPS 握手（TLS 1.3）

1. ClientHello：客户端发送支持的 TLS 版本、加密套件、Key Share（公钥）
2. ServerHello：服务端选择加密套件，发送证书 + 签名 + Key Share
3. 双方各自计算共享密钥（ECDHE）
4. 客户端发送 Finished（加密握手消息的 MAC）
5. 服务端发送 Finished
6. **TLS 1.3 只需 1-RTT**（vs TLS 1.2 需要 2-RTT）
7. **0-RTT**（early data）：复用之前会话可立即发送数据

### HTTP/2 多路复用

* 单一 TCP 连接上并行多个流（stream）
* **二进制分帧**：HTTP 头部和数据被拆分为帧（HEADERS、DATA、SETTINGS 等）
* **头部压缩（HPACK）**：静态表（61 个常用头部）、动态表（自定义）、Huffman 编码
* **服务器推送（Server Push）**：服务端可主动推送资源（如 HTML 中引用的 CSS/JS）
* **优先级**：流有依赖关系树，可设置权重

### HTTP/3 与 QUIC

* 基于 UDP，解决 TCP 队头阻塞问题
* **QUIC 特性**：
  * 0-RTT 连接建立
  * 连接迁移（IP/端口变化不中断连接，如 Wi-Fi 切 4G）
  * 多路复用无队头阻塞（一个流丢包不影响其他流）
  * 内置加密（TLS 1.3 集成，无明文版本）

## TCP 深入

### TCP 拥塞控制算法对比

| 算法 | 特点 | 适用场景 |
|------|------|---------|
| Reno | 经典算法：慢启动 + 拥塞避免 + 快重传 + 快恢复 | 传统网络 |
| Cubic | 窗口增长用三次函数，高带宽下更激进 | Linux 默认（高带宽长肥网络） |
| BBR | 基于带宽和 RTT 建模，不依赖丢包 | 高丢包、高延迟链路 |
| BIC | Binary Increase Control，Cubic 的前身 | 已淘汰 |

### TCP 保活机制

```shell
# 查看/修改保活参数
cat /proc/sys/net/ipv4/tcp_keepalive_time      # 7200 秒（2小时无数据开始探测）
cat /proc/sys/net/ipv4/tcp_keepalive_intvl     # 75 秒（探测间隔）
cat /proc/sys/net/ipv4/tcp_keepalive_probes    # 9 次（最多探测次数）
```

* 应用层心跳比 TCP 保活更灵活，推荐使用

### TIME_WAIT 详解

* **作用**：
  1. 确保最后一个 ACK 能到达服务端（服务端没收到会重发 FIN）
  2. 使过期连接数据包在网络中自然消失
* **持续时间**：2 MSL（Maximum Segment Lifetime，通常 60 秒）
* **过多 TIME_WAIT 的影响**：
  * 占用端口（客户端）
  * 占用内存（每个 socket 约 1-2KB）
* **优化**：
  * `tcp_tw_reuse`：客户端复用 TIME_WAIT socket（需开启时间戳）
  * `tcp_tw_recycle`：已被废弃（NAT 环境下有 Bug）
  * `tcp_max_tw_buckets`：限制 TIME_WAIT 数量

## 网络编程常见问题

| 问题 | 原因 | 解决 |
|------|------|------|
| 端口占用 Address already in use | TIME_WAIT 状态 | `SO_REUSEADDR` 选项 |
| 连接被拒绝 Connection refused | 端口未监听 / 防火墙 | 检查服务状态和 iptables |
| 连接超时 | 防火墙拦截 / 路由不可达 | 检查网络连通性 |
| 粘包 | TCP 是流式协议，无消息边界 | 应用层定义消息格式（长度前缀 / 分隔符） |
| 大量 CLOSE_WAIT | 服务端未主动 close | 检查代码是否正确关闭 socket |

## CDN（内容分发网）

* **原理**：在全球部署边缘节点，缓存静态资源，用户请求路由到最近的节点
* **关键技术**：
  * DNS 智能解析：返回离用户最近的节点 IP
  * 全局负载均衡（GSLB）
  * 缓存策略：主动推送（预热）vs 被动回源（首次访问）
* **常见问题**：
  * 缓存命中率低（设置合理的 Cache-Control）
  * 动态内容无法缓存（动态加速用 DCDN）
  * 刷新预热（API 强制更新缓存）

 