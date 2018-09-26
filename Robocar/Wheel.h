/*
* Wheel.h
*
* Created: 10/1/2015 9:38:43 AM
* Author: ensylam
*/


#ifndef WHEEL_H_
#define WHEEL_H_

namespace Wheel {

    // coding: LCRCMORL
    enum _command {STOP=0,
                   FORWARD =0b10100111, //LEFT CONNECT, RIGHT CONNECT, RIGHT FORWARD, LEFT FORWARD
                   BACKWARD =0b10100100, //LEFT CONNECT, RIGHT CONNECT, RIGHT BACKWARD, LEFT BACKWARD
                   ROTATELEFT =0b10101010, //LEFT CONNECT, RIGHT CONNECT, RIGHT FORWARD, LEFT BACKWARD
                   ROTATERIGHT=0b10101001, //LEFT CONNECT, RIGHT CONNECT, RIGHT BACKWARD, LEFT FORWARD
                   TURNLEFT =0b00101111, //LEFT STOP, RIGHT CONNECT, RIGHT FORWARD
                   TURNRIGHT =0b10001111, //LEFT CONNECT, RIGHT STOP, LEFT FORWARD
                   BTURNLEFT =0b10001100, //LEFT CONNECT, RIGHT STOP, LEFT BACKWARD
                   BTURNRIGHT =0b00101100, //LEFT STOP, RIGHT CONNECT, RIGHT BACKWARD
                  };

    void move(enum _command);
	unsigned char getL_speed(void);
	unsigned char getR_speed(void);
	void set(int speed);
	void setSpeed(int speed);
	void setP(int P);
	void setI(int I);
	void setD(int D);
	char getSensor();
	void usrCount(unsigned int step);
	void setPID(int p=11,int i=56,int d=60);
}



namespace Servo{
	enum servo_command {
		OPEN	= 8000,
		CLOSE	= 16000,
		LEFT	= 25500,
		RIGHT	= 5529,
		Right2  = 9000,
		MIDDLE	= 15000,
		UP1		= 6000,
		DOWN1	= 9500,
		UP2		= 18000,
		DOWN2	= 7000,};
	void GG();
	void delay100ms(int n=1);
	void set(int num,int name);
	void setname(int name);
	void setInitialise(int val=15084);
	void set(enum servo_command,int name);
	void set(int);
	void slowclose();
	int getwidth(int);
	void second();
	void slowclose1();
}




#endif /* WHEEL_H_ */




