#include <stdio.h>
#include <time.h>

int main(){
    struct tm* current_tm;
    char entertime[20], exittime[20], carno[10];
    time_t enter_s, exit_s;
    int duration;

    printf("[IN] Enter car number >");
    scanf("%s", carno);
    enter_s = time(0);
    current_tm = localtime(&enter_s);
    sprintf(entertime, "%02d:%02d:%02d", current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec);

    printf("[OUT] Enter car number >");
    scanf("%s", carno);
    exit_s = time(0);
    current_tm = localtime(&exit_s);
    sprintf(exittime, "%02d:%02d:%02d", current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec);

    duration = exit_s - enter_s;
    printf("Parking Info : Car #%s \n", carno);
    printf("IN - %s\n", entertime);
    printf("OUT - %s\n", exittime);
    printf("Duration : %d seconds\n", duration);
}