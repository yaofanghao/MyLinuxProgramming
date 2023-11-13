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