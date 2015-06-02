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

while(1){

getKey();

}
if(exit_graphics()){
printf("Graphics Closed");

}
return 0;
}
