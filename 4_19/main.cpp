#include"stdio.h"
#include"stdlib.h"

void Swap(int array[],int i,int j) {
	int tem = array[i];
	array[i] = array[j];
	array[j] = tem;
}


//Hover法
//对数组[low,high]做分组
//基准值是array[low]
//调整区间(low,end]
//使用low所在下标的基准值一直与后面的数值进行比较，排号小于pivot值的区间和大于pivot的区间
//因为排序的过程是从后往前找小于基准值的数字与从前往后找大于基准值的数字进行两者之间的交换着就会使得
//想要完成的小于基准值的区间内由无序（开始有大于基准值的数字）全部转换为小于基准值的数字集合；同理
//后面的想要完成的大于基准值的区间
//最终由于begin < end的限制，end只能在end = begin + 1或者 end = begin的位置处找到小于基准值的数字
//有限制可以得出最终，两个end = begin 或者 end = begin + 1完成了有序的排列
//最后一步就是将基准值与begin的下标之间数字进行交换，实现基准值处于中间的目的
int PartitionHover(int array[],int low,int high) {
	int begin = low;
	int end = high;
	int pivot = array[low];

	//[begin,end]区间是暂时还没有被比较过的部分
	while (begin < end) {
		//基准值设置的是左边，故需要从右边开始向左边开始走；寻找比基准值小的数，交换
		//基准值下标的数值与比基准值小的数（这样的话可以实现保证基准值的左边比基准值小）
		//然后从基准值下标的位置后一个开始寻找比基准值大的数值，并交换基准值与大于它的值
		//这样能够保证比基准值大的数值位于基准值的右边
		//上述的交换顺序都是左边右边同时进行的，以保证遍历完整数值区间的数值
		//一次遍历的时候能够实现，基准值下标的左边都是小于基准值的数
		//基准值下标的右边都是大于基准值的数
		//上述的步骤，基准值的下标一直在变化
		while (begin < end && array[end] >= pivot) {
			end--;
		}
		while (begin < end && array[begin] <= pivot){
			begin++;
		}
		//使用while循环，将不需要交换的位置进行移动
		//交换begin与end下标的数值
		//因为上述的while循环不满足的条件就是
		//1.array[end] < pivot
		//2.array[begin] > pivot
		//这两个条件就是满足交换的条件
		Swap(array,begin,end);
	}
	//low所处下标为基准值
	//[low + 1,begin]值都比基准值小
	//[begin + 1,high]都比基准值大
	Swap(array,low,begin);
	return begin;
}

// 挖坑法
// 对数组中 [low, high] 的区间做分组
// 基准值是 array[low]
//调整区间为[low,high]
int	PartitionDig(int array[],int low,int high) {
	int begin = low;
	int end = high;
	int pivot = array[low];
	while (begin < end) {
		//基准值在左边，需要从右边向左边开始挖
		while (begin < end && array[end] >= pivot) {
			end--;
		}
		array[begin] = array[end];
		while (begin < end && array[begin] <= pivot) {
			begin++;
		}
		array[end] = array[begin];
	}
	array[begin] = pivot;
	return begin;
}

// 前后指针（下标）法
// 对数组中 [low, high] 的区间做分组
// 基准值是 array[low]

int PartitionPointer(int array[],int low,int high) {
	int front = low + 1;
	int tail = low + 1;
	int pivot = array[low];

	while (tail <= high) {
		if (array[tail] < pivot) {
			Swap(array,front,tail);
			front++;
		}
		tail++;
	}
	Swap(array,low,front - 1);
	return front - 1;
}

void __QuickSort(int array[],int low,int high) {
	if (low >= high) {
		return;
	}
	//1.找基准值
	//2.遍历整个区间，将较小的部分放置左边，较大的部分放置右边；返回基准值所在的下标
	int pivotIdx = PartitionPointer(array,low,high);
	//3.分治算法，分别计算两个小区间,结束条件：小区间的长度为0或者1
	__QuickSort(array, low, pivotIdx - 1);
	__QuickSort(array, pivotIdx + 1,high);
}


void QuickSort(int array[],int size) {
	__QuickSort(array,0,size - 1);
}

#include"stack"

void QuickSortNor(int array[],int size) {
	std::stack<int> stack;
	stack.push(0);//low
	stack.push(size - 1);//high

	while (!stack.empty()) {
		int high = stack.top();
		stack.pop();
		int low = stack.top();
		stack.pop();
		
		if (low >= high) {
			continue;
		}
		int pivotIdx = PartitionDig(array,low,high);
		//[low,pivtIdx - 1]
		stack.push(low);
		stack.push(pivotIdx - 1);
		//[pivotIdx + 1,high]
		stack.push(pivotIdx + 1);
		stack.push(high);
	}
}

void Merge(int array[],int left,int mid,int right,int extra[]) {
	int M_left = left;
	int M_mid = mid;
	int M_extra = left;

	while (M_left < mid && M_mid < right) {
		if (array[M_left] <= array[M_mid]) {
			extra[M_extra++] = array[M_left++];
		}else {
			extra[M_extra++] = array[M_mid++];
		}
	}

	while (M_left < mid) {
		extra[M_extra++] = array[M_left++];
	}
	while (M_mid < right) {
		extra[M_extra++] = array[M_mid++];
	}
	//将extra的数据移动回来
	for (int i = left; i < right; ++i) {
		array[i] = extra[i];
	}
}


//归并排序
void __MergeSort(int array[],int left,int right,int extra[]) {
	if (left >= right) {
		return;
	}
	if (left + 1 == right) {
		return;
	}
	int mid = left + (right - left) / 2;
	//[left,mid)
	//[mid,right)
	
	__MergeSort(array,left,mid,extra);
	__MergeSort(array,mid,right, extra);

	Merge(array,left,mid,right,extra);
}

void MergeSort(int array[],int size) {
	int* extra = (int*)malloc(sizeof(int) * size);
	__MergeSort(array,0,size,extra);
	free(extra);
}

void PrintArray(int array[], int size) {
	for (int i = 0; i < size; ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

void Test() {
	int array[] = {3,9,1,4,7,5,2,8,0,10,9};
	int size = sizeof(array) / sizeof(int);
	
	PrintArray(array,size);
	//QuickSort(array,size);
	QuickSortNor(array,size);
	//MergeSort(array,size);
	PrintArray(array, size);
}



int main() {
	Test();
	system("pause");
	return 0;
}