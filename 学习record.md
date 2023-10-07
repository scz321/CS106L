# 前言

本人笔记都是以Q&A的形式记录，旨在：

- 引导思考
- 真实记录思考过程

git push前：

```
git config --global http.proxy
git config --global https.proxy 
git config --global --unset http.proxy
git config --global --unset https.proxy

(windows需要管理员权限)

如果上面的方法不行，可以试下面的方法（同样需要管理员权限）
git config --global http.sslVerify false
git config --global https.sslVerify false
```

```
git push github_remote thread:thread --force
```

token:

```
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
```

###### 

# Learning part	

## stream

### cin/cout

#### <</>>返回值

- 下面这段程序，为什么不仅Here is text followed by a number:可以被输出，31415也可以？

```
cout << "Here is text followed by a number: " << 31415 << endl;
```

> 在C++中，`<<` 流插入运算符的返回值确实是它的左操作数，也就是说，它返回了一个对应的输出流对象。这允许我们==链式地==使用多个 `<<` 运算符。
>
> 对于一个运算符来说，应当关注下面三个方面的内容：
>
> - 优先级
> - 结合性
> - ==返回值==

#### 错误处理

- 下面这段程序：当我输入S后，输出myInteger为0，这是为什么?

  ```cpp
  #include <iostream>
  using namespace std;
  int main() {
  	cout << "Please enter an integer: ";
  	int myInteger=90;
  	cin >> myInteger; // Value stored in myInteger
  	cout<<"myInteger:"<<myInteger<<endl;
  	return 0;
  }
  ```

  

  > (ChatGPT)当你尝试使用 `cin >> myInteger;` 从标准输入读取一个整数，但实际上输入了一个非整数字符（例如"S"），`cin` 会进入一个"失败"状态。在这种失败状态下，它不会修改 `myInteger` 的值。但由于你已经初始化 `myInteger` 为90，所以你可能期望看到90作为输出。
  >
  > 然而，这里的关键是当 `cin` 进入失败状态时，它实际上会设置一些内部标志，这些标志表示输入流已经遇到了错误。在这种情况下，任何后续的输入操作都不会成功，除非你首先清除这些错误标志。
  >
  > 在你的例子中，当你输入"S"时，`cin` 进入失败状态，并设置了其内部的错误标志。由于你没有清除这些标志，所以 `myInteger` 的值不会被修改，它仍然保持其初始值90。
  >
  > 但是，你提到当你输入"S"后，输出的 `myInteger` 为0。这是因为当输入流遇到一个无效的输入（如一个字符而不是一个整数）时，它不会改变变量的值，但在某些情况下，它可能会设置变量为0。这==取决于编译器和库的实现==。
  >
  > 为了处理这种情况，你可以检查 `cin` 的状态，并在必要时清除错误标志：
  >
  > ```
  > if (cin.fail()) {
  >     cin.clear(); // clear the error flags
  >     cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
  >     cout << "Invalid input. Please enter an integer." << endl;
  > }
  > ```
  >
  > 这样，你就可以捕获并处理无效的输入，确保程序的稳健性

#### cin流提取的终止条件

- 观察下面程序及其运行结果，可以得出几个重要的cin流提取的终止条件

```cpp
#include <iostream>
using namespace std;
int main() {
	int myInteger;
	string myString;
	cin >> myInteger >> myString; // Read an integer and string from cin
	cout<<"myInteger:"<<myInteger<<endl;
	cout<<"myString:"<<myString<<endl;
	return 0;
}
```

> ![image-20230909160334164](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20230909160334164.png)
>
> ![image-20230909160401251](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20230909160401251.png)
>
> ![image-20230909160418585](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20230909160418585.png)



> In practice, ==it is not a good idea to read values directly from cin==. Unlike GetInteger and the like, cin
> does not perform any safety checking of user input and if the user does not enter valid data, cin will begin
> behaving unusually.

#### cerr vs cout

- 错误处理优先使用cerr，尤其是类似于无限，没有出口的递归这种case

>std::cerr是标准错误输出流，不需要缓存，直接显示在显示器上，而且只能显示到显示器上，即std::cerr流不能转向。
>std::cout需要缓冲区（目的是为了减少屏幕刷新次数，一次全部显示），std::cout流可以转向，例如可将cout流流向文件操作中去。
>1.区别
>cout对应于标准输出流，默认情况下是显示器。这是一个被缓冲的输出，可以被重定向。
>cerr对应标准错误流，用于显示错误消息。默认情况下被关联到标准输出流，但它不被缓冲，也就说错误消息可以直接发送到显示器，而无需等到缓冲区或者新的换行符时，才被显示。一般情况下不被重定向。
>2.为什么要用cerr
>比如，你的程序遇到调用栈用完了的威胁（无限，没有出口的递归）。
>你说，你到什么地方借内存，存放你的错误信息？
>所以有了cerr。其目的，就是在你最需要它的紧急情况下，还能得到输出功能的支持。 缓冲区的目的，就是减少刷屏的次数——比如，你的程序输出圣经中的一篇文章。不带缓冲的话，就会每写一个字母，就输出一个字母，然后刷屏。有了缓冲，你将看到若干句子“同时”就出现在了屏幕上（由内存翻新到显存，然后刷新屏幕）
>————————————————
>版权声明：本文为CSDN博主「「已注销」」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
>原文链接：https://blog.csdn.net/hyqsong/article/details/38453511

### fstream

#### 对比

> Unlike cin and cout, which are concrete stream objects, ifstream and ofstream are types.To read or write
> from a file, you will create an object of type ifstream or ofstream, much in the same way that you would
> create an object of type string to store text data or a variable of type double to hold a real number

#### 记忆

> 要知道，程序也是以自我为中心的，所以ifstream的“in”是相对于程序而言的，因此ifstream类型的对象就是从别的文件读取内容到程序中。ofstream同理

#### good practice

```
ifstream input("myfile.txt");
if(!input.is_open())
cerr << "Couldn't open the file myfile.txt" << endl;
```

#### Stream Manipulators

- 常用eg
  - setw
  - setfiill
  - hex, dec, oct

- 这个还是挺有用的，可以用来帮处理一些杂事，尤其是写文档时候的格式问题，比如写了给目录加上.........，同时保持每一行的长度一样等等类似的重复性工作

  > eg：
  >
  > 原来：
  >
  > ![image-20230909170701575](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20230909170701575.png)
  >
  > 处理后：
  >
  > ![image-20230909170717322](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20230909170717322.png)

#### good practice

替换前：

- 这里也可以学习一下fail的使用

```cpp
while(true) {
    int intValue;
    double doubleValue;
    input >> intValue >> doubleValue;
    if(input.fail()) break;
    /* ... process values here ... */
}
```

替换后：

```cpp
int intValue;
double doubleValue;
while(input >> intValue >> doubleValue) {
	/* ... process values here ... */
}
```

> 你提到cin >> a的返回值是cin对象本身，if语句的括号中应该是一个bool值，这两者是否冲突？
>
> 
>
> ChatGPT
>
> 
>
> 不冲突。虽然 `cin >> a` 返回的是 `cin` 对象本身，但 `istream` 类（`cin` 的类）重载了 `void*` 类型的==类型转换操作符==，或者在 C++11 及以后版本中，重载了 `bool` 类型的类型转换操作符。这样，`cin` 对象可以在需要布尔值的地方，如 `if` 语句的条件中被隐式转换为 `bool` 类型。

#### When Streams Do Too Much

举个栗子：

```cpp
int age;
double hourlyWage;
cout << "Please enter your age: ";
cin >> age;
cout << "Please enter your hourly wage: ";
cin >> hourlyWage;
```

输入2.1234+回车，会发生什么？

- reading directly from `cin` is unsafe and poses more problems than it solves

#### >> vs getline

- 核心区别在于终止条件不同。

  >比如，cin>>a;的终止条件是空格==或其他分隔符（例如换行符）==，而getline(cin,a)的终止条件是遇到换行

- ==getline是更契合实际读取文件的一种方式==，原因在于大部分case下我们是不希望把whitespace作为终止条件之一的。可以看看cs106L教材的例子

#### sstream

- 全称：string streams，可以用来模仿java那种字符串拼接
- 头文件: <sstream>
- stringstreams are an example of an iostream, a stream that can perform ==both== input and output

```cpp
int main()
{
	stringstream myConverter;
	int myInt;
	string myString;
	double myDouble;
	myConverter << "137 Hello 2.71828"; // Insert string data
	//myConverter >> myInt >> myString >> myDouble; // Extract mixed data---------------------   line 1
	getline(myConverter,myString);//----------------------------------------------------------   line 2
	cout<<"myInt:"<<myInt<<endl;
	cout<<"myString:"<<myString<<endl;
	
	cout<<"myDouble:"<<myDouble<<endl;

}
```

> 输出如下：
>
> ![image-20230909190502984](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20230909190502984.png)

> 对比line1和line2作用下的输出结果，可以进一步加深上一小节的知识

#### formatting

- 解释原因：内存中，int型数据78979871通过iostream的方式存储到一个txt文件中，其实际占用的内存由4bytes变为8bytes。

> read and write: When you write numeric data to a stream, you're actually converting them into
> sequences of characters that represent those numbers. For example, when you print out the fourbyte
> value 78979871, you're using eight bytes to represent the data on screen or in a file – one for
> each character. These extra bytes can quickly add up, and it's actually possible to have on-disk
> representations of data that are more than twice as large as the data stored in memory. To get
> around this, C++ streams let you directly write data from memory onto disk without any
> formatting. All ostreams support a write function that writes unformatted data to a stream, and
> istreams support read to read unformatted data from a stream into memory. When used well,
> these functions can cut file loading times and reduce disk space usage. For example, The
> CS106B/X Lexicon class uses read to quickly load its data file into memory



- 学了编译原理的相关知识之后对这里的理解应该更深了

> 对于下面这个简单的demo：
>
> ```cpp
> stringstream myConverter;
> myConverter << "abc 123";
> 
> string temp;
> int num;
> myConverter >> temp >> num;
> cout << temp << endl;
> cout << num << endl;
> 
> ```
>
> abc  123本质上就是一个字符串，这里使用>>流提取运算符地过程中，本质上是调用了一个类似于lexer的词法分析器，该词法分析器的终止条件是空格或者回车，使用它会根据我们预期的数据类型，使用正则表达式进行匹配。比如这里我们先预期一个string，后预期一个int





#### 综合案例------GetInteger

核心在于解决cin和getline的缺点

- cin:可能“do too much"

- cin:可能fail

- getline可以避免上述问题

- 但是，getline只能读string：

  > ![image-20230909195527516](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20230909195527516.png)

- 最终得出GetInteger的实现，（注意，这里没有给出GetLine()函数的实现

  - GetInteger预期功能：
    - 参数：输入流对象is
    - 返回：从is中读取到的整数
    - 仅以回车为终止条件，需要获得一个完整的整数，完整整数的前后允许空格存在

- ```cpp
  
  #include <iostream>
  using namespace std;
  #include <iomanip>
  #include <sstream>
  
  int GetInteger() {
  	while (true) { // Read input until user enters valid data
  		stringstream converter;
  		converter << GetLine();
  		/* Try reading an int, continue if we succeeded. */
  		int result;
  		if (converter >> result) {
  			char remaining;
  			if (converter >> remaining) // Something's left, input is invalid
  				cout << "Unexpected character: " << remaining << endl;
  			else
  				return result;
  		}
  		else
  			cout << "Please enter an integer." << endl;
  		cout << "Retry: ";
  	}
  }
  
  
  ```

  

## Multi-File Programs, Abstraction, and the Preprocessor

### 链接

- 下面的程序会在什么阶段报错：为什么？

```cpp
#include <iostream>
using namespace std;
int Factorial(int n); // Prototype for a function to compute n!
int main() {
	cout << Factorial(10) << endl;
	return 0;
}
```

### preprocess

#### #include

- 类似于#include，#define的directive都不属于c++语法，所以下面都是错误的

  ```cpp
       #include <iostream>//前面不能有空格
   cout << #include <iostream> << endl; // Error: #include must start a line.
   #include <iostream>;
   #include
  <iostream> // Error: Multi-line preprocessor directives are illegal
  ```

- 应该把他们看作一种独立于cpp的语言

```cpp
#if MY_CONSTANT > 137 // Legal
#if MY_CONSTANT * 42 == MY_CONSTANT // Legal
#if sqrt(MY_CONSTANT) < 4 // Illegal, cannot call function sqrt
#if MY_CONSTANT == 3.14 // Illegal, can only use integral values
```

#### #define

- 首先要理解，在预编译阶段的程序都是且仅是文本
- 在此基础上，由#define带来的种种tricks也就不难理解了

#### #Include Guards Explained  && #if

- 为什么存在Include Guards Explained？

- #if：

  - 格式

    ```
    #if statement
    ...
    #elif another-statement
    ...
    #elif yet-another-statement
    ...
    #else
    ...
    #endif
    ```
  
  ```cpp
  
  #if MY_CONSTANT > 137 // Legal
  #if MY_CONSTANT * 42 == MY_CONSTANT // Legal
  #if sqrt(MY_CONSTANT) < 4 // Illegal, cannot call function sqrt
  #if MY_CONSTANT == 3.14 // Illegal, can only use integral values
  ```
  
  - 可以和defined结合使用
  
    eg:
  
    ```cpp
    #if defined(A)
    cout << "A is defined." << endl;
    #elif defined(B)
    cout << "B is defined." << endl;
    #elif defined(C)
    cout << "C is defined." << endl;
    #else
    cout << "None of A, B, or C is defined." << endl;
    #endif
    ```



#### 综合app

- 确保一个头文件即使被include多次，保证其中的变量声明且仅声明一次：

