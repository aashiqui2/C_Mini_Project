//! Docs:https://en.cppreference.com/w/cpp/chrono/c/strftime
#include <stdio.h>
#include <time.h>
void fill_time(char[]);
int main()
{
    // char *time = get_time();
    char time[50];
    fill_time(time);
    printf("%s", time);
    return 0;
}

void fill_time(char buffer[]) // array by default call by reference
{
    time_t raw_time;
    struct tm *current_time;

    // static char buffer[50]; //? we can make it static because at retunr time the addres of buffer deleted

    time(&raw_time);
    current_time = localtime(&raw_time);
    strftime(buffer, 50, "%I:%M:%S %p", current_time);
}