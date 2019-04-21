

##   构造方法:

  1)不能定义返回值类型 
  2)方法名必须和类名相同,包括大小写
  3)不能手工调用,只能在对象的创建过程中自动调用一次

## 对象的创建过程:

  1) 分配空间     属性被赋予默认值
  2) 初始化属性   属性被赋予初始值
  3) 调用构造方法 属性可以被赋予构造参数

  **如果一个类中,没有定义任何构造方法,系统会提供默认的无参的公开构造方法**

- 创建对象的语法: 

```
类名 变量名 = new 类名 (构造参数表)
```

- 访问对象的语法: 

```
变量名.属性
变量名.方法(实参列表)
```

##   引用:

对象类型的变量 (除去8种基本类型的变量,都属于引用)  存储对象的地址

  方法传递参数:基本类型的变量传值 . 对象类型的变量传地址 (实参和形参指向同一对象)

  this:引用 指向当前对象  访问类中的属性和方法,如果不加引用,默认为this引用
       用于区分成员变量和局部变量
  this():用在构造方法中,表示调用本类其他构造方法,必须是构造方法的第一条语句  

  封装  属性私有 get/set访问方法
  继承  子类 is a 父类     一般-特殊
        单继承:一个类只能有一个直接父类 类之间才能形成简单的树状结构  
      

        父类的哪些属性和方法能继承给子类? <==> 子类能访问父类的哪些属性和方法?
        
        访问修饰符        访问范围             继承性
        private           本类内部             不可继承              私有的
    (default)         本类+同包            同包子类可以继承      默认的 
        protected         本类+同包+子类       可以继承              受保护的
        public            公开                 可以继承              公开的
     
        构造方法:不可继承
    
        组合/聚合复用原则 对于违反里氏代换原则的两个类,由于不存在is a关系,所以不能定义继承,可以用组合的方式实现类的代码复用
     	
        方法覆盖 Override:子类用特殊的方法实现,替换掉父类继承给它的方法实现  
  	语法:方法名相同,参数表相同,返回值类型相同,访问修饰符相同或更宽 
             从JDK5开始,子类方法的返回值类型 可以是父类方法返回值类型的子类

     对象的创建过程:
  	1) 分配空间    
        2) 构造父类对象
  	3) 初始化本类属性    
  	4) 调用本类构造方法  

        A --- B --- C
        1)分配空间
    2)初始化A属性
    3)调用A构造方法
    4)初始化B属性
    5)调用B构造方法
        6)初始化C属性
        7)调用C构造方法     
       
     super
     super() 用在构造方法中,指明调用父类哪个构造方法 ,必须出现在构造方法的第一行
     如果一个构造方法的第一行不是super(...),也不是this(...) 默认代码为 super();
      
     super. 引用 指向父类对象
            用于访问父类被遮盖的属性
            用于调用父类被覆盖的方法

##   多态   

## 子类对象可以赋值给父类引用

​         1) 只能对引用调用其引用类型中声明的方法
​         2) 运行时,根据对象实际类型,调用子类覆盖之后的方法 
​         3) 对象类型不变 强制类型转换,用于父类引用赋值给子类引用,无法改变对象类型

       引用 instanceof 类名   "判断引用中的对象 是不是 类名"  用作在强制类型转换之前进行类型判断,避免类型转换异常
    
       多态的作用: 把不同子类的对象,统一看做是父类对象来处理.屏蔽了不同子类的差异  通用性
       多态用在参数上    m(A a):  m方法允许A类或A的某个子类对象作为实参
       多态用在返回值上  A m():   m方法返回的是A类或A的某个子类对象

