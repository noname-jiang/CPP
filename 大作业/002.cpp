/*重点利用附件2-6-2-12，2-17源码，建立单链表，注意单链表的结构为
typedef struct LNode //定义单链表
{
	int data;
	struct LNode* next;
} LNode, * LinkList;

输入1 3 4 7 10，能够输出
输入查找第3个位置，输出4
查找10所在位置，输出5
删除第4个位置，输出1 3 4 10
可结合课本单链表操作以及源码2-6-2-12（需要对代码进行修改）进行完善

实现有序表合并函数（2-17源码有，或教材P45页）
测试：建立两个有序表LA：1 3 4 7 10，LB： 2 6 8 9 ，输出 1 2 3 4 6 7 8 9 10
*/
#include<iostream>
#include<fstream>
using namespace std;
#define OK 1
#define ERROR 0

typedef struct LNode
{
	int data;
	struct LNode* next;
}LNode, * LinkList;

int InitList(LinkList& L)
{
	L = new LNode;
	L->next = NULL;
	return OK;
}

int InList_A(LinkList& LA) { //直接向单链表输入值
	LNode* p, * r;
	r = LA;
	int n;
	cout << "ListA:";
	while (cin >> n) {
		if (n <= 9 && n >= 0) {
			p = new LNode;
			p->data = n;
			p->next = NULL;
			r->next = p;
			r = p;
		}
		else
			return OK;
	}
}

int InList_B(LinkList& LB) { //直接向单链表输入值
	LNode* p, * r;
	r = LB;
	int n;
	cout << "ListB:";
	while (scanf_s("%d", &n)) {
		if (n <= 9 && n >= 0) {
			p = new LNode;
			p->data = n;
			p->next = NULL;
			r->next = p;
			r = p;
		}
		else
			return OK;
	}
}

void OutList_A(LinkList& LA) // 输出数据
{
	int i = 0;
	LNode* p;
	cout << "ListA:";
	p = LA->next;
	while (p) {
		if (i)
			cout << ",";
		cout << p->data;
		p = p->next;
		i = 1;
	}
}

void OutList_B(LinkList& LB) // 输出数据
{
	int i = 0;
	LNode* p;
	cout << "ListB:";
	p = LB->next;
	while (p) {
		if (i)
			cout << ",";
		cout << p->data;
		p = p->next;
		i = 1;
	}
}

void OutList_C(LinkList& LC) // 输出数据
{
	int i = 0;
	LNode* p;
	cout << "合并AB后得到ListC:";
	p = LC->next;
	while (p) {
		if (i)
			cout << ",";
		cout << p->data;
		p = p->next;
		i = 1;
	}
}

int FindList_1(LinkList &LA)         //查找单链表LA中第n个数据 
{
	int i{}, n{};
	cout << "输入需查找数据的位置：";
	scanf_s("%d", &n);
	LinkList p{};
	p = LA->next;
	for (i = 1; i < n; i++)
	{
		p = p->next;
	}
	cout << p->data;
	if (!p || i > n)
		return ERROR;
	return OK;
}

int FindList_2(LinkList& LA)
{
	int i{}, n{};
	cout << "输入需查找数据的大小：";
	scanf_s("%d", &n);
	LinkList p{};
	p = LA->next;
	for (i = 1;i < sizeof(LA); i++)
	{
		p = p->next;
		if (p->data == n) {
			cout << i+1;
			return OK;
		}
	}
	return ERROR;
}

int Delete(LinkList &LA)//删除单链表中第n个数据并输出
{
	int i{}, n{};
	cout << "输入被删除数据的位置：";
	scanf_s("%d", &n);
	LinkList p{}, q{};
	p = LA->next;
	for (i = 1; i < n-1; i++){
		p = p->next;
		if (p == NULL)
			return ERROR;
	}
	q = p->next;
	p->next = q->next;
	delete q;
	OutList_A(LA);
	return OK;
}

int CombineListAB(LinkList& LA, LinkList& LB, LinkList& LC) // 链表的合并
{
	LinkList pa, pb, pc;
	pa = LA->next;
	pb = LB->next; //pa和pb的初值分别指向两个表的第一个结点
	LC = LA; //用LA的头结点作为LC的头结点
	pc = LC; //pc的初值指向LC的头结点
	while (pa && pb) //两个表都非空
	{
		if (pa->data <= pb->data) //依次"摘取"两表中值较小的结点插入到LC表的最后
		{
			pc->next = pa; //将pa所指结点链接到pc所指结点之后
			pc = pa;
			pa = pa->next;
		}
		else {
			pc->next = pb; //将pb所指结点链接到pc所指结点之后
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb; //插入非空表的剩余段
	delete LB; //释放LB的头结点
	return OK;
}


int main()
{
	LinkList LA,LB,LC;
	int choose{};

	cout << "对单链表进行操作：" << endl << "输入数据：" << endl
		<< "********************************" << endl;
	if (!InitList(LA))
		cout << "单链表ListA初始化失败";
	InList_A(LA);
	OutList_A(LA);
	cout << endl << "1.查找相应位置的数据\n" 
		<< "2.查找相应数据的位置\n" 
		<< "3.删除相应位置的数据\n"
		<< "4.合并两表数据" << endl
		<< "********************************" << endl;
	getchar();
	scanf_s("%d", &choose);
//	cin >> choose;           //使用这个语句会自动赋值为0，原因暂未知
	switch (choose) {
	case 1: {
		if (!FindList_1(LA))
			cout << "查找失败";
	}break;
	case 2: {
		if (!FindList_2(LA))
			cout << "查找失败";
	}
	case 3:{
		if (!Delete(LA))
			cout << "删除失败";
		}break;
	case 4: {
		if (!InitList(LB))
			cout << "单链表ListB初始化失败";
		InList_B(LB);
		getchar();
		OutList_B(LB);
		cout << endl;
		if (!CombineListAB(LA, LB, LC))
			cout << "合并失败";
		OutList_C(LC);
		}break;
	}
	return 0;
}
