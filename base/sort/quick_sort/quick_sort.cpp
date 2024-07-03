#include "main.h"

void quick_sort(int arr[], int left, int right) {
    if (left < right) {
        int x = arr[left];
        int l = left;
        int r = right;
        while(l < r) {
            while(l < r && arr[r] > x) r--;
            if (l < r) {
                arr[l++] = arr[r];
            }
            while(l < r && arr[l] < x) l++;
            if (l < r){
                arr[r--] = arr[l];
            }
        }
        arr[l] = x;
        quick_sort(arr, left, l - 1);
        quick_sort(arr, l + 1, right);
    }
}
void QuickSort(int* a, int left, int right)
{
// 假设按照升序对array数组中[left, right)区间中的元素进行排序
	if (right <= left)
		return;
// 按照基准值对array数组的 [left, right)区间中的元素进行划分
	//int keyi = PartSort1(a, left, right);
	int keyi = PartSort2(a, left, right);
	//int keyi = PartSort3(a, left, right);
// 划分成功后以div为边界形成了左右两部分 [left, keyi-1) 和 [keyi+1, right)
// 递归排[left, keyi-1)
	QuickSort(a, left, keyi - 1);
// 递归排[keyi+1, right)
	QuickSort(a, keyi + 1, right);
}
//三数取中
int NumBers(int* a, int left, int right)
{
	int mid = (left + right) / 2;
	// left mid right
	if (a[left] < a[mid])
	{
		if (a[mid] < a[right])
		{
			return mid;
		}
		else if (a[left] > a[right])  // mid是最大值
		{
			return left;
		}
		else
		{
			return right;
		}
	}
	else // a[left] > a[mid]
	{
		if (a[mid] > a[right])
		{
			return mid;
		}
		else if (a[left] < a[right]) // mid是最小
		{
			return left;
		}
		else
		{
			return right;
		}
	}
}


int PartSort2(int* a, int left, int right)
{
	//三数取中优化
	//int keyi = NumBers(a, left, right);
	//Swap(&a[keyi], &a[left]);
	int key = a[left];
	int hole = left;//为第一个坑

	while (left < right)
	{
		while (left < right && key <= a[right])
		{
			--right;
		}
		a[hole] = a[right];
		hole = right;

		while (left < right && a[left] <= key)
		{
			++left;
		}
		a[hole] = a[left];
		hole = left;
	}
	a[hole] = key;
	return hole;
}