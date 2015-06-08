#include "library.h"
#include <stdio.h>

int main(void){




if(init_graphics()){
printf("Graphics Initialized");

}

/*if(sleep_ms(10)== 0){
	printf("Sleep successful\n");
}*/
char keyPressed;
/*do{
keyPressed = getKey();
if(keyPressed == 'a'){
//printf("Key pressed: %c\n",keyPressed);
}
}
while(keyPressed != 'q');
*/



int x = 0;
int y = 0;
int run = 1;
	while(run){

		char key = getKey();

		if(key == 'q'){
			exit_graphics();
			run = 0;
		}
		else if(key == 'w'){
			x += 10;
			printf("X: %d\nY: %d\n\n", x, y);
			//printf("sleep return : %d\n",sleep_ms(20));
		}
		else if(key == 's'){
			x -= 10;
			printf("X: %d\nY: %d\n\n", x, y);

		}
		else if(key == 'a'){
			y -= 10;
			printf("X: %d\nY: %d\n\n", x, y);
		
		}
		else if(key == 'd'){
			y += 10;
			printf("X: %d\nY: %d\n\n", x, y);
		}
		else if(key == 'b'){
			printf("draw rect\n");
			draw_pixel(20,20,20);
			sleep_ms(20);
		}
		

	}
/*
if(exit_graphics()){
printf("Graphics Closed");
*/

return 0;
}
