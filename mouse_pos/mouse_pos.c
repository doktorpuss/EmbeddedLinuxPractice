#include<stdio.h>
#include<stdlib.h>
#include<linux/input.h>
#include<fcntl.h>
#include<unistd.h>  
#include<string.h>

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

char **getInputDevicesList()
{
    char **devices_list = NULL;
    int num_devices = 0;


    // Read /proc/bus/input/devices
    char *buffer = NULL;
    buffer = readInputsDevicesFile(); 
    if (buffer == NULL) return NULL;
    
    // First device extraction
    num_devices++; 
    devices_list == (char**) calloc(num_devices , sizeof(char*));
    devices_list[num_devices-1] = (char*) calloc(DEVICE_INFO_SIZE , sizeof(char));
    *(devices_list[num_devices-1]) = *(strtok(buffer,"\n"));

    


    return devices_list;
}

int main() {
    char *content = NULL;

    content = readInputsDevicesFile();
    if (content == NULL){
        perror("Can't read /proc/bus/input/devices");
        return -1;
    }


    printf("%s \n size: %ld",content,strlen(content));

    free(content);
    
    return 0;
}