--------------------------------------------------------------------------------------------------------------
  abstract
   类 : 可以声明引用 不能创建对象
   方法 : 只有声明 没有实现

   如果一个类拥有抽象方法, 这个类必须是抽象类  抽象类未必有抽象方法
   子类继承一个抽象类,如果子类不希望也成为抽象类,就必须实现父类中所有的抽象方法

  static
   属性:静态属性 全类共有 可以用类名直接访问
   方法:类名调用   静态方法中只能访问类的静态成员,不能出现this
        静态方法只能被子类的静态方法覆盖,而且没有多态  (只根据引用类型,调用相应的静态方法)
   初始代码块:静态初始代码块在类加载的时候执行
   	类加载:当JVM第一次使用一个类时,读入这个类所对应的.class文件,并保存起来
   	类加载的时机: 1)创建对象  2)加载子类,需要先加载父类  3)访问静态成员  4)Class.forName("类名")
                      如果只是声明一个类的引用,不需要类加载
   类加载的步骤:
	1)如果需要,先加载父类
	2)按顺序初始化静态属性,或执行静态初始代码块

   final
   变量:常量 一旦赋值,不可改变
        final修饰属性的时候,该属性就没有默认值,就必须手动赋值 
   方法:final方法不能被子类覆盖
   类 : final类不能被继承

   private     属性   方法    构造方法   
   (default)   属性   方法    构造方法    类
   protected   属性   方法    构造方法
   public      属性   方法    构造方法    类


   private abstract    不能联用
   final   abstract    不能联用
   static  abstract    不能联用

   接口: 特殊的抽象类
   1.属性都是公开静态常量    public static final
   2.方法都是公开抽象方法    public abstract
   3.没有构造方法

   实现接口 implements
   一个类实现接口,如果这个类不希望成为抽象类,就必须实现接口中的所有抽象方法

   接口之间可以定义多继承关系
   一个类在继承另外一个类的同时,还能实现多个接口

   子类引用可以直接赋值给父类引用
   父类引用需要强转才能赋值给子类引用
   没有继承关系的两种类型之间不能强转赋值

   强转的两种类型中,如果包含接口类型, 强转代码一定编译通过

   弱耦合性
   接口作为标准, 使接口的使用者和接口的实现者分离, 实现弱耦合关系

   接口回调:程序员负责实现接口,从而实现接口中的方法.而不用关心方法何时被谁调用


   内部类:
   成员内部类: 创建对象:先创建外部类对象, 再通过"外部类对象.new 内部类类名()" 创建内部类对象
               外部类类名.this 引用外部类的当前对象

   静态内部类:只能访问外部类的静态成员
   局部内部类:作用范围:从定义开始,到代码块结束
              局部内部类不能定义静态成员
 	      局部内部类可以访问外部类的私有成员,还能访问外部类的局部变量,但是要加final

   匿名内部类: 特殊的局部内部类
   	1.继承某个类或者实现某个接口
	2.只会创建一个对象

        new 父类名或者接口名(){继承父类或者实现接口的代码}

=========================================================================================================
Object   所有Java类的父类
    Object o = 任何对象
    Object类中的方法 是 所有对象都具有的方法

    getClass():返回对象的实际类型  Class对象(反射)
    toString(): public String toString() 
                返回对象的字符串形式  打印对象,等同于打印对象的toString()方法的返回值
    equals():判断两个对象的内容是否相同   ==:判断两个引用是否指向同一对象
             public boolean equals(Object o):   s1.equals(s2):判断s1和s2内容是否相同
    
    垃圾回收: JVM自动回收垃圾对象,释放相应的内存空间
    垃圾对象的认定: 零引用算法
    垃圾对象的回收时机:延迟回收策略 
    finalize():对象被垃圾回收的时候,由垃圾收集器自动调用

包装类: 8种基本类型的对象形式
    int      Integer
    byte     Byte
    short    Short          Number   
    float    Float
    double   Double
    long     Long
    

    char     Character
    boolean  Boolean
    
    int a --> Integer    new Integer(a)   Integer.valueOf(a)
    Integer a --> int    a.intValue()
    
    自动封箱: 由编译器完成基本类型和包装类之间的转换
    
    int a --> String     a+""    String.valueOf(a)
    String s--> int      Integer.parseInt(s)
    
    Integer a --> String  a.toString()
    String s --> Integer    new Integer(s)  Integer.valueOf(s)


String
   toCharArray():转成字符数组
   new String(char[] cs) 利用字符数组构造字符串
   toUpperCase()/toLowerCase() 大小写转换

   contains(String s):判断s子串是否存在
   startsWith(String s):判断字符串是否以s子串开头
   endsWith(String s):判断字符串是否以s子串结尾
   indexOf(String s):返回s子串最早出现的下标
   lastIndexOf(String s):返回s子串最后出现的下标
   replace(String s1 , String s2) :将s1子串替换为s2子串
   substring(int a,int b):返回字符串中a下标到b下标的子串  (包含a下标,不包含b下标)
   length():长度
   split(String s):讲字符串以s为分隔符, 拆分为多个子串
   trim():去除字符串前后的回车与空格

   字符串的内容不可变: 我们可以利用串池去共享字符串对象 
   字符串连接 : StringBuilder

=============================================================================================================
集合 : 存储多个对象

Collection:元素是Object
    常用方法:
    add(Object) 把元素添加到集合中
    addAll(Collection c):把c集合中的所有元素添加到集合中
    clear():清空集合
    contains(Object o):判断o元素在集合中是否存在
    remove(Object o):从集合中删除元素o
    size():返回集合的长度
    toArray():将集合转化为数组	

    遍历
    1.迭代器遍历  Collection   可以通过迭代器,删除集合中的元素
    2.for-each    Collection   JDK5
    3.forEach() 方法 需要实现java.util.function.Consumer接口  JDK8

