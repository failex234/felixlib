#ifndef FLX_STDLIB
#define FLX_STDLIB

/*
 * Covert a string containing numbers to an int
 * "1337" -> 1337
 */
int toint( const char* );

/*
 * Calculate powers of ints
 */
int power( const int, int );

/*
 * Get size of a string
 */
int getsize( const char* );

/*
 * syntax strplit(splitarr, inputstring, splitchar)
 * splits inputstring every time splitchar is found
 * inside the string.
 * saves result in splitarr, returns number of array elements
 * 
 * inputstring = "Hello, World, Hello!", splitchar = ','
 * splitarr = ["Hello", " World", " Hello!"]
 */
char **strsplit( const char*, const char* ); 

/**
 * Checks if input string is a number
 */
int isnumber( const char* );

#endif
