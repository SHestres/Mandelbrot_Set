#ifndef ARBITRARY_PRECISION_H
#define ARBITRARY_PRECISION_H

#include <stdint.h>
#include <iostream>


class APnum
{
	public:
		
		APnum();
		APnum(int length);
		APnum(int length, float num);

		float toFloat();
		void storeFloat(float value);

		void printOut();

	private:
		uint8_t* num;
		int len;

};

#endif ARBITRARY_PRECISION_H