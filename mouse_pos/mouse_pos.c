#include<stdio.h>
#include<stdlib.h>
#include<linux/input.h>
#include<fcntl.h>
#include<unistd.h>  
#include<string.h>
#include<my_strlib.h>

#define READ_SIZE 1024 
#define DEVICE_INFO_SIZE 512

char *readInputsDevicesFile()
{
    int devices_fd = open("/proc/bus/input/devices", O_RDONLY);
    if (devices_fd < 0) return NULL;

    char *buffer = (char*)calloc(READ_SIZE,sizeof(char));
    char *content = NULL;
    int file_size = 0;
    int read_size = 0;

    while ((read_size = read(devices_fd,buffer,READ_SIZE)) > 0)
    {
        content = realloc(content,file_size + read_size + 1);
        memcpy(content + file_size,buffer,read_size);
        file_size += read_size;
        content[file_size] = '\0';
    }

    
    free(buffer);
    close(devices_fd);

    return content;
}

// Read input device file, 
// point device_list pointer to splited device list,
// return number of input devices
int getInputDevicesList(char ***device_list)
{
    *device_list = NULL;
    int capacity = 8;
    int count = 0;

    // read input device file
    char *buffer = readInputsDevicesFile();
    if (!buffer) return 0;

    *device_list = malloc(capacity * sizeof(char*));

    char *walker = buffer;
    char *dev = strsplit(walker, "\n\n");  // get first de

    while (dev != NULL)
    {
        // resize list if need
        if (count >= capacity) {
            capacity *= 2;
            *device_list = realloc(*device_list, capacity * sizeof(char*));
        }

        // store device info
        (*device_list)[count] = malloc(strlen(dev) + 1);
        strcpy((*device_list)[count], dev);
        count++;

        // find next input device
        dev = strsplit(NULL, "\n\n");     
    }

    free(buffer);
    return count - 1; 
}

void freeInputDevicesList(char **list, int num_device)
{
    for (int i = 0; i < num_device; i++) free(list[i]);
        free(list);
}


int main() {
    char **list;
    int n = getInputDevicesList(&list);

    for (int i = 0; i < n; i++)
        printf("Device %d:\n%s\n\n", i, list[i]);

    printf("Found %d devices\n",n);

    freeInputDevicesList(list,n);
    
    return 0;
}