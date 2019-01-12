#include"Debugger.h"
static char num2char(uint8_t i)
{
	char ret;
	switch (i)
	{
		case 0x0: ret = '0'; break;
		case 0x1: ret = '1'; break;
		case 0x2: ret = '2'; break;
		case 0x3: ret = '3'; break;
		case 0x4: ret = '4'; break;
		case 0x5: ret = '5'; break;
		case 0x6: ret = '6'; break;
		case 0x7: ret = '7'; break;
		case 0x8: ret = '8'; break;
		case 0x9: ret = '9'; break;
		case 0xA: ret = 'A'; break;
		case 0xB: ret = 'B'; break;
		case 0xC: ret = 'C'; break;
		case 0xD: ret = 'D'; break;
		case 0xE: ret = 'E'; break;
		case 0xF: ret = 'F'; break;
		default: break;
	}
	return ret;
}
std::string toHex(const void *data, size_t size)
{
	const uint8_t *ptr = reinterpret_cast<const uint8_t*>(data);

	uint64_t len = 2*size+size;

	char *buffer = new char[len];
	for (size_t byte=0; byte<size; byte++)
	{
		uint64_t i1 = 3*byte;
		uint64_t i2 = 3*byte+1;
		uint64_t i3 = 3*byte+2;

		uint8_t first  = ptr[byte] / 16;
		uint8_t second = ptr[byte] % 16;

		buffer[i1] = num2char(first);
		buffer[i2] = num2char(second);
		buffer[i3] = ' ';
	}
	buffer[len-1] = '\0';
	std::string string(buffer);
	delete buffer;
	return string;
}
