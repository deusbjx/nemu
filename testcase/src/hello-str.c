#include <stdio.h>
#include <string.h>
#include "trap.h"

char buf[128];

int main() {
	
	//set_bp();
	sprintf(buf, "%s", "Hello world!\n");
	//set_bp();
	nemu_assert(strcmp(buf, "Hello world!\n") == 0);

	//set_bp();

	sprintf(buf, "%d + %d = %d\n", 1, 1, 2);
	nemu_assert(strcmp(buf, "1 + 1 = 2\n") == 0);

	//set_bp();

	sprintf(buf, "%d + %d = %d\n", 2, 10, 12);
	nemu_assert(strcmp(buf, "2 + 10 = 12\n") == 0);

	return 0;
}
