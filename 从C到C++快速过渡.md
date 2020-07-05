by noname-pika
### C++编译环境
* 编译源文件，生成二进制的目标文件(.obj)
  * g++ -cfile.cpp  ==>  file.obj ; a.out(输出型文件)  
    (UNIX下编译，win用DOS窗口进行此编译)  
  * g++ -std=c++17 -cfile.cpp -oprog  ==>  file.obj ; prog.out  
    (用指定标准进行编译...prog:生成的文件的名字)  

* 链接目标文件，生成可执行文件(.exe)
    * g++ -o prog file1.obj file2.obj ......  
> MinGW:g++的windows平台移植版本 
> Online C++ Compiler:(用谷歌搜索)在线编译平台

==推荐使用IDB集成开发环境：CB(Code::Blocks);VS(Visual Studio)==
### C标准库的C++移植
* C++中包含了C标准库的移植版本  
* C标准库的头文件 x.h 基本上变成了 cx
> stdio.h => cstdio  
> math.h => cmath
> string.h => cstring  
> ...
也有例外：malloc.h就没变
### 条件编译
**不是条件语句**
 #if 0 ...... #endif  
 #if 1 ...... #else ...... #endif
 #if 1 ...... #elif ...... #elif ...... #endif
 > #表示预处理，处理完了再交给编译器编译
 > o舍1用  

 #ifdef xxx ...... #endif
 #ifdef xxx ...... #else ......#endif
 >ifdef表示如果前面宏定义了xxx即执行语句
 ### C++标准输入/输出
 ### 名字空间
 ``` 
  #include <iostream>
  int main ()
  {
      std::cout << "holle world";
      return 0;
  }
 ```
C++看作一个数据流向外部设备输入/输出
* 包含头文件 iostream
* cout是一个标准输出流对象，代表控制台窗口
* <<是运算符，假如o是输出流对象，x是数据，即可 o << x

C++调用的库多，使用名字空间限定以防止名字冲突  
就像现实中同名的情况：计算机::张伟 机械::张伟
* 加上std::以标明
* 函数体前加上 using std::cout; 提前对cout进行说明
* 函数体前加上 using namespace std; 引入整个名字空间
```
#include <iostream>
using std::cout;
using namespace std;
int main(){...}
```
> cout:标准输出流  
> <<输出符号  
> cin:标准输入流  
> \>>输入符号  
```
int a;   std::cin >> a;   std::cout << a;
//类似于
int a;   scanf("%d", &a);   printf("%d", a);
```
### 文件输入/输出流
```
#include <fstream>
using namespace std;
int main()
{
    ofstream oF("text.txt");
    oF << "hello world!" << endl;
    //创建文件并将字符串写入到文件
    ifstream iF("text.txt");
    string str;
    iF >> str;
    //找到文件并将字符串从文件中写到变量
    return 0;
}
```
* 头文件fstream
* 定义文件输入流 ifstream
* 定义文件输出流 ofstream
### 引用变量
* 引用变量是其他变量的别名  
* 定义引用变量时必须指明引用的是哪一个变量
> int a = 3;
> int &r = a;
* 引用变量“从一而终”，一旦定义不能再定义
> int &r = a;
> int &r = b;(x)
* 引用变量和被引用的变量类型必须匹配
> double a;
> int &r = a;(x)
* 对引用变量的操作就是对被引用变量的操作
### 函数的形参
* 值形参：形参作为函数的局部变量有自己单独的内存块，当函数调用时，实参将值赋值给形参。对形参的改变不会影响实参
* 指针形参：传递地址，从地址层面由形参改变实参，事实上，是直接对实参进行了操作
* **引用形参**：定义引用变量，从而引用实参，对引用形参的操作就是对实参的操作(C++特有)
```
void swap(int &a,int &b)
{
    int c;
    c = a;a = b;b = c;
}
int main()
{
    int a = 1, b = 2;
    swap(a,b);
}
```
### 函数的默认形参
* 函数的形参可以有默认值
> void print(char ch,int n=1);
* 默认形参必须在非默认形参右边，即一律靠右
> add(x, y=1, z=2);
> add(x=1, y, z=2);(x)
### 函数重载
* C++允许同一作用域内有同名的函数，只要他们的形参不同
> int add(int x);
> int add(double x);
> 可以同时存在
* 函数名和形参列表构造了**函数签名**
* 函数重载**不**能根据返回类型区分函数
> int add(int x);
> double add(int x);
> 这样不被允许
### 函数模板
* 通用模板：函数模板。也称为泛型算法
```
int add(int x,int y)
{
    return x+y;
}
double add(double x,double y)
{
    return x+y;
}
```
复制粘贴形成的，对于不同的情况要做不同的修改，不方便使用，所以C++对此有所改进
* 用template关键字增加一个模板头，将数据类型变成**类型模板参数**
```
template<typename T>
T add(T x, T y)
{
    return x+y;
}
```
T是模板头，这样定义的只是一个模板不是函数，运用时，将模板实例化，产生所需函数
```
int main()
{
    ...
    cout << add<int>(5, 3) << endl;
    cout << add<double>(5.3, 7.8) << endl;
    ...
}
```
这样就产生了所需的int add(int x,int y){...};和double add(double x,double y){...};  
而且只要保证模板的正确性
* 模板参数可自动推断，部分数据类型，编译器可以自己推断，省略类型也是允许的
```
int main()
{
    ...
    cout << add(5, 3) << endl;
    cout << add(5.3, 7.8) << endl;
    ...
}//等价于上一段代码
```
### 用户定义类型string和vector
##### string
* 是一个用户定义类型，表示字符串
> string s = "hello", s2("world");(两种定义方法)
* 用成员访问运算符点 . 访问string类的成员
> cout << s.size() << endl;
> string s3 = s.substr(1, 3);
> cout << s3 << endl;
* 用运算符对string对象进行运算，如+、[]
> +号进行字符串的拼接
>> string s = "123" + "456";

> []号类似于数组，对字符串进行取值
>> char s0 = s[4];
##### vector
C里一般的数组是静态数组，内存一旦分配即大小固定，而C++提供了新的一种类似于数组的数据类型vector
* 与上述的string有些类似，类似的原理，类似的对成员操作
* 向量，类似于数组，但可以动态增长。头文件<vector>
* 是一个类模板，实例化产生一个类，如:vector<int>产生一个数据元素是int的vector<int>类(向量)
* 同样，可以通过vector<int>类对象去访问其成员，如成员函数
```
#include <iostream>
#include <vector>
using namespace std;
int main()
{
	vector<int> v = {1, 2, 3};        //定义一个int类v
	v.push_back(4);                   //在末尾加上一个元素4
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	v.pop_back();                     //删去最后一个元素
	return 0;
}
```
### 动态内存分配
静态变量存放在内存的堆栈区，而内存里有堆存储区，由所有程序共享，动态分配内存即向堆存储区申请内存
* malloc/calloc：C里常用的一种内存分配函数
* **new**：C++新增的一种内存分配函数
> int *p = new int;//向内存申请一块int大小的内存
> int *p = new int[n];//向内存申请n块int大小的内存

申请的内存无用后记得要释放
* free：C里常用的一种内存释放函数
* **delete**：C++新增的一种内存释放函数
> delete p;
```
#include <iostream>
using namespace std;
int main()
{
	int* p = new int;
	*p = 1;
	cout << *p << endl;
	delete p;
	p = new int[4];
	for (int i = 0; i < 4; i++) 	p[i] = i;
	delete p;
	return 0;
}
```
### 类和对象
