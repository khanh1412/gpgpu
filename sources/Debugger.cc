#include"CL.h"
char num2char(uint8_t i)
{
	char ret;
	switch (i)
	{
		case 0:
			ret = '0';
			break;
		case 1:
			ret = '1';
			break;
		case 2:
			ret = '2';
			break;
		case 3:
			ret = '3';
			break;
		case 4:
			ret = '4';
			break;
		case 5:
			ret = '5';
			break;
		case 6:
			ret = '6';
			break;
		case 7:
			ret = '7';
			break;
		case 8:
			ret = '8';
			break;
		case 9:
			ret = '9';
			break;
		case 10:
			ret = 'A';
			break;
		case 11:
			ret = 'B';
			break;
		case 12:
			ret = 'C';
			break;
		case 13:
			ret = 'D';
			break;
		case 14:
			ret = 'E';
			break;
		case 15:
			ret = 'F';
			break;
		default:
			__builtin_trap();
	}
	return ret;
}
void print_data(const std::string& name, const void *data, size_t size)
{
	const uint8_t *ptr = reinterpret_cast<const uint8_t*>(data);

	uint64_t len = 2*size+size;

	char *str = new char[len];
	for (size_t byte=0; byte<size; byte++)
	{
		uint64_t i1 = 3*byte;
		uint64_t i2 = 3*byte+1;
		uint64_t i3 = 3*byte+2;

		uint8_t first  = ptr[byte] / 16;
		uint8_t second = ptr[byte] % 16;

		str[i1] = num2char(first);
		str[i2] = num2char(second);
		str[i3] = ' ';
	}
	str[len-1] = '\0';
	std::printf("%s:\t\"%s\"\n", name.c_str(), str);
	delete str;
}




