#include <stdio.h>
#include <limits>

int
main(void)
{
	if (std::numeric_limits<char>::is_signed)  {
		printf("char is signed and has %lu bits\n", (sizeof (char) * 8));
	} else {
		printf("char is unsigned and has %lu bits\n", (sizeof (char) * 8));
	}
	
	if (std::numeric_limits<unsigned char>::is_signed)  {
		printf("unsigned char is signed and has %lu bits\n", (sizeof (unsigned char) * 8));
	} else {
		printf("unsigned char is unsigned and has %lu bits\n", (sizeof (unsigned char) * 8));
	}
	
	if (std::numeric_limits<short int>::is_signed)  {
		printf("short int is signed and has %lu bits\n", (sizeof (short int) * 8));
	} else {
		printf("short int is unsigned and has %lu bits\n", (sizeof (short int) * 8));
	}
	
	if (std::numeric_limits<unsigned short int>::is_signed)  {
		printf("unsigned short int is signed and has %lu bits\n", (sizeof (unsigned short int) * 8));
	} else {
		printf("unsigned short int is unsigned and has %lu bits\n", (sizeof (unsigned short int) * 8));
	}
	
	if (std::numeric_limits<int>::is_signed)  {
		printf("int is signed and has %lu bits\n", (sizeof (int) * 8));
	} else {
		printf("int is unsigned and has %lu bits\n", (sizeof (int) * 8));
	}
	
	if (std::numeric_limits<size_t>::is_signed)  {
		printf("size_t is signed and has %lu bits\n", (sizeof (size_t) * 8));
	} else {
		printf("size_t is unsigned and has %lu bits\n", (sizeof (size_t) * 8));
	}
	
	if (std::numeric_limits<ssize_t>::is_signed)  {
		printf("ssize_t is signed and has %lu bits\n", (sizeof (ssize_t) * 8));
	} else {
		printf("ssize_t is unsigned and has %lu bits\n", (sizeof (ssize_t) * 8));
	}
	
	return 0;
}
