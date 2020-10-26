#define _CRT_SECURE_NO_WARNINGS

/*
	Find_reversed_numpairs/main.cpp
	(C) USTC_GAOWAY
*/

// use the thinking of merge sort, and time is O(lgn)
#include<stdio.h>
#include <stdlib.h>

const int MAX_NUM = 10000019;

//given two arrays of number,in order. So it's no need to compare with all of number, we can use the info of the compartion before.
// info: int *data mem the initial number,and the num between (data) to (data + len_1), the num between (data +len_1) to (data +len_1+len_2)
//is in order. we need to get the num array (data) to (data+ len_1+ len_2) are all in order.
int merge_find_rev(int* data, int len_1, int len_2) {
	int count = 0;
	int pos_1 = 0, pos_2 = 0;
	int* ptr2 = data + len_1;
	int* data_a = (int*)malloc(sizeof(int) * len_1);	   //mem the initial data
	int* data_b = (int*)malloc(sizeof(int) * len_2);
	for (int i = 0; i < len_1; ++i)
		data_a[i] = data[i];
	for (int i = 0; i < len_2; ++i) {
		data_b[i] = *(ptr2 + i);
	}
	for (int i = 0; i < len_1 + len_2; ++i) {				//use the info before.
		if (pos_1 >= len_1) {
			data[i] = data_b[pos_2];			
			pos_2++;
		}
		else if (pos_2 >= len_2) {
			data[i] = data_a[pos_1];			
			pos_1++;
		}

		else if (data_a[pos_1] <= data_b[pos_2]) {
			data[i] = data_a[pos_1];			
			pos_1++;
		}

		else if (data_a[pos_1] > data_b[pos_2]) {
			data[i] = data_b[pos_2];
			count += (len_1 - pos_1);			
			pos_2++;
		}
		count %= MAX_NUM;
	}	
	free(data_a);
	free(data_b);
	return count;
}  

// info: int* data mem the initial data, but not inorder. int len: the length of array, start as *data, end as *(data + len)
int Merge(int* data, int len) {
	int m = len / 2;
	int n = len - m;
	if (len == 0 || len == 1)
		return 0;
	int count = 0;
	count += Merge(data, m);
	count += Merge(data + m, n);			//get the data in order.
	count += merge_find_rev(data, m, n);	// comepare two array, and get the whole array in order. 
	return count % MAX_NUM;
}

int main() {
	int total = 0;
	int count = 0;
	scanf("%d", &total);
	int* data = (int*)malloc(total * sizeof(int));
	for (int i = 0; i < total; ++i)
		scanf("%d", data + i);
	count =Merge(data, total);
	printf("%d", count);
	free(data);
}