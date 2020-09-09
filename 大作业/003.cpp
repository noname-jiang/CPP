/*
1、实验目的
   掌握顺序栈的操作方法，并能够利用顺序栈解决实际问题。
2、实验内容
（1）顺序栈的定义
（2）栈操作，包括入栈、出栈、取栈顶元素
（3）匹配判断函数
（4）主程序
3、具体方法
算术表达式中右括号和左括号匹配的次序正好符合后到括号要最先被匹配的“后进先出”堆栈操作特点，
因此可以借用一个堆栈来进行判断。
⑴    顺序扫描算术表达式（表现为一个字符串）；
⑵    当遇到三种类型的左括号时，让该括号进栈；
⑶    当遇到某一种类型的右括号时，比较当前栈顶括号是否与之匹配，
⑷    若匹配则退栈，转(1)继续进行判断；
⑸    若不匹配，则左右括号配对次序不正确，结束。
⑹    若字符串当前为某一类型的右括号而堆栈为空，则右括号多于左括号，结束。
⑺    若字符串扫描结束而堆栈非空，则左括号多于右括号，结束。
⑻    若字符串扫描结束而堆栈为空，则左右括号匹配正确，结束。
4、测试
输入：( [ ] ( ) )
输出：YES
输入：[ ( [ ] [ ] ) ]
输出：YES
输入：4+(2+8)*[5/(9-7)]
输出：YES
输入：( ( ) ]
输出：NO
输入：2+[(2+8*30)/4-)]
输出：NO

实验步骤
1.顺序栈结构体定义
2. InitStack函数
3. IsEmpty函数
4. push、pop和GetTop函数
5.括号匹配算法的实现
*/
#include<iostream>
using namespace std;
#define OK 1
#define ERROR 0
#define MAXSIZE 100

typedef struct {
    char* base;//栈底
    char* top;//栈顶
    int stacksize;//栈最大容量
}SqStack;

int InitStack(SqStack& S) {
	S.base = new char[MAXSIZE];//动态分配空间
	if (!S.base)
		return ERROR;
	S.top = S.base; //把栈置空
	S.stacksize = MAXSIZE;
	return OK;
}

int IsEmpty(SqStack S) {//栈为空返回1，不为空返回0
	if (S.base == S.top)
		return OK;
	return ERROR;
}

int Push(SqStack& S, char e) {//入栈
	if (S.top - S.base == S.stacksize)
		return ERROR; //栈满
	*(S.top++) = e; //元素e压入栈顶，栈顶指针加1
	return OK;
}

int Pop(SqStack& S) {//出栈，单纯的减一栈的存储空间
	char e{};
	if (S.base == S.top)
		return ERROR;//栈空
	e = *(--S.top); //栈顶指针减1，将栈顶元素赋给e
	return OK;
}

char GetTop(SqStack S) {//返回S的栈顶元素
	if (S.top != S.base) //栈非空
		return *(S.top - 1); //返回栈顶元素的值，栈顶指针不变
}

int Matching(SqStack& S) {//匹配表达式括号
	//表达式以“#”结束
	char ch{};
	char x{};
	char ch1{};
	int flag = 1;
	cin >> ch;
	while (ch != '#' && flag) //假设表达式以“#”结尾
	{
		switch (ch) {
		case '[':
		case '(':
		case '{':
			Push(S, ch);
			break;
		case ')':
			if (GetTop(S) == '(')
				Pop(S);
			else
				flag = 0;
			break;
		case ']':
			if (GetTop(S) == '[')
				Pop(S);
			else
				flag = 0;
			break;
		case '}':
			if (GetTop(S) == '{')
				Pop(S);
			else
				flag = 0;
			break;
		}
		cin >> ch;
	}
	if (flag) {
		return OK;
	}
	else {
		return ERROR;
	}
}

int main() {
	SqStack S{};
	if (!InitStack(S)) {
		cout << "顺序栈初始化失败";
	}
	cout << "请输入待匹配的表达式，以“#”结束：" << endl;
	if ( Matching( S ) )
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
	return 0;
}
