// #include<stdio.h>
#include<stdlib.h>                  // free(), calloc(), realloc()
#include<fcntl.h>                   // open(), close()
#include<unistd.h>                  // uint*_t
#include<string.h>                  // strtok(), strstr(), strlen()
#include<linux/input.h>             // struct input_event
#include<my_strlib.h>               // strsplit()

#ifndef __MY_DEVICE__
#define __MY_DEVICE__

char *readInputsDevicesFile();
int getInputDevicesList(char ***device_list);
void freeInputDevicesList(char **list, int num_device);

#endif