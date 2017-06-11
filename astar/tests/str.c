#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* findlast(char* chaine, char find) {
	char *c = NULL, *p = NULL;
	c = strchr(chaine, find);
	while (c) {
		printf("%s\n",c);
		p = c;
		c = strchr(c+1, find);
		getchar();
	}
	return p;
}

int main(int argc, char **argv) {
	char str[25] = "coucou ceci est un test";
	printf("%s\n",findlast(str,'c'));
	return 0;
}
