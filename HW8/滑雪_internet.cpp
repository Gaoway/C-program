#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
int a[105][105];//用于接受数据 
int b[105][105] = { 0 };//初始化状态，0表示该点没有用过，之后用该点的最大滑雪长度覆盖这个值 
int c[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };//表示四个方向x,y的改变值
int n, m;//设行和列为全局变量，此为定义的函数的遍历需要 
int maxlen(int i, int j);//定义求最大滑雪长度的函数

int main()
{
	freopen("20.in", "r", stdin);
	freopen("20.ans", "w", stdout); // Do not write "1.out" or the answer output will be cleared

	int i, j;
	scanf("%d %d", &n, &m);
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			scanf("%d", &a[i][j]);
	int max = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++) {
			b[i][j] = maxlen(i, j);//求出该点的最大滑雪长度 
			if (b[i][j] > max)	//比较各点的最大长度，找到最大的那个值 
				max = b[i][j];
		}
	printf("%d", max);
		fclose(stdin);
	fclose(stdout);

}
int maxlen(int i, int j)
{
	if (b[i][j] != 0)	return b[i][j];
	int k, x, y;
	int s; int max = 0;
	for (k = 0; k < 4; k++) {
		x = i + c[k][0]; y = j + c[k][1];
		if ((x >= 0 && x < n) && (y >= 0 && y < m) && (a[x][y] < a[i][j])) {//边界条件，x,y在范围内，该点的值比原来的点的值要小 
			s = maxlen(x, y);//求出该方向的点的最大滑雪长度 
			if (s > max)	max = s;//比较并求出四个方向的最大滑雪长度 
		}
	}
	b[i][j] = max + 1;//之前的最大长度加上这个新的点 
	return max + 1;
}
