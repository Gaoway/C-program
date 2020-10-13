#include <stdio.h>
#include <string.h>

const int  LEN = 5,REAL_LEN = 13,MAX_LEN = LEN * 10;
const int  MAX_DIVISER = 10000, INDEX = 4;

/* 
 * function:  To get the number to operate, including the origin number	to operate,
 *           and the power of this operation. 
 * parameters: &power the power you want to operate the origin number, &dot_pos the position of the dot 
 * return value: the origin number (int) without dot. 
 */
int get_number(int& power, int& dot_pos)
{
	int multi = MAX_DIVISER,origin_num=0;		//initialize the target datas

	for (int i = 0; i <= LEN; i++)				//the first LEN data is the origin number and the last 2 number is power
	{
		char tmp = getchar();
		if (tmp == -1)							//if EOF, finish 
			return -1;

		if ((tmp >= '0') && (tmp <= '9'))		//get origin number
		{
			origin_num += (tmp - 48) * multi;
			multi /= 10;
		}
		else
			dot_pos = 5 - i;					//get dos_pos 
	}
	getchar();									//avoid the space " "

	char tmp = getchar();						//get the power number
	if ((tmp > '0') && (tmp < '9'))
	{
		power += 10 * (tmp - 48);  
		tmp = getchar();
		power += (tmp - 48);
	}
	else
	{
		tmp = getchar();
		power += (tmp - 48);
	}
	getchar();									//avoid the	space

	for (int i = 0; i < LEN; i++)				//to limit the data to the least 
	{
		if (dot_pos == 0)						// if the last number is '0' after dot_pos, 
			break;								// eliminate it and dot_pos-1
		else if (!(origin_num % 10))
		{
			origin_num /= 10;
			dot_pos--;
		}
	}
	return origin_num;
}

/*
 * function:  with the number and power to operate and get the final number
 * parameters: fianl_number is the array number with 10000hex and the maxminum 
 *				of it is 10000^13, int power is time you want to operate.(10000½øÖÆ)
 */
void operate(int* final_num, int power, int origin_num)
{
	int remainder = 0;								// remainder is the complement of a number with 10000hex
	for (int i = 0; i < power; i++)					// do 'power' time and origin of fianl_num is 1.
	{
		for (int j = 0; j < REAL_LEN; j++)
		{
			final_num[j] *= origin_num;				//muitiple each digits
			final_num[j] += remainder;				//ecch degits add the remainder they owns 
			if (!final_num[j] && j > i)
			{
				remainder = 0;						//refresh the number of the remainder
				break;
			}
			remainder = final_num[j] / MAX_DIVISER;	//to get the remainder 
			final_num[j] %= MAX_DIVISER;			//limit the number into 10000hex
		}
	}

}

/*
* function:  to print the number with dot 
* parameters: int number is one digit of 10000digit, int position is the place of dot in the digit
*			 int flag tells wherther the fianlnumber has available digit before it
*				int pos_1 tells the dot place of the fianlnumber(different with position)
*/
void putnumber(int number, int position, int flag, int pos_1)
{
	int multi = MAX_DIVISER / 10;				//initlize the rank as 1000
	for (int i = 1; i <= INDEX; i++)			//print the each digit one by one 
	{
		int digit = ((number / multi) % 10);
		multi /= 10;
		if (i <= (INDEX - position) && flag == 1)	//if fianlnumber have the available number before it, print all of the digits 
			printf("%d", digit);
		else if (i <= (INDEX - position) && flag == 0 && digit != 0)
		{											//if fianlnumber doesn't have the available, don't print the number '0' before 
			printf("%d", digit);
			flag = 1;
		}
		else if (i > (INDEX - position))			//print all the digit after dot_pos 
			printf("%d", digit);
		if (i == (INDEX - position) && pos_1+position != 0)	 //if the dot_pos is not in the fianl,print .
			printf(".");
	}
}

/*
* function:  to print the fianl number using fuction putnumber 
* parameters: int fianl_number[] is the result in 10000hex , int dot_pos is the postion of the dot 
*/
void print_number(int final_num[], int dot_pos)
{
	int pos_1 = dot_pos / 4, position = dot_pos % 4;	//pos_1 is the position in 10000hex's digit position is the digit in the pos_1
	int flag = 0;										//flag tell when it have the available number 

	for (int i = REAL_LEN - 1; i >= 0; i--)				//do each digit 
	{
		if (!final_num[i] && flag == 0 && i != pos_1)	//don't print the number when flag=0,change it when i is pos_1 
			continue;
		else
		{
			if (i != pos_1 && !flag)					//don't print 0 before the number 
				printf("%d", final_num[i]);
			else if (i != pos_1 && flag)				//print all of the number of the digit 
				printf("%04d", final_num[i]);
			else if (i == pos_1)
				putnumber(final_num[i], position, flag, pos_1);
			flag = 1;									//change the flag to 1 
		}
	}
	printf("\n");									
}

int main()
{
	int final_num[REAL_LEN];						
	for (;;)
	{
		memset(final_num, 0, sizeof(int) * REAL_LEN);	
		final_num[0] = 1;								  //inilitize the fianl_num	make it as 1(n^0)
		int power = 0, dot_pos = 0, origin_num = 0;
		origin_num = get_number(power, dot_pos);		  //if origin_num=-1 means EOF, or the origin_num is real number  

		if (origin_num == -1)
			break;

		operate(final_num, power, origin_num);
		dot_pos *= power;								  //change the origin dot position to the fianl position
		print_number(final_num, dot_pos);
	}
}
