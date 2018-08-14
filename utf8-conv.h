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

#ifndef UTF8_CONV_H
#define UTF8_CONV_H

/* Convert UTF-8 in character buffer to Unicode codepoint */
const int utf8_to_unicode(const char *);

/* Indicate how many octets consumed in a UTF-8 sequence
   and adjusts pointer accordingly */
const int consume_utf8(char **);

/* Convert Unicode codepoint to UTF-8 */
// char *unicode_to_utf8(int);

#endif /* UTF8_CONV_H */