```cpp
#ifndef MyStruct_Included
#define MyStruct_Included
struct MyStruct {
	int x;
	double y;
	char z;
};
#endif
```

- 注意，这里是须要#endif的，其实也是理所当然的

#### Macros

- 标准用法：

  ```
  #define macroname(parameter1, parameter2, ... , parameterN) macro-body*
  ```

- 准则：凡是变量能用括号括起来就括，防止运算优先级等问题产生



#### preprocessor预置变量

- eg

```
void test0() {
	cout << "This program was compiled on " << __DATE__ << " at time " << __TIME__ << endl;
	cout << "file info:" << __FILE__ << endl;
	cout << "line info:" << __LINE__ << endl;
}
```

![image-20230910135724780](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20230910135724780.png)



#### #define vs 函数

- 和preprocessor directives结合，可以做到一些c++函数无法实现的功能：

```
#define DECLARE_MY_VAR(type) type my_##type
DECLARE_MY_VAR(int);
```

## STL

### Sequence Containers

#### STL总览

> The STL is logically divided into six pieces, each consisting of generic components that interoperate with
> the rest of the library:
> • Containers. At the heart of the STL are a collection of container classes, standard C++'s analog to
> the CS106B/X ADTs. For example, you can store an associative collection of key/value pairs in an
> STL map, or a growing list of elements in an STL vector.
> • Iterators. Each STL container exports iterators, objects that view and modify ranges of stored
> data. Iterators have a common interface, allowing you to write code that operates on data stored
> in arbitrary containers.
> • Algorithms. STL algorithms are functions that operate over ranges of data specified by iterators.
> The scope of the STL algorithms is staggering – there are algorithms for searching, sorting,
> reordering, permuting, creating, and destroying sets of data.
>
> • Adapters. STL adapters are objects which transform an object from one form into another. For
> example, the stack adapter transforms a regular vector or list into a LIFO container, while the
> istream_iterator transforms a standard C++ stream into an STL iterator.
> • Functors. Because so much of the STL relies on user-defined callback functions, the STL provides
> facilities for creating and modifying functions at runtime. We will defer our discussion of functors
> to much later in this text, as they require a fairly nuanced understanding of C++.
> • Allocators. The STL allows clients of the container classes to customize how memory is allocated
> and deallocated, either for diagnostic or performance reasons. While allocators are fascinating
> and certainly worthy of discussion, they are beyond the scope of this text and we will not cover
> them here.
>
> ![image-20230910165424256](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20230910165424256.png)

### Associative Containers

- 着重了解这个“关联型容器”，之前了解不深
- set
  - insert
  - count(不是find)
  - erase

> There is a tension here between what the code accomplishes and the way in which it accomplishes it. The reason for this is that we're using the ==wrong abstraction==.

### iterator

- background：对于vector/deque，我们可以通过类似数组索引的方式来对其中的element进行traverse，但是对于set不可以

- 这就是Abstraction的魅力了：Iterators provide a clean, consistent mechanism for accessing data stored
  in containers, ==irrespective of== how that data may be stored

- 请明确说出一个container的end()函数的返回值

- more:`std::set` 在 C++ 中是一个有序集合，它会==自动按照元素的值进行排序==。由于 `std::set` 是基于红黑树实现的，所以它的元素总是按照升序排序。
  - 基于其内部实现，我们可以得知，在不考虑运算符重载的前提下，set仅支持比较运算符生效的8中基本数据类型。

- ->相比于.的优势：

  ```cpp
  for (set<string>::iterator itr = mySet.begin(); itr != mySet.end(); ++itr)
      cout << *itr.length() << endl; // Error: Incorrect syntax!
  	cout <<(*itr).length << endl;// right
  
  for (set<string>::iterator itr = mySet.begin(); itr != mySet.end(); ++itr)
  	cout << itr->length() << endl;
  ```


- 不同类型迭代器

  > ![image-20230911225859115](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20230911225859115.png)

### map

#### 与pair的关系：

- 一个map对象可以视为许多个pair的集合

- 所以pair的api适用于map中的一个element，例如make_pair就经常被用到

  ```
  numberMap.insert(make_pair("zero", 0));
  map<string, int>::iterator itr = myMap.begin(); itr != myMap.end(); ++itr)
  		cout << itr->first << ": " << itr->second << endl
  ```

  

#### 与vector的对比：

> Indexing into a map into a nonexistent key implicitly creates a key/value pair.

- 解释，下面程序的输出为什么是0？

  ```cpp
  int main() {
  	
  	map<string, int> test;
  	cout << test["test"] << endl;
  	return 0;
  }
  ```

#### 基于此，输出map[key]的good practice：

```cpp
map<string, int>::iterator itr = numberMap.find("key");
if (itr == numberMap.end())
	cout << "Key does not exist." << endl;
else
    cout << numberMap["key"] <<endl;
	/* ... */
```

- map iterators are slightly more complicated because they dereference to a ==key/value pair==----------`pair<const KeyType, ValueType>`

#### insert

> 和使用中括号进行插入不同，instert不支持更新已经存在的key对应的value

- 基于此，insert设计其返回值为：pair<`iterator`, bool>

- good practice：

  ```cpp
  /* Try to insert normally. */
  pair<map<string, int>::iterator, bool> result = myMap.insert(make_pair("STL", 137));
  /* If insertion failed, manually set the value. */
  if(!result.second)
  	result.first->second = 137;
  ```



### 综合案例——关键字数量统计

