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

#ifndef UNIHAN_H
#define UNIHAN_H

struct _Unihan
{
  int index;
  int kDefinition;
  int k1; /* the rest are now just fillers */
  int k2;
  int k3;
  int k4;
  int k5;
  int k6;
};

/* The data pointers. */
extern const struct _Unihan unihan[];
extern const char unihan_strings[];
extern const int unihan_count;
extern const int unihan_first();
extern const int unihan_last();


#endif /* UNIHAN_H */
