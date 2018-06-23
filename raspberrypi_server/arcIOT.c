#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	
	system("gpio mode 0 output");
	system("gpio mode 1 output");
	system("gpio mode 2 output");


	printf("%s\n", argv[1]);

	if (strcmp(argv[1], "red") == 0) {
		system("gpio write 0 0");
		system("gpio write 1 0");
		system("gpio write 2 0");
		//printf("red\n");
	}
	else if (!strcmp(argv[1], "green")) {
		system("gpio write 0 1");
		system("gpio write 1 0");
		system("gpio write 2 0");
	}
	else if (!strcmp(argv[1], "blue")) {
		system("gpio write 0 0");
		system("gpio write 1 1");
		system("gpio write 2 0");
	}
	else if (!strcmp(argv[1], "yellow")) {
		system("gpio write 0 1");
		system("gpio write 1 1");
		system("gpio write 2 0");
	}
	else if (!strcmp(argv[1], "cock")) {
		system("gpio write 0 0");
		system("gpio write 1 0");
		system("gpio write 2 1");
	}
	else if (!strcmp(argv[1], "purple")) {
		system("gpio write 0 1");
		system("gpio write 1 0");
		system("gpio write 2 1");
	}
	else if (!strcmp(argv[1], "white")) {
		system("gpio write 0 0");
		system("gpio write 1 1");
		system("gpio write 2 1");
	}
	else if (!strcmp(argv[1], "dark")) {
		system("gpio write 0 1");
		system("gpio write 1 1");
		system("gpio write 2 1");
	}


	

	return 0;
}
