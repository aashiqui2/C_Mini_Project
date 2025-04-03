//! Docs:https://en.cppreference.com/w/cpp/chrono/c/strftime
#include <stdio.h>
#include <time.h>
int main()
{
    //? time_t is a data type in C used to represent time values.
    time_t raw_time;
    struct tm *current_time; // struct tm is a structure in C that represents broken-down time (year, month, day, hour, etc.).

    char buffer[50];

    time(&raw_time);
    current_time = localtime(&raw_time);
    strftime(buffer, 50, "%I:%M:%S %p", current_time);//12 hours time
    // strftime(buffer, 50, "%H:%M:%S", current_time);//24 hours time
    printf("%s", buffer);
    return 0;
}