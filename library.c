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
#include "iso_font.h"

int graphics_device;
struct fb_var_screeninfo varInfo;
struct fb_fix_screeninfo fixInfo;
char *screen;
fd_set fileSet;
struct timeval timeOut;
static struct termios oldt, newt;


int init_graphics(){
//open frame buffer
graphics_device = open("/dev/fb0",O_RDWR);

if(graphics_device == -1){
	//check is frame buffer opened successfully
	return 1;
}

//get screen info
//get variable screen size
ioctl(graphics_device, FBIOGET_VSCREENINFO ,&varInfo);
//get fixed screen info
ioctl(graphics_device, FBIOGET_FSCREENINFO, &fixInfo);
//mmap frame buffer into file
screen =(char*) mmap(NULL, varInfo.yres_virtual * 
fixInfo.line_length, PROT_READ | PROT_WRITE, MAP_SHARED, 
graphics_device, 0);

if(screen == MAP_FAILED){
//memory map failed
return 1;
}


//remove canonical mode of terminal

//terminal won't wait for new line to read key
tcgetattr(0,&oldt); //save canonical settings
newt = oldt;

newt.c_lflag &= ~(ECHO | ICANON); //remove key echo and waiting for new 
//line
//apply new settings
tcsetattr(0, TCSANOW, &newt);

//listen for user input for getKey
FD_ZERO(&fileSet);
FD_SET(0,&fileSet);

//set select timeout
timeOut.tv_sec = 0;
timeOut.tv_usec = 0;



return 0;
}

int exit_graphics(){
//close frame buffer

if(close(graphics_device) != 0){
	//frame buffer didn't properly close
	return 1;
}


//unmap frame buffer
if(munmap(screen, varInfo.yres_virtual * fixInfo.line_length) == -1){
	//unmap error
	return 1;
}




//remove select listening
FD_ZERO(&fileSet);


//restor canonical mode: key echoes and new line wait restored
tcsetattr(0, TCSANOW, &oldt);


return 0;
}

int sleep_ms(long ms){
	//set sleep times
	struct timespec sleepTime;
	sleepTime.tv_nsec = ms * 1000000;
	sleepTime.tv_sec = 0;
	return nanosleep(&sleepTime, NULL);

}

char getKey(){
//tell select to listen to stdin
FD_ZERO(&fileSet);
FD_SET(0,&fileSet);

if(select(1,&fileSet,NULL,NULL, &timeOut) == 1){
	char key[1];
	//return key if pressed	
	if(read(0,&key,1)){
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

void clear_screen(){

	write(1, "\033[2J",sizeof("\033[2J"));
}

void draw_char(int x, int y, const char text, color_t color){

	int index = text * 16;
	int finalIndex = text * 16 + 15;
	int start_x = x;
	int start_y = y;
	
	int k ;
	for(k = index; k < finalIndex;k++){
		//move down line with each iteration of k
		
		//grab index
		unsigned char row = iso_font[k];
		//perform mask
		//get every bit from left to right
		int row_x = x;
		int bitLen = 8;
		int j;
		unsigned char mask = 1;
		for(j = 0; j < bitLen; j++){
			//perform masking
			char is_colored = (mask & row) << (bitLen-1)-j;
				if(is_colored){
				draw_pixel(row_x,y,color);
			}
			//shift bit to the next one
			mask = mask << 1;
			//increment x
			row_x++;
		}
		//increment y;
		y++;
		
		
		
		
		
	}

}

void draw_text(int x, int y, const char *text, color_t c){
	//draw character 
	//move the the right one width of a character
	//draw next character
	int i;
	for(i=0; text[i] != '\0'; i++){
		draw_char(x,y,text[i],c);
		x+=16;
	}
}
