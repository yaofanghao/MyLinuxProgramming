<!--
 * @Author: yao fanghao
 * @Date: 2023-04-19 20:40:34
 * @LastEditTime: 2023-08-10 21:44:02
 * @LastEditors: yao fanghao
-->

# MyLinuxProgramming

C/C++ 系统编程 / 操作系统 / 计算机网络 / 深度学习 学习记录仓库。

涵盖 APUE（Unix 环境高级编程）练习代码、CSAPP 实验、操作系统与网络学习笔记、PyTorch 动手学深度学习实践、测开知识体系整理等。

---

## 目录结构

### APUE/
`Unix 环境高级编程（Advanced Programming in the UNIX Environment）` 学习代码。

按章节组织：
- `1_IO/` — 标准 I/O 与系统调用 I/O（mycp、dup、fopen 等）
- `2_FS/` — 文件系统（stat、目录遍历、文件类型）
- `3_Process/` — 进程控制（fork、exec、简易 Shell ysh、守护进程 mydaemon）
- `4_Signal/` — 信号处理
- `Thread/` & `Thread_Pipeline/` — POSIX 线程（同步、线程池流水线）
- `IPC/` — 进程间通信（管道、消息队列、共享内存、信号量）
- `Socket/` & `IPv4_Media/` — Socket 网络编程（TCP/UDP、多播、IPv4/IPv6）
- `AdvancedIO/` — 高级 I/O（多路复用、异步 I/O、存储映射 I/O）
- 每目录均有对应 `.md` 笔记

### CSAPP-Labs/
`深入理解计算机系统（Computer Systems: A Programmer's Perspective）` 配套实验。

包含 Data Lab、Bomb Lab、Attack Lab、Buffer Lab、Architecture Lab（Y86-64）、Cache Lab、Performance Lab、Shell Lab、Malloc Lab、Proxy Lab 等。

### 学习笔记/
整理的计算机基础知识笔记（Markdown + 配图），涵盖：

| 文件 | 内容 |
|------|------|
| `-操作系统_小林coding.md` | 操作系统核心概念：进程线程/调度/IPC/同步互斥/内存管理/文件系统/设备管理/中断/CFS/RCU/NUMA/eBPF |
| `-计算机网络_小林coding.md` | TCP/IP 模型/HTTP 各版本/HTTPS-TLS/TCP 三次握手四次挥手/拥塞控制/CDN/DNS/Nginx/WebSocket |
| `-C-C++.md` | C/C++ 基础/面向对象/智能指针/移动语义/C++17-20 特性/STL 分析/内存布局/CMake/性能优化/面试题 |
| `-Linux.md` | Linux 基础命令/系统调用/proc/cgroups/namespaces/性能分析工具/容器基础/IO 模型/systemd |
| `-软件测试.md` | 测试理论/用例设计/安全测试(OWASP)/自动化架构/全链路压测/混沌工程/接口测试/代码覆盖率 |
| `-其他.md` | 设计模式(GoF23种)/SOLID/敏捷框架/DDD/架构模式/重构/API设计/分布式系统理论(CAP/BASE)/项目管理 |
| `docker_k8s.md` | Docker 镜像与 Dockerfile/K8s Pod-Deployment-Service/Helm/CNI/存储/监控/StatefulSet/Service Mesh |

### 测开-学习笔记/
测试开发方向学习笔记与脚本实践。

| 文件/目录 | 内容 |
|-----------|------|
| `持续交付.md` | 持续交付2.0/DevOps/双环模型/CI-CD 流水线/微服务/GitOps/DORA 指标/混沌工程 |
| `Linux基础复习-韩顺平网课.md` | Linux 常用命令/Vim/包管理/systemd/cron/LVM/SELinux/防火墙/SSH 加固 |
| `shell脚本编程.md` | Bash 编程完整教程：语法/数组/sed-awk/调试/实用脚本模式/跨平台兼容/性能优化 |
| `SQL基础语法.md` | SQL CRUD/联结/窗口函数/索引原理/Explain 优化/主从复制/反模式/备份恢复 |
| `shell_demo/` | Shell 脚本示例：包管理器检测、网络连通性检查、信号捕获等实用脚本 |

### PyTorch-动手学深度学习/
`动手学深度学习（李沐）》` PyTorch 版学习笔记与代码。

包含 120+ Jupyter Notebook，覆盖深度学习基础 / CNN / RNN / Attention / NLP / 计算机视觉 / 生成模型等。

### 深度学习进阶-自然语言处理/
`深度学习进阶：自然语言处理》` 的 Python 实现代码。

包含 Word2Vec / RNN / LSTM / GRU / Seq2Seq / Attention / Transformer 等模型的手写实现。

### 参考书/
参考书集合，包含 CSAPP / APUE / UNP / TCP/IP 详解 / 数据结构 / 设计模式 / 软件测试 / DevOps 等 36 本 PDF。

### 其他工具文件

| 文件 | 说明 |
|------|------|
| `set_for_docker` | Docker 开发环境配置脚本 |
| `set_for_vim` | Vim 配置脚本 |
| `create_git_for_ubuntu` | Git 环境配置脚本 |
| `useful_git_command` | 常用 Git 命令备忘 |

---

## 开发环境

| 工具 | 说明 |
|------|------|
| 系统 | Ubuntu 22.04 LTS / Windows (WSL) |
| 编译器 | gcc / g++ / gdb |
| 编辑器 | vim / VS Code |
| 构建 | Make / CMake |
| 文档 | Markdown / draw.io |

## 参考资料

* **CSAPP** — 深入理解计算机系统
* **APUE** — UNIX 环境高级编程（Stevens）
* **UNP** — UNIX 网络编程（Stevens）
* **TLPI** — Linux/Unix 系统编程手册 ([man7.org](https://man7.org/tlpi/))
* **K&R C** — C 程序设计语言
* **计算机网络-自顶向下方法**
* **操作系统导论 (OSTEP)**
* **小林coding** — [图解系统/网络](https://xiaolincoding.com/)
* **[李慧芹老师 Linux C 语言教程](https://www.bilibili.com/video/BV18p4y167Md)**
* **[南京大学 操作系统：设计与实现 (蒋炎岩)](https://www.bilibili.com/video/BV1N741177F5)**
