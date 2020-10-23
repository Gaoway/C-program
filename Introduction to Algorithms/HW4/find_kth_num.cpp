#define _CRT_SECURE_NO_WARNINGS
/*
    Find_the_K_th_number/main.c
    (C) 2020 USTC_GAOWAY
*/

//I ought to use the linera time complexity, like use merge solution, but quick sort is a good use, and O(n) time find Kth number

#include <stdio.h>
#include <stdlib.h>


int num_cmp(const void* a, const void* b) {
		return (*(int *)a)- (*(int*)b);
}

int main() {
	int total = 0, position = 0;
	scanf("%d %d", &total,&position);
	int* data = (int*)malloc(total * sizeof(int));
	for (int i = 0; i < total; ++i)
		scanf("%d", data + i);
	qsort(data, total, sizeof(int), num_cmp);
	printf("%d", data[position - 1]);

}

//inline void swap(int a, int b) {
//	int temp = 0;
//	temp = a;
//	a = b;
//	b = temp;
//}
//
//int Partition(int* data, int start, int end, int val) {
//	int count = start - 1;
//	int pos = start - 1;
//	for (int i = start; i < end; ++i) {
//		if (data[i] <= val) {
//			count += 1;
//			swap(data[count], data[i]);
//		}
//	}
//	return 0
//}