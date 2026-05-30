# 自学记录

2023.11.13-

## 参考资料

* SQL必知必会

## 创建表

```sql
-- 需要依次设置不同数据类型
CREATE TABLE Products
(
    prod_id        CHAR(10)            NOT NULL,
    vend_id        CHAR(10)            NOT NULL,
    prod_name      CHAR(254)           NOT NULL,
    prod_price     DECIMAL(8,2)       NOT NULL,
    prod_desc      VARCHAR(1000)      NULL
);
```

```sql
-- 给表增加新的一列
ALTER TABLE Vendors
ADD vend_phone CHAR(20);
```

## 检索

```sql
SELECT [列名] FROM [表名]
```

```sql
SELECT * FROM [表名]
```

```sql
-- 去重检索
SELECT DISTINCT [列名] FROM [表名]
```

```sql
-- 限制返回前5行
SELECT TOP 5 [列名]
FROM [表名];
```

```sql
-- 子查询
SELECT cust_id FROM Orders
WHERE order_num IN (SELECT order_num
                     FROM OrderItems
                     WHERE prod_id = 'RGAN01');
```

* UNION 组合查询
  * 将多个语句组合起来

## 排序

```sql
SELECT [列名] FROM [表名]
ORDER BY [列名];
```

```sql
-- 降序排列
SELECT [列名] FROM [表名]
ORDER BY [列名] DESC;
```

## 过滤

```sql
SELECT prod_name, prod_price FROM Products
WHERE prod_price = 3.49;
```

```sql
-- 过滤值在某一范围内的
SELECT prod_name, prod_price FROM Products
WHERE prod_price BETWEEN 5 AND 10;
```

```sql
SELECT prod_id, prod_price, prod_name FROM Products
WHERE vend_id = 'DLL01' AND prod_price <= 4;
```

```sql
SELECT prod_id, prod_price, prod_name FROM Products
WHERE vend_id = 'DLL01' OR prod_price <= 4;
```

```sql
-- 匹配指定内容
SELECT prod_name, prod_price FROM Products
WHERE vend_id  IN ('DLL01','BRS01')
```

```sql
SELECT prod_name FROM Products
WHERE NOT vend_id = 'DLL01'
```

## 通配符

* LIKE语句
* % 通配符
  
```sql
SELECT prod_id, prod_name FROM Products
WHERE prod_name LIKE 'Fish%';
```

* [] 字符集匹配方式

```sql
SELECT cust_contact FROM Customers
WHERE cust_contact LIKE '[JM]%'
ORDER BY cust_contact;
```

* ^ 脱字号，结果取反

## 插入

```sql
-- 安全但繁琐的方法
INSERT INTO Customers(cust_id,cust_name,cust_address,cust_city,
                        cust_state,cust_zip,cust_country,
                        cust_contact,cust_email)
VALUES(1000000006,'Toy Land','123 Any Street','New York',
        'NY','11111','USA',
        NULL,NULL);
```

## 更新和删除

```sql
-- 更新
UPDATE Customers
SET cust_email = 'kim@thetoystore.com'
WHERE cust_id = 1000000005;
```

```sql
-- 删除
DELETE FROM Customers
WHERE cust_id = 1000000006;
```

```sql
-- 删除表
DROP TABLE CustCopy;
```

## 计算

* 调用函数 ACG() COUNT() MAX() MIN() SUM()

* AS语句，取别名

```sql
SELECT COUNT(＊) AS num_items,
        MIN(prod_price) AS price_min,
        MAX(prod_price) AS price_max,
        AVG(prod_price) AS price_avg
FROM Products;
```

## 分组数据

```sql
-- 分组统计
SELECT vend_id, COUNT(＊) AS num_prods FROM Products
GROUP BY vend_id;
```

```sql
-- HAVING类似于WHERE，但是是过滤分组的
SELECT cust_id, COUNT(＊) AS orders FROM Orders
GROUP BY cust_id
HAVING COUNT(＊) >= 2;
```

