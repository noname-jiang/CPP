
//编写一个程序，要求用户输入小时数和分钟数。
//在main()函数中，将这两个值传递给一个void函数，后者以下面这样的格式显示这两个值
//Enter the number of hours:9
//Enter the number of minutes:28
//Time:9:28
#include<iostream>
using namespace std;

void print(int a, int b)
{
	cout << "Time:" << a << ":" << b;
}

int main()
{
	int num1{}, num2{};
	cout << "Enter the number of hours:";
	cin >> num1;
	cout << "Enter the number of minutes:";
	cin >> num2;
	print(num1, num2);
	return 0;
}
