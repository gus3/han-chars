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

#ifndef LOOKUP_H
#define LOOKUP_H

/* Given a Unicode (not UTF-8) codepoint, return a pointer to the definition
   for the glyph. If the codepoint is not found, return NULL. If the definition
	 is absent, return -1.
*/

extern char *find_definition(int);

#endif /* LOOKUP_H */