## 联结表

* JOIN 或 INNER JOIN 内联结，相当于取交集
* OUTER JOIN 外联结，相当于取并集

## 事务处理

```sql
-- 提交处理事务块
BEGIN TRANSACTION
...
COMMIT TRANSACTION
```

```sql
-- 回滚操作
DELETE FROM Orders;
ROLLBACK;
```

## 窗口函数

* 在每行数据上保留原有行，同时进行聚合/排序计算（不同于GROUP BY会折叠行）

```sql
-- 为每行计算所属部门的平均薪资
SELECT emp_name, dept_id, salary,
       AVG(salary) OVER (PARTITION BY dept_id) AS dept_avg_salary
FROM employees;
```

```sql
-- 窗口排序函数
SELECT emp_name, dept_id, salary,
       ROW_NUMBER()   OVER (PARTITION BY dept_id ORDER BY salary DESC) AS rn,
       RANK()         OVER (PARTITION BY dept_id ORDER BY salary DESC) AS rk,
       DENSE_RANK()   OVER (PARTITION BY dept_id ORDER BY salary DESC) AS dr
FROM employees;
```

* ROW_NUMBER：相同值给不同序号（无并列）
* RANK：相同值并列，序号跳跃
* DENSE_RANK：相同值并列，序号连续

## 索引原理

* **B+树索引**：非叶子节点只存键值，叶子节点存数据+链表指针
  * 范围查询高效（叶子节点链表顺序扫描）
  * 高度通常为 2-3 层，百万级数据只需 2-3 次 I/O
* **聚簇索引（Clustered Index）**
  * 数据物理顺序与索引顺序一致
  * InnoDB 的主键索引即为聚簇索引
  * 每张表只能有一个聚簇索引
* **辅助索引（Secondary Index）**
  * 叶子节点存储主键值，回表查询完整行
* **覆盖索引（Covering Index）**
  * 索引包含查询所需的所有列，无需回表

## SQL优化技巧

* **通过 EXPLAIN 分析执行计划**
```sql
EXPLAIN SELECT * FROM orders WHERE user_id = 123;
```
关注列：type（ALL=全表扫描，ref/range=走索引），rows（扫描行数），Extra

* **常见优化手段**
  * 避免 SELECT *，只返回需要的列
  * 针对 WHERE 条件中频繁过滤的列建索引
  * 大表分页优化：用游标（WHERE id > last_id）替代 OFFSET
  * JOIN 时小表驱动大表
  * 索引下推（Index Condition Pushdown）：在存储引擎层先过滤再回表
  * 避免在 WHERE 中对索引列使用函数或隐式类型转换

## 数据库设计范式

* **1NF**：每列不可再分（原子性）
* **2NF**：非主键列完全依赖于主键（消除部分依赖）
* **3NF**：非主键列不依赖于其他非主键列（消除传递依赖）
* **BCNF**：每个决定因素都是候选键

## 实际工作中常用

```sql
-- 连表更新
UPDATE t1 JOIN t2 ON t1.id = t2.id
SET t1.name = t2.name;

-- 公用表表达式 CTE（递归查询）
WITH RECURSIVE cte AS (
    SELECT id, name, parent_id FROM categories WHERE parent_id IS NULL
    UNION ALL
    SELECT c.id, c.name, c.parent_id
    FROM categories c JOIN cte ON c.parent_id = cte.id
)
SELECT * FROM cte;
```

## 表连接详解

### INNER JOIN vs LEFT JOIN vs RIGHT JOIN vs FULL JOIN