[代码实现](https://github.com/scz321/CS106L/blob/main/practicalDemo/practicalDemo/keyWordsCount.hpp)

- 自顶向下开发，先确定好有哪些函数，在一步步实现这些函数

- 了解cctype

  > `<cctype>` 头文件包含了一系列的函数，用于字符的属性检测和转换。下面是这个头文件中的一些常用函数：
  >
  > 1. **属性检测**:
  >    - `isalpha()`: 检测字符是否为字母 (a-z, A-Z)。
  >    - `isdigit()`: 检测字符是否为数字 (0-9)。
  >    - `isalnum()`: 检测字符是否为字母或数字。
  >    - `isspace()`: 检测字符是否为空白字符，例如空格、制表符、换行符等。
  >    - `islower()`: 检测字符是否为小写字母。
  >    - `isupper()`: 检测字符是否为大写字母。
  >    - `iscntrl()`: 检测字符是否为控制字符。
  >    - `isgraph()`: 检测字符是否有图形表示（即字符是可打印的并且不是空格）。
  >    - `isprint()`: 检测字符是否是可打印的，包括空格。
  >    - `ispunct()`: 检测字符是否为标点符号。
  >    - `isxdigit()`: 检测字符是否为十六进制数字。
  > 2. **字符转换**:
  >    - `tolower()`: 返回字符的小写形式，如果字符已经是小写或者不是字母，则返回原字符。
  >    - `toupper()`: 返回字符的大写形式，如果字符已经是大写或者不是字母，则返回原字符。

- set,map的合理使用
- sstream的妙用————一种简洁有效的逐个获取文本中所有words的方式

### DFA

- 凡是能画出状态转移图的，都大概率可以使用这种方法解决，关键在于，状态转移图不一定好画？

- app：邮箱命名格式判断

  - [代码实现](https://github.com/scz321/CS106L/blob/main/practicalDemo/practicalDemo/DFA.hpp)

  - q其核心代码相当简洁，核心是画出状态转移图，据此进行transitions的初始化，

    - 核心代码：

      ```cpp
      struct DFA {
      	map<pair<int, char>, int> transitions;
      	set<int> acceptingStates;
      	int startState;
      };
      
      bool SimulateDFA(DFA& d, string input) {
      	int currState = d.startState;
      	for (string::iterator itr = input.begin(); itr != input.end(); ++itr) {
      		cout << "当前状态转移：" << currState << "-->" << d.transitions[make_pair(currState, *itr)] << endl;;
      		currState = d.transitions[make_pair(currState, *itr)];
      		
      
      	}
      	//cout << "currState:" << currState << endl;
      	return d.acceptingStates.find(currState) != d.acceptingStates.end();
      }
      
      ```

    - 初始化：

      ```cpp
      
      //===========================下面是针对邮箱地址设置的相关内容，上面是通用设计=========
      struct DFA LoadEmailDFA() {
      	struct DFA ret;
      	ret.startState = 0;
      	ret.acceptingStates.insert(6);
      
      
      	//这里反而是最麻烦的地方hhh，打错一个地方就g
      	ret.transitions.insert(make_pair(make_pair(0,'a'),1));//注意，这里外层还需要一次make_pair
      	ret.transitions.insert(make_pair(make_pair(0, '.'), 7));
      	ret.transitions.insert(make_pair(make_pair(0, '@'), 7));
      
      	ret.transitions.insert(make_pair(make_pair(1, 'a'), 1));
      	ret.transitions.insert(make_pair(make_pair(1, '@'), 3));
      	ret.transitions.insert(make_pair(make_pair(1, '.'), 2));
      
      	ret.transitions.insert(make_pair(make_pair(2, 'a'), 1));
      	ret.transitions.insert(make_pair(make_pair(2, '@'), 7));
      	ret.transitions.insert(make_pair(make_pair(2, '.'), 7));
      
      	ret.transitions.insert(make_pair(make_pair(3, '@'), 7));
      	ret.transitions.insert(make_pair(make_pair(3, '.'), 7));
      	ret.transitions.insert(make_pair(make_pair(3, 'a'), 4));
      
      	ret.transitions.insert(make_pair(make_pair(4, '@'), 7));
      	ret.transitions.insert(make_pair(make_pair(4, '.'), 5));
      	ret.transitions.insert(make_pair(make_pair(4, 'a'), 4));
      
      	ret.transitions.insert(make_pair(make_pair(5, '@'), 7));
      	ret.transitions.insert(make_pair(make_pair(5, '.'), 7));
      	ret.transitions.insert(make_pair(make_pair(5, 'a'), 6));
      
      	ret.transitions.insert(make_pair(make_pair(6, '.'), 5));
      	ret.transitions.insert(make_pair(make_pair(6, 'a'), 6));
      	ret.transitions.insert(make_pair(make_pair(6, '@'), 7));
      
      	ret.transitions.insert(make_pair(make_pair(7, '@'), 7));
      	ret.transitions.insert(make_pair(make_pair(7, '.'), 7));
      	ret.transitions.insert(make_pair(make_pair(7, 'a'), 7));
      
      	return ret;
      }
      
      
      bool IsEmailAddress(string input) {
      	DFA emailChecker = LoadEmailDFA(); 
      	for (string::iterator itr = input.begin(); itr != input.end(); ++itr) {		
      		if (isalnum(*itr))
      			*itr = 'a';
      		else if (*itr != '.' && *itr != '@')
      			return false;
      	}
      	return SimulateDFA(emailChecker, input);
      }
      ```













### NFA

- 对它的实际应用还比较迷茫

### 花式算法

#### suffix 

- _if
  - 为什么调用IsEven时不用传递参数？解释

```
bool IsEven(int value) {
	return value % 2 == 0;
}

cout << count_if(myVec.begin(), myVec.end(), IsEven) << endl;
```

- _n
  - 

#### reorder

- 对于不支持<的数据类型，==不进行运算符重载==，同样可以调用sort：

  ```cpp
  bool ComparePlaces(placeT one, placeT two) {
      if(one.x != two.x)
          return one.x < two.x;
      return one.y < two.y;
  }
  sort(myPlaceVector.begin(), myPlaceVector.end(), ComparePlaces);
  ```

- sort的第三个是函数参数，默认是使得结果升序，这里可以做文章

#### Searching Algorithms





#### Iterator Adaptors

首先结合几个例子体会它的作用：

- ostream_iterator

```cpp
vector<int> myVector({ 1,2,3,4,5,77 });

copy(myVector.begin(), myVector.end(), ostream_iterator<int>(cout, " "));
```

- instert_iterator

```cpp
vector<int> myVector; /* Initially empty */
/* Create a back_insert_iterator that inserts values into myVector. */
back_insert_iterator< vector<int> > itr(myVector);
for (int i = 0; i < 10; ++i) {
    *itr = i; // "Write" to the back_insert_iterator, appending the value.
    ++itr;
}
/* Print the vector contents; this displays 0 1 2 3 4 5 6 7 8 9 */
copy(myVector.begin(), myVector.end(), ostream_iterator<int>(cout, " "));
```

第一个例子中体现出的adaptor的作用很明显，但是第二个看起来就有点多此一举？事实并非如此，

![image-20231004130225574](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231004130225574.png)

- 结合下面的case1和case2的运行结果即可体会iterator adptor的强大作用

```cpp
	vector<int> vec({ 1,2,3,4,5 });
	//下面把这五个元素赋值给另一个
	vector<int> dst;
	//case 1
	//copy(vec.begin(), vec.end(), dst.begin());
	
	//case 2
	back_insert_iterator<vector<int>> itr(dst);
	copy(vec.begin(), vec.end(), itr);

	//output
	copy(dst.begin(), dst.end(), ostream_iterator<int>(cout, " "));
```

> case2存在更简洁的写法：
>
> ```cpp
> copy(vec.begin(), vec.end(), back_inserter(dst));
> ```



这里背后的本质是：the line *itr = i will implicitly call myVector.push_back(i)

这也就意味着，这个back_insert_iterator仅仅对sequence container生效，对于associative container无效

solution也是有的：insert_iterator(相应的简洁写法insterter)。有一个注意点：

> ![image-20231004134559229](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231004134559229.png)

- more example:

![image-20231004135111148](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231004135111148.png)

#### Removal Algorithms

- 这就是我们热血沸腾的组合技（by remove&erase)

  ```cpp
  myVector.erase(remove(myVector.begin(), myVector.end(), 137), myVector.end());
  
  string StripPunctuation(string input) {
      input.erase(remove_if(input.begin(), input.end(), ispunct), input.end());
      return input;
  }
  ```

- remove会改变原来的container，如果不想改变，可以使用remove_copy/remove_copy_if

#### transform

- 啊？

  > ![image-20230912105653906](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20230912105653906.png)

- 呃呃，很合理啊，比如下面这个例子：

```cpp
double f(char c) {
	return toupper(c)+0.1;
}
void tempTest() {
	string input("abcdefg");
	vector<double> output;	
	transform(input.begin(), input.end(),inserter(output,output.begin()), f);
	copy(output.begin(), output.end(), ostream_iterator<double>(cout, " "));
}
```

![image-20231004142529544](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231004142529544.png)







min_element/max_element

> As with other algorithms, by default the elements are compared by <, but you can provide a binary
> comparison function to the algorithms as a final parameter to change the default comparison order.

#### 综合案例——回文字符串判定

```cpp
IsPalindrome:
bool IsPalindrome(string input) {
	input.erase(remove_if(input.begin(), input.end(), IsNotAlpha),
	input.end());
    transform(input.begin(), input.end(), input.begin(), ::toupper);
    return equal(input.begin(), input.begin() + input.size() / 2,input.rbegin());
}
```

more——回文文本判定：

```cpp
bool IsWordPalindrome(string input) {
    input.erase(remove_if(input.begin(), input.end(), IsNotAlphaOrSpace),input.end());//IsNotAlphaOrSpace可以使用<cctype>头文件的函数轻松实现
    transform(input.begin(), input.end(), input.begin(), ::toupper);
    stringstream tokenizer(input);
    vector<string> tokens;
    tokens.insert(tokens.begin(),istream_iterator<string>(tokenizer),istream_iterator<string>());
    return equal(tokens.begin(), tokens.begin() + tokens.size() / 2, tokens.rbegin());
}
```

- 主要亮点在于：`tokens.insert(tokens.begin(),istream_iterator<string>(tokenizer),istream_iterator<string>());`



### 









## template

###### 模板类接口函数实现&注意事项

- 经典错误1

```cpp
template <typename FirstType, typename SecondType> 
class MyPair {
public:
	FirstType getFirst();
	void setFirst(FirstType newValue);
	SecondType getSecond();
	void setSecond(SecondType newValue);
private:
	FirstType first;
	SecondType second;
};

FirstType MyPair::getFirst() { // Problem: Not legal syntax
	return first;
}
```

- 经典错误2--想起来了要加上template，但是把函数的prototype和implement放在了不同的文件中

  > 我认为本质原因在于，不同的源文件之间的template <typename FirstType, typename SecondType>是独立的，也就是说，a.h文件中的FirstType为int，b.h中的FirstType仍然是未知的。template的==作用域是单个源文件==
  >
  > 
  >
  > ChatGPT
  >
  > 
  >
  > 你是对的。在C++中，模板类和函数与普通的类和函数有一个重要的区别：它们不是在声明时被编译，而是在实例化时被编译。这意味着编译器只有在看到模板的实际使用（即实例化）时才会为其生成代码。
  >
  > 因为C++的==编译模型是基于单个编译单元（通常是一个`.cpp`文件及其包含的所有`.h`文件）进行编译的==，每个编译单元是独立编译的。如果模板的定义（即模板的全部代码，包括所有成员函数的实现）不在一个编译单元中被实例化，那么编译器就没有足够的信息来为这个模板生成代码。
  >
  > 这正是为什么模板的定义通常都放在头文件中，而不是`.cpp`文件中。这样，无论模板在哪个编译单元中被实例化，它的定义都是可用的，编译器都可以为它生成代码。
  >
  > 总之，由于C++的分离式编译模型和模板在实例化时才生成代码的特性，模板的定义必须对其所有的使用者都是可见的，以确保模板可以被正确编译和链接。

> 一般命名为xx.hpp

## 资源管理

- 可以再看看modern c++32讲的相关内容

### copy constructor vs assignment operator

- assignment 和 cocy的核心区别：

  > ![image-20230912185217556](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20230912185217556.png)

- 为什么要区分

  > When assigning an existing object a new value,the existing object's value ceases to be and we must make sure to ==clean up any resources== the object may have allocated before setting it to the new value.

- 它们都是基于对象进行讨论的，从这个角度来说，c++确实是一门面向对象的语言：

  ```cpp
  class MyClass {
  public:
      MyClass();
      ~MyClass();
      MyClass(const MyClass& other); // Copy constructor
      MyClass& operator = (const MyClass& other); // Assignment operator
      
      /* ... */
      
  };
  ```

- cpp默认提供的copy constructor 和assignment operator：

  > Unless you specify otherwise, C++ will automatically provide any class you write with a basic copy
  > constructor and assignment operator that invoke the copy constructors and assignment operators of all
  > the class's data members. In many cases, this is exactly what you want.

- 在某些case下，==必须弃用==默认的复制构造函数和赋值重载函数（eg：类中含有指针，复制之后，执行析构函数，将会导致对同一个内存释放两次

  - 一种方法是重写，老实人做法

  - 另一种办法:写成private hhh

  - > ![image-20230912205349959](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20230912205349959.png)

- 笑死，写成这样你就不认识了：

  ```cpp
  template <typename T> void Vector<T>::operator= (const Vector& other) {
      logicalLength = other.logicalLength;
      allocatedLength = other.allocatedLength;
      array = new T[allocatedLength];
      copy(other.begin(), other.end(), array);
  }
  ```

  换个写法：

  ```cpp
  template <typename T> 
  void Vector<T>::operator= (const Vector& other) {
      logicalLength = other.logicalLength;
      allocatedLength = other.allocatedLength;
      array = new T[allocatedLength];
      copy(other.begin(), other.end(), array);
  }
  ```

###### 人类高质量类模板

- ==人类高质量_类&结构：尤其是要记忆一些复制构造函数的写法==

  ```cpp
  MyClass::MyClass() : /* Fill in initializer list. */ {
  /* Default initialization here. */
  }
  MyClass::MyClass(const MyClass& other) {
  	copyOther(other);
  }
  MyClass& MyClass::operator =(const MyClass& other) {
  	if(this != &other) {
  		clear();
  // Note: When we cover inheritance, there's one more step here.
  		copyOther(other);
  	}
  	return *this;
  }
  MyClass::~MyClass() {
  	clear();
  }
  ```

- 深拷贝/浅拷贝问题

- 解释：为什么当你只定义了一个拷贝构造函数时，无法使用默认构造函数？

### SmartPointer

首先是类的最基本成员的定义：

mine：

```cpp
template<typename T>
class SmartPointer {
private:
	T* ptr;

public:
	SmartPointer(T* mameory);
	SmartPointer();
	SmartPointer& operator =(const SmartPoniter& other);

	T* operator ->() const;
	T* operator *() const;
};
```

correct:

```cpp
template<typename T>
class SmartPointer {
private:
	T* ptr;

public:
	explicit SmartPointer(T* mameory);
	SmartPointer();
	SmartPointer& operator =(const SmartPoniter& other);

	T& operator ->() const;
	T* operator *() const;
};
```

> 重载你函数的返回值还比较好理解，不好理解的地方在于explicit关键字的使用：
>
> Constructs a new SmartPointer that manages the resource specified as the parameter. The reference
> count is initially set to one. We will assume that the provided pointer came from a call to new. This
> function is marked explicit so that we cannot accidentally convert a regular C++ pointer to a
> SmartPointer. At first this might seem like a strange design decision, but it prevents a wide range of
> subtle bugs. For example, suppose that this constructor is not explicit and consider the following
> function:
>
> ```cpp
> void PrintString(const SmartPointer<string>& ptr) {
> 	cout << *ptr << endl;
> }
> ```
>
> This function accepts a SmartPointer by reference-to-const, then prints out the stored string. Now,
> what happens if we write the following code?
>
> ```cpp
> string* ptr = new string("Yay!");
> PrintString(ptr);
> delete ptr;
> ```
>
> The first line dynamically-allocates a string, passes it to PrintString, and finally deallocates it.
> Unfortunately, this code will almost certainly cause a runtime crash. The problem is that PrintString
> expects a SmartPointer<string> as a parameter, but we've provided a string*. C++ notices that the
> SmartPointer<string> has a ==conversion constructor== that accepts a string*, and makes a ==temporary==
> SmartPointer<string> using the pointer we passed as a parameter. This new SmartPointer starts
> tracking the pointer with a reference count of one. After the function returns, the parameter is cleaned
> up and its destructor invokes. This decrements the reference count to zero, and then deallocates the
> pointer stored in the SmartPointer. The above code then tries to delete ptr a second time, causing a
> runtime crash. To prevent this problem, we'll mark the constructor explicit, which ==makes the implicit==
> ==conversion illegal== and prevents this buggy code from compiling.

> 为什么重载运算符中，->的返回值是T&而dereferrence的返回值是T*?



- 评价为细节拉满

> 我注意到，我在类内声明时并没有明确设置返回值类型为SmartPointer<T>，为什么在类外实现时就需要？
>
> 
>
> ChatGPT
>
> 
>
> 我明白你的困惑了。在类模板中，类名后的模板参数 `<T>` 在类内部是可选的，但在类外部定义成员函数时则是必须的。这就是导致你看到这种差异的原因。
>
> 让我们详细解释一下。
>
> 1. **在类内部**：当你在类的内部声明成员函数时，编译器知道你是在为特定的模板实例 `SmartPointer<T>` 声明这些成员。所以，在返回类型或函数参数中，你可以直接使用 `SmartPointer` 而不用写 `SmartPointer<T>`。
>
>    ```
>    cppCopy codetemplate<typename T>
>    class SmartPointer {
>    public:
>        SmartPointer& operator =(const SmartPointer& other);
>    };
>    ```
>
> 2. **在类外部**：当你在类的外部定义这些成员函数时，你需要明确地告诉编译器这个成员函数是为哪个模板实例定义的。所以，你必须使用 `SmartPointer<T>`，而不能只用 `SmartPointer`。
>
>    ```
>    cppCopy codetemplate<typename T>
>    SmartPointer<T>& SmartPointer<T>::operator =(const SmartPointer& other) {
>        // ...
>    }
>    ```
>
> 这是C++模板语法的一个特性，有时会使人感到困惑，特别是对于初学者。不过一旦你理解了这一点，这个规则就变得很直观了。



### RALL & modern SmartPointer

- 智能指针的生命周期的结束伴随着其析构函数的执行，其析构函数的执行伴随着delete函数的调用，因此RAII原则得到实现

- [我的智能指针的实现](https://github.com/scz321/CS106L/blob/main/practicalDemo/practicalDemo/smartPtr.hpp)

  > 注意，我这里只是一个基本的实现，最好还应该加上get函数和reset函数。get函数的好处在于，
  >
  > - 对于我的原版智能指针来说，它的作用如下：
  >
  >   对于这种函数，原来需要一些trick才能使得myPtr表现得像是一个string（for ==semantical consisitance==)
  >
  >   > void DoSomething(string* ptr);
  >   >
  >   > 
  >   >
  >   > SmartPointer<string> myPtr(new string);
  >   >
  >   > DoSomething(&*myPtr);
  >   >
  >   > DoSomething(myPtr.operator-> ());
  >
  >   但是有了get函数，就可以直接调用以作为函数参数传入
  >
  > - 对于unique_ptr来说，其作用就更重要了，因为传入参数时会发生赋值，这会导致我们传入的指针指向的对象的资源被释放，这显然是我们不希望的

  > ![image-20230913144749258](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20230913144749258.png)



> C++11 引入了以下几种智能指针：
>
> 1. **std::unique_ptr**：它拥有其指向的对象，保证对象有且仅有一个 `unique_ptr` 指向它。当 `unique_ptr` 离开作用域或被销毁时，它所指向的对象也会被删除。
>
> 2. **std::shared_ptr**：多个 `shared_ptr` 可以指向同一个对象。每个 `shared_ptr` 都有一个引用计数，记录有多少指针指向同一个对象。当最后一个指向对象的 `shared_ptr` 被销毁时，对象也会被删除。
>
> 3. **std::weak_ptr**：它与 `shared_ptr` 一起使用，不增加引用计数。它主要用于打破潜在的循环引用问题。
>
>    `auto_ptr` 是 C++98/03 标准库中的一个早期智能指针。在很多方面，它的行为与 `unique_ptr` 相似，特别是它们都拥有对资源的独占所有权。但是，`auto_ptr` 有一些问题和局限性，这使得它在 C++11 中被废弃并由 `unique_ptr` 取代。



## error handling

- 结合代码理解这段话：

  > When this occurs, you can report the error by using the throw keyword to “throw” the exception into the ==nearest==
  > ==matching catch clause.==

```cpp
try {
// Do something
}
catch(int myInt) {
// If the code throws an int, execution continues here.
}
catch(const vector<int>& myVector) {
// Otherwise, if the code throws a vector<int>, execution resumes here.
}
catch(const string& myString) {
// Same for string
}
```

- 使用stdexcept来处理错误而不是直接将错误信息作为string传给catch的好处：

  > 1. **语义清晰**：使用特定的异常类，如`invalid_argument`，可以清晰地表达错误的原因。这使得代码的意图更明确，读者可以立即知道错误是由于传入了无效参数。
  >
  > 2. **代码结构化**：使用标准异常类，==你可以更容易地使用多个`catch`块来处理不同的异常类型。==
  >
  >    ```
  >    cppCopy codetry {
  >        // ...
  >    } catch (const std::invalid_argument& ia) {
  >        // 处理无效参数
  >    } catch (const std::out_of_range& oor) {
  >        // 处理超出范围的错误
  >    }
  >    ```
  >
  > 3. **复用性与扩展性**：你可能有很多函数都会因为类似的原因抛出异常。如果你决定在某个时刻改变如何响应这些异常（例如，记录它们、提供不同的反馈等），使用标准异常类会更容易实现。
  >
  > 4. **与标准库和第三方库的兼容性**：标准库和许多第三方库在发生错误时会抛出标准异常。因此，学习和使用它们可以使你的代码与其他代码更加一致。

- 总结：能不用就不用

  > in many cases there's a much better alternative that results in concise, readable, and thoroughly exception-safe code – object memory management.

- assert:

  > 意义在于可以在程序break down时输出错误信息，而不只是报一个programmer难以理解的错误。可以说，这是==使用cout来debug的进阶版本==。







## Generic Programming

### functor

- functor和function的核心区别
- 背景问题

> We need a way to construct a function that takes in only one parameter (the string to test), but which can be customized to accept an arbitrary maximum length. How can we do this?
>
> 一个典型的例子：count_if的第三个参数必须是一个仅接受一个参数的函数（指针）

- functor的作用

```cpp
public:
/* Accept and store an int parameter */
    explicit ShorterThan(size_t maxLength) : length(maxLength) {}
    /* Return whether the string length is less than the stored int. */
    bool operator() (const string& str) const {
        return str.length() < length;
    }
private:
	const size_t length;
};
```

然后我们的需求就被满足了：

```cpp
ShorterThan st(length);
count_if(myVector.begin(), myVector.end(), st);
```

一个更简单的写法：

```cpp
count_if(myVector.begin(), myVector.end(), ShorterThan(length));
```

这里其实不算很好理解：ShorterThan(length)和函数指针显然是不等价的。

> 在 C++ 中，functor（也被称为函数对象）是一个具有 `operator()` 的对象。由于它们是对象，所以可以拥有状态，这是它们与普通函数和函数指针的主要区别。在给出的示例中，functor `ShorterThan` 存储了一个 `length` 状态，可以在调用时使用这个状态。
>
> ### 为什么 Functor 可以替代函数指针？
>
> 在你给出的 `count_if` 示例中，functor 可以替代函数指针的原因是，C++ 的标准模板库（STL）算法是模板化的。`count_if` 函数模板不仅可以接受普通函数指针，也可以接受任何可以调用的对象，只要它们接受正确的参数并返回正确的类型。因为 `ShorterThan` 有 `operator()`，所以它是可调用的。
>
> 这种灵活性来自于 C++ 模板的特性。在编译时，编译器会为给定的参数类型生成特定的函数或类的实例。所以，无论你传递一个函数指针、lambda 表达式还是 functor，只要它是可调用的，并且满足参数和返回类型的要求，它就可以与 `count_if` 等算法一起使用。

ok,误会解除。下面的问题是，对于更普遍的case，函数（指针）和函数对象是不能混为一用的。例如：

```cpp
const double kLowerBound = 0.0;
const double kUpperBound = 1.0;
const int kNumSteps = 25;
const double kStepSize = (kUpperBound – kLowerBound) / kNumSteps;
   void TabulateFunctionValues(double function(double)) {
    for(double i = kLowerBound; i <= kUpperBound; i += kStepSize)
    cout << "f(" << i << ") = " << function(i) << endl;
}
```

这里我们就不能把functor传进去

- solution：

```cpp
template <typename UnaryFunction>
void TabulateFunctionValues(UnaryFunction function) {
    for(double i = kLowerBound; i <= kUpperBound; i += kStepSize)
    cout << "f(" << i << ") = " << function(i) << endl;
}
```

- 一个further的问题：改成这种形式之后确实是可以接受各种形式的函数对象了，但是它还能接受函数指针吗？？

- 答案是可以：

> 我不太理解这句话：==函数模板接受任何可调用的对象==
>
> 
>
> ChatGPT
>
> 
>
> 我可以更详细地解释这个概念。在 C++ 中，"可调用的对象" 是一个泛化的概念，它不仅包括函数和方法，还包括任何重载了 `operator()` 的对象（通常被称为 functor）和 lambda 表达式。
>
> ### 函数模板可以接受以下类型的可调用对象：
>
> 1. **普通函数**
>    - 这是最基本的可调用对象。例如，`void myFunction(int x)` 可以被直接调用，如 `myFunction(5)`。
> 2. **函数指针**
>    - 函数的地址可以被存储在指针变量中，并通过这个指针调用函数。
> 3. **成员函数指针**
>    - 类或结构体的成员函数的地址也可以被存储和调用，但需要一个对象实例来进行调用。
> 4. **Functor（函数对象）**
>    - 这些是重载了 `operator()` 的类或结构体的对象。它们可以像函数一样被调用。
> 5. **Lambda 表达式**
>    - 从 C++11 开始，可以在代码中直接定义匿名函数。这些也是可调用的对象。
>
> 这就是我所说的 "函数模板可以接受任何可调用的对象" 的含义。也就是说，你可以将以上任何类型的可调用对象传递给一个接受可调用对象参数的函数模板。
>
> 以下是一个例子，展示了一个函数模板是如何接受不同类型的可调用对象的：
>
> ```
> cppCopy code#include <iostream>
> #include <functional>  // 为 std::function
> 
> // 一个普通函数
> void function(int x) {
>     std::cout << "Function called with value: " << x << std::endl;
> }
> 
> // 一个 functor
> struct Functor {
>     void operator()(int x) const {
>         std::cout << "Functor called with value: " << x << std::endl;
>     }
> };
> 
> // 一个接受可调用对象的函数模板
> template <typename Callable>
> void call(int x, Callable callable) {
>     callable(x);
> }
> 
> int main() {
>     // 使用普通函数
>     call(5, function);
> 
>     // 使用 functor
>     Functor functor;
>     call(10, functor);
> 
>     // 使用 lambda 表达式
>     call(15, [](int x) {
>         std::cout << "Lambda called with value: " << x << std::endl;
>     });
> 
>     return 0;
> }
> ```
>
> 在这个例子中，`call` 函数是一个模板函数，可以接受任何类型的可调用对象——普通函数、functor 或 lambda 表达式，并且以相同的方式调用它们。希望这有助于解释和展示 "可调用对象" 的概念和灵活性。



### 再探STL algorithm

#### accumulate

定义：

```cpp
template <typename InputIterator, typename Type, typename BinaryFn>
inline Type accumulate(InputIterator start,
						InputIterator stop,
						Type accumulator,
						BinaryFn fn) {
    while(start != stop) {
        accumulator = fn(accumulator, *start);
        ++start;
    }
    return initial;
}
```

你不应该认为它仅仅是一个累加的函数，太狭隘了~：

eg:

```cpp
class LowerBoundHelper {
public:
explicit LowerBoundHelper(int lower) : lowestValue(lower) {}
int operator() (int bestSoFar, int current) {
	return current >= lowestValue && current < bestSoFar?
		current : bestSoFar;
}
private:
	const int lowestValue;
};
```

```cpp
int UnsortedLowerBound(const vector<int>& input, int lowerBound) {
    return accumulate(input.begin(), input.end(),
    numeric_limits<int>::max(),
    LowerBoundHelper(lowerBound));
}
```

![image-20231005124722644](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231005124722644.png)

#### Higher order programming

![image-20231005130248481](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231005130248481.png)

这部分内容（p397）感觉可以用functor代替，略多，暂时没有看

## modern cpp

- 那这部分内容可以说是无底洞了，课本上仅仅给出了c++0x，这里首先整理课本内容，然后结合《现代c++32讲》的内容进一步拓展

绷不住了，对面来了一对，好好好，这么玩是吧，他妈的（10.05）

- 好好好，现在也有人陪OrangeO_o一起学习了

#### lambda expression

- 示例：

![image-20231005134458228](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231005134458228.png)

这里主要涉及两个问题的理解：

- 首先是capture list：

> - 你是正确的，lambda 默认只能访问其参数列表中的参数。
> - 通过使用捕获列表，lambda 可以访问其外部作用域的局部变量。
> - Lambda 可以直接访问全局变量，无需使用捕获列表。

- 然后是整个lambda expression的返回对象

  (我们知道cpp与cool语言类似，本质上都是面向对象的语言，任何expression都会返回一个”类“)

> 我的另一个问题是，我们知道cpp是一个面向对象的语言，这里的lambda表达式整体最终返回的是一个什么类型的对象呢？
>
> 
>
> ChatGPT
>
> 
>
> 在 C++ 中，lambda 表达式实际上是一个匿名函数对象。当你声明一个 lambda 表达式时，编译器会为其生成一个未命名的、唯一的函数对象类型。因为这个类型是未命名的，所以你不能直接引用它，但你可以使用 auto 关键字来自动推断其类型。
>
> 下面的例子展示了一个 lambda 表达式的类型是如何被自动推断的：
>
> ```cpp
> #include <iostream>
> 
> int main() {
>     auto myLambda = [](int x, int y) { return x + y; };
> 
>     int result = myLambda(3, 4);
>     std::cout << "The sum is: " << result << std::endl;  // 输出：The sum is: 7
> 
>     return 0;
> }
> ```
>
> 在上面的例子中，`myLambda` 变量的类型是由编译器生成的一个特定、未命名的函数对象类型。这个类型是唯一的，并且是根据 lambda 表达式的具体形式（包括其捕获列表和参数列表）生成的。
>
> 你也可以使用 `std::function` 来存储 lambda 表达式，如果你需要的话。例如：
>
> ```cpp
> cppCopy code#include <iostream>
> #include <functional>
> 
> int main() {
>     std::function<int(int, int)> myLambda = [](int x, int y) { return x + y; };
> 
>     int result = myLambda(3, 4);
>     std::cout << "The sum is: " << result << std::endl;  // 输出：The sum is: 7
> 
>     return 0;
> }
> ```
>
> 在这个例子中，`myLambda` 的类型是 `std::function<int(int, int)>`，这是一个通用的函数对象包装器，可以存储任何可以调用的实体，其调用签名与指定的调用签名相匹配。

==每天一遍，焦虑再见。太喜欢这种，put everything aside的感觉了。==

#### move semantics

- 背景：在函数返回时，cpp会默认调用复制构造函数，这会造成毫无必要的空间浪费。

- 概念理解：左值，右值，左值引用，右值引用

评价为，gptyyds

> 我不太理解你提到的左值引用和右值引用的区别，请结合实例进行详细解释
>
> 
>
> ChatGPT
>
> 
>
> 左值和右值是 C++ 中两种基本的表达式分类。它们的区别和具体使用场景是 C++ 中较为复杂的概念。以下我将通过例子来说明它们的区别。
>
> ### 1. 左值（Lvalue）
>
> 左值是表达式的分类之一，它指的是那些有明确存储位置（例如变量）的对象。你可以把它理解为可以出现在赋值运算符左边的值。例如：
>
> ```
> cppCopy codeint a = 5; // 'a' 是左值
> a = 10;    // 'a' 可以出现在赋值运算符的左边
> ```
>
> ### 2. 右值（Rvalue）
>
> 右值是指那些不是左值的表达式的分类，通常是临时的、无法寻址的、短暂存在的值。例如：
>
> ```
> cppCopy code
> int b = a + 5; // 'a + 5' 是右值，是一个临时表达式，不能被赋值
> ```
>
> ### 3. 左值引用和右值引用
>
> 左值引用是我们常见的引用类型，它必须绑定到左值上。右值引用是 C++11 新增的类型，用于绑定到右值上，通常用于实现移动语义和完美转发等。
>
> - **左值引用示例**：
>
> ```
> cppCopy codeint a = 5;
> int &ref = a; // 左值引用绑定到左值 'a'
> ```
>
> - **右值引用示例**：
>
> ```
> cppCopy code
> int &&rref = 5 + 3; // 右值引用绑定到右值 '5+3'
> ```
>
> ### 移动语义
>
> 由于右值通常是临时对象，我们可以安全地“窃取”其资源，而不必担心之后会使用这些资源。这就是移动语义的基础。
>
> - **不使用移动语义**：
>
> ```
> cppCopy codestd::string str1 = "Hello, world!";
> std::string str2 = str1; // 这里发生了深拷贝
> ```
>
> - **使用移动语义**：
>
> ```
> cppCopy code
> std::string str3 = std::move(str1); // str3 窃取了 str1 的资源，str1 现在为空
> ```
>
> 在这个例子中，`str3` 成为了 `str1` 的资源的新所有者，避免了深拷贝，提高了程序的效率。
>
> ### 总结
>
> - **左值**：有明确存储位置的对象，可以被赋值。
> - **右值**：临时的、无法寻址的、短暂存在的值。
> - **左值引用**：绑定到左值的引用。
> - **右值引用**：绑定到右值的引用，通常用于实现移动语义。
>
> 这些概念在理解 C++ 的高级特性，如移动语义、完美转发等方面是非常关键的。希望这些例子能帮助您理解左值和右值，以及它们的引用。

- 好好好，这下不得不收集表情包了。。
- 等等，突然想到，颜文字好像也可以收集收集（doge

> 请结合实例解释cpp中的Move Semantics的概念
>
> 
>
> ChatGPT
>
> 
>
> C++的移动语义（Move Semantics）允许开发者直接移动资源（例如动态分配的内存），而不仅仅是复制资源。这在处理大对象或者资源管理对象（如智能指针、文件句柄、套接字等）时特别有用，可以大大提高程序的性能和效率。
>
> 移动语义通过引入了一个新类型的引用：右值引用（rvalue reference），用 `&&` 表示。与左值引用不同，右值引用可以绑定到将要销毁的对象，从而允许我们安全地移动它的资源。
>
> 下面的例子演示了移动语义的基本概念和用法：
>
> ```cpp
> #include <iostream>
> #include <vector>
> #include <string>
> 
> class MyString {
> public:
>     // 构造函数
>     MyString(const char* str) {
>         std::cout << "Copy data from: " << str << std::endl;
>         size_ = strlen(str);
>         data_ = new char[size_ + 1];
>         memcpy(data_, str, size_);
>         data_[size_] = '\0';
>     }
> 
>     // 拷贝构造函数
>     MyString(const MyString& other) {
>         std::cout << "Copy constructor called" << std::endl;
>         size_ = other.size_;
>         data_ = new char[size_ + 1];
>         memcpy(data_, other.data_, size_);
>         data_[size_] = '\0';
>     }
> 
>     // 移动构造函数
>     MyString(MyString&& other) noexcept {
>         std::cout << "Move constructor called" << std::endl;
>         size_ = other.size_;
>         data_ = other.data_;
>         other.size_ = 0;
>         other.data_ = nullptr;
>     }
> 
>     // 析构函数
>     ~MyString() {
>         delete[] data_;
>     }
> 
>     // 获取字符串长度
>     size_t size() const {
>         return size_;
>     }
> 
>     // 获取字符串数据
>     const char* c_str() const {
>         return data_;
>     }
> 
> private:
>     char* data_;
>     size_t size_;
> };
> 
> int main() {
>     MyString str1("Hello, world!");  // 调用构造函数
>     MyString str2 = str1;  // 调用拷贝构造函数
> 
>     MyString str3("Temporary string");
>     MyString str4 = std::move(str3);  // 调用移动构造函数
> 
>     std::cout << "str1: " << str1.c_str() << std::endl;
>     std::cout << "str2: " << str2.c_str() << std::endl;
>     std::cout << "str4: " << str4.c_str() << std::endl;
> 
>     return 0;
> }
> ```
>
> 在这个例子中，`MyString` 类有一个构造函数、一个拷贝构造函数和一个移动构造函数。拷贝构造函数用于从一个已存在的对象创建一个新的对象。移动构造函数用于从一个临时对象（或者被明确地转换为右值引用的对象）"窃取" 数据，而不进行复制。这通过转移原对象的内部资源指针实现，并将原对象的内部资源指针设置为 `nullptr`，以防止在原对象析构时释放这些资源。
>
> 在 `main()` 函数中，`str2` 是通过拷贝构造函数从 `str1` 创建的；`str4` 是通过移动构造函数从 `str3` 创建的。你可以看到，通过使用移动语义，我们可以避免不必要的数据复制，从而提高程序的性能。

然后我当时提出了一个很sb的问题：

> 对于上面的例子，我认为移动构造函数写成下面的形式会产生同样的效果： 
>
> ```
>  // 移动构造函数
>     MyString(MyString& other) noexcept {
>         std::cout << "Move constructor called" << std::endl;
>         size_ = other.size_;
>         data_ = other.data_;
>         other.size_ = 0;
>         other.data_ = nullptr;
>     }
> ```
>
> 提出这个问题说明你还没有完全理解右值引用存在的意义hhh。它就是为了与之区分，让程序明确地知道对于当前传进来的引用应该采取哪种类型的行为。

- std::move

它的出现有很现实的背景：以PA2的相关要求为例，我们调用移动构造函数时，大部分时间往往传入的仍然还是一个左值引用，那么这个时候我们就需要一个utility来起到左值向右值转换的功能，这就是std::move的作用，（其对应的头文件是ultility也就很自然了）

以前面的代码为例：

```cpp
MyString str4 = std::move(str3);  // 调用移动构造函数
```

这里涉及到一个比较重要的基础知识：上面这段程序本质上是在执行下面这段程序：（这涉及到你对于复制构造函数和赋值构造函数调用时机的理解）

```cpp
MyString str4(std::move(str3));
```

所以下面的这些case也就不难理解了(笑死，一开始忘记了这个point，人完全是懵的)

![image-20231007014324931](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231007014324931.png)

# Assignment Part

## PA1

###### std::find vs std::search

> 结合实例解释下面这段话： use std::search when looking for several elements in a row in a container, and use std::find when looking for a single element in a container).
>
> 
>
> ChatGPT
>
> 
>
> 这段话说明了在 C++ 中搜索容器中的元素时如何选择 `std::search` 和 `std::find`。当你想要在容器中查找单个元素时，你应该使用 `std::find`；当你想要查找容器中的一个子序列（即几个连续的元素）时，你应该使用 `std::search`。
>
> 以下是两个示例，分别演示了如何使用 `std::find` 和 `std::search`。
>
> ### 使用 `std::find` 查找单个元素
>
> ```cpp
> cppCopy code#include <iostream>
> #include <vector>
> #include <algorithm>
> 
> int main() {
>     std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
> 
>     // 使用 std::find 查找单个元素
>     auto it = std::find(numbers.begin(), numbers.end(), 5);
> 
>     if (it != numbers.end()) {
>         std::cout << "Found value: " << *it << std::endl;
>     } else {
>         std::cout << "Value not found" << std::endl;
>     }
> 
>     return 0;
> }
> ```
>
> 在这个例子中，我们使用 `std::find` 在 `numbers` 容器中查找值 `5`。`std::find` 返回一个迭代器，指向找到的元素，如果没有找到，则返回 `end()`。
>
> ### 使用 `std::search` 查找子序列
>
> ```cpp
> cppCopy code#include <iostream>
> #include <vector>
> #include <algorithm>
> 
> int main() {
>     std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
>     std::vector<int> pattern = {4, 5, 6};
> 
>     // 使用 std::search 查找子序列
>     auto it = std::search(numbers.begin(), numbers.end(), pattern.begin(), pattern.end());
> 
>     if (it != numbers.end()) {
>         std::cout << "Found pattern starting at index: " << std::distance(numbers.begin(), it) << std::endl;
>     } else {
>         std::cout << "Pattern not found" << std::endl;
>     }
> 
>     return 0;
> }
> ```
>
> 在这个例子中，我们使用 `std::search` 在 `numbers` 容器中查找 `pattern` 子序列。如果找到了子序列，`std::search` 返回一个迭代器，指向子序列的开始位置。
>
> 这两个例子清晰地展示了如何根据需要查找单个元素或子序列来选择使用 `std::find` 或 `std::search`。

