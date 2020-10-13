/*
 *  File tree/main.c
 *
 *  (C) 2020 USTC_GAOWAY
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAXLEN = 22;					//the maximum of one file and dic is 20, limit the MAX length to 21;
const int MAXHEAP = 40;					//Limit the largest heap colum to 40

/*
* function: to print the form of File Tree, input the deepth and print the exact form. 
* Paramenter: deepth the deepth of the file or dir you want to print. char *filename: 
*				the name of file or the dir.
*/
void printlist(const int deepth, const char* filename)			
{
	if (deepth == 0)
		puts(filename);							   //the functon of puts() print the '\n' in the end 
	else
	{
		for (int i = 0; i < deepth; i++)		
			printf("|     ");						//print the "|     " 'deepth' times 
		puts(filename);								
	}
}

/*
* function: to compare the file name in the FILE_HEAP** and use the qsort() to sort them 
* Paramenter: the name of file a and file b
* Return value: the strcmp value of *a and *b 
*/
int cmp_file(const void* a, const void* b)
{
	return strcmp((char *)a, (char *)b);
}

/*
* function: to get the file tree date standard input and transform them into the Visualizate tree.
* Paramenter: deepth the deepth of the file or dir. Time: the number of file tree.
* return value: 1: the standard input is not meet the end.
*				0: the input is meets the end. 
*/
int list_dir(int deepth, int time)
{
	int num = 0;										//num is the number of the file in this dir
	char heap[MAXHEAP][MAXLEN];							// the heap recodes the files' name 
	memset(heap, 0, MAXHEAP * MAXLEN * sizeof(char));	//to initial the heap 
	for (int i = 0; i < MAXHEAP; ++i)
	{
		char first = getchar();							// get the first letter of each line 

		if (i == 0 && deepth == 0 && first != '#')		// if the line is the begining, print the origin data
		{
			printf("DATA SET %d:\n", time);
			printf("ROOT\n");
		}

		if (first == '#')								// if the first letter is '#' the end of file trees
			return 0;
		else if (first == ']' || first == '*')			// if the first letter is '*' or ']', end of dir.
		{
			getchar();									// to get the '\n' behind the letter
			break;
		}
		else if (first == 'f')							// the letter of 'f' means the line is file name 
		{
			heap[num][0] = 'f';							//recode the file name 
			for (int j = 1; j < MAXLEN; ++j)
			{
				char temp = getchar();
				if (temp != '\n')
					heap[num][j] = temp;
				else
					break;
			}
			num++;										
		}
		else if (first == 'd')							// the letter of 'd' means the line is dir 
		{
			char dirname[MAXLEN];						
			memset(dirname, 0, MAXLEN * sizeof(char));
			dirname[0] = 'd';
			for (int j = 1; j < MAXLEN; ++j)			//to recode the dir name 
			{
				char temp = getchar();
				if (temp != '\n')
					dirname[j] = temp;
				else
					break;
			}
			printlist(deepth + 1, dirname);				 //print the dir name 
			list_dir(deepth + 1, time);					 //goto the next_dir until the end of the next_dir
		}
	}

	qsort(heap, num, sizeof(char[MAXLEN]), cmp_file);	 // to sort the file heap 
	for (int i = 0; i < num; ++i)
	{
		printlist(deepth, heap[i]);						 //print the file_name in order 
	}
	return 1;
}

int main()
{
//	freopen("2.in", "r", stdin);
//	freopen("2.ans", "w", stdout); // Do not write "1.out" or the answer output will be cleared
	for (int i = 1;; ++i)								  // i is recode the number of file tree
	{
		int flag = list_dir(0, i);						  // flag recode whether the file tree is to the wnd 
		if (flag == 1)
			printf("\n");
		else
			break;
	}
//	fclose(stdin);
//	fclose(stdout);
}
