#include "ArbitraryPrecision.h"

#include <bitset>

APnum::APnum()
{
	num = new uint8_t[10]{};
	len = 10;
}

APnum::APnum(int length)
{
	num = new uint8_t[length]{};
	len = length;
}

APnum::APnum(int length, float value)
{
	num = new uint8_t[length]{};
	len = length;
	storeFloat(value);
}

float APnum::toFloat()
{
	uint64_t intRep;

	//Grab first 64 bits of APnum
	void* memLoc = &num[len] - sizeof(uint64_t); //Stupid but needed for little Endian architecture
	std::memcpy(&intRep, memLoc, sizeof(uint64_t));

	std::cout << "toFloat intRep: " << intRep << std::endl;
	return (float)intRep / (float)((uint64_t)1 << 56);  //56 fractional bits used for standard precision in float conversion
}

void APnum::storeFloat(float value)
{
	uint64_t intRep = (uint64_t)(value * ((uint64_t)1 << 56)); //56 fractional bits
	
	std::cout << "storeFloat intRep: " << intRep << std::endl;

	//Copy intRep into num
	void* memLoc = &num[len] - sizeof(uint64_t); //Stupid but needed for little Endian architecture
	std::memcpy(memLoc, &intRep, sizeof(uint64_t));

	uint64_t pls = *num;

}

void APnum::printOut()
{
	/*
	for (int i = 0; i < len; i++)
	{
		std::bitset<8> n(num[i]);
		std::cout << n << std::endl;
	}
	*/

	std::bitset<8> n(num[9]);
	std::cout << n << std::endl;
}