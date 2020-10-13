#include<stdio.h>
#define length sizeof(elem)*8
#define OK 1
#define ERROR 0 
typedef int status;
typedef unsigned short elem;

status getbit(elem num,int data[])
{
	for (int i = 1; i <= length; i++)
	{
		elem a = num;
		num = num << 1;
		if (num == 2 * a)
			data[i] = 0;
		else
			data[i] = 1;	
//		printf("%d", data[i]);
	}
//	printf("\n");
	return OK;
}

status data_compare(int data_x[], int data_y[])
{
	int flag = 0;
	for (int i = 0; i < length; i++)
	{
		flag = 1;
		for (int j = 0; j < length; j++)
		{
	//		printf("%d_%d\n", data_x[(i + j) % (length + 1)], data_y[j + 1]);
			if (data_x[(i + j) % (length+1)] != data_y[j+1])
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
			return OK;
	}
	return ERROR;
}

/*int main()
{
	elem x,y;
	int spec,time;
	int data_x[length+1], data_y[length+1];
	scanf("%d", &time);
	for (int j = 0; j < time; j++) {
		for (int i = 0; i <= length; i++)
		{
			data_x[i] = 0;
			data_y[i] = 0;
		}
		scanf("%u%u%d", &x, &y, &spec);
		getbit(x, data_x);
		getbit(y, data_y);
		data_x[0] = spec;

		if (data_compare(data_x, data_y) == OK)
			printf("YES\n");
		else
			printf("NO\n");
	}
	
}			 */