List: 元素按顺序存储(下标) 元素可以重复
    常用方法:
    add(int pos, Object o):将元素插入到指定位置
    remove(int pos):删除指定位置的元素
    get(int pos):获得指定位置的元素
    indexOf(Object o):获得o元素的首下标
    lastIndexOf(Object o):获得o元素的尾下标
    set(int pos,Object o):将元素o设置到pos位置,覆盖原有的元素
    subList(int start,int end):获得某段位置的子集合

    遍历:
    1.下标遍历    List
    2.迭代器遍历  Collection   可以通过迭代器,删除集合中的元素
    3.for-each    Collection   JDK5
    4.forEach() 方法 需要实现java.util.function.Consumer接口
    
    实现类:
    1.ArrayList  数组实现  查询快 增删慢  线程不安全  并发效率高  JDK1.2
    2.Vector     数组实现                 线程安全    并发效率低  JDK1.0
    3.LinkedList 链表实现  查询慢 增删快
    
    排序: 
    Collections.sort(List) : 要求集合中的元素实现Comparable接口
    Collections.sort(List,Comparator):Comparator比较器, 实现排序逻辑 集合中的元素不需要实现Comparable接口
    list.sort(Comparator):直接对list调用sort方法排序,只能传入Comparator  JDK8

Set:元素无顺序 元素内容不可重复
    常用方法:等同于Collection接口
    遍历:
    1.迭代器遍历  Collection   可以通过迭代器,删除集合中的元素
    2.for-each    Collection   JDK5
    3.forEach() 方法 需要实现java.util.function.Consumer接口  JDK8

    实现类:
    1. HashSet : 保证内容重复对象只有一个
    1)覆盖hashCode()方法,保证相同对象返回相同的int , 尽可能保证不同对象返回不同的int
    	2)覆盖equals()方法,保证相同对象返回true
    2. LinkedHashSet  HashSet的子类, 维护元素添加到Set中的顺序
    3. TreeSet SortedSet(Set的子接口)的实现类   自动实现对元素的排序 依照排序规则判断重复对象

Queue:队列   FIFO
    常用方法:
    add()  : 添加元素
    offer(): 添加元素  优先使用
    remove():删除元素
    poll():删除元素 优先使用
    element():获取队列的头元素  
    peek():获取队列的头元素  优先使用
    实现类:
    LinkedList  ConcurrentLinkedQueue

Map : 元素是 key-value    key无顺序,不可重复   value 可重复
    常用方法:
    get(Object key) :通过key查找对应的value
    put(Object key,Object value):将key-value添加到Map中 如果key已存在,新的value覆盖旧的value
    remove(Object key):删除key所对应的key-value对
    size():长度
    containsKey(Object key): 判断key是否存在
    containsValue(Object value): 判断value是否存在
    
    遍历:
    1.keySet():Set          遍历Map中所有的key
    2.values():Collection   遍历Map中所有的value
    3.entrySet():Set Set中的元素为Map.Entry对象. 代表了一个键值对  遍历Map中的所有的键值对
    4.forEach(): 实现BiConsumer接口  直接遍历Map   JDk8
    
    实现类:
    HashMap : 依靠哈希算法保证key不重复   1.2 线程不安全 并发效率高   允许用null作为key或value
    Hashtable:                            1.0 线程安全   并发效率低  不允许用null作为key或value
    LinkedHashMap : HashMap的子类 维护元素添加到集合中的顺序
    TreeMap SortedMap(Map的子接口)的实现类 自动对key排序
    Properties Hashtable的子类 key和value都是String  通常用于配置文件的处理

  



泛型: JDK5
集合:约束集合中元素的类型

泛型没有多态, 赋值语句前后泛型必须一致
方法参数的泛型定义: 通配符 ?
? : 任何类型
? extends A: A或A的任何子类    A:可以是类 也可以是接口
? super A:A或A的父类

泛型方法: <T> 泛型定义在修饰符之后,返回值类型之前
<T extends A> T为A或A的子类
<T extends A & B> T为A或A的子类, 同时实现B接口

============================================================================================================
   try{ 
    插卡   
    输入密码和金额2000
    余额 -= 2000
    吐钱 2000
   }
   catch(吐钱异常 e){
    余额 += 2000   处理异常
   }
   finally{
    退卡
   }


