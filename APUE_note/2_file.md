<!--
 * @Author: yao fanghao
 * @Date: 2023-04-23 14:57:19
 * @LastEditTime: 2023-04-24 22:22:35
 * @LastEditors: yao fanghao
-->
# 文件系统 基础知识

# 参考资料

* 系统编程 第4、5章 文件I/O
* **APUE 第3-6章** 文件I/O、文件和目录、标准I/O库、系统数据文件和信息
* CSAPP 辅助参考学习
* 李慧琴网课 p142-166

# 学习进度

* 系统编程 第4、5章 文件I/O ok
* APUE 5.1
* 李慧琴网课 p151-

# 简要记录

## 目录和文件 参考代码-- 2_1_stat.c 2_2_glob.c 2_3_readdir.c

* 获取文件属性
  * ls -l
  * ls -a
  * ls -i
  * ls -n
  
* ```struct stat {...};```
  * 描述文件系统中文件属性的结构体

  ```C
  struct stat {
    mode_t     st_mode;      //文件对应的模式，文件，目录等
    ino_t      st_ino;       //inode节点号
    dev_t      st_dev;       //设备号码
    dev_t      st_rdev;      //特殊设备号码
    nlink_t    st_nlink;     //文件的连接数
    uid_t      st_uid;       //文件所有者
    gid_t      st_gid;       //文件所有者对应的组
    off_t      st_size;      //普通文件，对应的文件字节数
    time_t     st_atime;     //文件最后被访问的时间
    time_t     st_mtime;     //文件内容最后被修改的时间
    time_t     st_ctime;     //文件状态改变时间
    blksize_t st_blksize;    //文件内容对应的块大小
    blkcnt_t   st_blocks;    //伟建内容对应的块数量
  };
  ```

* 文件访问权限
  * 位图表示权限
  * ```umask``` 命令
  * 文件权限更改 ```chmod``` 命令

* 文件系统： FAT / UFS
  * FAT: 静态单链表
  
* 硬连接、符号链接
  * ```link();```
  * ```unlink();```
  * ```remove();```
  * ```rename();```

* mkdir、rm、cd

* 分析/读取目录
  * ```glob();```  // 解析模式或者通配符
  * 结构体```glob_t```:

    ```C
    typedef struct {
      size_t   gl_pathc;    /* Count of paths matched so far  */
      char   **gl_pathv;    /* List of matched pathnames.  */
      size_t   gl_offs;     /* Slots to reserve in gl_pathv.  */
    } glob_t;
    ```

  * ```char **gl_pathv;``` 非常类似于 ```char**argv;```
  * ```opendir();```
  * ```closedir();```
  * ```readdir();```
  * 结构体```dirent```:

  ````C
    struct dirent {
    ino_t          d_ino;       /* inode number i节点编号 */
    off_t          d_off;       /* not an offset; see NOTES 早期文件系统中，telldir返回文件在目录内的偏移 */
    unsigned short d_reclen;    /* length of this record dirent 记录的实际长度 */
    unsigned char  d_type;      /* type of file; not supported
                                    by all filesystem types 文件类型 */
    char           d_name[256]; /* filename 文件名 */
  `};
  ````
