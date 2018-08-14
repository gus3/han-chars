/*
 * Copyright © 2016 gus3
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02110-1301  USA
 */

#include <stdlib.h>
#include <stdio.h>
#include "utf8-conv.h"

/* A useful macro. Other statements may be added before the return. */
#define abort_utf8() \
	do \
	{ \
		return 0xFFFD; \
	} \
	while (0)


/* An explanation about Unicode and Han orthography:

   The Han region starts at 0x3400, and ends at 0x2FA1D. This means two
	 possible conversions between Unicode and UTF-8: the low end becomes
	 a three-octet UTF-8 sequence, but the high end takes on four octets.
	 The number of leading 1's in the first octet indicates the total number
	 of octets in the UTF-8 sequence. That is, a three-octet sequence starts
	 with a 1110xxxx, while a four-octet sequence starts with 11110xxx. Each
	 subsequent octet takes the form 10xxxxxx.
	 
	 "man utf-8" has a fantastic explanation of how Unicode and UTF-8 map
	 onto each other. Note that this code does *not* enforce the "shortest
	 valid form" rule of UTF-8.
*/

/* From bit 31 downward, how many zeros? */
static int __attribute__((unused)) count_leading_zeros(const int x)
{
	int p = 0x80000000;
	int c = 0;
	
	/* for a Unicode codepoint, this should execute at least one time */
	while ((x & p) == 0)
	{
		c++;
		p >>= 1;
	}
	return c;
}

/* From bit 8 downward, how many ones? */
static int count_leading_ones(const unsigned char x)
{
	int p = 0x80;
	int c = 0;
	
	/* 7-bit ASCII returns 0; for the first octet of a UTF-8 sequence, this should
	   execute at least two times */
	while (x & p)
	{
		c++;
		p >>= 1;
	}
	
	/* But we don't worry about UTF-8 conformance here */
	return c;
}

/* Here begin the public functions */

/* A utility function for the outside world */
const int consume_utf8(char **buf)
{
	int result = count_leading_ones(**buf);
	
	/* invalid byte count, not our problem */
	if (result == 1) return -1;
	
	/* 7-bit ASCII */
	if (result == 0) 
			result = 1;

	/* adjust pointer */
	(*buf) += result;
	
	return result;
}

const int utf8_to_unicode(const char *buf)
{
	/* A generic routine to re-assemble UTF-8 octets to a Unicode codepoint */

	int octets = count_leading_ones(*buf);
	int result;
	static int initial_mask[] = {0, 0, 31, 15, 7, 3, 1};
	
	/* plain 7-bit ASCII?  (actually 1 octet, hidden in code) */
	if (octets == 0)
		return (int)*buf;
	/* or invalid? (first octet can't be 10xxxxxx) */
	if (octets == 1)
		abort_utf8();
		
	/* otherwise, some re-assembly required */

	/* FIXME: get first UTF-8 bits from low bits of *buf */
	result = (*buf) & initial_mask[octets--];
	
	/* Now, pull in more sextets (subsequent 6 bits from UTF sequences) */
	while (octets--)
	{
		int t;	/* local temp, might get optimized out */
		
		/* next octet must be 10xxxxxx */
		if (((*++buf) & 0xC0) != 0x80)
			abort_utf8();
		
		/* mask */
		t = (*buf) & 0x3F;
		/* shift & load */
		result = t | ( result << 6);
	}
	
	/* as a final sanity check, make sure what follows is a valid first octet */
	if (((*++buf) & 0xC0) == 0x80)
		abort_utf8();

	/* If we got here, we probably have a valid codepoint from the buffer ptr */
	return result;
}

