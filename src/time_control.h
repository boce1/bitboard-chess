#ifndef TIME_CONTROL_H
#define TIME_CONTROL_H

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/time.h>
#endif
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int quit;
    int movestogo; // UCI "movestogo" command moves counter
    int movetime; // UCI "movetime" command time counter
    int time; // UCI "time" command holder (ms)
    int inc; // UCI "inc" command's time increment holder
    int starttime; // UCI "starttime" command time holder
    int stoptime; // UCI "stoptime" command time holder
    int timeset; // variable to flag time control availability
    int stopped; // variable to flag when the time is up
} time_controls;

time_controls* create_time_controls();
void init_time_controls(time_controls* info);
int get_time_ms();
int input_waiting();
void read_input(time_controls* info);
void communicate(time_controls* info);

#endif // TIME_CONTROL_H