```sql
-- 内连接：只返回匹配的行
SELECT o.order_id, c.cust_name
FROM Orders o
INNER JOIN Customers c ON o.cust_id = c.cust_id;

-- 左外连接：左表全部保留，右表无匹配则填 NULL
SELECT c.cust_name, o.order_id
FROM Customers c
LEFT JOIN Orders o ON c.cust_id = o.cust_id;

-- 右外连接：右表全部保留，左表无匹配则填 NULL
SELECT o.order_id, c.cust_name
FROM Orders o
RIGHT JOIN Customers c ON o.cust_id = c.cust_id;

-- 全外连接：两张表全部保留（MySQL 不支持 FULL JOIN，可用 UNION 模拟）
SELECT c.cust_name, o.order_id
FROM Customers c
LEFT JOIN Orders o ON c.cust_id = o.cust_id
UNION
SELECT c.cust_name, o.order_id
FROM Customers c
RIGHT JOIN Orders o ON c.cust_id = o.cust_id;
```

### 自连接

```sql
-- 查找同一部门的员工
SELECT e1.emp_name AS employee, e2.emp_name AS colleague
FROM employees e1
JOIN employees e2 ON e1.dept_id = e2.dept_id AND e1.emp_id < e2.emp_id;
```

## 子查询进阶

```sql
-- 标量子查询（返回单个值）
SELECT emp_name, salary,
       (SELECT AVG(salary) FROM employees WHERE dept_id = e.dept_id) AS dept_avg
FROM employees e;

-- 行子查询
SELECT * FROM employees
WHERE (dept_id, salary) = (SELECT dept_id, MAX(salary) FROM employees GROUP BY dept_id LIMIT 1);

-- EXISTS 子查询（比 IN 更高效，遇到第一个匹配即停止）
SELECT * FROM Customers c
WHERE EXISTS (SELECT 1 FROM Orders o WHERE o.cust_id = c.cust_id);
```

## 数据类型

| 类型 | 说明 | 示例 |
|------|------|------|
| INT / BIGINT | 整数（4/8字节） | `INT UNSIGNED` |
| DECIMAL(m,d) | 精确小数 | `DECIMAL(10,2)` 存金额 |
| VARCHAR(n) | 变长字符串 | `VARCHAR(255)` |
| CHAR(n) | 定长字符串 | `CHAR(32)` UUID |
| TEXT / LONGTEXT | 大文本 | 文章内容 |
| DATETIME / TIMESTAMP | 日期时间 | `DATETIME` 范围 '1000-01-01' 到 '9999-12-31' |
| ENUM | 枚举 | `ENUM('small','medium','large')` |
| JSON | JSON 类型（MySQL 5.7+） | 灵活存储结构化数据 |
| BLOB | 二进制数据 | 图片、文件 |

## 约束

```sql
CREATE TABLE Products (
    prod_id    CHAR(10)     PRIMARY KEY,          -- 主键约束
    prod_name  VARCHAR(255) NOT NULL,              -- 非空约束
    vend_id    CHAR(10)     NOT NULL,
    prod_price DECIMAL(8,2) CHECK (prod_price > 0),-- 检查约束（MySQL 8.0.16+）
    prod_desc  TEXT,
    UNIQUE (prod_name),                            -- 唯一约束
    FOREIGN KEY (vend_id) REFERENCES Vendors(vend_id) -- 外键约束
);
```

## 索引管理

```sql
-- 创建索引
CREATE INDEX idx_prod_name ON Products(prod_name);
CREATE UNIQUE INDEX idx_prod_code ON Products(prod_code);  -- 唯一索引
CREATE INDEX idx_name_price ON Products(prod_name, prod_price); -- 复合索引

-- 查看索引
SHOW INDEX FROM Products;

-- 删除索引
DROP INDEX idx_prod_name ON Products;

-- 慢查询日志（找出需要优化的SQL）
SET GLOBAL slow_query_log = ON;
SET GLOBAL long_query_time = 1;  -- 超过1秒记录
```

## 锁机制

