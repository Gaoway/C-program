#include <stdio.h>	 
#define len 9		 //the total of the clock
/*
* The origin data of clock, the number of it is len*len =81. It recode how to make one clock from 3 to the 12(other is 12)
* all of happens can sparate from this 9 origin things. Using the Linear algebra can solve the problem.
*/
const int DATA[len][len] = {	1,1,1,1,1,2,1,0,2,1,2,1,2,2,1,3,3,0,1,1,2,1,1,1,0,1,2,1,2,1,3,2,0,2,3,1,1,2,1,2,3,1,2,2,1,1,3,0,2,2,1,3,2,1,2,1,1,0,1,2,1,1,1,0,3,1,3,2,1,2,2,1,2,0,2,1,1,1,1,1,1 };

/* 
 * function: Get each clock's initial status from the float, 
 *			 and caculate do what steps to make the clock to the 12 o'clock.
 */
void get_step(int step[])
{
	int clk[len] = { 0 };					//initial the status, use the Gaussian elimination. 
	for (int i = 0; i < len; i++)
	{
		scanf("%d", &clk[i]);				//get status from outside 
		int multi = (clk[i] / 3) % 4;		//standardization the status. 3 to '1',6 to '2' 9 to '3' 12 to '0' 
		for (int j = 0; j < len; j++)
		{
			step[j] += DATA[i][j] * multi;	//use the origin data and Linear algebra,recode each step in step[i]
		}
	}
	for (int i = 0; i < len; i++)
	{
		step[i] = step[i] % 4;				//if step is large than 4, get the remainder of 4.
	}										//because a step do 4 times, it turn to the origin status 
}

/*
 * function: To print the the time of each step and avoid to printing the space in the end 
 *			and print the step from little to big 	
 */
void print_step(int step[],int *state)		
{
	int cnt = 0, sign = 0;
	for (int i = 0; i < len; i++)				//print the number from little to big
	{
		for (int j = 0; j < step[i]; j++)		// print the No.i step step[i] times 
		{
			sign++;
			if (cnt != 0)						// print the number with space ' '  
				printf(" %d", i);
			else
			{
				printf("%d", i);				//avoid to printing the last space' '
				cnt++;
			}
		}		
	}
	if (!sign)
		* state = 0;							//if state is 0, means get the invalid data and to the end the next
	else
		printf("\n");
}

int main()
{
	for (; ;)										//repate the operation until 
	{
		int step[len] = { 0 };
		int state = 1;
		get_step(step);
		print_step(step,&state);	
		if (!state)									//if status is 0, end of the progress, or continue  
			break;
	}
}


