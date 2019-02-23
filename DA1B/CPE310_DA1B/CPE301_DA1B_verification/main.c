 /*
 * CPE301_DA1B_verification.c
 *
 * Created: 2/22/2019 10:14:20 PM
 * Author : Cody
 */ 

#include <avr/io.h>

int main(void){
int *x ;
int *y ;
int *z ;

// set addresses for each of the address registers
x = 0x0200;
y = 0x0400;
z = 0x0600;

int ySum = 0;
int zSum = 0;

//initialize some indices for loops
int i = 0;
int i2 = 0;

    //Begin loop for inserting numbers into the sorting
    for (i=0;i<=255;i++){ 
		if (i <= 10 || i >= 255 ){ //decide whether the number is larger than 255 or less than 10
			//do nothing
		}
		else if(i2 < 99){ // store only 99 numbers
			*x = i; // let x value equal i
			x++;	// set x up for next value
			i2++;	// increase index
			
			//Check if divisible by 3
			if (i%3 == 0){ //if divisible, store into y
				*y=i;
				y++;
				ySum = ySum +i; // add all values of y
			}
			else{		// otherwise store into z
				*z=i;
				z++;
				zSum = zSum +i; // add all values of z
			}
		}		
	//output the values for ySum and zSum and store them in the next spot of memory
	*y = ySum;
	*z = zSum;
	}
	
	return 0;
}