| 锁类型 | 说明 |
|--------|------|
| **表级锁** | MyISAM 引擎，开销小，并发低 |
| **行级锁** | InnoDB 引擎，开销大，并发高 |
| **共享锁（S锁）** | `SELECT ... LOCK IN SHARE MODE`，允许其他事务读但不允许写 |
| **排他锁（X锁）** | `SELECT ... FOR UPDATE`，不允许其他事务读写 |
| **意向锁** | InnoDB 自动管理，表示事务准备在更细粒度上加锁 |
| **间隙锁（Gap Lock）** | 防止幻读，锁定索引记录之间的间隙 |

## 隔离级别

| 级别 | 脏读 | 不可重复读 | 幻读 |
|------|:----:|:----------:|:----:|
| READ UNCOMMITTED | 可能 | 可能 | 可能 |
| READ COMMITTED | 避免 | 可能 | 可能 |
| REPEATABLE READ (MySQL默认) | 避免 | 避免 | 可能（InnoDB 通过 MVCC+间隙锁避免） |
| SERIALIZABLE | 避免 | 避免 | 避免 |

```sql
-- 查看/设置隔离级别
SELECT @@transaction_isolation;
SET SESSION TRANSACTION ISOLATION LEVEL READ COMMITTED;
```

## 事务与 MVCC

* **MVCC（多版本并发控制）**
  * 每行记录有多个版本，每个事务看到的是自己开始时刻的快照
  * 通过 undo log 实现版本链
  * 读不加锁，写加行锁，读写互不阻塞
* **事务日志**
  * redo log：保证事务持久性（WAL，Write-Ahead Logging）
  * undo log：保证事务原子性（回滚）
  * binlog：主从复制和数据恢复

## 分库分表

* **垂直拆分**：按业务模块分库（用户库、订单库、商品库）
* **水平拆分**：按某个字段取模/范围分表（user_0、user_1、user_2）
* **常见中间件**：ShardingSphere、MyCat、Vitess
* **分片键选择**：尽量选择查询频率最高的字段

## 常用运维命令

```sql
-- 查看数据库大小
SELECT table_schema, ROUND(SUM(data_length + index_length) / 1024 / 1024, 2) AS size_mb
FROM information_schema.tables
GROUP BY table_schema;

-- 查看当前连接
SHOW FULL PROCESSLIST;

-- 杀掉连接
KILL CONNECTION 12345;

-- 查看表结构
DESC table_name;
SHOW CREATE TABLE table_name;

-- 备份和恢复
-- mysqldump -u root -p dbname > backup.sql
-- mysql -u root -p dbname < backup.sql
```

## MySQL 主从复制

### 复制原理

```
主库写入 → binlog → IO线程 → 从库 relay log → SQL线程 → 从库数据
```

| 步骤 | 说明 |
|------|------|
| 1 | 主库提交事务时写入 binlog |
| 2 | 从库 IO 线程连接主库请求 binlog |
| 3 | 主库 LOG DUMP 线程发送 binlog 给从库 |
| 4 | 从库 IO 线程写入 relay log |
| 5 | 从库 SQL 线程重放 relay log |

### 复制模式

| 模式 | 特点 | 一致性 |
|------|------|--------|
| 异步复制 | 主库提交即返回，不等从库 | 主库宕机可能丢数据 |
| 半同步复制 | 至少一个从库确认收到才提交 | 基本不丢数据 |
| 组复制（Group Replication）| 多数派节点确认 | 强一致性 |

### 配置步骤

```sql
-- 主库
SET GLOBAL server_id = 1;
CREATE USER 'repl'@'%' IDENTIFIED BY 'password';
GRANT REPLICATION SLAVE ON *.* TO 'repl'@'%';
SHOW MASTER STATUS;  -- 记录 File 和 Position

-- 从库
CHANGE MASTER TO
  MASTER_HOST='master_ip',
  MASTER_USER='repl',
  MASTER_PASSWORD='password',
  MASTER_LOG_FILE='mysql-bin.000001',
  MASTER_LOG_POS=123;
START SLAVE;
SHOW SLAVE STATUS\G  -- 查看 Slave_IO_Running 和 Slave_SQL_Running
```

