/* MDDRIVER.C - test driver for MD2, MD4 and MD5 */

/* Copyright (C) 1990-2, RSA Data Security, Inc. Created 1990. All
 * rights reserved.
 *
 * RSA Data Security, Inc. makes no representations concerning either
 * the merchantability of this software or the suitability of this
 * software for any particular purpose. It is provided "as is"
 * without express or implied warranty of any kind.
 *
 * These notices must be retained in any copies of any part of this
 * documentation and/or software.
 */

/* Editted by Dillion Nason - original implementation can be found in the docs
 *  - Function prototypes changed to a more modern style
 *  - MD2 and MD4 functionality removed for brevity
 *  - TimeTrial wasn't working properly, and it wasn't relevant to our 
 *  	implementation, so it was removed
 *  - MDFilter has been updated, details below
 */

#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "global.h"
#include "md5.h"

static void MDString (char *string);
static void MDTestSuite (void);
static void MDFile (char *filename);
static void MDFilter (void);
static void MDPrint (unsigned char digest[16]);

/* Main driver.
 *
 * Arguments (may be any combination):
 *   -sstring - digests string
 *   -x       - runs test script
 *   filename - digests file
 *   (none)   - digests standard input
 */
int main (int argc, char *argv[])
{
	int i;

	if (argc > 1) {
		for (i = 1; i < argc; i++)
			if (argv[i][0] == '-' && argv[i][1] == 's')
				MDString (argv[i] + 2);
			else if (strcmp (argv[i], "-x") == 0)
				MDTestSuite ();
			else
				MDFile (argv[i]);
	} else {
		MDFilter ();
	}

	return 0;
}

/* Digests a string and prints the result */
static void MDString (char *string)
{
	MD5_CTX context;
	unsigned char digest[16] = {0};
	unsigned int len = strlen (string);

	MD5Init (&context);
	MD5Update (&context, (unsigned char *)string, len);
	MD5Final (digest, &context);

	printf ("MD5 (\"%s\") = ", string);
	MDPrint (digest);
	printf ("\n");
}

/* Digests a reference suite of strings and prints the results */
static void MDTestSuite (void)
{
	printf ("MD5 test suite:\n");

	MDString ("");
	MDString ("a");
	MDString ("abc");
	MDString ("message digest");
	MDString ("abcdefghijklmnopqrstuvwxyz");
	MDString ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	MDString ("12345678901234567890123456789012345678901234567890123456789012345678901234567890");
}

/* Digests a file and prints the result */
static void MDFile (char *filename)
{
	FILE *file;
	MD5_CTX context;
	int len;
	unsigned char buffer[1024];
	unsigned char digest[16] = {0};

	if ((file = fopen (filename, "rb")) == NULL) {
		printf ("%s can't be opened\n", filename);
	} else {
		MD5Init (&context);
		while ((len = fread (buffer, 1, 1024, file)))
			MD5Update (&context, buffer, len);

		MD5Final (digest, &context);

		fclose (file);

		printf ("MD5 (%s) = ", filename);
		MDPrint (digest);
		printf ("\n");
	}
}

/* Digests the standard input and prints the result 
 *
 * This wasn't functioning properly, so the call to fread was 
 * replaced with a fgets, and the MD5 calculation was
 * replaced with a single call to MD5String 
 */
static void MDFilter (void)
{
	size_t buf_sz = 256;
	char buffer[buf_sz];
	int len;

	while (1) {
		memset(buffer, 0, buf_sz);
		fgets(buffer, buf_sz, stdin);
		/* fgets doesn't return the number of characters read like
		 * fread does, so this counts the length and removes the newline
		 * character */
		for (len = 0; buffer[len] != '\n'; len++) {}
		buffer[len] = '\0';
		MDString(buffer);
	}
}

/* Prints a message digest in hexadecimal */
static void MDPrint (unsigned char digest[16])
{
	unsigned int i;

	for (i = 0; i < 16; i++)
		printf ("%02x", digest[i]);
}
