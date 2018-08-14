/* Simple test for found, not-found, no-definition,
 out-of-bounds, and the first and last entries. */

#include <stdio.h>
#include "unihan.h"
#include "lookup.h"

// Convenience
#define lookup(x) find_definition(x)
#define fail(x) fprintf(stderr, #x "\n")

int main(int argc, char *argv[])
{
	char *result;
	
	// First, test the lower bound
	result = lookup(unihan_first() - 1);
	if (result != NULL)
		fail("Outside lower bound didn't fail");

	// Now upper bound
	result = lookup(unihan_last() + 1);
	if (result != NULL)
		fail("Outside upper bound didn't fail");

	// Test not-found
	result = lookup(0x3403);
	if (result != NULL)
		fail("Not-found didn't fail");

	// Test found
	result = lookup(0x3402);
	if (result == -1)
		fail("Valid lookup failed");
	
	// No definition
	result = lookup(0x3404);
	if (result != (char *)-1)
		fail("No definition didn't return -1");
	
	// Find the first
	result = lookup(unihan_first());
	if (result == -1)
		fail("Lookup first failed");

	// Find the last
	result = lookup(unihan_last());
	if (result == -1)
		fail("Lookup last failed");
	
	return 0;
}
