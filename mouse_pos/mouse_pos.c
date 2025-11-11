#include<stdio.h>
#include<stdlib.h>
#include<linux/input.h>
#include<fcntl.h>
#include<unistd.h>  // uint*_t
#include<string.h>
#include<my_strlib.h>
#include<my_device.h>

int main() {
    char **list;
    int n = getInputDevicesList(&list);

    char *event;
    for (int i = 0; i < n; i++)
        // printf("Device %d:\n%s\n\n", i, list[i]);
        if (strstr(list[i],"mouse")!=NULL)
        {
            event = strstr(list[i],"event");
            event = strsplit(event,"\n");
            printf("Device%d\t\t %s\n", i, event);
        }

    printf("Found %d devices\n",n);

    freeInputDevicesList(list,n);
    
    return 0;
}