#include <sys/select.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <time.h>
#include <linux/fb.h>
#include <termios.h>
#include "library.h"

int graphics_device;
struct fb_var_screeninfo varInfo;
struct fb_fix_screeninfo fixInfo;
char *screen;
fd_set fileSet;
struct timeval timeOut;
static struct termios oldt, newt;


int init_graphics(){
printf("Init graphics\n");
printf("Opening graphics device\n");
graphics_device = open("/dev/fb0",O_RDWR);

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

screen =(char*) mmap(NULL, varInfo.yres_virtual * 
fixInfo.line_length, PROT_READ | PROT_WRITE, MAP_SHARED, 
graphics_device, 0);

if(screen == MAP_FAILED){
printf("Memory Map not work\n");
return 1;
}


printf("ioctl() syscall\n\n");


printf("Remove Canonical Mode\n");

tcgetattr(0,&oldt);
newt = oldt;

newt.c_lflag &= ~(ICANON);

tcsetattr(0, TCSANOW, &newt);


printf("Add set select listening\n");
FD_ZERO(&fileSet);
FD_SET(0,&fileSet);

printf("Set select timeout\n");
timeOut.tv_sec = 0;
timeOut.tv_usec = 0;



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

printf("Set input listening\n");

FD_ZERO(&fileSet);


printf("Restore cannonical mode");

tcsetattr(0, TCSANOW, &oldt);


return 0;
}

int sleep_ms(long ms){
	//need struct timespec w/ tv_nsec field (long)
//	const struct timespec sleepTime;
	struct timespec sleepTime;
	sleepTime.tv_nsec = ms * 1000000;
	sleepTime.tv_sec = 0;
	return nanosleep(&sleepTime, NULL);


}

char getKey(){

FD_ZERO(&fileSet);
FD_SET(0,&fileSet);
/*int selRes = select(1,&fileSet,NULL,NULL,&
timeOut);


if(selRes){
printf("select value: %d\n",selRes);
}*/

//input = 0

if(select(1,&fileSet,NULL,NULL, &timeOut) == 1){
	char key[1];
	/*if(read(0,key,1)==1){
		printf("Key pressed: %c\n", key);
		//return key;
	}*/
	
	if(read(0,&key,1)){
	//printf("Key pressed %c\n", key[0]);
	return key[0];
	}
}

}


void draw_pixel(int x, int y, color_t color){
	long int offset = (fixInfo.line_length * y) + x;
	*(screen + offset) = color;

}

void draw_rect(int x1, int y1, int width, int height, color_t color){

	int i; //x counter
	int k; //y counter
	
	for(i = x1; i < (x1 + width); i++){
	
		for (k = y1; k < (y1 + height); k++){
			draw_pixel(i,k,color);
		}
	
	}
	


}
