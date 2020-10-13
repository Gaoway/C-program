/*
 *  Marginal_sea/main.c
 *
 *  (C) 2020 USTC_GAOWAY
 */
#include <stdio.h>
#include<string.h>
#define MAX_LEN 2010			// the maximum of length and width 

const char LAND='*';			// define the area not count as "*"
const char LAND_C='$';			// define the area has counted as "$"
const char SEA = '#';			// define the sea as "#"

char area[MAX_LEN][MAX_LEN];	//recode the whole area  

/*
* function: to get the whole area data 
* Paramenter: int  &len the length of the area, int &width the width of the area			
*/
void getdata(int &len,int &width)
{
	scanf("%d %d ", &len,&width);
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < width; j++)		  // C11 does't allow gets()function, use getchar() funtion.
			area[i][j] = getchar();
		getchar();							  //to get the '\n' in the end 
	}
}

/*
* function: To get the bondary of the current area, the bondary is rectangle, we need to know the max_len
*			the min_len, the max_width, the min_width 
* Paramenter: int pos_len, int pos_width the position of the current coordinate.
*			  int &min_len, int &max_len ,int &min_width, int &max_width the bondary of the exact rectange 
*/
void bondary(int pos_len,int pos_width,int& min_len, int& max_len,int &min_width,int &max_width)
{
	if ((pos_len >MAX_LEN) || (pos_len < 0))			//if the position is beyond the mark, end the func.
		return;
	else if ((pos_width > MAX_LEN) || (pos_width < 0))
		return;
	else if (area[pos_len][pos_width] == LAND)			//if the position is the LAND not counted, turn is as LAND_C (counted)
	{
		area[pos_len][pos_width] = LAND_C;
	}
	else												//if the position is SEA or the LAND_C (counted land) end the func 
		return;

	max_len = (pos_len > max_len ? pos_len : max_len);	//if the position is out of the bondary, extend the bondary 
	min_len = (pos_len < min_len ? pos_len : min_len);
	max_width = (pos_width > max_width ? pos_width : max_width);
	min_width = (pos_width < min_width ? pos_width : min_width);
	//use the deep first search ton find the LAND not counted
	bondary(pos_len+1, pos_width, min_len, max_len, min_width, max_width);		//search north 	
	bondary(pos_len, pos_width+1, min_len, max_len, min_width, max_width);		//search east 
	bondary(pos_len+1, pos_width+1, min_len, max_len, min_width, max_width);	//search north east 
	bondary(pos_len-1, pos_width, min_len, max_len, min_width, max_width);		//search south
	bondary(pos_len, pos_width-1, min_len, max_len, min_width, max_width);		//search west 
	bondary(pos_len-1, pos_width-1, min_len, max_len, min_width, max_width);	//search south west 
	bondary(pos_len-1, pos_width+1, min_len, max_len, min_width, max_width);	//search south east 
	bondary(pos_len+1, pos_width-1, min_len, max_len, min_width, max_width);	//search north west

	return;												//end of the func
}

/*
* function: input the bondary and count the number of SEA
* Paramenter: int min_len, int max_len ,int min_width, int max_width the bondary of the exact rectange
* return value: the number of the sea (marginal sea)
*/
int count_sea(int min_len, int max_len, int min_width, int max_width)
{
	int sea_num = 0;								   //initial the number of SEA
	for (int i = min_len; i <= max_len; i++)
	{
		for (int j = min_width; j <= max_width; j++)
		{
			if (area[i][j] == SEA)
				sea_num++;
		}
	}
	return sea_num;
}

/*
* function: in the whole area, we compare all of the marginal sea, and use the bondary() and count() function to 
*			get the max number of the marginal sea.
* Paramenter: int len. the length of the whole area, int width the width of the whole area.
* return value : the maximum of marginal sea.			  
*/
int find_max(int len, int width)
{
	int max_sea_num = 0;					//initial sea number 
	for (int i = 0; i < len; i++)			//select all of the area one by one
	{
		for (int j = 0; j < width; j++)
		{
			if (area[i][j] == LAND)
			{
				int min_len = MAX_LEN, min_width = MAX_LEN;		 //initial the nunmber 
				int max_len = 0, max_width = 0;
				int sea_num = 0;
				bondary(i, j, min_len, max_len, min_width, max_width);
				sea_num = count_sea(min_len, max_len, min_width, max_width);		
//				printf("sea %d\n", sea_num);
				max_sea_num = (sea_num > max_sea_num ? sea_num : max_sea_num);	   //compare and get the maximum 
			}
		}
	}
	return max_sea_num;
}

int main()
{
	//freopen("10.in", "r", stdin);
	//freopen("10.ans", "w", stdout); // Do not write "1.out" or the answer output will be cleared
	memset(area, 0, sizeof(char) * MAX_LEN * MAX_LEN);		//initial the area
	int len = 0, width = 0, sea_num = 0;
	getdata(len, width);
	sea_num = find_max(len, width);
	printf("%d\n", sea_num);
	/*fclose(stdin);
	fclose(stdout);*/
}