异常处理
异常的分类:
    Throwable  异常的父类
       |- Error      错误  严重 不可避免 不可处理
       |- Exception  异常  可以处理
             |- RuntimeException子类    未检查异常  可以避免  可处理可不处理
             |- 非RuntimeException子类  已检查异常  不可避免  必须处理

异常的产生
     throw 异常对象     抛出一个异常 
异常的传递
     沿着方法调用链,反向传递
异常的处理
     1.声明抛出  throws
     2.捕获异常  try-catch     多个catch 先catch子类异常,再catch父类异常
                 printStackTrace():打印异常栈追踪信息
        try-catch-finally    finally: 无论如何都会执行, 通常用来释放资源
        try-finally 

方法覆盖: 子类方法不能抛出一个父类方法没有抛出的异常
          子类方法抛出异常必须是父类方法抛出的异常的  同类,子类, 不抛

============================================================================================
线程 一个程序顺序执行流程
并发原理:CPU分时间片,交替执行  宏观并行 微观串行

CPU时间片: OS负责调度
数据空间:  堆空间共享, 栈空间独立
代码:  实现Runnable接口 实现run方法 Runnable对象:任务对象    new Thread(任务对象)
       继承Thread类  覆盖run方法   

Thread.sleep() 限时等待  休眠
Thread.yield() 放弃CPU 回到就绪状态
setDaemon(true) 设置线程为守护线程,  所有的非守护线程都结束时,进程就会结束
t.join(): 当前线程进入等待状态, 直到t线程终止 才会恢复执行

当多线程共同访问同一个对象(临界资源)的时候, 如果破坏了不可分割的操作(原子操作),就可能发生数据不一致

