#include <stdio.h>
#include "library.h"

void init_graphics(){
printf("Init graphics\n");
printf("Open graphics device\n");
printf("mmap() memory\n");
printf("Screen Info\n");
printf("ioctl() syscall\n\n");


}

void exit_graphics(){
printf("exit graphics\n");
printf("Close graphics device\n");
printf("munmap() memory\n");
printf("Renable keys with ioctl\n\n");
}
