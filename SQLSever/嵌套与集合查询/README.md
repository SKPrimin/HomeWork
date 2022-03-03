

### 针对供应管理数据库SPJ，进行各种嵌套与集合查询：

##### (1)查询使用了“S001”供应商供应的零件的工程项目信息；
```sql
SELECT
	* 
FROM
	J168 
WHERE
	JNO IN ( SELECT JNO FROM SPJ168 WHERE SNO = 'S001' ) 
```
<img src="嵌套与集合查询/image-20210529122734637.png" alt="image-20210529122734637" style="zoom:50%;" />

##### (2)查询供应零件“螺丝刀”的供应商信息；

```sql
SELECT
	* 
FROM
	S168 
WHERE
	SNO IN ( SELECT SNO FROM SPJ168 WHERE PNO IN ( SELECT PNO FROM P168 WHERE PNAME = '螺丝刀' ) )
```

<img src="嵌套与集合查询/image-20210529122848545.png" alt="image-20210529122848545" style="zoom:50%;" />

##### (3)查询供应商“北京新天地”的所有客户（工程项目）的信息；

```sql 
SELECT
	* 
FROM
	J168 
WHERE
	JNO IN ( SELECT JNO FROM SPJ168 WHERE SNO IN ( SELECT SNO FROM S168 WHERE SNAME = '北京新天地' ) )
```

<img src="嵌套与集合查询/image-20210529122930923.png" alt="image-20210529122930923" style="zoom:50%;" />

##### (4)查询供应了“J003”工程“P002”零件的供应商信息；

```sql 
SELECT
	* 
FROM
	S168 
WHERE
	SNO IN ( SELECT SNO FROM SPJ168 WHERE JNO = 'J003' AND PNO = 'P002' )
```

<img src="嵌套与集合查询/image-20210529123005596.png" alt="image-20210529123005596" style="zoom:50%;" />

##### (5)查询使用了“天津”供应商供应的“红色”零件的工程项目信息；

```sql  
SELECT
	* 
FROM
	J168 
WHERE
	JNO IN (
	SELECT
		JNO 
	FROM
		SPJ168 
	WHERE
		SNO IN ( SELECT SNO FROM S168 WHERE CITY = '天津' ) 
		AND PNO IN ( SELECT PNO FROM P168 WHERE COLOR = '红色' ) 
	)
```

<img src="嵌套与集合查询/image-20210529123026897.png" alt="image-20210529123026897" style="zoom:50%;" />

##### (6)查询没有使用“天津”供应商供应的“红色”零件的工程项目信息；

```sql 
SELECT
	* 
FROM
	J168 
WHERE
	JNO IN (
	SELECT
		JNO 
	FROM
		SPJ168 
	WHERE
		PNO != ALL (
		SELECT
			PNO 
		FROM
			P168 
		WHERE
			COLOR = '红色' 
			AND PNO IN ( SELECT PNO FROM SPJ168 WHERE SNO IN ( SELECT SNO FROM S168 WHERE CITY = '天津' ) ) 
		) 
	)
```

<img src="嵌套与集合查询/image-20210529123051778.png" alt="image-20210529123051778" style="zoom:50%;" />

##### (7)查询使用了“S002”供应的“螺母”零件的工程信息；

```sql  
SELECT
	* 
FROM
	J168 
WHERE
	JNO IN ( SELECT JNO FROM SPJ168 WHERE PNO IN ( SELECT PNO FROM P168 WHERE PNAME = '螺  母' ) AND SNO = 'S002' )
```

<img src="嵌套与集合查询/image-20210529123112535.png" alt="image-20210529123112535" style="zoom:50%;" />

##### (8)查询使用了 “螺母”零件的工程信息及相应供应商信息；
```sql 
SELECT
	J168.JNO,
	JNAME,
	J168.CITY,
	S168.SNO,
	SNAME,
	S168.CITY,
	STAT 	
FROM
	J168,S168,SPJ168,P168
WHERE
	SPJ168.SNO = S168.SNO	AND SPJ168.JNO = J168.JNO AND SPJ168.PNO = P168.PNO AND PNAME = '螺  母' 
```

