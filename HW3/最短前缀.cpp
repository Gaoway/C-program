#include <stdio.h> 
#include <string.h>

#define MAX_NUM 1000		 //the maximum of the vocabulary
#define LENGTH 20			 //the maximum length of the each word

char strings[MAX_NUM][LENGTH + 1] = { 0 };	   //to recode all of the vocabulary

/*
 * function: input all of the words going to input using the function of getchar()
 *			 And amount recodes the number of input words.
 *
 * Parament :char strings[][LENGTH+1] is to recode the words input.
 *			
 * return value: amount is the number of words input.
 *
 */

int input(char strings[][LENGTH+1])
{	
	int amount = MAX_NUM;					 //initialize the amount and if in the loop of the function amount can't be returned 
	for (int i = 0; i < MAX_NUM; i++)
	{
		for (int j = 0; j < LENGTH+1; j++)
		{
			char tmp = 0;
			tmp = getchar();			

			if (((tmp<97)|| (tmp>122))&&(!j))	//if the word is't what we want, return the amount.
			{ 
				amount = i;
				return amount;
			}
				
			if ((tmp < 97) || (tmp > 122))
				break;
			
			strings[i][j] = tmp; 
		}
	}
	return amount;						 // if in the loop of the function amount can't be returned, in the last it return as MAX_NUM
}

/*
 * function: output the short of all of the words. To compare wherther is the special short words,
 *			 use 
 * Parament :char strings[][LENGTH+1] is to recode the words input.	amount is the number of words.
 * Interpretation :the array equal[amount] is to recode whether the other words is equal to the target word
 *				   acocount the i from 0 to amount. If the other word[j] is not same to the target word[j] 
 *				   make the equal[i] as 0, until itself in the equal is 1. And print it from 0 to j.
 */

void output(char strings[][LENGTH+1],int amount)
{
	for (int i = 0; i < amount; i++)		   //account words from 0 to amount
	{
		int length = 0;
		length = strlen(strings[i]);
		int* equal=new int[amount];			   //equal's interpretation is above 

		for (int j = 0; j < amount; j++)
			equal[j] = 1;
											   //refresh the array of equal
		int total = amount ;
		printf("%s ", strings[i]);			  

		for (int j = 0; j < length; j++)	   //to compare each letters of target word
		{
			for (int k = 0; k < amount; k++)   //And compare the target letter with each word
			{
				if ((equal[k]==1)&& (strings[i][j] != strings[k][j]) )  //If the target letter is't equal toeach other, 				   //make equal as 0 
				{
					total--;
					equal[k] = 0;
				}
			}
			if (total)						  //if total is not below 1, printr the target letter. 
				putchar(strings[i][j]);		
			if (total == 1)
				break;
		}
		printf("\n");						  //turn to the next word. 
	}
}

int main()												
{
	int amount = 0;								//refresh amount to 0

	for (int i = 0; i < MAX_NUM * (LENGTH + 1); i++)		//To refresh the global array of strings[MAX_NUM][LENGTH +1]
	{
		*(strings[0] + i) = 0;
	}
	//��nput all of the words 	
	amount = input(strings);		
	//output all of the short of the words 	
	output(strings, amount);								
}	//100 lines is my last stubbornness