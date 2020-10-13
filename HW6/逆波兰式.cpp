/*
 *  main.c
 *
 *  (C) 2020 USTC_GAOWAY
 */
#include <stdio.h>
#include <string.h>

#define LEN 100							
#define MAX_LEN LEN

#define LCHILD(num) (stack[stack[num].rchild].lchild-1) 

typedef struct 
{
	/*
	* information of students. Use the Binary tree to show the Intermediate Polish
	* member:
	* exp: the operator and the number between '0' and '9'
	* lchild: the position of left expression of operator.  
	* rchild: the position of right expression of operator.
	*/
	char exp;
	unsigned short lchild,rchild;
}node;

node stack [MAX_LEN];			//the data of the expression
 
/*
* function: assume the number is level 0, the '+ and '-' is level 1. And '*' and '/'
*			is level 2. To rate the chareator input.
* Paramenter: char a: the charator going to be rated
* return value: the rate of the charator 
*/
inline int get_leval(char a)
{
	if (a >= '0' && a <= '9')
		return 0;
	else if (a == '+' || a == '-')
		return 1;
	else if (a == '*' || a == '/')
		return 2;
	else
		return -1;					// if the charator is not the target, return -1.
}

/*
* function: the right expression is close the exp, and the left expression is close to the right 
*			expression, not close to exp. the function is to get the position od the left child.
* Paramenter: the position of the current position
* return value: the position of the left child 
*/
inline int get_leftchlid(int num)
{
	int right = stack[num].rchild;				//search the right chlid.

	while (get_leval(stack[right].exp) != 0)	//search the left child's left child, until it is number. 
		right = stack[right].lchild;

	return right - 1;							//the position of left child is close to the right child 
}

/*
* function: To get the Binary tree while getting the standard input.			
*
* return value: the length of the expression.
*/
int get_line()
{
	int num = 0;			//initial the length of the expression
	for (;;)
	{
		char temp;			
		if (get_leval(temp = getchar()) != -1)		  //if the charator is not the data we want, end of the function
		{
			if (get_leval(temp)== 0)				  //if the charator is number. the lchid and rchild is itself
			{
				stack[num].exp = temp;
				stack[num].lchild = stack[num].rchild = num;
				num++;
			}
			else									 //if the charator is operator, the rchild cloes to it and lchild is get_left()
			{
				stack[num].exp = temp;
				stack[num].rchild = num - 1;
				stack[num].lchild = get_leftchlid(num);
				num++;
			}
		}
		else
			break;
	}
	return num-1;
}

/*
* function: get the length of expression and the data in the stack, use In-order traversal
*			to out-put the expression 
* paramenter: int num: the length of the expression, int old_leval: the leval of the old charator.
*				int position : to get the exp is the lchild or right child
* 
*/
void put_polish(int num,int old_leval,int position)		  
{
	int new_leval = get_leval(stack[num].exp);		//get new leval
	if (new_leval == 0)								//if the charator is number print it 
	{
		putchar(stack[num].exp);
		return;
	}
	if(new_leval<=old_leval&&position==1)				// if in the rchild and newleval<=oldleval, print '()'
		printf("(");
	else if (new_leval < old_leval && position == 0)	//if in the lchild and newleval<oldleval, print '()'
		printf("(");

	put_polish(stack[num].lchild,new_leval,0);			//go to the left_child. 

	putchar(stack[num].exp);							//print the charator 

	put_polish(stack[num].rchild,new_leval,1);			//go to the right_child

	if (new_leval <= old_leval && position == 1)
		printf(")");
	else if (new_leval < old_leval && position == 0)
		printf(")");
}
										    
int main()
{
	//freopen("6.in", "r", stdin);
	//freopen("6.ans", "w", stdout); // Do not write "1.out" or the answer output will be cleared
	int num=get_line();				//get the length and give the number to put_polish() function.
	put_polish(num,-1,0);
	//fclose(stdin);
	//fclose(stdout);
}