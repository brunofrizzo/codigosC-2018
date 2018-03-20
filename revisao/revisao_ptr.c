#include <stdio.h>
#include <stdlib.h>

int main() {

	int a = 10;
	int *ptr = malloc(sizeof(int));

	*ptr = 99;
	ptr = &a;

	printf("a = %d      |      %p       |       %d\n", a, ptr, *ptr);

}