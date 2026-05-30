<!--
 * @Author: yao fanghao
 * @Date: 2023-10-27 10:51:33
 * @LastEditTime: 2023-11-13 14:26:40
 * @LastEditors: yao fanghao
-->

# Linux 基础复习（韩顺平网课）

## 参考资料

* 韩顺平 Linux 教程
* 鸟哥的 Linux 私房菜
* Linux 命令行与 shell 脚本编程大全

## 目录结构

* **/** 根目录
* **/bin** 常用命令（普通用户可用）
* **/sbin** 系统管理命令（root 可用）
* **/home** 普通用户家目录
* **/root** root 用户家目录
* **/etc** 配置文件
* **/usr** 系统资源
* **/var** 可变数据（日志、缓存）
* **/tmp** 临时文件
* **/dev** 设备文件
* **/proc** 进程信息（虚拟文件系统）
* **/opt** 第三方软件

## 常用命令

### 文件操作

| 命令 | 说明 |
|------|------|
| ls -lha | 列出文件详情（包含隐藏文件，人性化大小） |
| cd ~ | 进入家目录 |
| pwd | 当前路径 |
| mkdir -p a/b/c | 递归创建目录 |
| rmdir | 删除空目录 |
| rm -rf | 强制递归删除 |
| cp -r | 递归复制目录 |
| mv | 移动或重命名 |
| touch | 创建空文件或更新时间戳 |
| cat / more / less | 查看文件内容 |
| head -n 5 / tail -n 5 | 查看文件头/尾 |
| tail -f | 实时跟踪文件追加 |

### 权限管理

```
drwxr-xr-x
│└┬┘└┬┘└┬┘
│  │  │  └─ 其他用户权限
│  │  └──── 同组用户权限
│  └─────── 所有者权限
└────────── 文件类型（-文件 d目录 l链接）
```

* **chmod** 修改权限
  * `chmod u+x file` 所有者加执行权限
  * `chmod 755 file` 数字法（rwx r-x r-x）
  * `chmod -R 755 dir` 递归修改目录

* **chown** 修改所有者
  * `chown user:group file`
  * `chown -R user dir`

* **chgrp** 修改所属组

### 用户管理

| 命令 | 说明 |
|------|------|
| useradd -m username | 创建用户并创建家目录 |
| passwd username | 设置/修改密码 |
| userdel -r username | 删除用户及家目录 |
| usermod -aG groupname user | 将用户添加到附加组 |
| groups username | 查看用户所属组 |
| id username | 查看用户UID/GID信息 |
| su - username | 切换用户 |
| sudo command | 以root权限执行 |
| whoami | 当前用户名 |

### 组管理

| 命令 | 说明 |
|------|------|
| groupadd groupname | 创建组 |
| groupdel groupname | 删除组 |
| cat /etc/group | 查看所有组信息 |
| cat /etc/passwd | 查看所有用户信息 |
| cat /etc/shadow | 查看密码信息（root可读） |

### 文件搜索

| 命令 | 说明 |
|------|------|
| find /path -name "*.txt" | 按文件名搜索 |
| find /path -type f -size +100M | 搜索大文件 |
| find /path -mtime -7 | 7天内修改的文件 |
| locate keyword | 基于数据库快速搜索（需updatedb） |
| which command | 搜索命令路径 |
| whereis command | 搜索命令及文档路径 |
| grep -r "pattern" /path | 递归搜索文件内容 |

### 进程管理

| 命令 | 说明 |
|------|------|
| ps -ef | 查看所有进程（全格式） |
| ps aux | 查看所有进程（BSD格式） |
| top / htop | 动态监控进程 |
| kill PID | 终止进程 |
| kill -9 PID | 强制终止 |
| pkill process_name | 按名称终止 |
| pgrep -l pattern | 按名称查找进程PID |
| jobs | 查看后台作业 |
| bg / fg | 后台/前台切换作业 |

### 网络管理

| 命令 | 说明 |
|------|------|
| ifconfig / ip addr | 查看/配置网络接口 |
| ping -c 4 host | 测试连通性 |
| netstat -anp | 查看端口和连接 |
| ss -tlnp | 查看TCP监听端口 |
| curl http://url | HTTP请求工具 |
| wget url | 下载文件 |
| scp user@host:path local | 远程复制文件 |
| ssh user@host | SSH远程登录 |
| telnet host port | 测试端口连通性 |

### 压缩与归档

