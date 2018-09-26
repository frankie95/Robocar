/*
 * eeprom.h
 *
 * Created: 3/30/2016 8:34:07 PM
 *  Author: Student
 */ 
namespace EEPROM {

	
	int getP();
	int getI();
	int getD();
	void savePID(int,int,int);
	bool retore();
	bool save();
	int* getServo();
}