### 主从延迟监控与处理

```sql
-- 查看延迟秒数
SHOW SLAVE STATUS\G
-- Seconds_Behind_Master 字段

-- 常见延迟原因
-- 1. 从库硬件弱于主库
-- 2. 大事务（一次性删除大量数据）
-- 3. DDL 操作（ALTER TABLE 锁表）
-- 4. 从库并行复制参数配置不当
```

### 高可用方案

| 方案 | 自动故障转移 | 一致性 | 适用场景 |
|------|------------|--------|---------|
| MHA | 是（需额外组件）| 最终一致性 | 中小规模 |
| Orchestrator | 是 | 最终一致性 | 中大规模 |
| InnoDB Cluster（MySQL 8.0）| 是（Group Replication）| 强一致性 | 新项目首选 |

### 读写分离

```shell
# 应用层：框架支持（如 ShardingSphere）
# 中间件层：ProxySQL / MyCat / MaxScale
# 配置 ProxySQL 读写分离示例
mysql -h 127.0.0.1 -P 6032 -u admin -p
INSERT INTO mysql_servers(hostgroup_id, hostname, port) VALUES (0, 'master', 3306);
INSERT INTO mysql_servers(hostgroup_id, hostname, port) VALUES (1, 'slave1', 3306);
INSERT INTO mysql_query_rules(rule_id, active, match_digest, destination_hostgroup)
VALUES (1, 1, '^SELECT.*', 1);  -- SELECT 走从库
LOAD MYSQL SERVERS TO RUNTIME;
SAVE MYSQL SERVERS TO DISK;
```

## SQL 反模式案例

| 反模式 | 问题 | 正确做法 |
|--------|------|---------|
| **EAV 模型** | 用行存储属性，查询需大量 JOIN 或 GROUP BY | JSON 列或垂直分表 |
| **多值列** | 一个字段存逗号分隔的值（`tag1,tag2,tag3`） | 创建关联表存储多值 |
| **乱用 ENUM** | ENUM 添加新值需要 ALTER TABLE | 关联字典表或 CHECK 约束 |
| **NULL 滥用** | 用 NULL 表示"不适用"和"未知"混合语义 | 分别设计，或使用默认值 |
| **隐式类型转换** | `WHERE phone = 13800138000`（数值 vs 字符串） | 保持类型一致或显式转换 |

## 备份恢复策略

### 备份类型

| 类型 | 说明 | 恢复速度 |
|------|------|---------|
| 全量备份 | 完整数据库 | 快 |
| 增量备份 | 自上次备份以来的变更 | 慢（需叠加） |
| 差异备份 | 自上次全量备份以来的变更 | 中等 |

```shell
# 逻辑备份（mysqldump，适合小库）
mysqldump -u root -p --single-transaction --routines --triggers mydb > full.sql

# 物理备份（XtraBackup，适合大库）
xtrabackup --backup --target-dir=/backup/full
xtrabackup --prepare --target-dir=/backup/full

# 增量备份
xtrabackup --backup --target-dir=/backup/inc1 --incremental-basedir=/backup/full

# 恢复
xtrabackup --copy-back --target-dir=/backup/full
chown -R mysql:mysql /var/lib/mysql
```

### PITR（时间点恢复）

```sql
# 前提：有全量备份 + 所有 binlog
# 1. 恢复全量备份
mysql -u root -p mydb < full.sql

# 2. 重放 binlog 到指定时间点
mysqlbinlog --stop-datetime="2025-06-01 10:00:00" /var/log/mysql/binlog.000001 | mysql -u root -p

# 3. 或恢复到指定 position
mysqlbinlog --stop-position=12345 /var/log/mysql/binlog.000001 | mysql -u root -p
```