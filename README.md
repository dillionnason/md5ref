# MD5 Message-Digest Algorithm

This is an edited reference implementation of the MD5 algorithm, derived from the RSA Data Security, Inc. MD5 Message-Digest Algorithm ([RFC1321](https://www.rfc-editor.org/rfc/rfc1321.txt)). None of the core functionality of the algorithm has been touched, only bugfixes for 64-bit machines, some formatting changes, and some functions were removed from the driver code.

## Disclaimer

***MD5 is not a cryptographically secure algorithm.*** This project is purely for educational purposes, I make no assurances about security or functionality.

## Changes

- Most importantly the definitions found in [global.h](src/global.h) have been replaced throughout with uint32_t and uint16_t. The original implementation does not work on 64-bit machines otherwise.
- Function prototypes have been updated to a more modern style.
- Formatting has been changed throughout to improve readability.
- The MD2 and MD4 functionality has been removed, the algorithms were not part of the reference implementation.
- MD5TimeTrial() was not functioning properly and was removed.
- MDFilter() was not functioning properly, so it has been updated to use fgets() instead of fread(), and now passes the string to MDString() rather than doing the MD5 setup itself.

## Use 

```bash
$ git clone https://github.com/dillionnason/md5ref
$ cd md5ref && make

# generates hash from standard input
$ ./bin/md5

# runs test suite
$ ./bin/md5 -x
MD5 test suite:
MD5 ("") = d41d8cd98f00b204e9800998ecf8427e
MD5 ("a") = 0cc175b9c0f1b6a831c399e269772661
MD5 ("abc") = 900150983cd24fb0d6963f7d28e17f72
MD5 ("message digest") = f96b697d7cb7938d525a2f31aaf161d0
MD5 ("abcdefghijklmnopqrstuvwxyz") = c3fcd3d76192e4007dfb496cca67e13b
MD5 ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") = d174ab98d277d9f5a5611c2c9f419d9f
MD5 ("12345678901234567890123456789012345678901234567890123456789012345678901234567890") = 57edf4a22be3c955ac49da2e2107b67a

# generates hash from string input
$ ./bin/md5 -s"The quick brown fox jumped over the lazy dog"
MD5 ("The quick brown fox jumped over the lazy dog") = 08a008a01d498c404b0c30852b39d3b8

# generates hash from file
$ ./bin/md5 docs/rfc1321.txt
MD5 (docs/rfc1321.txt) = dbb140ad9ec3ec8d922df2573e018f89
```

## References
- Rivest, R., "The MD5 Message-Digest Algorithm", RFC 1321, DOI 10.17487/RFC1321, April 1992, <https://www.rfc-editor.org/info/rfc1321>.
- Turner, S. and L. Chen, "Updated Security Considerations for the MD5 Message-Digest and the HMAC-MD5 Algorithms", RFC 6151, DOI 10.17487/RFC6151, March 2011, <https://www.rfc-editor.org/info/rfc6151>.

