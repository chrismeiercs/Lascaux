#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include "library.h"

int graphics_device;
struct fb_var_screeninfo varInfo;
struct fb_fix_screeninfo fixInfo;



int init_graphics(){
printf("Init graphics\n");
printf("Opening graphics device\n");
graphics_device = open("/dev/fb0",O_RDWR | O_APPEND);

if(graphics_device == -1){
	printf("Graphics Device failed to opened\n");
	return 1;
}
else{
	printf("Graphics device opened");
}

printf("Getting Screen Info\n");
//get var size

ioctl(graphics_device, FBIOGET_VSCREENINFO ,&varInfo);
printf("varInfo: %d\n", varInfo.yres_virtual);
ioctl(graphics_device, FBIOGET_FSCREENINFO, &fixInfo);
printf("fixInfo: %d\n", fixInfo.line_length);

printf("Mmap screen info\n");
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
printf("Renable keys with ioctl\n\n");

return 0;
}
