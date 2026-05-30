<!--
 * @Author: yao fanghao
 * @Date: 2023-04-14 22:13:52
 * @LastEditTime: 2023-08-10 21:44:02
 * @LastEditors: yao fanghao
-->

# 参考资料

* **<https://learn.microsoft.com/en-us/cpp/?view=msvc-170>**
* **<https://google.github.io/styleguide/cppguide.html>**
* **C++Primer**
* K&R-C程序设计语言
* C Primer Plus
* C标准库
* C++标准库
* 嵌入式软件开发笔试面试指南
* linux/unix系统编程手册
* **APUE**
* 剑指offer √
* C专家编程 √
* **STL源码剖析**
* 现代C++语言核心特性解析
* 王道-数据结构
* 【史上最强最细腻的linux嵌入式C语言学习教程【李慧芹老师】】 <https://www.bilibili.com/video/BV18p4y167Md>
* 【《C++ Primer 第五版》】 <https://www.bilibili.com/video/BV1z64y1U7hs>
* 【黑马程序员-Linux网络编程】 <https://www.bilibili.com/video/BV1iJ411S7UA>
* 【彻底搞懂 进程&线程、进程池&线程池】 <https://www.bilibili.com/video/BV1V84y1Y77s>

# C / C++ 基本概念

* 字符串默认每个占用1字节，末尾还要加上\0

* 左值和右值
  * 左值lvalue 指向内存位置，可以被修改
  * 右值rvalue 指向存储在内存的数值
* 短路求值

* 位运算
  * 把操作数第n位置1，其他不变 num = num | 1<<n;
  * 把操作数第n为清零，其他不变 num = num &~ (1<<n);

* **const**
  * 不可改变值
  * 约束某些内容不可更改
* const float pi = 3.14
  * 指定常量，同时指定了类别
* **指针常量和常量指针**
  * const int *p 常量指针，不能修改指向的值
  * int const *p 常量指针，不能修改指向的值
  * int *const p 指针常量，不能修改指针的指向

* static
  * 默认初始化为0
  * 只用一块空间
  * 只能在本文件中使用
  * 可以在函数调用间保持局部变量值
  * 可以定义静态成员和静态成员函数
* 变量作用范围
  * 内部屏蔽外部
* extern
  * 扩大了作用范围
  * 可以用于另一个文件中声明全局变量或函数
* extern const
  * 在另一文件中引用const常量
* extern"C"
  * 使编译器对这部分按照C语言进行编译

* typedef 
* define 不做正确性检查

* struct 和 union
  * struct 按最大成员的size或其size的整数倍对齐
  * union有数据对齐

* 静态库 动态库
  * 静态库
    * libxx.a
    * 是先吃撑了，防止之后饿
  * 动态库
    * libxx.so
    * 是把粮食带着，等饿了再吃

* size_t
  * 表示C中任何对象所能达到的最大长度，是无符号整数

* 声明和定义
  * 声明不分配空间
  * 声明可以有多个，定义只有一个

* inline 内联函数
  * 用于频繁被调用的函数中
  * 以空间换时间

* namespace
  * 区分不同库中的相同函数、变量等

# 面向对象

* 类成员默认为私有 private
  
* 友元函数 friend
  
* this指针
  
* 多继承

* 多态
  * virtual 虚函数
  * 晚绑定
  * 纯虚函数 virtual .... = 0
  
* 深拷贝 浅拷贝
  * 深拷贝在析构时，各自对象占用资源不会冲突

# C++ 新特性

* 异常处理
  * try ... catch
  * throw

* 动态内存
  * new delete
  * malloc需要人为计算申请内存大小，而new可以自动计算申请内存大小
  * realloc
  * new分配的内存块保存在**堆区**

* 内存管理
  * CSAPP-p587
  * 代码段 数据段 BSS段 堆区 文件映射区 栈区
  * 代码段：只读存储区和文本
  * 数据段：存储**已初始化**的全局变量和静态变量
  * BSS段：存储**未初始化和初始化为0**的全局变量和交通便利
  * 堆区：程序员分配和管理 malloc
  * 映射区：动态链接库及调用mmap
  * 栈区：编译器自动分配管理 存放局部变量

