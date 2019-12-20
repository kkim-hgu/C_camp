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

typedef struct Node
{
    PARKING* data;
    struct Node* next;
} Node;

Node* insert_end(Node* head);
Node* sort_list(Node* head);
void display(Node* head);
void update_node(Node* head);
void amount(Node* head);


int main(int argc, char *argv[])
{
    Node* start = NULL;
    int option;
    do
    {
        printf("Menu : 1.Enter 2.Exit 3.List 4.Amount 5.Sort >> ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            start = insert_end(start);
            break;
        case 2:
            update_node(start);
            break;
        case 3:
            display(start);
            break;
        case 4:
            amount(start);
            break;
        case 5:
            start = sort_list(start);
            break;
        }
    } while (option != 0);
    return 0;
}

void display(Node* head){
    Node* ptr;
    ptr = head;
    printf("No Car#     IN     OUT    time  fee\n");
 
    while (ptr != NULL)
    {
        printf("%d %s %s ", ptr->data->no, ptr->data->carno, ptr->data->enter_str);
        if(ptr->data->duration > 0)
            printf("%s %d %d", ptr->data->exit_str, ptr->data->duration, ptr->data->fee);
        printf("\n");
        ptr = ptr->next;
    }
}

void amount(Node* head){
    int sum=0, count=0;
    Node* ptr;
    ptr = head;
 
    while (ptr != NULL)
    {
        if(ptr->data->duration > 0){
            sum += ptr->data->fee;
            count++;
        }
        ptr = ptr->next;
    }
    printf("Total %d cars, %dwon\n", count, sum);
}

Node* insert_end(Node* head){
    Node* ptr;
    Node* new_node;
    PARKING* newcard;
    int num=100;
    struct tm* _tm;
    
    newcard = (PARKING*)malloc(sizeof(PARKING));
    printf("[IN] Enter car number >");
    scanf("%s", newcard->carno);
    newcard->enter_s = time(0);
    _tm = localtime(&(newcard->enter_s));
    sprintf(newcard->enter_str, "%02d:%02d:%02d", _tm->tm_hour, _tm->tm_min, _tm->tm_sec);
    newcard->duration = 0;

    new_node = (Node* ) malloc(sizeof(Node));
    new_node->data = newcard;
    new_node->next = NULL;

    if (head == NULL){
        head = new_node;
    }
    else{
        ptr = head;
        num = ptr->data->no;
        while (ptr->next != NULL){
            if (num < ptr->next->data->no) num = ptr->next->data->no;
            ptr = ptr->next;
        }
        ptr->next = new_node;
    }
    newcard->no = 1+num;
    return head;
}

void update_node(Node* head){
    Node* ptr;
    Node* preptr;

    char carno[10];
    int found=0;
    printf("[OUT] Enter car number >");
    scanf("%s", carno);

    ptr = head;
    while (ptr != NULL){
        if(strcmp(carno, ptr->data->carno)==0) {
            found = 1;
            break;
        }
        ptr = ptr->next;
    }
    if (found==0) {
        printf("No such car!!\n");
        return;
    }

    ptr->data->exit_s = time(0);
    struct tm* _tm = localtime(&(ptr->data->exit_s));
    sprintf(ptr->data->exit_str, "%02d:%02d:%02d", _tm->tm_hour, _tm->tm_min, _tm->tm_sec);
    ptr->data->duration = ptr->data->exit_s - ptr->data->enter_s;
    ptr->data->fee = ((ptr->data->duration + 10)/10)*500;
}

Node* sort_list(Node* head){
    Node* ptr1;
    Node* ptr2;
    PARKING* temp;
    if(head != NULL){
        ptr1 = head;
        while (ptr1->next != NULL)
        {
            ptr2 = ptr1->next;
            while (ptr2 != NULL)
            {
                if (ptr1->data->duration < ptr2->data->duration)
                {
                    temp = ptr1->data;
                    ptr1->data = ptr2->data;
                    ptr2->data = temp;
                }
                ptr2 = ptr2->next;
            }
            ptr1 = ptr1->next;
        }
    }
    return head; // Had to be added
}