#include <cstdlib>
#include <iostream> // for std::cout , etc.
#include <iomanip>  // additional formatting for cout
#include <cstdint>  // standard int types like uint64_t 
#include <stdio.h> // in case you want to use printf
#include "Tools.h" // Tools function declarations


using namespace std;
using namespace Y86;  

int main(int argc, char *argv[])
{
	// For testing the file
    cout << hex << setfill('0') << setw(16) << getBits(63,62,0xabcdef0123456789)<<endl;
    cout << hex << setfill('0') << setw(16) << setBits(12,15,0x0123456789abcdef)<<endl;
	cout << hex << setfill('0') << setw(16) << clearBits(12,15,0x0123456789abcdef)<<endl;
	cout << hex << setfill('0') << setw(16) << assignOneBit(12,1,0x0123456789abcdef)<<endl;
	cout << hex << setfill('0') << setw(16) << getByteNumber(3,0x0011223344556677)<<endl;
	cout << hex << setfill('0') << setw(16) << putByteNumber(3,0x00,0x0011223344556677)<<endl;
	cout << hex << setfill('0') << setw(16) << buildWord('f','0','f','0','0','0','0','0')<<endl;
	cout << "expand bits testing stuff" <<endl;
	char buf[72];
	expandBits(0xAABBCCDDEE001122UL,buf);
	cout << hex << setfill('0') << setw(16) << buf[0] <<endl;
	cout << hex << setfill('0') << setw(16) << buf[1] <<endl;
	cout << hex << setfill('0') << setw(16) << buf[2] <<endl;
	cout << hex << setfill('0') << setw(16) << buf[3] <<endl;
	cout << hex << setfill('0') << setw(16) << buf[68] <<endl;
	cout << hex << setfill('0') << setw(16) << buf[69] <<endl;
	cout << hex << setfill('0') << setw(16) << buf[70] <<endl;
	cout << hex << setfill('0') << setw(16) << buf[71] <<endl;
	cout << hex << setfill('0') << setw(16) << buf[72] <<endl;
}



