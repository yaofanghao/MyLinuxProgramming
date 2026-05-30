<!--
 * @Author: yao fanghao
 * @Date: 2023-04-14 22:13:52
 * @LastEditTime: 2023-04-23 11:42:29
 * @LastEditors: yao fanghao
-->
# 已不更新-- 转移至 MyLinuxProgramming 仓库

## 参考资料

* **CSAPP**
* Linux是怎样工作的-武内觉 √
* 操作系统导论 √
* 嵌入式软件开发笔试面试指南
* linux/unix系统编程手册
* **APUE**
* <http://www.cyc2018.xyz/>
* 【史上最强最细腻的linux嵌入式C语言学习教程【李慧芹老师】】 <https://www.bilibili.com/video/BV18p4y167Md/>
* 【黑马程序员-Linux网络编程】 <https://www.bilibili.com/video/BV1iJ411S7UA/>
* 【[过期] 2020 南京大学 “操作系统：设计与实现” (蒋炎岩)】 <https://www.bilibili.com/video/BV1N741177F5/>
* 【彻底搞懂 进程&线程、进程池&线程池】 <https://www.bilibili.com/video/BV1V84y1Y77s/>
* 【[原创] 每个程序员都应该知道的内存知识 (带你走读Ulrich Drepper的经典论文)】 <https://www.bilibili.com/video/BV1Xy4y1b7SK/>

## Linux 基本概念

* root用户：#
* 一般用户：$

* vi / vim
  * / 自上而下查找
  * ？ 自下而上查找
  * dgg 删除当前行以上所有内容

* rm
  * -i 逐一询问删除
  * -f 不询问强制删除
  * -r 将目录中全部删除

* z 压缩
* x 解压缩

* **obdjump**
  * 反汇编

## 文件

* 用户权限
  * 111 **rwx** 可读可写可执行

* ldd
  * 查看程序依赖的库

* libc
  * Linux中常用的C标准库
  * ldd /bin/echo 查看C标准库信息

* **readelf**
  * <https://www.man7.org/linux/man-pages/man1/readelf.1.html>
  * 查看ELF格式可执行文件的信息
  * -h 查看起始地址
  * -S 查看代码段与数据段在文件中的偏移量、大小和起始地址

## 进程

* CPU**内核模式**和用户模式
  * 只有处于内核模式才允许访问设备
  * 进程： 用户模式---[发起系统调用]内核模式--[从系统调用恢复运行]用户模式

* **系统调用** system call
* 进程依赖于内核的处理时，必须通过系统调用向内核发起请求
* 系统调用的种类如下：
  * 进程控制（创建和删除）
  * 内存管理（分配和释放）
  * 进程间通信
  * 网络管理
  * 文件系统操作
  * 文件操作（访问设备）

* **strace** 监控进程和内核交互的情况
  * <https://strace.io/>
  * strace -o hello.log ./hello
  * -T  查看系统调用消耗时间（微秒级）

* **sar** 获取进程在用户模式与内核模式下运行时间的比例
  * <http://c.biancheng.net/view/6212.html>

* **fork()**
  * 创建子进程
  * fork()函数给父进程和子进程返回不同的值
* **execve()**
  * 启动另一个程序
  * 并非新增一个进程，而是替换了当前进程
  * fork and execve
  * 常用的新建进程的方式
* shell命令执行机制就是 fork+exec 执行命令  

* 逻辑CPU
* 调度器
  * 多个进程轮流使用逻辑CPU
  * 时间片
* 上下文切换
  * 切换进程

***ps ax**

* 列举当前正在运行的所有进程
* STAT 表示进程状态
* 进程状态
  * 初始态 就绪态 运行态 挂起态 终止态

* 吞吐量与延迟
  * 所有逻辑CPU都不处于空闲状态后，不管继续增加多少进程，吞吐量都不再变化
  * 进程数量增加，延迟边长
* 负载均衡
  * 调度器为各个进程分配均等的CPU时间

* **nice()**
  * 设定进程优先级
  * -19最高，20最低
  * nice -n 程序运行时指定优先级

## 内存管理

***free**

* 查看内存总量和已消耗内存量
* OOM
  * out of memory 表示内存不足
  * OOM killer 强制终止进程以释放内存

* **虚拟内存**
  * 解决了内存碎片化问题
  * 虚拟地址（VA）---> 内存管理单元（MMU） ---> [映射到]物理地址（PA）
* 页表
* 多级页表
  
* mmap()
  * CSAPP-p585
  * <https://blog.csdn.net/dlutbrucezhang/article/details/9080173>
  * 内存映射函数

* **malloc()**
  * 底层调用了mmap()

* Swap
  * 换出与换入 --又称为分页
  * 系统长期内存不足，会导致不断交换，陷入系统抖动状态

## 存储

* 层次结构（容量从大到小，访问速度从慢到快）
  * CSAPP-p421
  * 外部存储器--内存--高速缓存SRAM--寄存器

* **高速缓存**
  * 为了抹平内存与寄存器的性能差距
  * 添加标记，检查脏位

* 多级缓存
  * L1、L2、L3

* 访问局部性
  * 时间局部性
  * 空间局部性

* 页表缓冲
  * 也称为转译后备缓冲区 TLB
* 页面缓存
  * 为了抹平外部存储器与内存的性能差距
  * 脏页的标记
  
* 超线程

## 系统调用深入

### 系统调用流程（x86-64）

