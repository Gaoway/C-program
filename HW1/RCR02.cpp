#include<stdio.h>
#define length sizeof(elem)*8

#define OK 1
#define ERROR 0 

typedef int status;
typedef unsigned short elem;   	  //elem makes the function portable

/*
* function: insert two numbers in the range of unsigned short and the number 1 or 0
*			if the two numbers with 1 or 0 can do the operation like RCR in computer 
*			to transfer into each other return OK otherwise return ERROR;
*/

status RCR(elem x, elem y, elem spec)
{
	/*
	*	introduction :
	*	x and y is unsigned short numbers ,spec is 0 or 1.
	*	make compare with x and y at most length times. If x equals y return OK, or change x
	*	x shift right 1 bit. spec and tem is temperary num to recore 0 or 1, and make the  
	*	spec in the first place of x, recore the new spec. Compare x y again.
	*	If all x and y don't equals ,return ERROR
	*/

	elem tem_1 = spec;	
	for (int i = 0; i < length; i++)
	{	
		if (x == y)
			return OK;
		
		int tmp_2 = x % 2;   		//if x%2=0 means that the last word is 0 or is 1,which to be the spec number   		
		x = (x >> 1) + (tem_1 << (length - 1));	   // And put the spec number inthe first place of number x
		
		if (x == y)
			return OK;
		tem_1 = tmp_2;				//to tranmit the spec num
	}
	return ERROR;
}

int main()
{
	elem x = 0, y = 0, spec = 0;		
	int time = 0;
	scanf("%d", &time);				//recode the amount of x and y
	for (int i = 0; i < time; i++)
	{
		scanf("%hu", &x);
		scanf("%hu", &y);
		scanf("%hu", &spec);

		if (RCR(x, y, spec))		//if RCR function returns OK print YES
			printf("YES\n");		//or return ERRO
		else
			printf("NO\n");
	}
}