| 命令 | 说明 |
|------|------|
| tar -czf archive.tar.gz dir/ | 创建tar.gz压缩 |
| tar -xzf archive.tar.gz | 解压tar.gz |
| tar -cjf archive.tar.bz2 dir/ | 创建tar.bz2压缩 |
| tar -xjf archive.tar.bz2 | 解压tar.bz2 |
| zip -r archive.zip dir/ | 创建zip压缩 |
| unzip archive.zip | 解压zip |
| gzip file / gunzip file.gz | gzip压缩/解压 |

### 磁盘管理

| 命令 | 说明 |
|------|------|
| df -h | 查看磁盘分区使用情况 |
| du -sh dir | 查看目录总大小 |
| du -h --max-depth=1 | 查看一级子目录大小 |
| lsblk | 查看块设备 |
| fdisk -l | 查看磁盘分区表（root） |
| mount / unmount | 挂载/卸载 |
| dd if=/dev/zero of=file bs=1M count=100 | 创建指定大小文件 |

## Vim 编辑器

### 三种模式
1. **命令模式**（默认进入）：移动光标、复制粘贴、删除
2. **底行模式**：`:w`保存 `:q`退出 `:wq`保存退出 `:q!`强制退出
3. **编辑模式**：按 `i` `a` `o` 进入，按 `Esc` 退出

### 常用操作

| 操作 | 说明 |
|------|------|
| yy | 复制当前行 |
| p | 粘贴 |
| dd | 删除当前行 |
| u | 撤销 |
| Ctrl+r | 恢复撤销 |
| /pattern | 搜索 |
| :set nu | 显示行号 |
| :%s/old/new/g | 全局替换 |
| gg / G | 跳转文件首/尾 |

## Linux 软件包管理

### Debian/Ubuntu（apt）

```shell
apt update                 # 更新包索引
apt install package        # 安装包
apt remove package         # 卸载包
apt purge package          # 完全卸载（含配置文件）
apt autoremove             # 清理无用依赖
apt list --installed       # 列出已安装
dpkg -i package.deb        # 安装本地deb包
dpkg -r package            # 卸载deb包
```

### Red Hat/CentOS（yum/dnf）

```shell
yum install package        # 安装
yum remove package         # 卸载
yum update package         # 更新
yum list installed         # 列出已安装
rpm -ivh package.rpm       # 安装本地rpm包
rpm -e package             # 卸载rpm包
```

## 系统服务管理（systemd）

```shell
systemctl start service    # 启动服务
systemctl stop service     # 停止服务
systemctl restart service  # 重启服务
systemctl status service   # 查看状态
systemctl enable service   # 开机自启
systemctl disable service  # 关闭开机自启
systemctl list-units --type=service  # 列出所有服务
journalctl -u service      # 查看服务日志
```

## 定时任务（cron）

```shell
crontab -e    # 编辑当前用户的定时任务
crontab -l    # 查看当前用户的定时任务

# 格式：分 时 日 月 周 命令
# 示例：
0 2 * * * /path/to/backup.sh     # 每天凌晨2点执行
*/5 * * * * /path/to/check.sh    # 每5分钟执行
0 9-17 * * 1-5 /path/to/work.sh  # 工作日9-17点每小时执行
```

## Shell 环境变量

```shell
export PATH=$PATH:/new/path      # 临时添加PATH
echo $HOME                       # 家目录
echo $SHELL                      # 当前shell
echo $USER                       # 当前用户

# 永久生效：写入 ~/.bashrc 或 ~/.bash_profile
echo 'export MY_VAR=hello' >> ~/.bashrc
source ~/.bashrc
```

## 网络配置（/etc/network 与 nmcli）

```shell
# NetworkManager 命令行
nmcli dev status                # 查看网络设备状态
nmcli con show                  # 查看连接配置
nmcli con up "connection-name"  # 启用连接

# 查看DNS
cat /etc/resolv.conf

# 查看主机名
hostname
hostnamectl set-hostname newname
```

## 常见问题排查思路

### 系统启动慢
```shell
systemd-analyze blame          # 查看各服务启动耗时
systemd-analyze critical-chain # 查看启动关键链
```

### 磁盘空间不足
```shell
df -h                          # 查看分区使用率
du -sh /* 2>/dev/null | sort -hr | head -10  # 根目录下最大的10个
find / -type f -size +500M -exec ls -lh {} \; 2>/dev/null  # 查找大文件
```

### 内存不足
```shell
free -h                        # 查看内存使用
top -o %MEM                    # 按内存占用排序进程
ps aux --sort=-%mem | head -10 # 内存占用前10进程
```

### CPU 过高
```shell
top -o %CPU                    # 按CPU占用排序
ps aux --sort=-%cpu | head -10 # CPU占用前10
perf top                       # 实时性能分析
strace -p PID                  # 跟踪进程系统调用
```
