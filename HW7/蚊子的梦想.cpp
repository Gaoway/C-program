#define _CRT_SECURE_NO_WARNINGS
/*
*  mosquito's dream /main.c
*
*  (C) 2020 USTC_GAOWAY
*/
#include <stdio.h>
#include <ctype.h>		
#include <string.h>
#include <stdlib.h>

#define LEN_POS(pos) LEN_DATA[pos]%100 			
const int MAX = 100;					   //the maximum number of mosquito
int  	GROUP[MAX][MAX];					   //Recode the relationship between mosquito and people 
int 	LEN_DATA[MAX];						   //Recode the data of len of the relationship
int 	STATUS[MAX];						   //Recode whether the people have a mosquito

/*
* function: The function for the Qsort(), to compare a and b.
* Paramenter: const void *a, const void *b: two number need to be compared
* Return value: 1: *a is larger
*				0: *b is larger
*/
int cmp_len_data(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

/*
* function: get the relationship between mosquito and people 
*			Recode them in "GROUP" array and "LEN_DATA"	array
*/
int get_group()
{
	memset(GROUP, 0, sizeof(int) * MAX * MAX);
	memset(LEN_DATA, 0, sizeof(int) * MAX);
	int mosq_num = 0;
	scanf("%d", &mosq_num);							//recode mosquito's number 
	getchar();										//get '\n'
	for (int i = 0; i < mosq_num; ++i)
	{
		char c = 0;
		int j = 0;
		while ((c = getchar()) != '\n')				//check whether the data is the last charater in the line 
		{
			if (isdigit(c))
			{
				ungetc(c, stdin);					//put 'c' back to stdin.
				scanf("%d", &GROUP[i][j++]);		//get mosquito and people's realtionship
			}
		}
		LEN_DATA[i] = i + MAX * j;					//the end of one line, recode the data, i is mosquito's ID number  
	}												// j is length of the mosquito's people. j*MAX is easy to sort from less to more
	qsort(LEN_DATA, mosq_num, sizeof(int), cmp_len_data);	//the first data is the mosquito which conbines least people
	return mosq_num;
}

/*
* function: Get the One-to-one correspondence of mosquito and people.
*			STATUS recodes whether the people has the mosquito. If the flag is 0,
*			means the  chioce is not correct, and restore the last state, change 
*			another choice until get correct choice.
* Paramenter: mosq_num : the number of mosquito and the linage of GROUP.
*				pos: the function is to search the "pos" mosquito's people.
* Return value: get the correct relationship,return 1,else return 0;
*/
int detribution(const int mosq_num, const int pos)
{
	int flag = 0;				//flag recode whether the next mosquito's choice is correct 
	if (pos == 0)
		memset(STATUS, -1, sizeof(int) * MAX);
	for (int i = 0; i < LEN_DATA[pos] / MAX; ++i)	//LEN_DATA[pos]/MAX is number of relationship.
	{
		if (STATUS[GROUP[LEN_POS(pos)][i]] >= 0)	//GROUP[LEN_POS(pos)][i] is the IDnumber of people.If the people's status is -1, 
		{											// the people don't have mosquito.
			if (i == LEN_DATA[pos] / MAX - 1)
				return 0;
			continue;
		}
		else
		{
			STATUS[GROUP[LEN_POS(pos)][i]] = LEN_POS(pos);	  //change the people's status 
		}

		if (pos == mosq_num - 1)
			return 1;
		flag = detribution(mosq_num, pos + 1);
		if (flag == 0)
			STATUS[GROUP[LEN_POS(pos)][i]] = -1;		//if the choice is not correct, restore the last status. 
		else
			return 1;
	}
	return 0;											//IF all of the status is not suitable, return 0;
}

/*
* function: print the relationship in correct order.
*/
void print_order(const int mosq_num)
{
	for (int i = 0; i < mosq_num; ++i)			//from the first mosquito to the last 
	{
		for (int j = 0; j < mosq_num; ++j)		//find the correspond people.
			if (STATUS[j] == i)
				printf("%d\n", j);
	}
}

int main()
{
	int mosq_num = 0;
	mosq_num = get_group();						 //recode the number of mosquito
	detribution(mosq_num, 0);
	print_order(mosq_num);
}