等等，我突然发现这里的search的功能有点强大呀，它在编译器前端的应用我都不敢想啊

###### part A

- 这里有一个前提：默认html的语法都是正确的

- 初步体会search、find的强大作用

核心代码：[github链接]()

![image-20231005160316766](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231005160316766.png)

十分有九分的绷不住，对面那俩差不多得了





###### part B

- first, we need to figure out what this "intelligent way" to visit each link on a given page might be:

解决按理说不难，难在高效

核心问题：

![image-20231005161742984](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231005161742984.png)

solution：

> The intuition is that pages dealing with similar content will often have more links in common than unrelated pages.

那么自然而然就会用到优先级队列了

- 然后优先级队列的构建时，lambda expression就有用武之地了

关于lambda表达式中的capture list的细节：



> ```cpp
>     auto cmp_fn = [&w, &target_set](const vector<string>& left, const vector<string>& right) {
>         // replace all of these lines.
>         (void) w;
>         (void) target_set;
>         (void) left;
>         (void) right;
>         return false; // replace this line! make sure to use numCommonLinks.
>     };
> ```
>
> 对上面这段程序，为什么在capture list中我们要使用&w的形式而不是仅仅使用w
>
> 
>
> ChatGPT
>
> 
>
> 在这个 lambda 表达式的捕获列表中使用 `&w` 的原因是要以引用的方式捕获 `w` 变量，而不是拷贝它。如果你只使用 `w`，那么 `w` 的一个拷贝将被创建和存储在 lambda 表达式的闭包对象中，原始的 `w` 变量和 lambda 中的 `w` 变量将是两个完全独立的对象。
>
> ### 使用 `&w`（按引用捕获）
>
> ```
> cppCopy codeauto cmp_fn = [&w, &target_set](const vector<string>& left, const vector<string>& right) {
>     // 使用原始 w 变量的引用
> };
> ```
>
> 这里，`w` 是以引用的方式被捕获的，这意味着在 lambda 函数中使用的 `w` 实际上是原始 `w` 变量的引用。对 `w` 的任何修改都将影响原始的 `w` 变量。
>
> ### 使用 `w`（按值捕获）
>
> ```
> cppCopy codeauto cmp_fn = [w, target_set](const vector<string>& left, const vector<string>& right) {
>     // 使用 w 变量的一个拷贝
> };
> ```
>
> 在这种情况下，`w` 是通过值被捕获的，即创建了 `w` 的一个拷贝并存储在 lambda 表达式的闭包对象中。原始的 `w` 变量和 lambda 中的 `w` 变量是两个完全独立的对象。
>
> ### 选择哪种捕获方式
>
> 选择按值捕获还是按引用捕获，通常取决于你的具体需求：
>
> - 如果你不想在 lambda 表达式中修改外部作用域中的变量，或者你想在 lambda 生命期超出原始变量生命期的情况下继续使用这些变量（例如，在多线程中），你可能会选择按值捕获。
> - 如果你想在 lambda 中修改外部作用域中的变量，并且你确信在 lambda 的整个生命期中，这些变量都是可访问的，那么你可能会选择按引用捕获。





