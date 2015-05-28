#include "library.h"
#include <stdio.h>

int main(void){

if(init_graphics()){
printf("Graphics Initialized");

}
if(exit_graphics()){
printf("Graphics Closed");

}
return 0;
}
