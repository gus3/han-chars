#include <stdio.h>
#include "unihan.h"
#include "lookup.h"
#include "utf8-conv.h"

/* This program accepts UTF-8 on stdin, up to 4095 bytes, parses it into
   Unicode codepoints, then searches the Han dictionary for translations.
	 Anything not having a translation in the Han dictionary will be noted
	 as such on the output.
	 
	 Bugs: if input is truncated in the middle of a UTF-8 sequence, it will
	 be reported as invalid.
	 Final CR/LF characters are read and processed.
	 
	 This program should not be considered secure on any level.
*/

char *notrans = "(No Han translation exists.)";

int main(int argc, char *argv[])
{
	static char buf[4096] ; // = "A\303\200\343\220\200\360\257\244\207";
	char *ptr, *utf8pt, *translation;
	int cp; /* Unicode codepoint */
	
	/* get some UTF-8 */
	fgets(buf, sizeof(buf), stdin);

	/* begin the parse-lookup-advance loop */
	ptr = buf;
	while (*ptr)
	{
		/* to Unicode */
		cp = utf8_to_unicode(ptr);
		/* invalid? */
		if (cp == 0xFFFD)
		{
			/* halt immediately with complaint */
			fprintf(stderr, "Invalid UTF-8 detected; terminating.\n");
			return -1;
		}
		/* now to print out the UTF-8 */
		/* save the current ptr */
		utf8pt = ptr;
		/* skip to the next UTF-8 */
		consume_utf8(&ptr);
		/* and print the octets one by one */
		while (utf8pt != ptr)
		{
			fputc(*utf8pt, stdout);
			utf8pt++;
		}
		
		/* Now to show the Han definition, or indicate if none exists */
		translation = find_definition(cp);
		if (translation == -1)
			translation = " -- ?";
		
		fprintf(stdout, "   %s\n", translation);
	}
	
	/* if we got here, all UTF-8 input was processed */
	return 0;
}
