#ifndef ARBITRARY_PRECISION_H
#define ARBITRARY_PRECISION_H

#include <stdint.h>
#include <iostream>

#define BIT9 256  //Bitmask for bit9

class APnum
{
	public:
		
		APnum();
		APnum(int length);
		APnum(float value);
		APnum(int length, float num);

		float toFloat();
		void storeFloat(float value);
		void Add(APnum addend);

		void printOut();
		uint8_t* getNum();
		int getLength();


	private:
		uint8_t* num;
		int len;

		void invert();

};

#endif ARBITRARY_PRECISION_H