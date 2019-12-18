#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char line[200];
    char* words[20];
    int count=0;
    printf("Enter a line >> ");
    fgets(line, 200, stdin);
    line[strlen(line)-1]='\0';
    char* ptr = strtok(line, " ");
    while(ptr){
        words[count] = (char*)malloc(sizeof(char)*strlen(ptr));
        strcpy(words[count], ptr);
        count++;
        ptr = strtok(NULL, " ");
    }
    printf("total %d Words\n", count);
    for(int i=0; i<count; i++){
        int index=i;
        for(int j=0; j<count; j++){
           printf("%s ", words[index]);
           index = (index+1)%count;
        }
        printf("\n");
    }
}