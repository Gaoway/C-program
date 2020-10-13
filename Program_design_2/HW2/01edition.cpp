#include <stdio.h>
#define N_MAX 2000			//the maximum of the numuber of cities
#define Ci_MAX 100000		//the maximum of the numuber of cities' Charisma 
typedef unsigned long long elem;		//means that unsigned long long type can only code the number 

elem get_summary(int *Ci,int *capital,int n_num,int k_num,elem &cap_adds)
{
	/**
	* Introduction:
	*		Totally, the function wants to devide the fianl number into two parts
	*	the one is summary, which means that we can use the Law of multiplication
	*	to summary up all of the roads' cost, but it makes some repetition.
	*	
	*	So, the next function is going to summary up the extraty cost of all roads.
	*
	*	Paramenters :
	*	int Ci[n_number] recode the all of cities' Charism , int capital[k_num] recode the indetifier of 
	*	the capitals ,int  n_num is the number of cities ,int k_num is the number of capitals 
	*	elem &cap_adds to recode the extra part of capitals 
	*
	*	 Return values 
	*	 the summary of the roads' costs including the repetition costs
	*/
	elem adds = 0,sum=0;				//add is the summary parts and use the Law of multiplication.

	for (int i = 0; i < n_num; i++)
	{
		scanf("%d", &Ci[i]);
		adds += Ci[i];
		if (i > 0)
			sum += (elem)Ci[i] * (elem)Ci[i - 1];		//computing the one part of summary, the cost of anastomosis of cities's road
	}

	sum += (elem)Ci[n_num - 1] * (elem)Ci[0];			//the cost of the first city and the last city

	for (int i = 0; i < k_num; i++)
	{
		scanf("%d", &capital[i]);
		capital[i]--;
		cap_adds += Ci[capital[i]];						//the cost of the capital cities and other cities (include the situaltion of repetition)

		sum += Ci[capital[i]] * adds;					//use Law of multiplication
	}

	return sum;
}

elem get_extra(int* Ci, int* capital, int n_num, int k_num, elem cap_adds)
{
	/**
	*	Introduction:
	*	As following, thism part is to summary part of the cost of extra.
	*	
	*	Paramenters :
	*	int Ci[n_number] recode the all of cities' Charism , int capital[k_num] recode the indetifier of 
	*	the capitals ,int  n_num is the number of cities ,int k_num is the number of capitals 
	*	elem &cap_adds to recode the extra part of capitals 
	*
	*	 return value 
	*	 the extra costs of the roads and we can also use the Law of multiplication
	*
	*/
	elem extra = 0;				//The extra costs 

	for (int i = 0; i < k_num; i++)
	{
		extra += cap_adds * Ci[capital[i]];					//Because of the Law of multiplication, we have to halve the number but we 
															//don't know whether the number is odd, so we dobule the number and halve it fianlly
		extra += (elem)Ci[capital[i]] * (elem)Ci[(capital[i] + 1) % n_num] * 2;		//the cost of capital cities and the other capital cities 
		extra += (elem)Ci[capital[i]] * (elem)Ci[(capital[i] - 1 + n_num) % n_num] * 2;		//the cose of the capital cities and the anastomosis cities 
		extra += (elem)Ci[capital[i]] * (elem)Ci[capital[i]];			//use the Law of multiplication

		if (capital[i + 1] - capital[i] == 1 || capital[(i + 1) % k_num] - capital[i] == -n_num + 1)
			extra -= 2 * (elem)Ci[capital[(i + 1) % k_num]] * (elem)Ci[capital[i]];		  //Consider the special condition that the two capitals is anastomosis.
	}

	extra /= 2;					//to halve the cost fianlly
	return extra;
}

int main()
{
	elem sum= 0, extra = 0, cap_adds = 0;		//intalize the recoder paramenters 

	int n_num = 0, k_num = 0;					//the cities' number and the capital number
	int* Ci, * capital;							//the cities's Charisma and the indetifier of the capitals
	scanf("%d", &n_num);
	scanf("%d", &k_num);

	Ci = new int[n_num];
	capital = new int[k_num];

	sum=get_summary(Ci, capital, n_num, k_num, cap_adds);

	extra=get_extra(Ci, capital, n_num, k_num, cap_adds);

	sum -= extra;
	printf("%lld", sum);						 //to have the fianl number 

}//100 lines is my last stubbornness QAQ