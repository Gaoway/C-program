#define _CRT_SECURE_NO_WARNINGS
/*
*  Divide_number/main.c
*
*  (C) 2020 USTC_GAOWAY
*/
#include <stdio.h>
#include <ctype.h>

/*
* function: get number from stdin, and recode the date in number and part
* Return value: the number is correct, return 1,
*				the number is wrong, go to the end of the stdin, return 0;
*/
int get_data(int& number, int& part)
{
	char temp = getchar();
	if (temp <= '9' && temp >= '0')		//check whether the first charater is number,
	{
		ungetc(temp, stdin);
		scanf("%d", &number);
		scanf("%d", &part);
		getchar();
		return 1;
	}
	return 0;						   //if the character is not number. The data is wrong.
}

/*
* function: use recurrence to get the number of divide options.
* Paramenter:int number: the number which to be divided, int part: the number of part,
*			int max_num: the biggest part number shound't bigger than max_num, in other words,
*			the divide part number is from bigger to less.
* Return number: the number of divide choice.
*/
int get_number(const int number, const int part, const int max_num)
{
	if (part == 1)				//if the number only divide into 1 part, the number of option is 1,
		return 1;
	int plus = 0;
	for (int i = max_num; i > 0; i--)	//from big to little
	{
		if (number - i < part - 1)		//if rest number can't be divided into "part-1", end.
			continue;
		if (i * part < number)			//if rest number must have the part,which bigger than this part, means current part is too small.
			break;						//end of the loop
		plus += get_number(number - i, part - 1, i);	  //do the next part.
	}
	return plus;
}

int main()
{
	for (;;)			//do the function until the end of stdin.
	{
		int number = 0, part = 0, sum = 0, status = 0;
		status = get_data(number, part);
		if (status == 0)
			break;		//the end of stdin, end of the function
		sum = get_number(number, part, number);
		printf("%d\n", sum);
	}
}