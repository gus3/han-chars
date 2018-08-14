#include <stdio.h>

#define array_sizeof(x) (sizeof(x)/sizeof(x[0]))

static struct S { int a[3]; } s[5];

main() {
	printf("sizeof(s) is %d\n", sizeof(s));
	printf("sizeof(s)/sizeof(struct S) is %d\n", sizeof(s)/sizeof(struct S));
	printf("sizeof(s[0]) is %d\n", sizeof(s[0]));
	printf("sizeof((s+2)->a) is %d\n", sizeof((s+2)->a));
	printf("sizeof(s[3].a[2]) is %d\n", sizeof(s[3].a[2]));
	
	printf("array_sizeof(s) is %d\n", array_sizeof(s));
	printf("array_sizeof(s[3].a) is %d\n", array_sizeof(s[3].a));
}
