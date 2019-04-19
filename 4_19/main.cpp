#include"stdio.h"
#include"stdlib.h"

void Swap(int array[],int i,int j) {
	int tem = array[i];
	array[i] = array[j];
	array[j] = tem;
}


//Hover��
//������[low,high]������
//��׼ֵ��array[low]
//��������(low,end]
//ʹ��low�����±�Ļ�׼ֵһֱ��������ֵ���бȽϣ��ź�С��pivotֵ������ʹ���pivot������
//��Ϊ����Ĺ����ǴӺ���ǰ��С�ڻ�׼ֵ���������ǰ�����Ҵ��ڻ�׼ֵ�����ֽ�������֮��Ľ����žͻ�ʹ��
//��Ҫ��ɵ�С�ڻ�׼ֵ�������������򣨿�ʼ�д��ڻ�׼ֵ�����֣�ȫ��ת��ΪС�ڻ�׼ֵ�����ּ��ϣ�ͬ��
//�������Ҫ��ɵĴ��ڻ�׼ֵ������
//��������begin < end�����ƣ�endֻ����end = begin + 1���� end = begin��λ�ô��ҵ�С�ڻ�׼ֵ������
//�����ƿ��Եó����գ�����end = begin ���� end = begin + 1��������������
//���һ�����ǽ���׼ֵ��begin���±�֮�����ֽ��н�����ʵ�ֻ�׼ֵ�����м��Ŀ��
int PartitionHover(int array[],int low,int high) {
	int begin = low;
	int end = high;
	int pivot = array[low];

	//[begin,end]��������ʱ��û�б��ȽϹ��Ĳ���
	while (begin < end) {
		//��׼ֵ���õ�����ߣ�����Ҫ���ұ߿�ʼ����߿�ʼ�ߣ�Ѱ�ұȻ�׼ֵС����������
		//��׼ֵ�±����ֵ��Ȼ�׼ֵС�����������Ļ�����ʵ�ֱ�֤��׼ֵ����߱Ȼ�׼ֵС��
		//Ȼ��ӻ�׼ֵ�±��λ�ú�һ����ʼѰ�ұȻ�׼ֵ�����ֵ����������׼ֵ���������ֵ
		//�����ܹ���֤�Ȼ�׼ֵ�����ֵλ�ڻ�׼ֵ���ұ�
		//�����Ľ���˳��������ұ�ͬʱ���еģ��Ա�֤����������ֵ�������ֵ
		//һ�α�����ʱ���ܹ�ʵ�֣���׼ֵ�±����߶���С�ڻ�׼ֵ����
		//��׼ֵ�±���ұ߶��Ǵ��ڻ�׼ֵ����
		//�����Ĳ��裬��׼ֵ���±�һֱ�ڱ仯
		while (begin < end && array[end] >= pivot) {
			end--;
		}
		while (begin < end && array[begin] <= pivot){
			begin++;
		}
		//ʹ��whileѭ����������Ҫ������λ�ý����ƶ�
		//����begin��end�±����ֵ
		//��Ϊ������whileѭ�����������������
		//1.array[end] < pivot
		//2.array[begin] > pivot
		//�����������������㽻��������
		Swap(array,begin,end);
	}
	//low�����±�Ϊ��׼ֵ
	//[low + 1,begin]ֵ���Ȼ�׼ֵС
	//[begin + 1,high]���Ȼ�׼ֵ��
	Swap(array,low,begin);
	return begin;
}

// �ڿӷ�
// �������� [low, high] ������������
// ��׼ֵ�� array[low]
//��������Ϊ[low,high]
int	PartitionDig(int array[],int low,int high) {
	int begin = low;
	int end = high;
	int pivot = array[low];
	while (begin < end) {
		//��׼ֵ����ߣ���Ҫ���ұ�����߿�ʼ��
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

// ǰ��ָ�루�±꣩��
// �������� [low, high] ������������
// ��׼ֵ�� array[low]

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
	//1.�һ�׼ֵ
	//2.�����������䣬����С�Ĳ��ַ�����ߣ��ϴ�Ĳ��ַ����ұߣ����ػ�׼ֵ���ڵ��±�
	int pivotIdx = PartitionPointer(array,low,high);
	//3.�����㷨���ֱ��������С����,����������С����ĳ���Ϊ0����1
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
	//��extra�������ƶ�����
	for (int i = left; i < right; ++i) {
		array[i] = extra[i];
	}
}


//�鲢����
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