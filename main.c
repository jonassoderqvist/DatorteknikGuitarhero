#include <pic32mx.h>
#include <stdint.h>
#include <stdlib.h>

extern void _enable_interrupt();

void setPwm(int pwm, int duty){
	OC1RS = duty;
	PR2 = pwm;
}
initSong(int song){
    if(song==1){
        return {1,3,0,5,0,3,1,4,2,1,3,0,5,0,3,1,4,2,1,3,0,5,0,3,1,4,2,1,3,0,5,0,3,1,4,2,1,3,0,5,0,3,1,4,2,1,3,0,5};
}
void runGame(int song[50], int speed) {
    int score = 0;
    int x=0;
    int i = 0;
	for(;;) {
        int note = song[x];
        if(i==6000/speed){
            x++;
            i=0;
        }
        i++;
		int btns = getBtns();
		// Check buttons. If button is pressed, corresponding note's play-value will be set to 1 (true)
		if((PORTD & 0b000011100000) == ){
		}
	}
}

int getBtns(void) {
 	return((PORTD >>5) &0x7);	/* Port D bits 5 through 8 is used for the Buttons and is set to 1 (input) */
 }

 int getSwitches(void) {
 	return((PORTD>>8) &0xF); 	/* Port D bits 8 through 12 is used for the Switches and is set to 1 (input) */
 }

 int getbtn(void) {
 	return(PORTD &0x1);
 }


void initPwm(){
	T2CON = 0x070; // Clear timer2, prescale at 1:1
	TMR2 = 0x0; // Timer2 value starts at 0
	OC1CON = 0x0000; // Turn off and clear pwm
	OC1R = 0x0001;
	OC1RS = 0; // Dutycycle
	OC1CON = 0x0006; // Configure for PWM mode without Fault pin
	PR2 = 0;
	IECSET(0) = 0x0100; // Enable T2 interrupt
	IPCSET(2) = 0x01C; // Set T2 interrupt priority to 7
	enable_interrupt();
	OC1CONSET = 0x08000; // Enable OC1
	// Om något knasar, titta lite djupare på OC1CONSET!!!
	T2CONSET |= 0x08000; // Enable Timer2
}
    int speed(){
        for(;;){
            if((PORTD & 0b000000100000) == 0b000000100000){
                return 1;
            }
            if((PORTD & 0b000001000000) == 0b000001000000){
                return 2;
            }
            if((PORTD & 0b000010000000) == 0b000010000000){
                return 3;
            }
        }
    }
    int menu(){
        for(;;){
        if((PORTD & 0b000000100000) == 0b000000100000){
            return 1;
        }
        if((PORTD & 0b000001000000) == 0b000001000000){
            return 2;
        }
        if((PORTD & 0b000010000000) == 0b000010000000){
            return 3;
        }
    }
    }
int main(void) {
	TRISE = 0x00; 	/* Port E bits 0 through 7 is used for the LED and is set to 0 (output) */
	PORTE = 0x00;
    int song = menu();
    int speed = speed();
	initPwm();
    int songArr[] = initSong(song);
	runGame(songArr, speed);
    showScore();
	return 0;
}

void user_isr( void ) {
	if((IFS(0)&0x0100)==0x0100){
		PORTE = 0xffff;
        IFSCLR(0) = 0x0100;
	}
}
