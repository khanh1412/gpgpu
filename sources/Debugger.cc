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
void print_data(const std::string& name, void *data, size_t size)
{
	uint8_t *ptr = reinterpret_cast<uint8_t*>(data);

	uint64_t len = 2*size;

	char *str = new char[len+1];
	str[len] = '\0';
	for (size_t byte=0; byte<size; byte++)
	{
		uint64_t i1 = 2*byte;
		uint64_t i2 = 2*byte+1;

		uint8_t first  = ptr[byte] / 16;
		uint8_t second = ptr[byte] % 16;

		str[i1] = num2char(first);
		str[i2] = num2char(second);
	}
	std::printf("%s: \"%s\"\n", name.c_str(), str);
	delete str;
}




