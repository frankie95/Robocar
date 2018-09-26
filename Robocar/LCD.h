#ifndef LCD_H_
#define LCD_H_

namespace LCD {
    enum {LINE1=0, LINE2=64, FOLLOW=254, STATUS=255};

    void print(unsigned char position, const char *s);	// flash staring
	void print(unsigned char position, char *s);		// ram staring
}



#endif /* LCD_H_ */