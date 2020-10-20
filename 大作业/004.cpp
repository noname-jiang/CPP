//实现对直接插入排序、折半插入排序、希尔排序、冒泡排序、快速排序、简单选择排序、 归并排序算法的验证
//第一步，利用程序随机生成10000个在0 - 9999之间的数字（可以考虑百度相关方法），将10000个数据保存在数组A中
//第二步，分别编写直接插入排序、折半插入排序、希尔排序、冒泡排序、快速排序、简单选择排序、 归并排序算法程序（每个算法用函数封装）
//第三步，调用每个排序方法对数组A进行排序，同时计算消耗时间，并输出（参考以往教学幻灯，或百度如何计算时间）
#include<iostream>
#include<ctime>
using namespace std;
#define NUMBER 10000

typedef struct {
	int key;
}ElemType;

typedef struct {
	ElemType* r;
	int length;
}SqList;

void show(SqList L)
{
	int i;
	for (i = 1; i <= L.length; i++)
		cout << L.r[i].key << " ";
}

//直接插入排序

double InsertSort(SqList L)  { //直接插入排序
	clock_t starttime{}, endtime{};
	int i, j;
	for (i = 2; i <= L.length; ++i)
		if (L.r[i].key < L.r[i - 1].key)
		{   										//"<"，需将r[i]插入有序子表
			L.r[0] = L.r[i];				 			//将待插入的记录暂存到监视哨中
			L.r[i] = L.r[i - 1];	            		//r[i-1]后移
			for (j = i - 2; L.r[0].key < L.r[j].key; --j)			//从后向前寻找插入位置
				L.r[j + 1] = L.r[j];					//记录逐个后移，直到找到插入位置
			L.r[j + 1] = L.r[0];						//将r[0]即原r[i]，插入到正确位置
		}
	cout << "直接插入排序为：";
	show(L);
	endtime = clock();
	return (double)(endtime - starttime) / CLOCKS_PER_SEC;
}

//折半插入排序

double BInsertSort(SqList L) {   //折半插入排序
	clock_t starttime, endtime;
	starttime = clock();
	int i, j, low, high, m;
	for (i = 2; i <= L.length; ++i)
	{
		L.r[0] = L.r[i];          					//将待插入的记录暂存到监视哨中
		low = 1; high = i - 1;        					//置查找区间初值
		while (low <= high)
		{											//在r[low..high]中折半查找插入的位置
			m = (low + high) / 2;             			//折半
			if (L.r[0].key < L.r[m].key)  high = m - 1;	//插入点在前一子表
			else  low = m + 1;					   		//插入点在后一子表
		}//while
		for (j = i - 1; j >= high + 1; --j)  L.r[j + 1] = L.r[j];	//记录后移
		L.r[high + 1] = L.r[0];							//将r[0]即原r[i]，插入到正确位置
	}
	cout << "折半排序结果为：";
	show(L);
	endtime = clock();
	return (double)(endtime - starttime) / CLOCKS_PER_SEC;
}

//希尔排序

void ShellInsert(SqList L, int dk)
{
	//对顺序表L做一趟增量是dk的希尔插入排序
	int i, j;
	for (i = dk + 1; i <= L.length; ++i)
		if (L.r[i].key < L.r[i - dk].key)
		{										//需将L.r[i]插入有序增量子表
			L.r[0] = L.r[i];						//暂存在L.r[0]
			for (j = i - dk; j > 0 && L.r[0].key < L.r[j].key; j -= dk)
				L.r[j + dk] = L.r[j];				//记录后移，直到找到插入位置
			L.r[j + dk] = L.r[0];					//将r[0]即原r[i]，插入到正确位置
		}
}

double ShellSort(SqList L, int dt[], int t) {   //希尔排序
	clock_t starttime, endtime;
	starttime = clock();
	int k;
	for (k = 0; k < t; ++k)
		ShellInsert(L, dt[k]);			 		//一趟增量为dt[t]的希尔插入排序
	cout << "希尔排序结果为：";
	show(L);
	endtime = clock();
	return (double)(endtime - starttime) / CLOCKS_PER_SEC;
}

//快速排序

int Partition(SqList L, int low, int high){
	int pivotkey;
	L.r[0] = L.r[low];
	pivotkey = L.r[low].key;
	while (low < high)
	{
		while (low < high && L.r[high].key >= pivotkey) 
			--high;
		L.r[low] = L.r[high];
		while (low < high && L.r[low].key <= pivotkey) 
			++low;
		L.r[high] = L.r[low];
	}//while
	L.r[low] = L.r[0];
	return  low;
}

void QSort(SqList L, int low, int high){
	int pivotloc;
	if (low < high)
	{										//长度大于1
		pivotloc = Partition(L, low, high); 		//将L.r[low..high]一分为二，pivotloc是枢轴位置
		QSort(L, low, pivotloc - 1);				//对左子表递归排序
		QSort(L, pivotloc + 1, high);        	//对右子表递归排序
	}

}											//QSort

