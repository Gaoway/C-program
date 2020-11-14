#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Getdata(int** data, int total, int relation) {
	int status = 1;
	for (int i = 0; i < relation; ++i) {
		int tmp1, tmp2;
		scanf("%d %d", &tmp1, &tmp2);
		if (data[tmp1] == NULL && data[tmp2] == NULL) {
			int* tag = (int *)malloc(sizeof(int));
			*tag = status;
			data[tmp1] = tag;
			data[tmp2] = tag;
			status++;
		}
		else if (data[tmp1] == NULL && data[tmp2] != NULL) {
			data[tmp1] = data[tmp2];
		}
		else if (data[tmp2] == NULL && data[tmp1] != NULL) {
			data[tmp2] = data[tmp1];
		}
		else if (data[tmp1] != NULL && data[tmp2] != NULL &&*data[tmp1] != *data[tmp2]) {
			if (*data[tmp1] > * data[tmp2]) {
				*data[tmp1] = *data[tmp2];
			}
			else {
				*data[tmp2] = *data[tmp1];
			}
		}
	}
	return status;
}

void Find_relation(int** data, int find) {
	for (int i = 0; i < find; ++i) {
		int tmp1 = 0, tmp2 = 0;
		scanf("%d %d", &tmp1, &tmp2);
		int result = (*data[tmp1] == *data[tmp2] ? 1 : 0);
		printf("%d ", result);
	}
}

void Free_data(int** data, int total) {
	free(data);
	return;
}

int main() {
//	freopen("2.in", "r", stdin);
//	freopen("2.ans", "w", stdout);

	int total = 0, relation = 0, find = 0;
	scanf("%d %d %d", &total, &find, &relation);
	int** data = (int**)malloc(total * (sizeof(int*)));
	memset(data, NULL, total * sizeof(int*));
	Getdata(data, total, relation);
	Find_relation(data, find);
	Free_data(data, total);
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}

//	  7 2 6 4 1 0 1 5 2 4 0 6 3 3 5 0 5 4 0
