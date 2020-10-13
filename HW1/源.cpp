#include<stdio.h>
#include <string.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0 
#define PRST_A 0.40
#define PRST_B 0.05

typedef int status;

typedef struct
{
	/*
	*	information of students.
	*	member:
	*	name: as problem description indicates
	*	id: as problem description indicates
	*	grade: from 0 to 100
	*	grade_f: from 0 to 100 as the finally grade the students gets
	*/
	char name[21];
	char id[11];
	int grade;	
	int grade_f;
}student;

student* getdata(int num)
{
	/*
	*	information of getdata(int num)
	*	num : as the number of students
	*	info[num] recodes all students' information
	*	use gets function to recode strings.
	*	return info[num]
	*/
	student* info =new student[num];
	for (int i = 0; i < num; i++)
	{
		getchar();
		gets(info[i].name);
		gets(info[i].id);
		scanf("%d", &info[i].grade);
		info[i].grade_f = info[i].grade;
	}
	return info;
}
	
int cmp(const void* a, const void* b)
{
	/*
	*	information of cmp
	*	if the two student's final grades equal to each other and student a's id 
	*	less than student b's return 0, else return 1
	*	if a's final grade less than b's return 1 else return 0
	*/
	if ((*(student*)a).grade_f == (*(student*)b).grade_f)
		return (strcmp((*(student*)a).id, (*(student*)b).id));
	else
		return (*(student*)b).grade_f - (*(student*)a).grade_f;
}

void getregion(student* info, int num, int* up_grade, int* down_grade)
{
	/*
	*	 info of get region
	*	 to get the range of [x-100] and the range of [0-y]
	*	 
	*/
	int up_num = 0, down_num = 0, fail = 0;
	int tmp_x = *up_grade, tmp_y = *down_grade;		//to recode the temperary of x and y 
	qsort(info, num, sizeof(student), cmp);			//use the sysytem function of qsort by cmp
	up_num = (int)num * PRST_A;						//up_num and down_num is number of students who are ultra and failed
	down_num = (int)num * PRST_B;

	*down_grade = info[num - 1].grade;				//to refresh x and y
	*up_grade = info[0].grade;
	for (int i = 0; i < num; i++)					//to make sure the number of high grades students below up_num
	{
		*up_grade = info[up_num].grade;
		if (info[i].grade < 60)						//recoder of the grades below 60
			fail++;
		tmp_y = info[num - 1 - down_num].grade;
		
		if ((i >num-1-down_num) && info[i].grade < tmp_y)
		{
			*down_grade = tmp_y;
			tmp_y = info[num - 1 - i].grade;
		}
	}

	(*up_grade)++; (*down_grade)--;
	if (fail <= down_num)							//if the recoder less than 5% of students, change down_grade as 59
	{
		*down_grade = 59;
		down_num = fail;
	}
}

void tramsfer(student* info, int num,int up_grade,int down_grade)
{
	/*
	*	 info of transfer 
	*	 to change the students' final grade 
	*	 use the date website give
	*/
	int minus = 0;
	for (int i = 0; i < num; i++)
	{
		if (info[i].grade >= up_grade)															//the students's final grades up the 85
		{
			info[i].grade_f = 85 + (15 * (info[i].grade - up_grade) / (100 - up_grade));		//use the equation of up_grade
		}
		else if ((info[i].grade < up_grade) && (info[i].grade >= down_grade))					// the student's grades between 85 and 60
		{
			info[i].grade_f = 60 + (24 * (info[i].grade - down_grade - 1) / (up_grade - 2 - down_grade));
		}																						//use the equation of down_grade
		if ((info[i].grade <= down_grade))									 //the students' grades less than 85
		{
			if ((info[i].grade < info[i - 1].grade)&&(minus<10))			//minus is the rank of the students who below 60
				minus++;
			info[i].grade_f = 60 - minus;
		}			
	}
	qsort(info, num, sizeof(student), cmp);
}

status printinfo(student* info, int num)
{
	for (int i = 0; i < num; i++)
	{
		puts(info[i].name);
		printf("%d\n", info[i].grade_f);
	 }
	return OK;
}

int main()
{
//	freopen("7.in", "r", stdin);
//	freopen("7.ans", "w", stdout); // Do not write "1.out" or the answer output will be cleared

	int num = 0, up_grade = 101, down_grade =-1 ;
	scanf("%d", &num);
	student* info = getdata(num);			//结构体数组

	getregion(info, num, &up_grade, &down_grade);
	tramsfer(info, num, up_grade, down_grade);		//if the don't use the function it fix the question of D
	
	printinfo(info, num);
//	fclose(stdin);
//	fclose(stdout);
}


