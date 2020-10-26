#define _CRT_SECURE_NO_WARNINGS
/*
    弹幕/main.c
    (C) 2020 USTC_GAOWAY
*/

// Given the data not in order and use quicksort get in order data, then get their DIF  
#include <stdio.h>
#include <stdlib.h>

int max_size(int* data, int total) {        //Find the biggest DIF 
	int max = 0;
	for (int i = 0; i < total - 1; ++i) {
		int temp = data[i + 1] - data[i];
		max = (temp > max ? temp: max);
	}
	return max;
}

int num_cmp(const void* a, const void* b) {
	return (*(int *)a)- (*(int*)b);
}

int main() {
	int total = 0;
	scanf("%d", &total);
	int* data = (int*)malloc(sizeof(int) * total);
	for (int i = 0; i < total; ++i) {
		scanf("%d", data + i);
	}
	qsort(data, total, sizeof(int), num_cmp);
	
	printf("%d", max_size(data, total));
	free(data);
	return 0;
}