有点复杂就开摆？真有你的嗷

--事实证明，静心思考，step by step，everything will workout





- 拉满了：因为我们前面贪图方便使用了auto，在后面可以使用相应的decltype来获取类型。好好好，狼狈为奸。

![image-20231005195007143](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231005195007143.png)

- 细节2：我们在定义的前半部分只是传递comparison函数的type，其定义是通过构造函数传递的！

![image-20231005195155350](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231005195155350.png)

因此，正确的priority_queue的定义如下：

```cpp
    std::priority_queue<vector<string>,vector<vector<string>>,decltype(cmp_fn)> queue(cmp_fn);
```



呃呃，PA1暂时到这就结束了，后半部分由于网络原因无法进行测试。

（命令行似乎无法访问国外网站）

## PA2

- assignment中的一些重要事项

> When a user of the hashmap class tries to look up or insert a key, the HashMap class first converts the key, no matter what type it is, to an integer. I

- 核心目标不是通过test，切记

> We have implemented all of this logic for you, and we ==highly encourage you to read through the code== to understand what is happening. However, this assignment does not ask you to implement anything except some SMFs, which only deal with initializing the private member variables.

- function signature:函数声明‘

#### 源码分析

首先，最重要的部分当然是源码分析，自然是从mian函数开始：

```cpp
int main() {

    
    int answer;
    cout << "Please enter a number and then hit ENTER\n1) Milestone 1 code\n2) Milestone 2 tests" << endl;
    cin >> answer;
    if(answer == 1){
        student_main();
    } else if (answer == 2) {
        cout << ":P" << endl;
        //UNCOMMENT THIS FOR MILESTONE 2
        // run_test_harness();
    } else {
        cout << "Please run your code again and hit 1 or 2 only!";
    }
}
```

#### milestone 1

这里我们首先关注answer==1的case，此时我们跳转到student_main：

```cpp
int student_main() {
    cout << "This is student main. You can try using HashMap as a client by editing the code here!" << endl;
    HashMap<string, int> map;
    init_map(map);
    std::set<string> keys = find_keys(map);
    cout << "Find the difference in time between two lecturers! \n" <<
        "Please enter two names from this list, separated by a space. Then hit ENTER\n" << endl;
    for(auto it = keys.begin(); it != keys.end(); ++it){
        cout << *it << endl;
    }
    string name1;
    string name2;
    cin >> name1;
    cin >> name2;
    print_difference(map, name1, name2);
    //cout<<"map:"<<map<<end;
    return 0;
}
```

