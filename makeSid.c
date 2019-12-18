#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char* make_id(int n[]);
int main(){
    int n1, n2, n3; // n1: 1~3, n2:4~7, n3:8
    int year;
    printf("Entry year? ");
    scanf("%d", &year);

    n1 = (year/1000)*100 + (year%100);

    srand(time(0));
    n2 = rand() % 999 + 1; // 1~999

    int sum = 0;
    sum += n1 / 100;  // n1=219 --> 2
    sum += (n1%100) / 10;  // 
    sum += n1 % 10;

    sum += n2 / 100;
    sum += (n2%100) / 10;
    sum += n2 % 10;

    sum = sum % 10;
    n3 = 10 - sum;

    char sid[10];
    snprintf(sid, 10, "%3d%04d%1d", n1,n2,n3);
    printf("Your ID : %s\n", sid);
    return 0;
}

int main_old()
{
    int number[8] = {0};
    int year;
    printf("Entry year? ");
    scanf("%d", &year);
    number[0] = year / 1000;
    number[1] = (year % 100) / 10;
    number[2] = year % 10;

    srand(time(0));
    number[4] = rand() % 10;
    number[5] = rand() % 10;
    if (number[4] == 0 && number[5] == 0)
        number[6] = rand() % 9 + 1;
    else
        number[6] = rand() % 10;

    int sum = 0;
    for (int i = 0; i < 7; i++)
        sum += number[i];
    sum = sum % 10;
    number[7] = 10 - sum;

    char *sid = make_id(number);

    printf("Your ID : %s\n", sid);
    return 0;
}

char *make_id(int n[]){
    char* str = (char*)malloc(sizeof(char)*10);
    //snprintf(str, 8, "%d%d%d%d%d%d%d%d", n[0], n[1], .....)
    for(int i=0; i<8; i++)
        sprintf(str+i,"%d",n[i]);
        //snprintf(str+i, 2, "%d", n[i]);
        // str[i] *(str+i)
    return str;
}
