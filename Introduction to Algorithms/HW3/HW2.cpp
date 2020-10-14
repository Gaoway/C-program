#define _CRT_SECURE_NO_WARNINGS
/*
    Students' grade sort/main.c
    (C) 2020 USTC_GAOWAY 
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    /* data */
    int id;
    short math;
    short english;
} student;

int student_grade_rank(const void *a, const void *b)
{
    short math_1 = (*(student *)a).math;
    short math_2 = (*(student *)b).math;
    short eng_1 = (*(student *)a).english;
    short eng_2 = (*(student *)b).english;
    int id_1 = (*(student *)a).id;
    int id_2 = (*(student *)b).id;
    short total_1 = math_1 + eng_1;
    short total_2 = math_2 + eng_2;

    if (total_1 > total_2)              //total grade first, math grade second, id_num third
        return 0;
    else if (total_1 < total_2)
        return 1;
    else if (math_1 > math_2)
        return 0;
    else if (math_1 < math_2)
        return 1;
    else if (eng_1 > eng_2)
        return 0;
    else if (eng_1 < eng_2)
        return 1;
    else if (id_1 < id_2)
        return 1;
    else
        return 0;
}

int main()
{
    int total = 0;
    scanf("%d", &total);
    student* info = new student[total];
    
    for (int i = 0; i < total; ++i)
    {
        scanf("%d", &info[i].id);
        scanf("%d", &info[i].math);
        scanf("%d", &info[i].english);
    }
    qsort(info, total, sizeof(student), student_grade_rank);    //use qsort to compare
    printf("%d", info[0].id);
    for (int i = 1; i < total; ++i)
        printf(" %d", info[i].id);
    return 0;
}