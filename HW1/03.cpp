#include<stdio.h>
#define length sizeof(elem)*8

#define OK 1
#define ERROR 0 
typedef int status;
typedef unsigned short elem;		 //elem makes the function portable

/*
* function: insert two numbers x and y in the range of unsigned short. X and y can 
*			transfer into binary. If x can loop serval times(less than length) become y
*			return OK or return ERROR
*/

status loops(elem x, elem y)
{
	int tmp = 0;
	for (int i = 0; i < length; i++)
	{
		if (x == y)
			return OK;
		if (x % 2)					//x%2 =1 proves that the last number of binary x is 1 
			tmp = 1;
		
		x = (x >> 1 )+ (tmp << length - 1);	// make the last number be the first number of binary x
		tmp = 0;						//refresh tmp number 
		if (x == y)					//compare x and y
			return OK;
	}
	return ERROR; 
}


int main()								
{
	elem x = 0, y = 0;				//x and y is the number you want to input 
	int time = 0;
	scanf("%d", &time);				//record the amount of x and y
	for (int i = 0; i < time; i++)
	{
		scanf("%hu", &x);
		scanf("%hu", &y);
		
		if (loops(x, y))			//if function returns OK print YES			
			printf("YES\n");		//or print NO
		else
			printf("NO\n");
	}
}
