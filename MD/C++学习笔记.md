# 2019/3/16
## 字符串初始化
```
string s1 = "aaaaa";
	string s2("bbbbb");
	string s3 = s2; //通过拷贝构造函数，初始化s3
	string s4(10, 'a');
	//string s5 = "hello" + "world";  //错误
	cout << "s1:" << s1 << endl;
	cout << "s2:" << s2 << endl;
	cout << "s3:" << s3 << endl;
	cout << "s4:" << s4 << endl;

s1:aaaaa
s2:bbbbb
s3:bbbbb
s4:aaaaaaaaaa
```
---
## 字符串数组
```
string name[5];
string name[5] = {"123","wang","li","zhang","ok"};\
```
赋值时可以缺省,缺省的项在数组中为空<br>
输出字符串数组只能用下标输出<br>
字符串数组的元素中不包括"\0"<br>

---
# new和delete关键字
`new 类型[初值];`<br>
new 数组时不能赋初值

`delete 指针变量;`  
`delete []指针变量` 对数组空间的操作  

---
# 