每个Java对象都有一个互斥锁标记,用来分配给线程
synchronized(o){   ｝　对ｏ加锁的同步代码块，只有拿到ｏ的锁标记的线程，才能进入对ｏ加锁的同步代码块

synchronized 方法修饰符  对this加锁的同步代码块
只有拿到o的锁标记的线程,才能调用o的同步方法

线程通信  等待-通知
o.wait() : 必须出现在对o加锁的同步代码块  线程会释放锁标记,进入等待状态   (进入o的等待队列)
o.notify()/notifyAll() :必须出现在对o加锁的同步代码块  从等待状态中释放一个/全部线程 

JDK5
ExecutorService 线程池 线程资源共享
Calllable和Future  线程任务可以有返回值, 可以抛异常
Lock  锁对象   tryLock()方法 可以尝试拿到锁,拿不到不会阻塞
Condition 等待队列对象

ReadWriteLock 读写锁  写锁未分配时,读锁可以反复分配     读写分离
      

CopyOnWriteArrayList 利用复制数组的方式实现数组元素的修改 写效率低 读效率高 (读操作远多于写操作)
CopyOnWriteAraySet 
ConcurrentHashMap 分段锁 (1.5)   CAS(1.8)
ConcurrentLinkedQueue 线程安全的队列(链表实现)   利用无锁算法实现线程安全 CAS

BlockingQueue 阻塞队列 
     put()   添加元素到队列中 如果队列满,则等待
     take()  删除队头元素, 如果队列空,则等待
实现类:
     ArrayBlockingQueue    数组实现   有界队列    put方法可能等待     
     LinkedBlockingQueue   链表实现   无界队列    put方法不可能等待

=============================================================================================================
集合的整理
Collection
    |- List (ArrayList LinkedList Vector CopyOnWriteArrayList)
    |- Set  (HashSet LinkedHashSet CopyOnWriteArraySet)
	|- SortedSet (TreeSet)
    |- Queue(LinkedList ConcurrentLinkedQueue) 
	|- BlockingQueue (ArrayBlockingQueue  LinkedBlockingQueue) 

Map (HashMap LinkedHashMap Hashtable Properties ConcurrentHashMap )
    |- SortedMap (TreeMap)

ForkJoin 框架  分治-合并 1.7
ForkJoinPool 线程池 默认线程数:CPU核数  工作窃取算法
    RecursiveTask 覆盖 compute() 有返回值     join():以同步的方式获得返回值
    RecursiveAction 覆盖 compute() 无返回值

AtomicInteger 原子整数    CAS算法

Semaphore 信号量 
CountDownLatch 倒计数器  
CyclicBarrier 多线程汇合

=============================================================================================================
I/O
   数据方向: 输入流/输出流
   数据单位: 字节流/字符流
   流的功能: 节点流/过滤流    (节点流:完成数据读写  过滤流:为其他流增强功能)

   1.创建节点流
   2.包装过滤流
   3.读写数据
   4.关闭流

字节流:
   InputStream   字节输入流的父类  抽象类
	int read() 读一个字节 返回值:读到的字节数据  返回-1表示结束
	int read(byte[] bs):尝试读满bs数组 返回值:读到的字节个数  返回-1表示结束
	int read(byte[] bs , int start , int length):尝试读满bs数组中的一段  返回值:读到的字节个数  返回-1表示结束  

   OutputStream  字节输出流的父类  抽象类
	write(int a):      (byte)a 写一个字节	   
	write(byte[] bs):  将bs数组中所有的数据写出去
        write(byte[] bs , int start, int length):将bs数组中的一段写出去 
   FileInputStream/FileOutputStream 文件字节流   节点流
   DataInputStream/DataOutputStream 读写8种基本类型和String  过滤流
   BufferedOutputStream/BufferedInputStream 缓冲流  过滤流     flush()清空缓冲区
   ObjectOutputStreram/ObjectInputStream 读写对象  过滤流  
      通过流传输对象:对象序列化
      只有实现了Serializable接口的对象才能序列化
      用transient修饰的属性为临时属性, 不参与对象序列化

字符的编码: 字符的编码方式和解码方式不统一,可能造成乱码问题
     ASCII  美国   
     ISO-8859-1  西欧
     GB2312 简体中文   
     GBK    简体中文
     Big5   繁体中文
     Unicode 全球统一   UTF-16    UTF-8 (变长)

字符流
     Reader/Writer  字符流的父类 抽象类
     FileReader/FileWriter 文件字符流   节点流
     BufferedReader/BufferedWriter  缓冲 过滤流
                    PrintWriter 缓冲 
     InputStreamReader/OutputStreamWriter  桥转换 将字节流转换为字符流 可以指定编解码方式

File: 代表磁盘上的文件或目录
=======================================================================================================
ByteBuffer  :  ByteBuffer.allocate(容量)       ByteBuffer.wrap(byte[])
         position:当前读写位置
         limit:限制
         capacity:容量
         flip():limit=position   position = 0  从写模式 --> 读模式
         clear():position=0  limit=capacity  从读模式 --> 写模式

=========================================================================================================
网络: 若干主机(host) 客户端 服务器
IP:标识网络主机的逻辑地址 (192.168.0.1)  
端口号:标识主机中的进程  进程预先绑定唯一的端口号 监听   0-65535    0-1024(预留端口)
协议:约定 规范


应用层   HTTP FTP SMTP TELNET
传输层   TCP(面向连接 安全可靠)   UDP(无连接 不可靠)
网络层   IP  寻址 路由
网络接口 

BIO  ServerSocket               Socket
NIO  ServerSocketChannel        

=============================================================================================
反射
类对象: 记录了类的信息的对象 类加载的产物   Class类的对象

获取类对象:
1.  类名.class    int.class  double.class
2.  类的对象.getClass()  
3.  Class.forName("类的全名")   通过类名获得类对象

java.lang.reflect
Field       属性对象
Method      方法对象
Constructor 构造方法对象

getFields():获得公开属性 (包括父类) 
getDeclaredFields():获得所有属性 (只包括本类)

getMethods()或取公开方法
getDeclaredMethods():获取所有方法

getConstructors():获取公开构造方法
getDeclaredConstructors():获取所有构造方法

类对象.newInstance()  通过类对象创建类的对象
方法对象.invoke(o) 对o对象调用方法

================================================================================================
枚举:  类:拥有的对象是特定的几个值
  enum  枚举名{
	枚举值,
	枚举值,
	枚举值
  }
  访问:  枚举名.枚举值     枚举值:枚举类中的公开静态常量, 类型为枚举类型    

  Enum 默认是所有枚举的父类

标注: 描述代码的代码

 标记标注  没有属性    @标注名
 单值标注  一个属性    @标注名(属性名=属性值)   如果属性名为value @标注名(value=属性值) @标注名(属性值)
 多值标注  多个属性    @标注名(属性名1=属性值1,属性名2=属性值2 ...)           

 元标注:
 Target 描述可以为哪些程序组件添加此标注  (类 属性 构造方法 方法 ...)
 Retention 描述标注信息保留到什么时候

 属性类型: 必须是具有字面值的类型
           8种基本类型,String,Enum,Class 以及它们的数组 

============================================================================================
JDK8
接口: 允许有静态方法, 允许有默认方法 (default)
Lambda表达式: 实现接口,并创建对象 (匿名内部类的简化写法)
 (参数表)->{方法实现}
 (参数表)->表达式  等价于  return 表达式;
 (参数表)->单句实现  (return 语句不能视为单句实现)

函数式接口: 只有一个抽象方法的接口

方法引用: (S s1,Object s2)->s1.method(s2)  S::method 












​    