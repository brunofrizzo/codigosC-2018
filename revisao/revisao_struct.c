#include <stdio.h>
#include <stdlib.h>

struct ponto {
	int x, y;
};

int main() {
	struct ponto a;
	struct ponto *ptr;

	a.x=10;
	a.y=20;

	// ptr=&a;
	ptr=malloc(sizeof(struct ponto));
	ptr->x = 0;
	ptr->y = 0;

	// printf("ponto a = (%d, %d)\n", a.x, a.yy);
	printf("ponto a = (%d, %d)\n", ptr->x, ptr->y);
}