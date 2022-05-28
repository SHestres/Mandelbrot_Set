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

APnum::APnum(float value)
{
	num = new uint8_t[10]{};
	len = 10;
	storeFloat(value);
}

uint8_t* APnum::getNum()
{
	return num;
}

int APnum::getLength()
{
	return len;
}


float APnum::toFloat()
{
	int64_t intRep;

	//Grab first 64 bits of APnum
	void* memLoc = &num[len] - sizeof(int64_t); //Stupid but needed for little Endian architecture
	std::memcpy(&intRep, memLoc, sizeof(int64_t));

	//std::cout << "toFloat intRep: " << intRep << std::endl;
	return (float)intRep / (float)((int64_t)1 << 56);  //56 fractional bits used for standard precision in float conversion
}

void APnum::storeFloat(float value)
{
	//Negative Numbers must be inverted to positive, then set negative after
	bool isNeg = value < 0;
	if (isNeg) value *= -1;
	
	uint64_t intRep = (uint64_t)(value * ((uint64_t)1 << 56)); //56 fractional bits
	
	//std::cout << "storeFloat intRep: " << intRep << std::endl;

	//Copy intRep into num
	void* memLoc = &num[len] - sizeof(uint64_t); //Stupid but needed for little Endian architecture
	std::memcpy(memLoc, &intRep, sizeof(uint64_t));

	uint64_t pls = *num;

	if (isNeg) invert();

}

void APnum::invert()
{
	//Flip every bit
	for (int i = 0; i < len; i++)
	{
		num[i] = ~num[i];
	}
	
	//Add one to LSB
	APnum negBit = APnum(len);
	negBit.getNum()[0] = (uint8_t)1;

	Add(negBit);

}

//Not complete, just for simple checks
void APnum::printOut()
{

	//Print MSbyte (End of array because little endian)
	std::bitset<8> a(num[len - 1]);
	std::cout << a << std::endl;

	//Second MSbyte
	std::bitset<8> b(num[len - 2]);
	std::cout << b << std::endl;
}

//Add another number to this
void APnum::Add(APnum addend)
{
	uint8_t* other = addend.getNum();
	uint8_t* self = num;

	int otherLength = addend.getLength();

	//Align the two arrays to add properly
	int otherIndOffset = 0;
	int selfIndOffset = 0;
	int endInd;

	if (len < otherLength)
	{
		endInd = len;
		otherIndOffset = otherLength - len;
	}
	else
	{
		endInd = otherLength;
		selfIndOffset = len - otherLength;
	}

	//LSbyte, has no carry in
	int sum = *num + *other;
	*num = (uint8_t)sum;
	bool carry = sum & BIT9;

	//Loop through array with offsets
	for (int i = 1; i < endInd - 1; i++)
	{
		//Add each byte into an int
		sum = *(num + i + selfIndOffset) + *(other + i + otherIndOffset) + (1 * carry);
		//Store 8 bits in array slot
		*(num + i + selfIndOffset) = (uint8_t)sum;
		//Carry overflow bit
		carry = sum & BIT9;
	}

	//MSbyte, would OOB the array
	sum = *(num + selfIndOffset + endInd - 1) + *(other + otherIndOffset + endInd - 1) + carry;
	*(num + selfIndOffset + endInd - 1) = (uint8_t)sum;
	

}