#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include "library.h"

int graphics_device;
struct fb_var_screeninfo varInfo;
struct fb_fix_screeninfo fixInfo;
void *screen;


int init_graphics(){
printf("Init graphics\n");
printf("Opening graphics device\n");
graphics_device = open("/dev/fb0",O_RDWR | O_APPEND);

if(graphics_device == -1){
	printf("Graphics Device failed to opened\n");
	return 1;
}
else{
	printf("Graphics device opened\n");
}

printf("Getting Screen Info\n");
//get var size

ioctl(graphics_device, FBIOGET_VSCREENINFO ,&varInfo);
printf("varInfo: %d\n", varInfo.yres_virtual);
ioctl(graphics_device, FBIOGET_FSCREENINFO, &fixInfo);
printf("fixInfo: %d\n", fixInfo.line_length);

printf("Mmap screen info\n");

screen = mmap(NULL, varInfo.yres_virtual * 
fixInfo.line_length, PROT_READ | PROT_WRITE, MAP_SHARED, 
graphics_device, 0);

if(screen == MAP_FAILED){
printf("Memory Map not work\n");
return 1;
}


printf("ioctl() syscall\n\n");

return 0;
}

int exit_graphics(){
printf("exit graphics\n");
printf("Closing graphics device\n");
if(close(graphics_device) == 0){
printf("Graphics device closed\n");
}


printf("munmap() memory\n");
if(munmap(screen, varInfo.yres_virtual * fixInfo.line_length) == -1){
	printf("Unmap Error\n");
	return 1;
}



printf("Renable keys with ioctl\n\n");

return 0;
}
