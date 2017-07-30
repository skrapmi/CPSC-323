#include <stdio.h>

// assume getint() and putint() are std library functions
int getint(){
	int	retInt;
	scanf("%d", &retInt);
	return retInt;
}

void putint(int pInt){
	printf("%d \n", pInt);
}

int	main () {
	int i = getint(), j = getint();
	
	while(i != j) {
		if (i > j) i = i -j;
		else j = j -i;
		}
	putint(i);
	return 0;
}