1. 应用程序调用库函数（如 `write()`）
2. 库函数将参数放入寄存器（rdi, rsi, rdx, r10, r8, r9）
3. 将系统调用号放入 rax 寄存器
4. 执行 `syscall` 指令（比 `int 0x80` 更快）
5. CPU 切换到内核模式，内核执行 `sys_call_table[rax]`
6. 返回结果在 rax 中，出错时置负值（errno）

### 常见系统调用号（x86-64）

| 调用号 | 函数 | 说明 |
|-------|------|------|
| 0 | read | 读取文件 |
| 1 | write | 写入文件 |
| 2 | open | 打开文件 |
| 9 | mmap | 内存映射 |
| 56 | clone | 创建进程/线程 |
| 57 | fork | 创建子进程 |
| 59 | execve | 执行程序 |
| 60 | exit | 退出进程 |

### 系统调用 vs 库函数

```c
// 库函数（带缓冲，用户态缓存）
fwrite(buf, 1, n, fp);
// → 用户空间 stdio 缓冲区
// → 缓冲区满时才触发 write() 系统调用

// 系统调用（直接进入内核，无缓冲）
write(fd, buf, n);
// → 立即进入内核，性能开销大
```

## /proc 文件系统

* 内核暴露信息的虚拟文件系统，不占用磁盘

| 文件 | 说明 |
|------|------|
| /proc/cpuinfo | CPU 信息（型号、核心数、缓存） |
| /proc/meminfo | 内存信息（总量、可用、缓存） |
| /proc/self | 当前进程的 proc 目录 |
| /proc/[pid]/fd | 进程打开的文件描述符 |
| /proc/[pid]/maps | 进程内存映射 |
| /proc/[pid]/status | 进程状态、内存、权限 |
| /proc/[pid]/cmdline | 进程启动命令行 |
| /proc/[pid]/environ | 进程环境变量 |
| /proc/loadavg | 系统负载（1/5/15分钟） |
| /proc/uptime | 系统运行时间 |

## 进程优先级与调度策略

### Linux 调度策略

| 策略 | 说明 | 应用场景 |
|------|------|---------|
| SCHED_OTHER (CFS) | 默认，完全公平调度 | 普通进程 |
| SCHED_FIFO | 实时 FIFO，先到先服务 | 实时任务（高优先级） |
| SCHED_RR | 实时轮转，时间片 | 实时任务（同优先级轮转） |
| SCHED_BATCH | 批量调度 | CPU 密集型批处理 |
| SCHED_IDLE | 低优先级 | 后台空闲任务 |

### CFS（完全公平调度器）

* 每个进程维护虚拟运行时间 `vruntime`
* 每次选择 `vruntime` 最小的进程运行
* 权重（nice 值）决定时间片分配比例
* 红黑树管理就绪队列，O(log n) 选取

### cgroups（控制组）

* 限制、隔离、统计进程组的资源使用
* **子系统**：
  * cpu：CPU 时间分配
  * memory：内存上限
  * blkio：块设备 I/O
  * cpuset：绑定 CPU 核心
  * pids：进程数上限
* **典型路径**：`/sys/fs/cgroup/cpu/docker/[container-id]/`
* **应用**：Docker 容器资源限制、systemd 服务资源控制

### namespaces（命名空间）

* Linux 容器（Docker）的核心隔离机制

| 命名空间 | 隔离内容 | 作用 |
|---------|---------|------|
| PID | 进程编号 | 容器内 PID 从 1 开始 |
| Network | 网络设备、IP、端口 | 容器独立网络栈 |
| Mount | 挂载点 | 容器独立文件系统 |
| UTS | 主机名和域名 | 容器独立主机名 |
| User | 用户和 UID | 容器内 UID 映射 |
| IPC | 进程间通信资源 | 容器独立 IPC |

## 性能分析工具

| 工具 | 用途 | 常用参数 |
|------|------|---------|
| top/htop | 实时进程监控 | top -o %CPU / -o %MEM |
| perf | CPU 性能采样 | perf top / perf record / perf report |
| strace | 系统调用跟踪 | strace -p PID -T -c |
| ltrace | 库函数调用跟踪 | ltrace -p PID |
| valgrind | 内存泄漏检测 | valgrind --leak-check=full ./a.out |
| gdb | 调试器 | gdb -p PID / break / run / bt |
| tcpdump | 网络抓包 | tcpdump -i eth0 -nn port 80 |
| iostat | 磁盘 I/O 统计 | iostat -x 1 |
| vmstat | 虚拟内存统计 | vmstat 1 |
| sar | 系统活动报告 | sar -u -r -d 1 |

## 容器技术基础（Docker）

* 容器 = cgroups（资源限制）+ namespaces（隔离）+ UnionFS（镜像分层）
* 镜像只读层通过 UnionFS（OverlayFS / AUFS）叠加
* 容器共享宿主机内核，比虚拟机更轻量
* 常见容器运行时：runc（默认）、containerd、CRI-O

### 容器 vs 虚拟机

| 维度 | 容器 | 虚拟机 |
|------|------|--------|
| 启动速度 | 毫秒级 | 秒到分钟级 |
| 内核 | 共享宿主机内核 | 独立内核（Hypervisor） |
| 资源开销 | 几乎零开销 | 每个 VM 有独立 OS |
| 隔离性 | 进程级隔离（较弱） | 硬件级隔离（强） |
| 镜像大小 | MB 级（alpine 约 5MB） | GB 级 |