首先，使用默认构造函数创建了一个HashMap的实例。这里自然涉及到对HashMap结构体的解析，但是由于该结构体预计解析较长，因此单独进行讲解而不是在这里按照程序执行顺序进行解释。[点此跳转到HashMap数据结构](#HashMap解析)

然后执行init_map:

```cpp
//This will fill parameter map with lecturer -> year they lectured pairs
void init_map(HashMap<string, int>& map) {
    cout << "Hello from your past and current lecturers!" << endl;
    map.insert({"Anna", 2019});
    map.insert({"Avery", 2019});
    map.insert({"Nikhil", 2020});
    map.insert({"Ethan", 2020});
    map.insert({"Frankie", 2021});
    map.insert({"Sathya", 2021});
    //demonstrate the map in action!
    map.debug();
    map.rehash(5);
    map.debug();
}
```

呃呃，然后可以进行简单地测试：
![image-20231006193251080](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231006193251080.png)

下面开始处理mileston 1要求的const correctness的问题。

首先，根据给出的hint，阅读示例代码begin函数及其重载：

```cpp
//一个使用const的example
template <typename K, typename M, typename H>
typename HashMap<K, M, H>::iterator HashMap<K, M, H>::begin() {
    size_t index = first_not_empty_bucket();
    if (index == bucket_count()) {
        return end();
    }
    return make_iterator(_buckets_array[index]);
}

//注意函数中const关键字的使用
template <typename K, typename M, typename H>
typename HashMap<K, M, H>::const_iterator HashMap<K, M, H>::begin() const {
    // This is called the static_cast/const_cast trick, which allows us to reuse
    // the non-const version of find to implement the const version.
    // The idea is to cast this so it's pointing to a non-const HashMap, which
    // calls the overload above (and prevent infinite recursion).
    // Also note that we are calling the conversion operator in the iterator class!

    //类似于委托构造函数
    return static_cast<const_iterator>(const_cast<HashMap<K, M, H>*>(this)->begin());
}

```

这里主要涉及到cpp的一个static_cast和const_cast的trick。

- 当时，我对此感到不解：为什么一定要两个版本的begin呢？
- 事实证明（gpt证明），确实很有必要：

> ### 需要 `const` 重载版本的原因：
>
> 在 C++ 中，成员函数后面的 `const` 修饰符表示该成员函数是一个常量成员函数，它不会修改对象的状态。这意味着，在一个 `const` 成员函数内部，你不能修改对象的任何成员变量（除非这些成员变量被声明为 `mutable`），也不能调用该对象的任何非 `const` 成员函数。
>
> 为一个成员函数提供 `const` 和非 `const` 两个版本的重载，通常是为了在不同情况下提供不同的接口。`const` 成员函数可以被 `const` 对象调用，也可以被非 `const` 对象调用；但非 `const` 成员函数只能被非 `const` 对象调用。
>
> ### 示例：
>
> 考虑下面的例子：
>
> ```cpp
> const HashMap<int, std::string> constMap;
> auto it = constMap.begin();  // 这里应该调用 const 版本的 begin()
> 
> HashMap<int, std::string> nonConstMap;
> auto it2 = nonConstMap.begin();  // 这里可以调用非 const 版本的 begin()
> ```
>
> 在第一个调用中，`constMap` 是一个 `const` 对象，所以它只能调用 `const` 成员函数。如果 `HashMap` 类没有提供 `const` 版本的 `begin()`，那么这个调用就会导致编译错误。
>
> ### 分析 `const` 和非 `const` 的 `begin()` 函数：
>
> 1. 非 `const` 版本的 `begin()` 返回一个普通迭代器，该迭代器可以用来修改 `HashMap` 中的元素。
> 2. `const` 版本的 `begin()` 返回一个 `const_iterator`。`const_iterator` 是一种特殊类型的迭代器，它不允许通过迭代器修改容器中的元素。这就确保了 `const` 对象的不可变性。
>
> 在你提供的代码示例中，`const` 版本的 `begin()` 通过 `const_cast` 临时地移除了 `this` 指针的 `const` 属性，调用了非 `const` 版本的 `begin()`，然后将结果转换为 `const_iterator`。这是一种常见的技巧，可以避免代码重复。但要注意，不当使用 `const_cast` 可能会破坏对象的 `const` 约束，导致未定义行为。
>
> ### 总结
>
> 为 `begin()` 函数提供 `const` 和非 `const` 两个版本的重载是为了保证在不同的上下文中，都能以适当、安全的方式访问容器的元素，保持对象的不可变性和接口的一致性。

那么到现在为止，我们对于milestone 1给出的const correctness的要求就很明确了：想必我们只要编译不报错，就算大成功了。



- 这个trick感觉还是挺具有通用性的。

- 同时也暴露出oop的基础知识没掌握牢固qwq。const对象只能调用const函数这种知识都需要去问gpt了qwq。

- 有一说一，这个trick确实挺不错的

> 这里，`const_cast` 是用来移除 `const` 限定符的，因为我们希望调用非 `const` 版本的 `begin()` 函数。原型函数 `begin() const` 是一个 `const` 成员函数，这意味着在这个成员函数内部 `this` 指针是一个指向 `const` 对象的 `const` 指针，即 `const HashMap<K, M, H>* const` 类型。我们使用 `const_cast` 移除 `const` 限定符，将 `this` 指针转换为非 `const` 类型，即 `HashMap<K, M, H>*`，这样就可以调用非 `const` 版本的 `begin()` 函数了。
>
> 在代码
>
> ```
> 
> return static_cast<const_iterator>(const_cast<HashMap<K, M, H>*>(this)->begin());
> ```
>
> 中，
>
> 1. `const_cast<HashMap<K, M, H>*>(this)` 移除 `this` 指针的 `const` 限定符，使其能够调用非 `const` 成员函数。
> 2. `const_cast<HashMap<K, M, H>*>(this)->begin()` 在非 `const` 对象上调用非 `const` 版本的 `begin()` 函数。
> 3. `static_cast<const_iterator>(...)` 将返回的迭代器从非 `const` 迭代器转换为 `const` 迭代器。
>
> 因此，这里的 `const_cast` 正确地将 `const` 对象转换为非 `const` 对象，以便能够调用非 `const` 版本的 `begin()` 函数。



另外，你会发现这种方式修改起来并不复杂：下面这段代码只需要把最后一个find函数调用改掉就可以进行复用了

```cpp
return static_cast<const_iterator>(const_cast<HashMap<K, M, H>*>(this)->find());
```



那么下一个需要考虑的问题就是，哪些函数应该进行类似的重载呢？呃呃，看你测试程序那么长，估计凡是不会修改属性值的函数都会被重载hhh。

当然还有一个思路（doge），那就是面向报错编程（😎🤯😇🤣）

很难抵挡住后者的诱惑啊qwq





- 先浅浅测试一下面向报错编程的合理性，下面是修改前的报错情况

![image-20231006202634230](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231006202634230.png)

根据报错信息，定位到test.cpp的203行：很明显是contains不支持被const对象调用

![image-20231006202900190](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231006202900190.png)

下面按照begin的示例对contains进行修改，修改后我们会发现，error它消失了，它真的，我哭死

![image-20231006203429783](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231006203429783.png)



然后就有惊无险地拿下了捏~😤😤😤😤😤😤😤😤😤（乐，当时只是看到了PASS就以为拿下了，下面的6/8没看到吗宝子）

![image-20231006212257362](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231006212257362.png)



#### HashMap解析

>  首先要指出，源代码的注释部分已经对源码进行了详细的解释，我这下面最多只能说是对于注释的conclusion
>
> 出于简洁的考虑，我在下面的copy中删除了所有注释，==但是注释中有很多有价值的信息（比如提供了很多的usage）==，如果不熟悉还是很建议去瞅瞅

首先是三个模板参数：
* K = key type
* M = mapped type
* H = hash function type used to hash a key; if not provided, defaults to std::hash<K>

然后是几个using；结合这里的例子，对using的使用有了更深的理解!

这using关键字的作用比你想象的要大！我大胆推测，在stl中，正是我们在每一个container中都使用using封装了一个与之对应的iterator，才形成了我们对于container的一种统一的访问方式。

这里的另一个point在于，我们声明了两个iterator，具体来说，分别是：

- iterator
- const_iterator

两者的区别在于实例化时的模板参数不同，这里具体参见[HashMapIterator解析](#HashMapIterator解析)







- 然后是构造函数的声明

  - 这里，对于默认构造函数，我们使用了委托构造函数的方式（注意这里使用{}的效果和使用（）效果一样）

  ```cpp
  HashMap<K, M, H>::HashMap() : 
      HashMap{kDefaultBuckets} { }
  ```

  - 另一个值得注意的point是，对于有参构造函数，我们明确声明了explicit，==这里的explicit不是可有可无的，而是必要的！！==

> ```
> /*
> * Constructor with bucket_count and hash function as parameters.
> *
> * Creates an empty HashMap with a specified initial bucket_count and hash funciton.
> * If no hash function provided, default value of H is used.
> *
> * Usage:
> *      HashMap(10) map;
> *      HashMap map(10, [](const K& key) {return key % 10; });
> *      HashMap map{10, [](const K& key) {return key % 10; }};
> *
> * Complexity: O(B), B = number of buckets
> *
> * Notes : what is explicit? Explicit specifies that a constructor
> * cannot perform implicit conversion on the parameters, or use copy-initialization.
> * That's good, as nonsense like the following won't compile:
> *
> * HashMap<int, int> map(1.0);  // double -> int conversion not allowed.
> * HashMap<int, int> map = 1;   // copy-initialization, does not compile.
> */
> 
> 
> ```

- 然后是一些比较简单的功能函数，省略
- 然后是insert函数，这里的注意疑惑在于，它似乎没有考虑发生hash冲突的情况？

```cpp
std::pair<typename HashMap<K, M, H>::iterator, bool> HashMap<K, M, H>::insert(const value_type& value) {
    const auto& [key, mapped] = value;
    auto [prev, node_to_edit] = find_node(key);
    //这里的index似乎没有考虑发生hash冲突的情况？？
    size_t index = _hash_function(key) % bucket_count();

    if (node_to_edit != nullptr) {
        return {make_iterator(node_to_edit), false};
    }

    auto temp = new node(value, _buckets_array[index]);
    _buckets_array[index] = temp;

    ++_size;
    return {make_iterator(temp), true};
}
```

好吧，是我天真了：

> 实际上，哈希冲突在该 `insert` 函数中是被考虑的。哈希冲突是指两个或多个不同的键在哈希表中映射到同一个索引的情况。在这个 `HashMap` 的实现中，哈希冲突通过链地址法解决。让我们逐步解析代码。
>
> ```cpp
> size_t index = _hash_function(key) % bucket_count();
> ```
> 上面的代码通过哈希函数计算给定键的哈希值，并使用模运算确定该键应该插入到哪个桶（bucket）中。如果其他键也映射到这个桶中，就会发生哈希冲突。
>
> ```cpp
> auto [prev, node_to_edit] = find_node(key);
> ```
> `find_node` 函数在给定的桶中查找是否已经有与给定键相等的节点。如果有，`node_to_edit` 将是一个指向该节点的指针；否则，它将是 `nullptr`。
>
> ```cpp
> if (node_to_edit != nullptr) {
>     return {make_iterator(node_to_edit), false};
> }
> ```
> 如果 `node_to_edit` 不是 `nullptr`，这意味着给定的键已经存在于 `HashMap` 中，因此不会插入新节点，直接返回一个指向已存在节点的迭代器。
>
> ```cpp
> auto temp = new node(value, _buckets_array[index]);
> _buckets_array[index] = temp;
> ```
> 如果 `node_to_edit` 是 `nullptr`，这意味着给定的键不在 `HashMap` 中。在这种情况下，会创建一个新节点并将其插入到正确的桶中。如果该桶已经有其他节点（即发生了哈希冲突），新节点将被插入到链的开头。这里的 `_buckets_array[index]` 存储的是链表的头指针。
>
> 所以，哈希冲突实际上是通过链地址法来处理的，这是一种常用的处理哈希冲突的方法。在这种方法中，哈希表的每个桶都存储一个链表，所有映射到该桶的键都存储在这个链表中。

- 到此为止，已经对整个HashMap的运行逻辑比较清晰了（笑死，其实主要也就是看来一个insert函数及其相关函数）

```cpp


#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>             // for cout
#include <iomanip>              // for setw, setprecision, setfill, right
#include <sstream>              // for istringstream
#include "hashmap_iterator.h"
#include <vector>


template <typename K, typename M, typename H = std::hash<K>>
class HashMap {
public:
    
    using value_type = std::pair<const K, M>;
    using iterator = HashMapIterator<HashMap, false>;
    using const_iterator = HashMapIterator<HashMap, true>;
    
    friend class HashMapIterator<HashMap, false>;
    friend class HashMapIterator<HashMap, true>;


    HashMap();
    explicit HashMap(size_t bucket_count, const H& hash = H());


    ~HashMap();


    inline size_t size();
    inline bool empty();
    inline float load_factor();
    inline size_t bucket_count() const;
    bool contains(const K& key);
    M& at(const K& key);
    void clear();
    iterator find(const K& key);

    /*
    * Inserts the K/M pair into the HashMap, if the key does not already exist.
    * If the key exists, then the operation is a no-op.
    *
    * Parameters: const l-value reference to value_type (K/M pair)
    * Return value:
    *          pair<iterator, bool>, where:
    *              iterator - iterator to the value_type element with the given key
    *                         this element may have been just added, or may have already existed.
    *              bool - true if the element was successfully added,
    *                      false if the element already existed.
    *
    * Usage:
    *      HashMap<int, std::string> map;
    *      auto [iter1, insert1] = map.insert({3, "Avery"}); // inserts {3, "Avery"}, iter1 points to that element, insert1 = true
    *      auto [iter2, insert2] = map.insert({3, "Anna"});  // no-op, iter2 points to {3, "Avery"}, insert2 = false
    *
    * Complexity: O(1) amortized average case
    */
    std::pair<iterator, bool> insert(const value_type& value);

    /*
    * Erases a K/M pair (if one exists) corresponding to given key from the HashMap.
    * This is a no-op if the key does not exist.
    *
    * Parameters: const l-value reference to K, key to be removed.
    * Return value: true if K/M pair was found and removed, false if key was not found.
    *
    * Usage:
    *      map.erase(3);           // assuming K = int, erases element with key 3, returns true
    *
    * Complexity: O(1) amortized average case, O(N) worst case, N = number of elements
    *
    * Notes: a call to erase should maintain the order of existing iterators,
    * other than iterators to the erased K/M element.
    */
    bool erase(const K& key);

    /*
    * Erases the K/M pair that pos points to.
    * Behavior is undefined if pos is not a valid and dereferencable iterator.
    *
    * Parameters: const_iterator pos, iterator to element to be removed
    * Return value: the iterator immediately following pos, which may be end().
    *
    * Usage:
    *       auto iter = map.find(3);
    *       auto next = map.erase(iter);    // erases element that iter is pointing to
    *
    * Complexity: O(1) amortized average case, O(N) worst case, N = number of elements
    *
    * Notes: a call to erase should maintain the order of existing iterators,
    * other than iterators to the erased K/M element.
    */
    iterator erase(const_iterator pos);

    /*
    * Resizes the array of buckets, and rehashes all elements. new_buckets could
    * be larger than, smaller than, or equal to the original number of buckets.
    *
    * Parameters: new_buckets - the new number of buckets. Must be greater than 0.
    * Return value: none
    *
    * Usage:
    *      map.rehash(30)
    *
    * Exceptions: std::out_of_range if new_buckets = 0.
    *
    * Complexity: O(N) amortized average case, O(N^2) worst case, N = number of elements
    *
    * Notes: our minimal HashMap implementation does not support automatic rehashing, but
    * std::unordered_map will automatically rehash, even if you rehash to
    * a very small number of buckets. For this reason, std::unordered_map.rehash(0)
    * is allowed and forces an unconditional rehash. We will not require this behavior.
    * If you want, you could implement this.
    *
    * Previously, this function was part of the assignment. However, it's a fairly challenging
    * linked list problem, and students had a difficult time finding an elegant solution.
    * Instead, we will ask short answer questions on this function instead.
    */
    void rehash(size_t new_buckets);

    /*
     * Returns an iterator to the first element.
     * This overload is used when the HashMap is non-const.
     *
     * Usage:
     *      auto iter = map.begin();
     */
    iterator begin();

    /*
     * Returns a const_iterator to the first element.
     * This overload is used when the HashMap is const.
     *
     * Usage:
     *      auto iter = cmap.begin();
     */    
    const_iterator begin() const;

    /*
     * Returns an iterator to one past the last element.
     * This overload is used when the HashMap is non-const.
     *
     * Usage:
     *      while (iter != map.end()) {...}
     */
    iterator end();


    /*
    * Function that will print to std::cout the contents of the hash table as
    * linked lists, and also displays the size, number of buckets, and load factor.
    *
    * Parameters: none
    * Return value: none
    *
    * Usage:
    *      map.debug();
    *
    * Complexity: O(N), N = number of elements.
    *
    * Notes: debug will not compile if either K or V does not support operator<< for std::ostream.
    * this function will crash if your linked list logic is incorrect (eg. forgot to reset the
    * last node's next to nullptr). Check where the source of the compiler error comes from
    * before complaining to us that our starter code doesn't work!
    *
    * Tip: place map.debug() in various places in the test cases to figure out which operation
    * is failing. Super useful when we debugged our code.
    */
    void debug();

    /* EXTRA CONSTURCTORS */

    /*
     * Range constructor
     * Creates a HashMap with the elements in the range [first, last).
     *
     * Requirements: InputIt must be iterators to a container whose elements are pair<K, M>.
     *
     * Usage:
     *      std::vector<std::pair<char, int>> vec {{'a', 3}, {'b', 5}, {'c', 7}};
     *      HashMap<char, int> map{vec.begin(), vec.end()};
     *
     * Complexity: O(N), where N = std::distance(first, last);
     */
    template <typename InputIt>
    HashMap(InputIt first, InputIt last, size_t bucket_count = kDefaultBuckets, const H& hash = H());

    /*
     * Initializer list constructor
     * Creates a HashMap with the elements in the initializer list init
     *
     * Requirements: init must be an initializer_list whose elements are pair<K, M>.
     *
     * Usage:
     *      HashMap<char, int> map{{'a', 3}, {'b', 5}, {'c', 7}};
     *
     * Complexity: O(N), where N = init.size();
     *
     * Notes: you may want to do some research on initializer_lists. The most important detail you need
     * to know is that they are very limited, and have three functions: init.begin(), init.end(), and init.size().
     * There are no other ways to access the elements in an initializer_list.
     * As a result, you probably want to leverage the range constructor you wrote in the previous function!
     *
     * Also, you should check out the delegating constructor note in the .cpp file.
     */
    HashMap(std::initializer_list<value_type> init, size_t bucket_count = kDefaultBuckets, const H& hash = H());

    /*
     * Indexing operator
     * Retrieves a reference to the mapped value corresponding to this key.
     * If no such key exists, a key/mapped value pair will be added to the HashMap.
     * The mapped value will have the default value for type M.
     *
     * Usage:
     *      HashMap<int, std::string> map;
     *      map[3] = "Avery"; // creates the pair {3, "Avery"}
     *      auto name = map[3]; // name is now "Avery"
     *      auto name2 = map[4]; // creates the pair {4, ""}, name2 is now ""
     *
     * Complexity: O(1) average case amortized plus complexity of K and M's constructor
     */
    M& operator[](const K& key);

    /* Milestone 2 headers (you need to declare these) */
    // TODO: declare headers for copy constructor/assignment, move constructor/assignment

private:
    /*
    * node structure represented a node in a linked list.
    * Each node consists of a value_type (K/M pair) and a next pointer.
    *
    * This is implemented in the private section as clients should not be dealing
    * with anything related to the node struct.
    *
    * Usage;
    *      HashMap<K, M, H>::node n;
    *      n->value = {3, 4};
    *      n->next = nullptr;
    */
    struct node {
        value_type value;
        node* next;

        /*
        * Constructor with default values, so even if you forget to set next to nullptr it'll be fine.
        *
        * Usage:
        *      node* new_node = node({key, mapped}, next_ptr);
        */
        node(const value_type& value = value_type(), node* next = nullptr) :
            value(value), next(next) {}
    };

    /*
    * Type alias for a pair of node*'s.
    *
    * This is used in find_node.
    *
    * Usage:
    *      auto& [prev, curr] = node_pair{nullptr, new node()};
    */
    using node_pair = std::pair<typename HashMap::node*, typename HashMap::node*>;

    /*
    * Finds the node N with given key, and returns a node_pair consisting of
    * the node whose's next is N, and N. If node is not found, {nullptr, nullptr}
    * is returned. If node found is the first in the list, {nullptr, node} is returned.
    *
    * Example given list: front -> [A] -> [B] -> [C] -> /
    * where A, B, C, D are pointers, then
    *
    * find_node(A_key) = {nullptr, A}
    * find_node(B_key) = {A, B}
    * find_node(C_key) = {B, C}
    * find_node(D_key) = {nullptr, nullptr}
    *
    * Usage:
    *      auto& [prev, curr] = find_node(3);
    *      if (prev == nullptr) { ... }
    *
    * Complexity: O(1) amortized average case, O(N) worst case, N = number of elements
    *
    * Notes: this function is necessary because when erasing, we need to change the
    * next pointer of the node before the one we are erasing.
    *
    * Hint: on the assignment, you should NOT need to call this function.
    */
    node_pair find_node(const K& key) const;

    /*
    * Finds the first bucket in _buckets_array that is non-empty.
    *
    * Hint: on the assignment, you should NOT need to call this function.
    */
    size_t first_not_empty_bucket() const;

    /*
    * Creates an iterator that points to the element curr->value.
    *
    * Hint: on the assignment, you should NOT need to call this function.
    */
    iterator make_iterator(node* curr);

    /* Private member variables */

    /*
    * instance variable: _size, the number of elements, which are K/M pairs.
    * Don't confuse this with the number of buckets!
    */
    size_t _size;

    /*
    * instance variable: _hash_function, a function (K -> size_t) that is used
    * to hash K's to determine which bucket they should be inserted/found.
    *
    * Remember to mod the output of _hash_function by _bucket_count!
    *
    * Usage:
    *      K element = // something;
    *      size_t index = _hash_function(element) % _bucket_count;
    *
    */
    H _hash_function;
    //咱就是说还是得把握好分寸
    /*
    * The array (vector) of buckets. Each bucket is a linked list,
    * and the item stored in the bucket is the front pointer of that linked list.
    *
    * Usage:
    *      node* ptr = _buckets_array[index];          // _buckets_array is array of node*
    *      const auto& [key, mapped] = ptr->value;     // each node* contains a value that is a pair
    */
    std::vector<node*> _buckets_array;

    /*
    * A constant for the default number of buckets for the default constructor.
    */
    static const size_t kDefaultBuckets = 10;

    /*
     * A private type alias used by the iterator class so it can traverse
     * the buckets.
     */
    using bucket_array_type = decltype(_buckets_array);

};

/*
* Ask compiler to put the template implementation here.
*/
#include "hashmap.cpp"

#endif // HASHMAP_H

```



#### HashMapIterator解析

首先给出去除注释后的源码（类似于前面的HashMap，这里源码的注释同样十分详细，足以你彻底理解代码）

```cpp
template <typename Map, bool IsConst = true>
class HashMapIterator {

public:
 
    using value_type        =   std::conditional_t<IsConst, const typename Map::value_type, typename Map::value_type>;


  
    using iterator_category =   std::forward_iterator_tag;
    using difference_type   =   std::ptrdiff_t;
    using pointer           =   value_type*;
    using reference         =   value_type&;

    friend Map;
    friend HashMapIterator<Map, true>;
    friend HashMapIterator<Map, false>;

    operator HashMapIterator<Map, true>() const {
        return HashMapIterator<Map, true>(_buckets_array, _node, _bucket);
    }

 
    reference operator*() const;
    pointer operator->() const;

    HashMapIterator<Map, IsConst>& operator++();
    HashMapIterator<Map, IsConst> operator++(int);

    template <typename Map_, bool IsConst_>
    friend bool operator==(const HashMapIterator<Map_, IsConst_>& lhs, const HashMapIterator<Map_, IsConst_>& rhs);

    template <typename Map_, bool IsConst_>
    friend bool operator!=(const HashMapIterator<Map_, IsConst_>& lhs, const HashMapIterator<Map_, IsConst_>& rhs);

    HashMapIterator(const HashMapIterator<Map, IsConst>& rhs) = default;
    HashMapIterator<Map, IsConst>& operator=(const HashMapIterator<Map, IsConst>& rhs) = default;

    HashMapIterator(HashMapIterator<Map, IsConst>&& rhs) = default;
    HashMapIterator<Map, IsConst>& operator=(HashMapIterator<Map, IsConst>&& rhs) = default;

private:
    /*
     * Determines what is the type of the nodes that the HashMap is using.
     */
    using node = typename Map::node;

    /*
     * Determines what is the type of the _buckets_array that the HashMap is using.
     */
    using bucket_array_type = typename Map::bucket_array_type;

    /*
     * Instance variable: a pointer to the _buckets_array of the HashMap this iterator is for.
     */
    bucket_array_type* _buckets_array;

    /*
     * Instance variable: pointer to the node that stores the element this iterator is currently pointing to.
     */
    node* _node;

    /*
     * Instance variable: the index of the bucket that _node is in.
     */
    size_t _bucket;

    HashMapIterator(bucket_array_type* buckets_array, node* node, size_t bucket);

};
```



- 关于std::conditional_t

> std::conditional_t changes the value_type (at compile-time) to a const one if IsConst is true.

- 然后是4个using：(gpt好样的)

> 当然，下面我将详细解释每个 `using` 声明，并使用示例来说明其作用。
>
> ### 1. `using iterator_category = std::forward_iterator_tag;`
>
> 这个 `using` 声明定义了 `iterator_category` 类型，用于表示迭代器的类型。在这里，迭代器被定义为前向迭代器，意味着它可以从容器的一个元素移动到下一个元素。
>
> #### 示例：
>
> ```
> cppCopy code// 当我们有一个前向迭代器时，我们可以这样使用它：
> for(auto it = container.begin(); it != container.end(); ++it) {
>     // 访问或操作元素 *it
> }
> ```
>
> ### 2. `using difference_type = std::ptrdiff_t;`
>
> `difference_type` 用于表示两个迭代器之间的距离。这是一个有符号整数类型，通常用于表示迭代器之间的差异。
>
> #### 示例：
>
> ```
> cppCopy code// 使用 difference_type 来计算两个迭代器之间的距离
> auto it1 = container.begin();
> auto it2 = container.end();
> std::ptrdiff_t distance = it2 - it1; // 这里 distance 是 difference_type 类型
> ```
>
> ### 3. `using pointer = value_type*;`
>
> 这里的 `pointer` 类型是元素的指针类型。在这个上下文中，`value_type` 是 HashMap 中元素的类型，所以 `pointer` 是指向 HashMap 元素的指针。
>
> #### 示例：
>
> ```
> cppCopy code// 使用 pointer 类型来访问元素
> auto it = hashmap.begin();
> pointer ptr = &(*it); // 获取元素的指针
> ```
>
> ### 4. `using reference = value_type&;`
>
> `reference` 类型是 HashMap 中元素的引用类型。这使得我们可以直接访问和修改 HashMap 中的元素。
>
> #### 示例：
>
> ```
> cppCopy code// 使用 reference 类型来访问和修改元素
> auto it = hashmap.begin();
> reference ref = *it; // 获取元素的引用
> ref = newValue; // 修改元素的值
> ```
>
> 这些 `using` 声明使得 `HashMapIterator` 类型更具有可读性和可用性，它们定义了与迭代器相关的基本类型，这些类型在算法和其他与迭代器交互的场景中非常有用。

- 然后是friend class的声明，比较容易理解

- 然后是一段不太理解的代码:按照注释的说法，它可以实现从iterator到const_iterator的implicit conversion，例如：

  ```
  iterator iter = map.begin();
  const_iterator c_iter = iter;    // implicit conversion
  ```

```
  operator HashMapIterator<Map, true>() const {
        return HashMapIterator<Map, true>(_buckets_array, _node, _bucket);
    }
```

这里主要涉及到一个类型转换操作符的概念：

> 类型转换操作符是类成员函数的一种，用于将类类型的对象转换为其他类型。其基本语法规则如下：
>
> ### 语法
>
> ```
> cppCopy code
> operator TypeName() const;
> ```
>
> 其中:
>
> - `operator`: 关键字，用于定义类型转换操作符。
> - `TypeName`: 要转换的目标类型的名称。
> - `const`: (可选) 如果类型转换操作符不修改调用它的对象，则应将其声明为 const 成员函数。
>
> ### 注意事项
>
> 1. **无参数**：类型转换操作符不应有参数。
> 2. **无返回类型**：不需要（也不允许）指定返回类型，目标类型是通过操作符后面的类型名来指定的。
> 3. **必须是成员函数**：类型转换操作符必须是类的成员函数，不能是全局函数。
>
> ### 示例
>
> ```cpp
> #include <iostream>
> 
> class Meter {
> private:
>     float distance;
>     
> public:
>     // 构造函数，用于初始化 Meter 对象
>     Meter(float m) : distance(m) {}
> 
>     // 类型转换操作符，将 Meter 对象转换为 float
>     operator float() const {
>         return distance;
>     }
> };
> 
> int main() {
>     Meter m(5.0);  // 创建一个表示 5 米的 Meter 对象
>     
>     float dist = m;  // 使用类型转换操作符将 Meter 对象隐式转换为 float
>     std::cout << "Distance: " << dist << " meters" << std::endl;  // 输出：Distance: 5 meters
>     
>     return 0;
> }
> ```

然后就很好理解前面的代码了。

> 小积累，结构化绑定：
> 这个示例中的用法利用了 C++17 引入的结构化绑定（structured bindings）特性。结构化绑定允许你将一个结构体、类、数组或者元组中的多个成员一次性解包到多个变量中。
>
> 在示例 `auto [key, value] = *iter;` 中，假设 `iter` 是一个指向 `std::pair` 的迭代器（比如一个 `std::map` 或者本示例中的 `HashMap` 的迭代器），通过解引用 `*iter` 我们得到一个 `std::pair` 对象。通过结构化绑定，我们可以将这个 `pair` 的 `first` 和 `second` 成员分别赋给 `key` 和 `value` 变量。
>
> 下面是一个完整示例以帮助理解：
>
> ```cpp
> #include <iostream>
> #include <map>
> 
> int main() {
>     std::map<int, std::string> myMap;
>     myMap[1] = "one";
>     myMap[2] = "two";
>     myMap[3] = "three";
> 
>     for (const auto& iter : myMap) {
>         // 使用结构化绑定获取键和值
>         auto [key, value] = iter;
>         std::cout << "Key: " << key << ", Value: " << value << std::endl;
>     }
> 
>     return 0;
> }
> ```
>
> 在这个例子中，我们有一个 `std::map` 对象，其中存储了整数键和字符串值。我们使用范围基础的 `for` 循环遍历 `map`，并用结构化绑定 `auto [key, value] = iter;` 来解包每个 `std::pair` 元素的键和值。然后我们可以直接使用 `key` 和 `value` 变量。
>
> 这种结构化绑定的特性在处理成对数据或者需要将对象的成员解包到单独变量时非常有用。

- 然后是*和->的操作符重载：（这里直接给出定义）这里主要是理解_node的作用

```cpp
typename HashMapIterator<Map, IsConst>::reference HashMapIterator<Map, IsConst>::operator*() const {
    return _node->value; // _node can't be nullptr - that would be dereferencing end()
}

template <typename Map, bool IsConst>
typename HashMapIterator<Map, IsConst>::pointer HashMapIterator<Map, IsConst>::operator->() const {
    return &(_node->value); // _node can't be nullptr - that would be dereferencing end()
}
```

> 小积累，关于前置递增、后置递增运算符的重载：
>
> 为什么在参数列表中加了int就表示后置递增？我不太理解？
>
> 
>
> ChatGPT
>
> 
>
> 在 C++ 中，前置和后置递增/递减运算符的区别是通过==function signature==来区分的。为了区分它们，后置版本接受一个额外的 `int` 参数。这个 `int` 参数没有实际的意义和用途，它仅仅是一个占位符，用于在编译时区分前置和后置运算符。
>
> ### 例子：
>
> ```
> // 前置递增
> T& operator++();
> 
> // 后置递增
> T operator++(int);
> ```
>
> 在后置递增/递减中，我们不需要实际传递任何值给这个 `int` 参数。这个 `int` 参数纯粹是为了在编译时产生一个不同的函数签名，从而区分前置和后置版本。

- 然后是==和！=运算符的重载，这俩原来的代码没有实现，应该是我的work

- 然后是许多和HashMap结构体相关的private变量+相应的构造函数，这部分主要涉及[HashMap解析](#HashMap解析)

  - 这里值得一提的是，HashMapIterator的构造函数被设置成了`private`,其原因如下：

  >     /*
  >      * Private constructor for a HashMapIterator.
  >      * Friend classes can access the private members of class it is friends with, 
  >      * so HashMap is able to call HashMapIterator's private constructor 
  >      * (e.g, in begin()). We want the HashMapIterator constructor to be private 
  >      * so a client can't randomly construct a HashMapIterator without asking for one 
  >      * through the HashMap's interface.
  >      */

#### milestone 2

hint中有这样一段话：

>Any ==good STL-compliant class== must have correct **special member functions.**. Recall that there are six major special member functions:
>
>- Default constructor *(implemented for you)*
>- Destructor *(implemented for you)*
>- Copy constructor
>- Copy assignment operator
>- Move constructor
>- Move assignment operator

这里涉及到一个概念：good STL-compliant class

> 一个 "good STL-compliant class" 指的是一个类，其设计和实现遵循 C++ 标准库（STL, Standard Template Library）的规范和准则。为了保证类的对象能够和 STL 容器、算法等无缝协作，必须确保这个类实现了一系列特殊的成员函数。这些成员函数包括：
>
> 1. **默认构造函数**：它可以没有任何参数，或者所有的参数都有默认值，以便可以不带任何参数地创建对象。
> 2. **析构函数**：负责在对象生命周期结束时进行清理工作，例如释放动态分配的内存等。
> 3. **拷贝构造函数**：允许以已存在的对象为模板，创建新对象的副本。
> 4. **拷贝赋值运算符**：允许将一个对象的内容赋给另一个已经存在的对象。
> 5. **移动构造函数**：允许“移动”一个对象而非复制，通常在对象内部有动态分配内存或其他资源时使用，可以提高效率。
> 6. **移动赋值运算符**：与移动构造函数类似，允许将一个对象的内容“移动”给另一个已经存在的对象。



好好好，开始还债了。之前的move semantics你因为觉得它篇幅有点长就不看是吧，现在还是得老老实实回头看了。

![image-20231006221419089](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231006221419089.png)

四个byd排好队，哥们一个一个解决：
首先是copy constructor：
下面是我一开始的写法，但是还没等测试我就意识到了不对hhh，看来看书还是挺有效果的：

```cpp
//首先是复制构造函数 --当然是要深拷贝啦
template <typename K, typename M, typename H>
HashMap<K,M,H>::HashMap(HashMap<K,M,H>& other){
    this->_size=other->_size;
    this->_hash_function=other->_hash_function;
    //你直接这样copy是会出错的！这种意识应该要有，或者说，对于copy函数，这才是你该记的
    copy(other->_buckets_array.begin(),other->_buckets_array.end(),_buckets_array.begin)
    
}
```

```cpp

//是时候展现adaptor的威力了！
    copy(other->_buckets_array.begin(),other->_buckets_array.end(),back_insert_iterator(this->_buckets_array.begin()));

```

- 好，下一步是赋值构造函数，这里我一开始还十分有逻辑地思考了一小会儿，然后突然想起来，这不是有模板的嘛hhh。理解模板，记忆模板，成为模板（doge

[模板链接](#人类高质量类模板)





好家伙，看了模板链接之后好像还是没写对qwq。

先给出我当前的move的俩函数：（仍然会报错）

```cpp
//好好好，这种活学活用的感觉好快乐！

//下面是move构造函数
template <typename K, typename M, typename H>
HashMap<K,M,H>::HashMap(HashMap<K,M,H>&& other){
    this->_size=other->_size;
    this->_hash_function=other->_hash_function;
    //你直接这样copy是会出错的！这种意识应该要有，或者说，对于copy函数，这才是你该记的
    //copy(other->_buckets_array.begin(),other->_buckets_array.end(),_buckets_array.begin)

    //是时候展现adaptor的威力了！
    copy(other->_buckets_array.begin(),other->_buckets_array.end(),back_insert_iterator(this->_buckets_array.begin()));

    //增加一个销毁步骤
    // other._size=0;
    // other._hash_function=NULL;
    // other._buckets_array.clear();
    // // 使用 shrink_to_fit() 函数释放不需要的内存
    // other._buckets_array.shrink_to_fit();
    other.clear();
}

//move赋值函数
template <typename K, typename M, typename H>
HashMap<K,M,H>& HashMap<K,M,H>::operator=(HashMap<K,M,H>&& other){
    if(other!=this){
        clear();
        this->_size=other->_size;
        this->_hash_function=other->_hash_function;
        //你直接这样copy是会出错的！这种意识应该要有，或者说，对于copy函数，这才是你该记的
        //copy(other->_buckets_array.begin(),other->_buckets_array.end(),_buckets_array.begin)

        //是时候展现adaptor的威力了！
        copy(other->_buckets_array.begin(),other->_buckets_array.end(),back_insert_iterator(this->_buckets_array.begin()));

        //增加一个销毁步骤
        //谁教你这样销毁的，笨猪
        // other._size=0;
        // other._hash_function=NULL;
        // other._buckets_array.clear();
        // // 使用 shrink_to_fit() 函数释放不需要的内存
        // other._buckets_array.shrink_to_fit();
        other.clear();

        return *this;
    }
    return *this;
}
```

你写出上面的代码只能说明你淡忘了move semantics的核心理念（想想那张图！）

---------------------------------------------

- 最难绷的一集

小小的四个函数写了有两个多小时了还没写对，这要是让你写整个HashMasp，我都不敢想你要写多久，写不对，完全写不对qwq。

-----------------

下面面临一个抉择，继续写or看参考答案qwq





好好好，结合答案，还是没写对。不过颇有收获！！

首先，在参考了网上的答案之后，我写出了如下版本的move semantics：

```cpp
template <typename K, typename M, typename H>
 HashMap<K,M,H>& HashMap<K,M,H>::operator=(HashMap<K,M,H>&& other)
 {
    if(&other==this) return *this;
    clear();
    _size=std::move(other._size);
     _hash_function = std::move(other._hash_function);
    //_buckets_array=std::move(other._buckets_array);
     _buckets_array.resize(other.bucket_count());

    other._size=0;

    return *this;
 }
```

自信满满地运行，莫名其妙地报错：
![image-20231007213232038](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231007213232038.png)

 网上的资料好像说是浮点数除以0会出现这种情况，但是经过本人的大胆推测，小心求证，推测这个错误的原因是野指针的存在。

本质原因可以参考下面这段对话：（一言以蔽之，_buckets_array中的每个元素都是一个单独的链表的头指针！都需要把头指针置为knullptr！）

> 我现在已经发现了问题所在，请你仔细阅读我之前提供给你的HashMap.h，我相信你也可以发现这里使用遍历方式的必要性
>
> 
>
> ChatGPT
>
> 
>
> 经过重新查看你提供的 `HashMap.h` 文件，我注意到这里的问题可能与 `node*` 在 `std::vector<node*>` 中的处理有关。在你的原始移动赋值操作符的实现中：
>
> ```cpp
> _buckets_array=std::move(other._buckets_array);
> ```
>
> 你是对整个 `_buckets_array` 进行了移动操作。这通常是有效的，但在这个特定情况中，由于 `std::vector<node*>` 包含的是指向节点的指针，你可能需要更明确地处理这些指针来避免潜在的问题。
>
> 在你修改后的代码中：
>
> ```cpp
> for (size_t i = 0; i < rhs.bucket_count(); i++) {
>     _buckets_array[i] = std::move(rhs._buckets_array[i]);
>     rhs._buckets_array[i] = nullptr;
> }
> ```
>
> 你显式地移动了每个 `node*` 并将它们设置为 `nullptr`。这确保了每个节点都被正确地转移，并且源 `HashMap` 不再有指向这些节点的指针。这样可以防止在 `other` 被销毁或再次使用时出现未定义的行为或错误。
>
> 所以，我认为你通过更明确地管理 `node*` 指针解决了这个问题，这是一个更安全和清晰的做法。

总之还是我太天真了，我天真地认为STL vector的move semantic可以处理所有case，所以认为一句话就够了。可以参照教材中给出的vector的参考实现

![image-20231007212928024](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231007212928024.png)





好好好，进行了进一步修改：

```cpp
template <typename K, typename M, typename H>
HashMap<K,M,H>::HashMap(HashMap<K,M,H>&& other):
_size{std::move(other._size)},
_hash_function{std::move(other._hash_function)},
_buckets_array{other.bucket_count(), nullptr}
//这里我假设了STL_vector提供了与之对应的move semantics
//楼上是小丑🤣🤣🤣
{
    _buckets_array.resize(other.bucket_count());
    for(size_t i=0;i<other.bucket_count();i++){
        _buckets_array[i]=std::move(other._buckets_array[i]);
        other._buckets_array[i]=nullptr;
    }
    other._size=0;
}


template <typename K, typename M, typename H>
 HashMap<K,M,H>& HashMap<K,M,H>::operator=(HashMap<K,M,H>&& other)
 {
    if(&other==this) return *this;
    clear();
    _size=std::move(other._size);
     _hash_function = std::move(other._hash_function);
     //下面这种方法使不得
    //_buckets_array=std::move(other._buckets_array);
    _buckets_array.resize(other.bucket_count());
    for (size_t i = 0; i < other.bucket_count(); i++) {
            _buckets_array[i] = std::move(other._buckets_array[i]);
            other._buckets_array[i] = nullptr;
        }

    other._size=0;

    return *this;
 }
// move a
```

然后...信心满满地运行，不出意外地报错🤣🤣

![image-20231007220033557](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231007220033557.png)

是你逼我的，只能使出最后一招，面向测试用例编程了。

定位到错误信息处，稍作分析（其实还分析了有一会儿hhh），即可发现问题所在！！scz真棒！

问题在于，你当时尚未领会到move operator的精髓所在！下面红框的部分是彻彻底底多余的！！

![image-20231007221410201](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231007221410201.png)

自信运行，拿下！（另，看来网上的答案也不一定全对hhh）

![image-20231007221304181](C:\Users\OrangeO_o\AppData\Roaming\Typora\typora-user-images\image-20231007221304181.png)
