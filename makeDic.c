#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
    char eng[20];
    char kor[60];
    int scount;
    int wcount;
} WORD;

void makewords(const char* filename, WORD* w[], int* s);
void listwords(WORD *w[], const int s);
void oxtest(WORD *w[], const int s);
void stest(WORD *w[], const int s);
void rtest(WORD *w[], const int s);
void makerandom(int range, int size, int result[]);

int main(int argc, char *argv[])
{
    WORD *d[500];
    int size = 0, menu;

    if (argc < 2)
    {
        printf("사용법 : makeDic [filename]\n");
        return 0;
    }
    srand(time(0));
    makewords(argv[1], d, &size);
    while (1)
    {
        printf("Menu : 1.list 2. O/X 3. Test A 4. Save 0.exit > ");
        scanf("%d", &menu);
        switch (menu)
        {
        case 1 : listwords(d, size);
            break;    
        case 2 : oxtest(d, size);
            break;
        case 3:
            stest(d, size);
            break;
        case 4:
            rtest(d, size);
            break;
        }
    if (menu == 0)
        break;
    }
}

void makewords(const char *filename, WORD *w[], int *s){
    char line[80];
    char eng[20], kor[60];
    FILE *f;
    int i = *s;
    f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("No such file!\n");
        exit(1);
    }
    while (!feof(f))
    {
        if (fgets(line, 80, f) == NULL)
            break;
        w[i] = (WORD*)malloc(sizeof(WORD));
        char *str = strtok(line, "\t");
        strcpy(w[i]->eng, str);
        str = strtok(NULL, "\n");
        strcpy(w[i]->kor, str);
        w[i]->scount=0;
        w[i]->wcount=0;
        i++;
    }
    *s = i;
    printf("%d words read!!\n", i);
}

void listwords(WORD *w[], const int s){
    int more;
    for(int i=0; i<s; i++){
        printf("%d %s -> %s\n", i + 1, w[i]->eng, w[i]->kor);
        if (i % 15 == 14){
            printf("Print more? (1.Yes, 0.No) > ");
            scanf("%d", &more);
            if(more==0) break; 
        }
    }
}

void makerandom(int range, int size, int result[]){
    int count=0;
    int number;
    int i;
    while(count < size){
        number = rand()%range;
        for(i=0;i<count; i++){
            if(result[i] == number) break;
        }
        if(i==count){
            result[count] = number;
            count++;
        }
    }
}

void oxtest(WORD *w[], const int s){
    int q[2], answer, ans, more;
    while(1){
        makerandom(s, 2, q);
        printf("O/X 문제 : ");
        if(rand()%2==0){
            printf("%s - %s\n", w[q[0]]->eng, w[q[0]]->kor);
            answer = 1;
        }
        else{
            printf("%s - %s\n", w[q[0]]->eng, w[q[1]]->kor);
            answer = 0;
        }
        printf("당신의 답은? (1-O, 0-X) >");
        scanf("%d", &ans);
        if(ans == answer)
            printf(" >> 정답! \n");
        else
            printf(" >> 오답! 단어의 뜻 : %s \n", w[q[0]]->kor);
        printf("--> 계속? (1-Yes, 0-No) >");
        scanf("%d", &more);
        if(more==0) break;
    }
}

void stest(WORD *w[], const int s)
{
    int q[4], answer, ans, more;
    while (1)
    {
        makerandom(s, 4, q);
        printf("객관식 문제 : ");
        answer = rand()%4;
        printf("다음 중 %s의 뜻은?\n", w[q[answer]]->eng);
        for(int i=0; i<4; i++)
            printf("(%d) %s\n", i+1, w[q[i]]->kor);
        printf("당신의 답은? >");
        scanf("%d", &ans);
        if (ans == answer+1)
            printf(" >> 정답! \n");
        else
            printf(" >> 오답! 정답은 %d번\n", answer+1);
        printf("--> 계속? (1-Yes, 0-No) >");
        scanf("%d", &more);
        if (more == 0)
            break;
    }
}

void rtest(WORD *w[], const int s)
{
    int q[80], answer[20], ans, more;
    int num;
    printf("몇 문제씩 출제할까요?(1~10) >");
    scanf("%d", &num);
    makerandom(s, num*8, q);
    printf("다음 단어의 뜻을 찾으시오.\n");
    for(int j=0; j<num; j++){
        int b=j*4;
        answer[j] = rand() % 4;
        printf("\n문제 %d. %s\n", j+1, w[q[b+answer[j]]]->eng);
        for (int i = 0; i < 4; i++)
            printf("(%d) %s\n", i + 1, w[q[b+i]]->kor);
    }
    printf("다음 뜻에 해당하는 단어를 찾으시오.\n");
    for (int j = num; j < num*2; j++)
    {
        int b = j * 4;
        answer[j] = rand() % 4;
        printf("\n문제 %d. %s\n", j + 1, w[q[b + answer[j]]]->kor);
        for (int i = 0; i < 4; i++)
            printf("(%d) %s\n", i + 1, w[q[b + i]]->eng);
    }
    printf("정답 - ");
    for (int i = 0; i < num*2; i ++)
        printf("%d.(%d) ",i+1, answer[i]+1);
    printf("\n");
}