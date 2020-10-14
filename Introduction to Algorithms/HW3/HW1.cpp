#define _CRT_SECURE_NO_WARNINGS
/*
    Get_num_frequence/main.c
    (C) 2020 USTC_GAOWAY
*/

#include<stdio.h>
#include <stdlib.h>

typedef struct {
    int number; 
    int times;  //frequence of number
}data;

int compare_info(const void* a, const void* b) {
    int times_a = (*(data*)a).times;
    int times_b = (*(data*)b).times;
    int num_a = (*(data*)a).number;
    int num_b = (*(data*)b).number;
    if (times_a > times_b)          //first compare the frequence
        return 0;
    else if (times_a < times_b)
        return 1;
    else if (num_a > num_b)
        return 1;
    else
        return 0;
}

int main() {
    int total = 0,count =0;             // conut is the number of diff data

    scanf("%d", &total);

    data* info = new data[total];       //give the data zone

    for (int i = 0; i < total; ++i) {
        int temp = 0;
        scanf("%d", &temp);
        int j = 0;
        for (j = 0; j < count; ++j) {   //if the number in the info array, only add times
            if (info[j].number == temp) {
                info[j].times++;
                break;
            }
        }

        if (j == count) {
            info[count].number = temp;
            info[count].times = 1;
            count++;
        }
    }

    qsort(info, count, sizeof(data), compare_info);     //info has the count number of data(the diff num)

    for (int i = 0; i < count; ++i) {                   //relop 'count' times
        printf("%d ", info[i].number);
        printf("%d\n", info[i].times);
    }
    return 0;
}