* **智能指针**
  * unique_ptr、shared_ptr、weak_ptr
  * 解决了内存泄漏（忘记释放）、二次释放等问题

* STL
  * 容器 算法 迭代器

* auto

* decltype

* labmda表达式

* 并行编程 #include <thread>
  * join()
  * detach()

# C++ 现代特性深度详解

## 智能指针原理

* **shared_ptr**
  * 引用计数原理：控制块（control block）存储引用计数，每新增一个shared_ptr计数+1，析构时-1，归零时释放对象
  * make_shared：一次内存分配同时创建对象+控制块，比`new shared_ptr`更高效
  * 引用计数是线程安全的（原子操作），但指向的对象不一定线程安全

* **weak_ptr**
  * 解决shared_ptr循环引用导致的内存泄漏
  * 通过`lock()`获取shared_ptr，若对象已释放则返回空
  * 不增加引用计数（强引用），只增加弱引用计数

* **unique_ptr**
  * 独占所有权，不可复制，只能移动
  * 可作为函数返回值传递所有权
  * 可自定义删除器（deleter）

## 左值右值与移动语义

* **左值（lvalue）**：有内存地址，可取地址
* **右值（rvalue）**：临时对象，无持久地址（如字面量、函数返回值）
* **右值引用（&&）**：绑定到右值，实现移动语义
  ```cpp
  std::vector<int> v1(1000);
  std::vector<int> v2 = std::move(v1); // v1资源被"偷走"
  ```

* **完美转发（std::forward）**
  * 保持参数原有的左值/右值属性转发给下一个函数
  * 常用于泛型编程和工厂函数

* **引用折叠规则**
  * T& & → T& , T&& & → T& , T& && → T& , T&& && → T&&

## constexpr 与编译期计算

* **constexpr**：编译期求值的常量表达式（C++11）
* **constexpr if**（C++17）：编译期条件分支，消除运行时代码
  ```cpp
  if constexpr (std::is_integral_v<T>) { ... }
  ```
* **consteval**（C++20）：强制编译期求值，否则编译错误
* **constinit**（C++20）：保证静态变量在编译期初始化（不保证const）

## C++17/20 核心特性

* **结构化绑定**（C++17）
  ```cpp
  auto [key, value] = my_map; // 解构pair/tuple
  ```

* **std::optional**（C++17）：表示可能存在或不存在的值，替代返回-1等哨兵值

* **std::variant**（C++17）：类型安全的联合体

* **std::any**（C++17）：可存储任意类型的值

* **std::string_view**（C++17）：非拥有字符串视图，零拷贝

* **协程 coroutine**（C++20）
  * co_await、co_yield、co_return
  * 相比线程更轻量，由程序自身控制调度

* **概念 Concept**（C++20）
  * 约束模板参数，替代SFINAE
  ```cpp
  template<typename T> requires std::integral<T>
  ```

* **范围 Range**（C++20）
  ```cpp
  std::ranges::sort(vec);
  ```

## STL 容器底层分析

| 容器 | 底层结构 | 迭代器失效场景 |
|------|---------|--------------|
| vector | 动态数组，倍增扩容（通常1.5x或2x） | 插入/删除导致重分配时所有迭代器失效 |
| deque | 分块连续存储（中控器+缓冲区） | 中间插入/删除使所有迭代器失效 |
| list | 双向链表 | 除被删元素外，其他迭代器不失效 |
| unordered_map | 哈希表+开链法（桶数组+链表/红黑树） | 重哈希时全部失效 |
| map/set | 红黑树（自动平衡二叉搜索树） | 删除操作只影响被删元素 |

## 并发与同步

* **std::async**：异步执行任务，返回std::future
* **std::future / std::promise**：线程间单向传递结果
* **std::atomic**：无锁编程基础，支持memory_order（relaxed/acquire/release/acq_rel/seq_cst）
* **std::jthread**（C++20）：自动join的线程，支持协作式取消

## 内存序（Memory Order）

