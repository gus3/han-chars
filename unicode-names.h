/*

 This mostly-data file is derived from gucharmap's unicode-names.h which is
 itself a generated file. gucharmap 3.12.1 does not have a license stipulation
 in the unicode-names.h file, from which this file is derived. Therefore, as I
 understand it, I am not bound by any software license, free or proprietary.

 However, to avoid any questions about licensing, this file is hereby placed
 under the GPLv3, as a "Covered Work" as defined in section 0 (Definitions).
 Since the overall Program will be under the same License, this is a sensible
 action.
 
 Note that, in removing the <10 lines of code, I acknowledged this file to be
 "Source Code" as defined in section 1, "Source Code". But in doing so, I
 changed this file into "Object Code", that is, something that is very difficult
 (for me) to modify. Even after adding a few lines of utility code at the end,
 the bulk of this work remains primarily "Object Code". Given this ambiguity,
 classifying it as a "Covered Work" can keep the GPLv3 in force, without
 declaring the specific type of coverage that applies.
 
 If you wish to use these structs in your own program, that does not involve
 deriving a program from this one, I refer you instead to the source code for
 gucharmap, in particular the header file unicode-names.h. The structure of the
 data is fairly straightforward. If you are concerned about your legal
 rights/obligations, you should consult a lawyer.
*/

#ifndef UNICODE_NAMES_H
#define UNICODE_NAMES_H

typedef struct _UnicodeName UnicodeName;

struct _UnicodeName
{
  int index;
  int name_offset;
};

extern const struct _UnicodeName unicode_names[];
extern const char unicode_names_strings[];
extern const int unicode_names_count;
extern const int unicode_names_last();

#endif  /* #ifndef UNICODE_NAMES_H */
