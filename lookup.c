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

#include <stdio.h>
#include <stddef.h>
#include "lookup.h"
#include "unihan.h"
#include "unicode-names.h"

/* the unihan* symbols come from unihan.h */

/* codepoint is a U+xxxxx integer. The return value corresponds to the
   definition pointer in the unihan table. If the codepoint isn't present
	 (incl. out of bounds), the return value is NULL. If the codepoint
	 is present, but has no definition, the return value is -1, as practiced
	 in the unihan table. */
char *find_definition(int codepoint)
{
	char *result = NULL; // default return value
	int i, unimax;	// generic loop

	// first, check bounds
	if ((codepoint >= unihan_first()) && (codepoint <= unihan_last()))
	{	
		// now, search the ordered table
		i = 0;
		unimax = unihan_last();

		while (unihan[i].index <= unimax)
		{
			// check equality first
			if (codepoint == unihan[i].index)
				// codepoint found, fetch definition, or -1 if absent
				result = (char *) ((unihan[i].kDefinition == -1) ? -1 :
					unihan_strings + unihan[i].kDefinition);
			// now check for terminating conditions: codepoint found or absent
			if (codepoint <= unihan[i].index)
				// if not equal, current candidate is higher than our search
				break;
			// match not found, index not exceeded
			i++;
		}
	}
	
	// if we found a definition, return it
	if (result)
		return result;

	// otherwise, duplicate the above loop, but over the Unicode names tables
	i = 0;
	// with slightly different boundary management
	while (i <= unicode_names_count)
	{
		// check equality first
		if (codepoint == unicode_names[i].index)
		{
			// codepoint found, fetch Unicode name
			result = unicode_names_strings + unicode_names[i].name_offset;
			break;
		}
		// match not found, index not exceeded
		i++;
	}
	
	// we've done all we can do; send it back
	return result;
}