* memory_order_relaxed：仅保证原子性，不做顺序约束
* memory_order_acquire：之后的读写操作不能重排到此之前
* memory_order_release：之前的读写操作不能重排到此之后
* memory_order_acq_rel：同时有acquire和release语义
* memory_order_seq_cst：全局顺序一致性（默认，最严格）

# C 语言深入

## C 内存布局（x86-64 Linux ELF）

| 区域 | 内容 | 方向 |
|------|------|------|
| .text | 可执行机器码 | 只读 |
| .rodata | 只读数据（字符串常量、const 全局） | 只读 |
| .data | 已初始化全局/静态变量 | 读写 |
| .bss | 未初始化全局/静态变量（运行时清零） | 读写 |
| 堆（heap） | malloc/new 分配，向上增长 | 读写 |
| 文件映射区 | 动态库、mmap | 读写 |
| 栈（stack） | 局部变量、函数参数、返回地址，向下增长 | 读写 |
| 内核空间 | 系统保留（3G+1G 分割） | 只读/特权 |

## C 语言常见陷阱

### 数组与指针

```c
// sizeof 数组 vs 指针
int arr[10];
int *p = arr;
sizeof(arr);  // 40（整个数组）
sizeof(p);    // 8（指针本身大小）

// 数组名退化为指针（函数参数、sizeof 除外）
void func(int arr[]) {
    sizeof(arr);  // 8，退化为指针！
}

// 字符串字面量不可修改
char *p = "hello";
p[0] = 'H';  // 未定义行为（段错误）
char arr[] = "hello";
arr[0] = 'H'; // OK，栈上拷贝
```

### 整数溢出

```c
// 有符号整数溢出是未定义行为
int a = INT_MAX;
a + 1;  // 未定义！可能优化器直接删除这段代码

// 无符号整数回绕（wraparound）是定义的
unsigned int u = UINT_MAX;
u + 1;  // 0（定义行为）
```

### 序列点与未定义行为

```c
i = i++;   // 未定义行为
printf("%d %d", ++i, ++i); // 未定义，函数参数求值顺序未指定
arr[i] = i++; // 未定义行为
```

## 数据结构（面试高频）

### 链表反转

```c
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode *prev = NULL, *curr = head, *next;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
```

### LRU 缓存（哈希表 + 双向链表）

* 核心操作 O(1)：
  * get(key)：查到则移到链表头部
  * put(key, value)：存在则更新并移到头部；不存在则插入头部，超出容量则删除尾部

### 快速排序（分治）

```c
void quick_sort(int arr[], int l, int r) {
    if (l >= r) return;
    int i = l, j = r, pivot = arr[l + (r - l) / 2];
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
            i++; j--;
        }
    }
    quick_sort(arr, l, j);
    quick_sort(arr, i, r);
}
```

## C++ 常见面试题

| 问题 | 答案 |
|------|------|
| 虚函数表存在哪里？ | 每个含虚函数的类有一个 vtable（只读数据段），每个对象有一个 vptr 指向它 |
| 为什么构造函数不能是虚函数？ | vptr 需要在构造完成后才初始化，构造函数执行期间 vptr 未设置 |
| 为什么析构函数建议是虚函数？ | 基类指针指向派生类对象时，非虚析构不会调用派生类析构，导致资源泄漏 |
| vector 的 push_back 复杂度？ | 均摊 O(1)，每次扩容导致拷贝所有元素 |
| map 和 unordered_map 的区别？ | map 红黑树 O(log n)；unordered_map 哈希表 O(1) 均摊 |
| shared_ptr 线程安全吗？ | 引用计数原子操作安全，但指向的对象需外部同步 |

## C++ 编码规范（Google Style 摘录）

* 文件名小写加下划线：`my_class.cpp`
* 类名大驼峰：`MyClass`
* 变量小写加下划线：`my_variable`
* 常量 k 开头：`const int kDaysInWeek = 7;`
* 避免使用 `using namespace std;`（头文件中禁止）
* 传参：输入参数用 `const T&`，输出参数用指针
* 智能指针优先于裸指针
* 头文件自包含，尽量 forward declare 减少依赖
