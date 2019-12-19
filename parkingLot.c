#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char carno[10]; //차번호 - 문자열 4자리.. 
    time_t enter_s; //입차시각 - time_t (long int)
    char enter_str[20]; //입차시각문자열
    time_t exit_s; //출차시각 - time_t
    char exit_str[20]; //출차시각문자열
    int fee;    //요금 - 정수
    int no; //카드일련번호 - 정수
    int duration;   //주차시간 - 정수
} PARKING;

void entercar(PARKING *p[], int* s);
void exitcar(PARKING *p[], const int s);
void listcards(PARKING *p[], const int s);
void printamount(PARKING *p[], const int s);

int main(){
    PARKING* myparking[100];
    int size=0; // 주차카드 생성 갯수
    int menu;
    while(1){
        printf("Menu : 1.Enter 2.Exit 3.List 4.Amount >> ");
        scanf("%d", &menu);
        switch(menu){
            case 1: 
                entercar(myparking, &size);
                break;
            case 2:
                exitcar(myparking, size);
                break;
            case 3:
                listcards(myparking, size);
                break;
            case 4:
                printamount(myparking, size);
                break;
            case 0 : return 0;
        }
    }
}

void entercar(PARKING *p[], int *s){
    struct tm *_tm;
    int i = *s;
    p[i] = (PARKING*)malloc(sizeof(PARKING));
    printf("[IN] Enter car number >");
    scanf("%s", p[i]->carno);
    p[i]->enter_s = time(0);
    _tm = localtime(&(p[i]->enter_s));
    sprintf(p[i]->enter_str, "%02d:%02d:%02d", _tm->tm_hour, _tm->tm_min, _tm->tm_sec);
    p[i]->duration = 0;
    p[i]->no = 100+i;
    (*s)++;
}
void exitcar(PARKING *p[], const int s){
    char carno[10];
    int i;
    printf("[OUT] Enter car number >");
    scanf("%s", carno);
    for(i=0; i<s; i++){
        if(strcmp(carno, p[i]->carno)==0) break;
    }
    if (i==s) {
        printf("No such car!!\n");
        return;
    }

    p[i]->exit_s = time(0);
    struct tm* _tm = localtime(&(p[i]->exit_s));
    sprintf(p[i]->exit_str, "%02d:%02d:%02d", _tm->tm_hour, _tm->tm_min, _tm->tm_sec);
    p[i]->duration = p[i]->exit_s - p[i]->enter_s;
    p[i]->fee = ((p[i]->duration + 10)/10)*500;
}
void listcards(PARKING *p[], const int s){
    printf("No Car#     IN     OUT    time  fee\n");
    for (int i = 0; i < s; i++)
    {
        if(p[i]->duration == 0)
            printf("%d %s %s\n", p[i]->no, p[i]->carno, p[i]->enter_str);
        else
            printf("%d %s %s %s %d %d\n", p[i]->no, p[i]->carno, p[i]->enter_str, p[i]->exit_str, p[i]->duration, p[i]->fee);
    }
}
void printamount(PARKING *p[], const int s){
    int sum=0, count=0;
    for (int i = 0; i < s; i++)
        if (p[i]->duration > 0){
            sum += p[i]->fee;
            count++;
        }
    printf("Total %d cars, %dwon\n", count, sum);
}
