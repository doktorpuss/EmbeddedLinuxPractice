#include<stdio.h> // printf(), sprintf()
#include<stdlib.h>
#include<linux/input.h>
#include<fcntl.h>
#include<unistd.h>  // uint*_t
#include<string.h>
#include<my_strlib.h>
#include<my_device.h>

int main() {

    // Get input devices list
    char **list;
    int n = getInputDevicesList(&list);

    // Find USB Mouse
    char *event;
    for (int i = 0; i < n; i++)
    {
        // printf("Device %d:\n%s\n\n", i, list[i]);
        if (strstr(list[i],"mouse")!=NULL && strstr(list[i],"Phys=usb")!=NULL)
        {
            event = strstr(list[i],"event");
            event = strsplit(event," ");
            printf("%s\n\n",list[i]);

        }
    }

    printf("%s\n",event);
    // Make event path
    printf("1\n");
    char device[32];
    sprintf(device,"/dev/input/%s",event);
    printf("%soke\n",device);

    struct input_event mouse_ev;
    int x = 0;
    int y = 0;

    // Open device's event file
    int mouse_fd = open(device,O_RDONLY);
    if (mouse_fd < 0)
    {
        printf("%d\n",mouse_fd);
        perror("Open device event file failed\n");
        return -1;
    }

    // Loop cycle
    while(1)
    {
        read(mouse_fd, &mouse_ev, sizeof(struct input_event));

        if(mouse_ev.type == EV_REL)
        {
            if (mouse_ev.code == REL_X) x += mouse_ev.value;
            if (mouse_ev.code == REL_Y) y += mouse_ev.value;

            system("clear");
            printf("%d\t\t%d\n",x,y);
        }
    }


    freeInputDevicesList(list,n);

    close(mouse_fd);
    return 0;
}