<img src="嵌套与集合查询/image-20210529152803979.png" alt="image-20210529152803979" style="zoom:50%;" />

##### (9)查询给“长春一汽”项目供应零件的供应商信息和供应情况；
```sql 
SELECT
	S168.SNO,
	SNAME,
	S168.CITY,
	P168.PNO,
	PNAME,
	COLOR,
	WT 
FROM
	S168,	SPJ168,	J168,	P168 
WHERE
	SPJ168.SNO = S168.SNO 
	AND SPJ168.JNO = J168.JNO 
	AND SPJ168.PNO = P168.PNO 
	AND JNAME = '长春一汽'
```

<img src="嵌套与集合查询/image-20210529152828541.png" alt="image-20210529152828541" style="zoom:50%;" />

##### (10)查询给“长春一汽”项目供应“螺母”零件最多的供应商信息和供应情况;

```sql 
SELECT
	S168.SNO,
	SNAME,
	S168.CITY,
	P168.PNO,
	PNAME,
	COLOR,
	WT 
FROM
	S168,
	SPJ168,
	J168,
	P168 
WHERE
	SPJ168.SNO = S168.SNO 
	AND SPJ168.JNO = J168.JNO 
	AND SPJ168.PNO = P168.PNO 
	AND JNAME = '长春一汽' 
	AND WT IN ( SELECT MAX ( WT ) FROM P168 WHERE PNAME = '螺  母' )
```

<img src="嵌套与集合查询/image-20210529152855223.png" alt="image-20210529152855223" style="zoom:50%;" />

##### (11)查询使用了“螺母”或“螺丝刀”零件的工程项目信息；

```sql 
SELECT
	* 
FROM
	J168 
WHERE
	JNO IN ( SELECT JNO FROM SPJ168 WHERE PNO IN 
	( SELECT PNO FROM P168 WHERE PNAME = '螺  母' 
	UNION SELECT PNO FROM P168 WHERE PNAME = '螺丝刀' ) )
```

<img src="嵌套与集合查询/image-20210529152932732.png" alt="image-20210529152932732" style="zoom:50%;" />

##### (12)查询既使用了“螺母”又使用了“螺丝刀”零件的工程项目信息；

```sql  
SELECT
	* 
FROM
	J168 
WHERE
	JNO IN ( SELECT JNO FROM SPJ168 WHERE PNO IN 
	( SELECT PNO FROM P168 WHERE PNAME = '螺  母' 
	INTERSECT SELECT PNO FROM P168 WHERE PNAME = '螺丝刀' ) )
```

<img src="嵌套与集合查询/image-20210529153002803.png" alt="image-20210529153002803" style="zoom:50%;" />

##### (13)查询使用了“螺母”零件但没有使用“螺丝刀”零件的工程项目信息；

```sql 
SELECT
	* 
FROM
	J168 
WHERE
	JNO IN ( SELECT JNO FROM SPJ168 WHERE PNO IN ( SELECT PNO FROM P168 WHERE PNAME = '螺  母' EXCEPT SELECT PNO FROM P168 WHERE PNAME = '螺丝刀' ) )
```

<img src="嵌套与集合查询/image-20210529153025922.png" alt="image-20210529153025922" style="zoom:50%;" />

##### (14)查询使用过所有供应商供应的零件的工程项目信息。 不存在任何零件没使用
```sql  
SELECT
	* 
FROM
	J168 
WHERE
	NOT EXISTS (
	SELECT
		* 
	FROM
		P168 
	WHERE
		NOT EXISTS ( SELECT * FROM SPJ168 WHERE SPJ168.PNO = P168.PNO AND SPJ168.JNO = J168.JNO ) 
	)
```

<img src="嵌套与集合查询/image-20210529153102697.png" alt="image-20210529153102697" style="zoom:50%;" />



