# 19/1/26
## 内部类
- 在Java中,将一个类定义在另一个类或者方法中,这样的类叫做内部类.  

- 主要分为四类
>成员内部类、局部内部类、匿名内部类、静态内部类

1.成员内部类
--
(1).成员内部类是最普通的内部类，它的定义为位于另一个类的内部。<br>

(2).成员内部类可以无条件访问外部类的所有成员属性和成员方法<br>
**（包括private成员和静态成员）**。<br>

(3).当成员内部类拥有和外部类同名的成员变量或者方法时，会发生隐藏现象，即默认情况下访问的是成员内部类的成员。<br>
访问外部类的同名成员，需要以下面的形式进行访问：

>外部类.this.成员变量<br>
外部类.this.成员方法

(4).外部类想访问成员内部类的成员必须先创建一个成员内部类的对象，再通过指向这个对象的引用来访问

日后遇到其他再补充
===
----
# 19/1/27
## 参数
**方法中对参数的局部操作并不会改变参数以外实际变量的值.他只是变量值的一份拷贝.**
## 重载
- 方法签名:**方法名**及方法的**参数个数及类型**
- 方法重载:定义两个或多个名称相同的方法,方法名称相同,签名不同.
- 参数列表的**参数类型排列不同**
## 继承
- Java的类没有多继承,接口有多继承.
# 19/1/31
## super();
直接对父类对象的引用;<br>
可以直接调用父类中被子类覆盖的方法或属性;<br>
super().f();//调用父类的方法<br>
super().value;//调用父类中的属性<br>

## 构造树的继承
构造方法的第一句总是super();无论你写或不写.<br>
所以子类的构造方法总要先调用父类的构造器

## 重写和覆盖(Override)

子类用特殊的方式实现、替代父类继承给他的方法
**语法**:方法名相同、参数表相同、返回值类型相同、访问修饰符相同或更宽
**解释:**

1. 返回值类型相同(或返回子类类型):调用时父类对象的返回值类型与覆盖方法的返回值痛报错.
2. 调用父类被覆盖方法时,实际调用子类方法,若覆盖方法修饰符范围变窄,则无法访问

## 对象创建的过程

1. 分配空间
2. 构造父类对象
3. 初始化本类属性
4. 调用本类构造方法

## 访问修饰符

| 访问修饰符 | 访问范围       | 继承性           |
| :--------- | :------------- | :--------------- |
| private    | 本类内部       | 不可继承         |
| default    | 本类+同包      | 同包子类可以继承 |
| protected  | 本类+同包+子类 | 可以继承         |
| public     | 公开           | 可以继承         |

## 抽象类是否拥有对象

**抽象类存在对象**

抽象类的对象一定是某个子类的一部分,但是不允许抽象类直接new对象

```java
abstract calss A{
    int m = 10;
    public void print(){
        System.out.println(this.m);	//this表明抽象类存在对象
    }
}
```

## 接口:特殊的抽象类

### 定义

1. 属性都是公开静态常量	public static final
2. 方法都是公开抽象方法	public abstract
3. 没有构造方法

```java
abstract class ClassA{	//改造成接口
    public static final int A = 10;	//公开静态常量
    public static final int B = 1;
    public abstract void m1();		//公开抽象方法
    public abstract void m2();
    public ClassA(){};	//存在默认构造方法[.class文件大小的差别]
}

interface IA{	//接口
    public static final int A = 10;
    public static final int B = 1;
    public abstract void m1();
    public abstract void m2();
}

interface IA{	//简化
    int A = 10;
    int B = 1;
    void m1();
    void m2();
}
```

### 接口的实现

**关键字:**implements

**一个类实现接口,如果这个类不希望成为抽象类,就必须实现接口中的所有抽象方法**[什么意思哟]

```java
class Myclass implements IA{
    public void m1();
    pubilc void m2();
}
```

### 接口的多继承

```java
interface IB{
    void m3();
}

interface IC{
    void m4();
}

interface ID extends IB,IC{
    void m5();
}

abstract class ClassE{
    public abstract void m6();
}

class Myclass extends ClassE implements IA,ID{
    public void m1();	//实现IA接口
    public void m2();	//实现IA接口
    public void m3();	//实现ID接口
    public void m4();	//实现ID接口
    public void m5();	//实现ID接口
    public void m6();	//继承ClassE
}	//Myclass继承ClassE的同时实现IA接口

//以上六个类少一个,Myclass都得是抽象类
```

​	**一个类在继承另外一个类的同时,还能实现多个接口.**

### 接口的作用

- 子类可以直接复制给父类
- 父类必须强转才能赋值给子类

### 接口的回调

- 程序员负责实现接口,从而实现接口中的方法
  而不用关心方法何时被谁调用

```java
import java.util.Arrays;

public class TestHuiDiao {
    public static void main(String[] args) {
        Student[] a = new Student[]{
                new Student("alipapa",112),
                new Student("jingdong",20),
                new Student("wangboa",123)
        };
        Arrays.sort(a);
        for (int i = 0; i < 3; i++) {
            a[i].print();
        }
    }
}

class Student implements Comparable<Student>{
    String name;
    int age;
    public Student(String name,int age){
        this.age = age;
        this.name = name;
    }
    public void print(){
        System.out.println("Student Name:"+name+age);
    }

    @Override
    public int compareTo(Student o) {
        if (o.age > this.age)
            return 1;
        else if (o.age < this.age)
                return -1;
        else return 0;
    }
}

```

## 内部类

### 成员内部类

- 创建-先创建外部类对象,再通过外部类.new 内部类类名();

- 不能定义静态成员

  ```java
  class Student{
      class name{
          
      }
  }
  
  Student.name n = new Student.new name();
  或
  Student student = new Student();
  Student.name n = student.new name();
  ```

- 外部类的当前对象的引用

  **外部类类名.this**

```java
  class Student{
  private string name;		//外部类对象的属性
      class name{
          private String name;		//内部类的属性
          private String getname(){
              if("返回内部类属性") return name;
              else if("返回内部类属性") return this.name;
              else if("返回外部类") return Student.this.name;
          } 
      }
  }
```

### 局部内部类

**在方法内部定义的内部类**

```java
class Student{
    public void boyplay(){
        class shout{
            
        }
    }
}

//		class shout{}; 就是局部内部类.
```

- 作用范围:从此类的定义开始到代码块代码块结束
- 不能定义静态成员
- 局部内部类访问外部类的局部变量时,要求局部变量必须加final
- 局部内部类可以访问我外部类的私有成员

### 静态内部类

- 静态内部类的创建不在依托外部类的存在

- 只能访问外部类的静态成员

- 创建
 ```java
Outer.StaticInner in = new Outer.StaticInner();
 ```

###   匿名内部类

- 特殊的局部内部类:

  1.继承某个类或实现某个接口

  2.只会创建一个对象

  


