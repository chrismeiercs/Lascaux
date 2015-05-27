#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "library.h"
int graphics_device;
void init_graphics(){
printf("Init graphics\n");
printf("Opening graphics device\n");
graphics_device = open("/dev/fb0",O_RDWR | O_APPEND);
if(graphics_device >-1){
printf("Graphics Device opened\n");
}
printf("mmap() memory\n");
printf("Screen Info\n");
printf("ioctl() syscall\n\n");


}

void exit_graphics(){
printf("exit graphics\n");
printf("Closing graphics device\n");
if(close(graphics_device) == 0){
printf("Graphics device closed\n");
}


printf("munmap() memory\n");
printf("Renable keys with ioctl\n\n");
}