double QuickSort(SqList L){   //快速排序
	clock_t starttime, endtime;
	starttime = clock();
	QSort(L, 1, NUMBER-1);
	cout << "快速排序结果为：";
	show(L);
	endtime = clock();
	return (double)(endtime - starttime) / CLOCKS_PER_SEC;
}

//冒泡排序

double BubbleSort(SqList L){  //冒泡排序
	clock_t starttime, endtime;
	starttime = clock();
	int m, j, flag;
	ElemType t;
	m = L.length - 1; flag = 1; 				//flag用来标记某一趟排序是否发生交换
	while ((m > 0) && (flag == 1))
	{
		flag = 0;           				//flag置为0，如果本趟排序没有发生交换，则不会执行下一趟排序
		for (j = 1; j <= m; j++)
			if (L.r[j].key > L.r[j + 1].key)
			{
				flag = 1;					//flag置为1，表示本趟排序发生了交换
				t = L.r[j]; L.r[j] = L.r[j + 1]; L.r[j + 1] = t;	//交换前后两个记录
			}							//if
		--m;
	}
	cout << "冒泡排序结果为：";
	show(L);
	endtime = clock();
	return (double)(endtime - starttime) / CLOCKS_PER_SEC;
}

//简单选择排序

double SelectSort(SqList& L){  //简单选择排序
	clock_t starttime, endtime;
	starttime = clock();
	int i, j, k;
	ElemType t;
	for (i = 1; i < L.length; ++i)
	{  												//在L.r[i..L.length] 中选择关键字最小的记录
		k = i;
		for (j = i + 1; j <= L.length; ++j)
			if (L.r[j].key < L.r[k].key)  k = j;			//k指向此趟排序中关键字最小的记录
		if (k != i) { t = L.r[i]; L.r[i] = L.r[k]; L.r[k] = t; } //交换r[i]与r[k]        
	}
	cout << "简单选择排序结果为：";
	show(L);
	endtime = clock();
	return (double)(endtime - starttime) / CLOCKS_PER_SEC;
}

//归并排序

void Merge(ElemType R[], ElemType T[], int low, int mid, int high){
	int i, j, k;
	i = low; j = mid + 1; k = low;
	while (i <= mid && j <= high)
	{
		if (R[i].key <= R[j].key) T[k++] = R[i++];
		else T[k++] = R[j++];
	}
	while (i <= mid) 
		T[k++] = R[i++];
	while (j <= high)
		T[k++] = R[j++];
}

void MSort(ElemType R[], ElemType T[], int low, int high){
	int mid;
	ElemType* S = new ElemType[NUMBER];
	if (low == high) T[low] = R[low];
	else
	{
		mid = (low + high) / 2;
		MSort(R, S, low, mid);	
		MSort(R, S, mid + 1, high);		
		Merge(S, T, low, mid, high);
	}
}

double MergeSort(SqList& L){  //归并排序 
	clock_t starttime, endtime;
	starttime = clock();
	MSort(L.r, L.r, 1, L.length);
	cout << "归并排序结果为：";
	show(L);
	endtime = clock();
	return (double)(endtime - starttime) / CLOCKS_PER_SEC;
}

//主程序

void Create_Sq(SqList& L)
{
	int number[NUMBER]{};
	for (int i = 0; i < NUMBER; i++) {
		number[i] = rand() % NUMBER;
	}
	int i;
	for (i = 0; i < NUMBER; i++)
	{
		L.r[i].key = number[i];
		L.length++;
	}
}

int main()
{
	SqList L;
	double time[7]{};
	L.r = new ElemType[NUMBER + 1];
	L.length = 0;


	Create_Sq(L);
	
	time[0] = InsertSort(L);//直接插入排序

	getchar();
	time[1] = BInsertSort(L);//折半插入排序

	getchar();
	int t;//增量数组的长度
	int* dt = new int[NUMBER];//增量数组
	t = 3;
	dt[0] = 1; dt[1] = 2; dt[2] = 3;
	time[2] = ShellSort(L, dt, t);//希尔排序

	getchar();
	time[3] = BubbleSort(L);//冒泡选择排序

	getchar();
	time[4] = QuickSort(L);//快速排序

	getchar();
	time[5] = SelectSort(L);//简单选择排序

	getchar();
	time[6] = MergeSort(L);//归并排序


	cout << "直接插入排序所需时间：" << time[0] << endl;
	cout << "折半插入排序所需时间：" << time[1] << endl;
	cout << "  希尔排序  所需时间：" << time[2] << endl;
	cout << "冒泡选择排序所需时间：" << time[3] << endl;
	cout << "  快速排序  所需时间：" << time[4] << endl;
	cout << "简单选择排序所需时间：" << time[5] << endl;
	cout << "  归并排序  所需时间：" << time[6] << endl;

	return 0;
}
