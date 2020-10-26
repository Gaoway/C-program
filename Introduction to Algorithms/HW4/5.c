#define _CRT_SECURE_NO_WARNINGS
/*
    Bank card/main.c
    (C) USTC_GAOWAY
*/

#include <stdio.h>
#include <stdlib.h>

void find_max(int* data,int end, int* maxnum, int* counter) {
	int temp_maxnum = 0, temp_counter = 0;
	if (start == end) {
		temp_maxnum = data[start];
		temp_counter = 1;
	}
	else if (start > end) {
		temp_maxnum = -1;
		temp_counter = 1;
	}
	else {
		for (int i = 0; i <= end; ++i) {
			if (data[i] > temp_maxnum) {
				temp_counter = 1;
				temp_maxnum = data[i];
			}
			else if (data[i] == temp_maxnum) {
				temp_counter++;
			}
		}
	}	
	*maxnum = temp_maxnum;
	*counter = temp_counter;
}

int print_max(int* data, int n_day, int k_day) {
	int maxnum = 0, counter = 0;
	find_max(data, 0, k_day-1, &maxnum, &counter);
	printf("%d ", maxnum);
	for (int i = k_day; i < n_day; ++i) {
		int inarray = data[i];
		int outarray = data[i - k_day];
		if (outarray == maxnum) {
			if (counter > 1) {
				counter--;
			}
			else if (counter == 1) {
				find_max(data+(i - k_day + 1), i-1, &maxnum, &counter);
			}
		}
		if (inarray == maxnum) {
			counter++;
		}
		else if (inarray > maxnum) {
			maxnum = inarray;
			counter = 1;
		}
		printf("%d ", maxnum);
	}
	return 0;
}

int main() {
	int n_day = 0, k_day = 0;
	scanf("%d %d", &n_day, &k_day);
	int* data = (int*)malloc(sizeof(int) * n_day);
	for (int i = 0; i < n_day; ++i) {
		scanf("%d", data + i);
	}
	print_max(data, n_day, k_day);
	return 0;
}