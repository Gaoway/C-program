#define _CRT_SECURE_NO_WARNINGS
/*
*  Digital_Pyramid/main.c
*
*  (C) 2020 USTC_GAOWAY
*/
#include <stdio.h>
#include <string.h>

const int  MAX_NUM = 11;					// the maxium of the pyramid's high 
const int length = MAX_NUM * sizeof(int);

int mutiple[MAX_NUM];						//recode the multiple of each number
int number[MAX_NUM];

/*
* function: to get the mutiple of each number. Inlitize the first multiple '1'
*			and with properties of the pyraid, the next array's number add itself 
*			and the former number.
* Paramenter: int high :the high of the pyramid.
*/
void get_mutilple(const int high)
{
	memset(mutiple, 0, MAX_NUM * sizeof(int));		//initial the array.
	mutiple[0] = 1;
	for (int i = 1; i < high; ++i)					// do 'high' times.
	{
		for (int j = i; j >= 1; --j)
			mutiple[j] += mutiple[j - 1];			//add the former number and it self.	
	}
}

/*
* function: To get the number of each position, use recurrence to get the number.
*			.because the first and the last number have the same mutiple, compute the
*			data each two number.
* Parament: int high, the high of pyramid, int sum, the total number of recoded data
*			int fin_sum the final data you want to get.
* Return value: 1: the function have got the correct data.
*				0: the function have not got the currect data. Need to try another chioce.
*/
int get_number(const int high, const int sum, const int time, const int fin_sum)
{
	if (high - time * 2 == 1)			//if the mulitple has one number.
	{
		for (int i = 0; i < high; ++i)
			if (number[i] == -1)		//Search the correct position
			{
				number[i] = time;
				if ((sum + mutiple[time] * (i + 1)) == fin_sum)
					return 1;			//get right data.
				else
				{
					number[i] = -1;		//get wrong data, try another. 
					return 0;
				}
			}
	}
	else if (high - time * 2 == 0)				//the last multiple have no number.
	{
		if (sum == fin_sum)				//compare with the data you want.
			return 1;
		else
			return 0;
	}
	else
	{
		for (int i = 0; i < high; ++i)	//not meet the last.the multiple havs two number. 
		{
			if (number[i] == -1)
			{
				number[i] = time;		//find the first number.
				for (int j = high - 1; j > i; --j)	//the question needs this order. 
				{
					if (number[j] == -1)//find the 2nd number.
					{
						int flag = 0;
						int tem_sum = 0;
						number[j] = time;
						tem_sum = sum + mutiple[time] * (i + j + 2);	 //DONOT change the sum, use the temp number.
						flag = get_number(high, tem_sum, time + 1, fin_sum);	//check whether the data is we want
						if (flag == 1)											//yes, end of the function.
							return 1;											//No, try another data 
						else
							number[j] = -1;
					}
				}
				number[i] = -1;
			}
		}
		return 0;
	}
}

/*
* function: to print the correct form.
* Paramenter pyramid's high.
*/
void print_num(const int high)
{
	int heap[MAX_NUM];				  //use the array to recode the order
	for (int i = 0; i < high; ++i)
		heap[i] = 0;

	for (int i = 0; i < high; ++i)	  //recode the order.
	{
		int temp = number[i];
		if (heap[temp] == 0)
			heap[temp] = i + 1;
		else
			heap[high - temp - 1] = i + 1;
	}
	for (int i = 0; i < high - 1; ++i) //print the order 
		printf("%d ", heap[i]);
	printf("%d\n", heap[high - 1]);
}

int main()
{
	int high = 0, total = 0;
	scanf("%d%d", &high, &total);
	memset(number, -1, sizeof(int) * MAX_NUM);		//initical the array.
	get_mutilple(high);
	get_number(high, 0, 0, total);		//use the former data 
	print_num(high);
}
