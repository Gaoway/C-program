#include <stdio.h> 
#include <string.h>
#include <math.h>
#include <stdlib.h>

const int MAX_LEN 520				//The length of the total txt, the first task is 100 the second is 500

/*
* function: insert data of char to compare whether the data is we want to get  
*           and the available data is between 'A' to 'Z' and '?'and 'a' to 'z' 
* return value: 1 or 0. 1 is the data is what we want, 0 is that the data is't we want 
* 
* Paramenter:char word is the word we want to compare.
*/

inline int available_data(char word)
{
	if (word == '?')
		return 1;
	else if ((word >= 'a') && (word <= 'z'))
		return 1;
	else if ((word >= 'A') && (word <= 'Z'))
		return 1;
	else
		return 0;
}

/*  
 * function: get the data from the input data. And dapart them to 2 or 3 parts, the longest string T 
 *           and the string before the word '#' P_1 and then string after the word '#' P_2
 *			 If the short string doesn't have the word '#' sign is 0 or the sign is 1
 * return value : the number of sign. 0 or 1, if the short string don't have '#' sign is 0 or sign is 1
 *
 * Parament: T[MAX_LEN] is the longest string we need to compare. P_1[MAX_LEN] is the first part of the 
 *			 short string, P_2[MAX_LEN]	is second part of the short string
 *
 */

int get_string(char T[], char P_1[], char P_2[])
{

	int sign = 0;					//To initiallize the sign 
	for (int i = 0; i < MAX_LEN; i++)
	{
		T[i] = getchar();
		if (T[i] == '\n')
		{
			break;					//Recode the long string into char T[MAX_LEN] until the '\n'
		}//end if
	}

	for (int i = 0; i < MAX_LEN; i++)
	{
		P_1[i] = getchar();
		if (P_1[i] == '#')			//Recode the first part of short string into P_1[MAX_LEN] until the '\n' or '#'
		{
			P_1[i] = '\n';
			sign = 1;				//If the last word of P_1 is '#' change it into '\n' and make sign to 1 
			break;
		}
		else if (P_1[i] == '\n')	//If the last word of P_1 is '\n' end of the function. 
		{
			break;
		}//end if 
	}

	if (sign == 1)					//Recode the second part of short string into P_2[MAX_LEN] until the '\n'
	{
		for (int i = 0; i < MAX_LEN; i++)
		{
			P_2[i] = getchar();
			if (!available_data(P_2[i]))		//If the data isn't what we want end the function 
			{		
				P_2[i] = '\n';
				return sign;
			}//end if 
		}
	}
	return sign;
}

/* 
 * function: input the long string and one part of the short string and the length of them, 
 *			 P_pos is to recode the first position of the substring. And P_pos[0] is the length of P_pos
 *            
 * Parament :char T[MAX_LEN] is the long string. char P[MAX_LEN] is the one part of the short string T_len is the length of T[]
 *			 P_len is the length of P[]. int P_pos[MAX_LEN]	is the position of substrings
 */

void string_compare(char T[], char P[], int P_pos[], int T_len, int P_len)
{
	int coder = 0;				//coder is the number of T[]'s substring with P[]
	for (int i = 0; i <= T_len; i++)			//i is position of T[]
	{
		for (int j = 0; j < P_len; j++)			//j is position of P[]
		{
			if (i + j >= T_len)					//when compare to the last word, end the loop
				break;

			if ((T[i + j] - P[j] != 0) && (P[j] != '?') && (abs(T[i + j] - P[j]) != 32))
			{
				break;							//If one word does'n equal end the loop 
			}
			else if (j == P_len - 1)
			{
				coder++;						
				P_pos[coder] = i;				//recode the position of substring 
			}//end if
		}

		if (P_len == 0)							//if P[] length is 0, make P_pos[] is all of the T[]
		{
			coder ++;
			P_pos[coder] = i;
		}//end if 
	}
	P_pos[0] = coder ;							// P_pos[0] is the length of P_pos[]
}

/*
 * function: input the long string and two parts of the P_pos[MAX_LEN] and the length of them,
 *			 if flag=1 the function compare the two position and print the words between the two position
 *			 if flag=0 the function print the words of the position of P_pos_1 and the length of P_1[MAX_LEN]
 *
 * Parament :char T[MAX_LEN] is the long string. int P_pos_1[MAX_LEN] and int P_pos_2[MAX_LEN]is the two part of the 
 *			 positions, int P_1_pos and int P_pos_2 is length of P_1[MAX_LEN] and P_2[MAX_LEN
 *			 flag is to get weather the short string have '#'
 *		
 */

void print_substr(char T[], int P_pos_1[], int P_pos_2[], int P_1_len, int P_2_len, int flag)
{
	if (flag)		   //If then short string have '#' compare the P_Pos_1 and P_pos_2
	{
		for (int i = 1; i <= P_pos_1[0]; i++)	   //i is the NO.i of the postion of P_pos_1
		{
			for (int j = 1; j <= P_pos_2[0]; j++)  //j is the NO.j of the postion of P_pos_2 
			{
				if (P_pos_1[i] + P_1_len <= P_pos_2[j])
				{
					printf("%d ", P_pos_1[i]);	   // the substring we want is between P_pos_1[i] and P_pos_2[j]
					for (int k = P_pos_1[i]; k <= P_pos_2[j] + (P_2_len - 1); k++)
					{
						putchar(T[k]);
					}
					printf("\n");
				}//end if 
			}
		}
	}
	else				//If the short string don't have '#', only focus on P_pos_1[MAX_LEN]
	{
		for (int i = 1; i <= P_pos_1[0]; i++)
		{
			printf("%d ", P_pos_1[i]);			//the substring we want between P_pos_1[i] and P_pos_1[i]+P_1_len
			for (int j = P_pos_1[i]; j < P_pos_1[i] + P_1_len; j++)
			{
				putchar(T[j]);
			}
			printf("\n");

		}
	} //end if
}

int main()
{	
	char T[MAX_LEN] , P_1[MAX_LEN] , P_2[MAX_LEN] ;		
	int P_pos_1[MAX_LEN], P_pos_2[MAX_LEN];

	for (int i = 0; i < MAX_LEN; i++)				   //initialize the array of T[] P_1[] P_2[],P_pos_1[],P_pos_2[]
	{
		T[i] = 0;
		P_1[i] = 0;
		P_2[i] = 0;									  
		P_pos_1[i] = MAX_LEN ;						 //make the P_pos_1 the biggest number   
		P_pos_2[i] = -1;							 //make the P_pos_2 the smallest number
	}

	int flag = get_string(T, P_1, P_2);				 //recode the number of flag, T_len, P_1_len, P_2_len
	int T_len = strlen(T) -1;
	int P_1_len = strlen(P_1) -1;
	int P_2_len = strlen(P_2) -1;

	string_compare(T, P_1, P_pos_1, T_len, P_1_len); //compare the T[] and P_1[]

	if (flag)
		string_compare(T, P_2, P_pos_2, T_len, P_2_len);	//if flag=1 compare the T[] and P_2[]

	print_substr(T, P_pos_1, P_pos_2, P_1_len, P_2_len, flag);
}
