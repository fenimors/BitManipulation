/*
    Utility functions (e.g., for bit/byte manipulations)
    
    Author:    Sam Fenimore
*/
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <cstdint>
#include "Tools.h"

namespace Y86 {
    
/*-----------------------------------------------------------------------------------------------
    getBits
	Extracts bits 'low' to 'high' (inclusive) from 'source' and returns the result as
	an 64-bit integer. 
	Example:
	
	getBits(12,15,0x0123456789abcdef);
	
	would return the value:
	
	0x00000000000000c;
	
	(Bits 12-15 of the 64-bit word, counting from the right correspond to hex digit 'c' in the
	source word. Note that any number of bits from 1 to 64 could be specified depending on the values
	of 'low' and 'high'.
	The value of high must be greater than or equal to low and high must be in the range 0 to 63. 
------------------------------------------------------------------------------------------------*/
uint64_t getBits(unsigned low, unsigned high, uint64_t source)
{
    assert(high < 64 && (low <= high));
	uint64_t mask = -1;
    uint64_t c = 0;
	mask = mask << (high - low);
	mask = mask << 1;
	mask = ~mask;
	mask = mask << (low);
	c = source & mask;
	c = c >> low;
    return c;
}
/*-----------------------------------------------------------------------------------------------
    setBits
	Sets (to 1) the bits from bit numbers 'low' to 'high' (inclusive) in 
	the source word and returns the resulting word.
	
	The value of high must be greater than or equal to low and high must be in the range 0 to 63. 
------------------------------------------------------------------------------------------------*/
uint64_t setBits(unsigned low, unsigned high, uint64_t source)
{
	assert(high < 64 && (low <= high));
	uint64_t mask = -1;
    uint64_t c = 0;
	mask = mask << (high - low);
	mask = mask << 1;
	mask = ~mask;
	mask = mask << (low);
	c = source | mask;
	
    return c;
}
/*-----------------------------------------------------------------------------------------------
    clearBits
	
	Clears (to 0) the bits from bit numbers 'low' to 'high' (inclusive) in 
	the source word and returns the resulting word.
	
	The value of high must be greater than or equal to low and high must be in the range 0 to 63. 
------------------------------------------------------------------------------------------------*/
uint64_t clearBits(unsigned low, unsigned high, uint64_t source)
{
	assert(high < 64 && (low <= high));
	uint64_t mask = -1;
    uint64_t c = 0;
	mask = mask << (high - low);
	mask = mask << 1;
	mask = ~mask;
	mask = mask << (low);
	mask = ~mask;
	c = source & mask;
	
    return c;
}

/*-----------------------------------------------------------------------------------------------
    assignOneBit
	Sets the bit number 'bitNum' to the binary value (0 or 1) specified by 'bitVal' in
	the source word and returns the resulting word.
	
	'bitNum' must be in the range 0 to 63 (inclusive) and 'bitVal' must be 0 or 1.
------------------------------------------------------------------------------------------------*/
uint64_t assignOneBit(unsigned bitNum, unsigned bitVal, uint64_t source)
{
	assert(bitNum < 64 && (bitVal <= 1));
	uint64_t mask = -1;
    uint64_t c = 0;
	mask = mask << 1;
	mask = ~mask;
	mask = mask << (bitNum);
	if(bitVal == 0)
	{
		mask = ~mask;
		c = source & mask;
	}
	else
	{
		c = source | mask;
	}
	
    return c;
}

/*-----------------------------------------------------------------------------------------------
    getByteNumber
	Returns the specified byte number from the source word.
	
	Example:
	getByteNumber(3,0x0011223344556677);
	
	will return the single byte value:
	
	0x44
	
	(Note that the '3' refers to byte 3 of a 8-byte unsigned integer (bytes are numbered from
	the right starting at 0 when looking at a word value in hex). 
------------------------------------------------------------------------------------------------*/
uint8_t getByteNumber(unsigned byteNum, uint64_t source)
{
	assert(byteNum < 8);
	uint64_t mask = -1;
    uint64_t c = 0;
	mask = mask << 8;
	mask = ~mask;
	mask = mask << (byteNum * 8);
	c = (source & mask);
	c = c >> (byteNum * 8);
	
    return c;
}
/*-----------------------------------------------------------------------------------------------
    putByteNumber
	Returns the source word after replacing the specified byte (byteNum) with a given 
	byte value (byteVal).
	
	Example:
	putByteNumber(3,0x00,0x0011223344556677);
	
	will return the value:
	
	0x0011223300556677
	
	(Note that the '3' refers to byte 3 of a 8-byte unsigned integer (bytes are numbered from
	the right starting at 0 when looking at a word value in hex). 
------------------------------------------------------------------------------------------------*/
uint64_t putByteNumber(unsigned byteNum, uint8_t byteVal, uint64_t source)
{
	assert(byteNum < 8);
	uint64_t mask = -1;
	uint64_t setOneMask = -1;
    uint64_t c = 0;
	mask = mask << 8;
	setOneMask = setOneMask << 8;
	setOneMask = ~mask;
	setOneMask = setOneMask << (byteNum * 8);
	c = source | setOneMask;
	
	mask = (mask | ((uint64_t) byteVal));
	mask = ~mask;
	mask = mask << (byteNum * 8);
	mask = ~mask;
	c = c & mask;

	return c;
}
/*-----------------------------------------------------------------------------------------------
    buildWord
	
	Returns a 64 bit word consisting of the 8 parameter bytes, where b0 is the least significant
	and b7 is the most significant byte.
------------------------------------------------------------------------------------------------*/
uint64_t buildWord(unsigned char b0, unsigned char b1,unsigned char b2, unsigned char b3,
                          unsigned char b4, unsigned char b5,unsigned char b6, unsigned char b7)
{
	uint64_t c = -1;
	uint64_t temp = b7;
	temp = temp << 56;
	c = c & temp;
	temp = b6;
	temp = temp << 48;
	c = c | temp;
	temp = b5;
	temp = temp << 40;
	c = c | temp;
	temp = b4;
	temp = temp << 32;
	c = c | temp;
	temp = b3;
	temp = temp << 24;
	c = c | temp;
	temp = b2;
	temp = temp << 16;
	c = c | temp;
	temp = b1;
	temp = temp << 8;
	c = c | temp;
	temp = b0;
	c = c | temp;
    return c;           
}
/*-----------------------------------------------------------------------------------------------
    isNegative

	Returns true if the input parameter is negative when interpreted as a signed value.
------------------------------------------------------------------------------------------------*/
bool isNegative(uint64_t source)
{
	uint64_t c = source;
	c = c >> 63;
	if(c == 1)
		return true;
	else
		return false;
}
/*-----------------------------------------------------------------------------------------------
    expandBits
	
	Reads the source and converts it to a character string consisting of 72 bytes--71 characters
	followed by a '\0' character (string terminator).
	Example usage: 
		char buf[72];
		expandBits(0xAABBCCDDEE001122UL,buf);

		Will cause the following string to be written to the buf[] array (not including quotes):
	
	"10101010 10111011 11001100 11011101 11101110 00000000 00010001 00100010"
	
	Note the space after every group of 8 digits except the last. The last byte of
	the string is the '\0' byte, that is not printable but used to indicate the end
	of a C string.
------------------------------------------------------------------------------------------------*/
void expandBits(uint64_t source, char *bits)
{
	assert(bits != __null);
	uint64_t mask = -1;
	uint64_t nSource = source;
	uint64_t c = 0;
	uint64_t count = 0;
	for(int i = 8; i > 0; i--)
	{
		nSource = nSource >> (8*(i-1));
		for(int j = 8; j > 0; j--)
		{
			mask = -1;
			mask = mask << 1;
			mask = ~mask;
			mask = (mask << (j-1));
			c = (nSource & mask);
			c = (c >> (j-1));
			bits[count] = (char) c;
			count++;
		}
		
		bits[count] = ' ';
		count++;
		nSource = source;
	}
	bits[71] = '\0';
    return;
}
/*-----------------------------------------------------------------------------------------------
    clearBuffer
	Treats pbuf as a pointer to an array of 'size' bytes and clears them all to zero.
------------------------------------------------------------------------------------------------*/
void clearBuffer(char * pbuf, int size)
{
	assert(pbuf != __null && size >= 0 && size <= (2147483647));
	for(int i = 0; i < size; i++)
	{
		pbuf[i] = 0;
	}

    return;
}

} // end namespace Y86
