#define _CRT_SECURE_NO_WARNINGS

/*
	Data_Base/main.c
	(C) 2020 USTC_GAOWAY
*/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
// use hash list to memory the data
//Use the divide as a hash function. the DIVIDE number select 40000 ,when I use 8501, time is out of limit
const int MAX_NUM = 40000;
//link list to memory the same number of hash function
typedef struct hashptr{
	int id;
	int num;
	hashptr* next;
}hashptr ;

hashptr* data[MAX_NUM];

void Insert_Hash_Data(int id, int num) {
	hashptr* insert = new hashptr;		//when I use `hashptr insert, something wrong happens, maybe bcs it in the stack`
	insert->id = id;
	insert->num = num;
	insert->next = NULL;
	hashptr* ptr = data[num % MAX_NUM];
	if (ptr == NULL) {
		data[num % MAX_NUM] = insert;
		return;
	}
	while (ptr->next != NULL)
		ptr = ptr->next;
	
	ptr->next = insert;
}

int Find_Hash_Data(int num) {
	hashptr* ptr = data[num % MAX_NUM];
	while (ptr != NULL) {
		if (ptr->num == num)
			return ptr->id;
		else
			ptr = ptr->next;
	}
	return -1;
}

int main() {

	memset(data, NULL, sizeof(hashptr*) * MAX_NUM);
	char *title = (char *)malloc(sizeof(char) * 12);
	scanf("%s", title);			//read the whole string and compare the first char limit time
	while (title[0] != 'E') {
		
		if (title[0] == 'I') {
			int id = 0, num = 0;
			scanf("%d %d", &id,&num);
			 Insert_Hash_Data(id, num);
		}
		else if (title[0] == 'F') {
			int num = 0;
			scanf("%d", &num);
			printf("%d\n",Find_Hash_Data(num));
		}
		scanf("%s", title);
	}
	free(title);
	return 0;
}