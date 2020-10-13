#define  _CRT_SECURE_NO_WARNINGS
/*
*  skee/main.c
*
*  (C) 2020 USTC_GAOWAY
*/

#include <stdio.h>
#include <string.h>

#define MINUS(X) (MAX_len+(X)-1)%(MAX_len)		
const int MAX_len = 105;			//The maximum length of the whole area
const int MAX_wid = 105;

int AREA[MAX_len][MAX_wid];		  	//Recode the altitude of the whole area 
int SKE_LEN[MAX_len][MAX_wid];		//Recode the longest way of all of the position
									//so that the function don't need to compute same position twice 
/*
* function: Recode the altitude date of the area in the "ARAE" array
* Paramenter: int &len, int &width: the original data of the area
*/
void get_data(int& len, int& width)
{
	memset(AREA, 0, sizeof(int) * MAX_len * MAX_wid);			//reset the array
	memset(SKE_LEN, 0, sizeof(int) * MAX_len * MAX_wid);
	scanf("%d %d", &len, &width);
	for (int i = 0; i < len; ++i)								//Recode the altitude
		for (int j = 0; j < width; ++j)
			scanf("%d", &AREA[i][j]);
}

/*
* function: To get the biggest number amount the 4 number
* Paramenter: const int a,b,c,d The numbers going to compare
* Return value: the biggest number
*/
inline int max_4(const int a, const int b, const int c, const int d)					
{
	int max = 0;
	max = (a >= b ? a : b);
	max = (max >= c ? max : c);
	max = (max >= d ? max : d);
	return max;
}

/*
* function: Use recurrence to get the longest number. By finding the longest number of 
* 			the 4 position near by, and add 1 is the longest way of the exact position
* Paramenter: const int len, width, the bondary of the area, const int len_pos,wid_pos
*				the position you want to get the longest way
* Return value: the longest way of the position.
*/
int get_skee_len(const int len, const int width, const int len_pos, const int wid_pos)
{
	if (len_pos >= len || wid_pos >= width)				//if the position is out of the bondary
		return 0;										//then,end of the function
	else if (len_pos < 0 || wid_pos < 0)
		return 0;
	if (SKE_LEN[len_pos][wid_pos] > 0)
		return SKE_LEN[len_pos][wid_pos];
	else
	{													
		int left, right, up, down, temp;
		if (AREA[len_pos][wid_pos] > AREA[len_pos + 1][wid_pos])
			left = 1 + get_skee_len(len, width, len_pos + 1, wid_pos);	//recode the number of the left position
		else left = 1;

		if (AREA[len_pos][wid_pos] > AREA[len_pos][wid_pos + 1])		//recode the number of the down position
			down = 1 + get_skee_len(len, width, len_pos, wid_pos + 1);
		else down = 1;

		if (AREA[len_pos][wid_pos] > AREA[len_pos - 1][wid_pos])		//recode the number of the right position
			right = 1 + get_skee_len(len, width, len_pos - 1, wid_pos);
		else right = 1;

		if (AREA[len_pos][wid_pos] > AREA[len_pos][wid_pos - 1])		//recode the number of the up position
			up = 1 + get_skee_len(len, width, len_pos, wid_pos - 1);
		else up = 1;

		temp = max_4(left, right, up, down);		//get the largest number
		SKE_LEN[len_pos][wid_pos] = temp;			//recode the largest number
		return temp;
	}
	return 0;
}

/*
* function: To get the biggest number of the whole area, ergodic the ARRAY,
*			if one position don't ever have the longest number, use get_skee_len()
*			function to get it. 
* Paramenter: const int len width, the bondary of the array.
* Return value: the biggest number
*/
int total_sum(const int len, const int width)
{
	int max = 0;
	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			int temp;
			temp = get_skee_len(len, width, i, j);
			max = (max >= temp ? max : temp);		//find the biggest number
		}
	}
	return max;
}

int main()
{
	//freopen("15.in", "r", stdin);
	//freopen("15.ans", "w", stdout); 
	int len = 0, width = 0, max = 0;
	get_data(len, width);					//Recode the data 
	max = total_sum(len, width);
	printf("%d\n", max);					//print the biggest number
	//fclose(stdin);
	//fclose(stdout);
}
