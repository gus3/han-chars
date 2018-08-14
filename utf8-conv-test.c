#include <stdio.h>
#include "utf8-conv.h"

/* a function useful for setting debug breakpoints */
static inline void fail(const char *x)
{
	fprintf(stderr, "FAIL: %s\n", x);
}

int main(int argc, char *argv[])
{
	/* Points to char strings of varying UTF-8 characteristics */
	char *c;
	
	c = "A";
	if (utf8_to_unicode(c) != 65)
		fail("ASCII to Unicode");
	if (consume_utf8(&c) != 1)
		fail("ASCII is one byte");
	
	c = "";
	if (utf8_to_unicode(c) != 0)
		fail("ASCII NUL to Unicode");
	if (consume_utf8(&c) != 1)
		fail("ASCII NUL is one byte");
	
	c = "\303\200\0"; /* UTF-8: capital A with grave accent */
	if (utf8_to_unicode(c) != 0xC0) /* Unicode */
		fail("UTF-8 2-byte to Unicode");
	if (consume_utf8(&c) != 2)
		fail("Didn't consume 2 bytes");

	c = "\342\272\200\0"; /* UTF-8: CJK radical repeat */
	if (utf8_to_unicode(c) != 0x2E80) /* Unicode */
		fail("UTF-8 3-byte to Unicode");
	if (consume_utf8(&c) != 3)
		fail("Didn't consume 3 bytes");
		
	c = "\345\205\267\0"; /* UTF-8: implement, wrirting tool */
	if (utf8_to_unicode(c) != 0x5177) /* Unicode */
		fail("UTF-8 3-byte to Unicode, codepoint > 0x4000");
	if (consume_utf8(&c) != 3)
		fail("Didn't consume 3 bytes");

	c = "\360\257\244\207\0"; /* UTF-8: Cantonese: mud, mire */
	if (utf8_to_unicode(c) != 0x2F907) /* Unicode */
		fail("UTF-8 4-byte to Unicode");
	if (consume_utf8(&c) != 4)
		fail("Didn't consume 4 bytes");

	c = "\200A";
	if (utf8_to_unicode(c) != 0xFFFD)
		fail("Invalid first byte #1");
	if (consume_utf8(&c) != -1)
		fail("First byte invalid, sequence fails");

	c = "A\200";
	consume_utf8(&c);
	if (utf8_to_unicode(c) != 0xFFFD) /* Unicode */
		fail("Invalid following 1 byte");

	c = "\303\200\200"; /* UTF-8: capital A with grave accent, then invalid */
	if (utf8_to_unicode(c) != 0xFFFD) /* Unicode */
		fail("Invalid following 2 bytes");

	c = "\342\272\200\200"; /* UTF-8: CJK radical repeat */
	if (utf8_to_unicode(c) != 0xFFFD) /* Unicode */
		fail("Invalid following 3 bytes");

	c = "\360\257\244\207\200"; /* UTF-8: Cantonese: mud, mire */
	if (utf8_to_unicode(c) != 0xFFFD) /* Unicode */
		fail("Invalid following 4 bytes");

	c = "\200\0"; /* invalid 1st byte */
	if (utf8_to_unicode(c) != 0xFFFD) /* Unicode */
		fail("Invalid first byte #2");
	if (consume_utf8(&c) != -1)
		fail("Didn't return unknown byte count");

	c = "\300\0"; /* invalid 2nd byte */
	if (utf8_to_unicode(c) != 0xFFFD) /* Unicode */
		fail("Invalid second byte");

	c = "\340\200\0"; /* invalid 3rd byte*/
	if (utf8_to_unicode(c) != 0xFFFD) /* Unicode */
		fail("Invalid third byte");

	c = "\360\200\200\0"; /* invalid 4th byte*/
	if (utf8_to_unicode(c) != 0xFFFD) /* Unicode */
		fail("Invalid fourth byte");
	
	/* Now for a big test, one through four bytes in a valid UTF-8 string */
	c = "A\303\200\342\272\200\360\257\244\207";
	/* in UTF-8 order:
	   A => 0x41 (octal \101, for the interested)
		 \303\200 => 0xC0
		 \342\272\200 => 0x2E80
		 \360\257\244\207 => 0x2F907
	*/
	
	printf("The following hexadecimal sequence should show: 41 c0 2e80 2f907\n");
	
	while (*c)
	{
		printf("%x ", utf8_to_unicode(c));
		consume_utf8(&c);
	}
	printf("\n");

	return 0;
}
