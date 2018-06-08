#include "felixlib.h"
#include <stdlib.h>
#include <string.h>

/*
 * get size of a string
 */
int getsize(const char *string) {
	int ch;
	int i = 0;
	while ((ch = string[i]) != '\0') {
		i++;
	}

	return i;
}

/*
 * calculate base to the power of exp
 */
int power(const int base, int exp) {
	int result = 1;
	while(exp != 0) {
		result *= base;
		exp--;
	}

	return result;
}

/* Convert string to int by firstly
 * getting the single number on any position by subtracting 48 (or in this case '0')
 * then multiplying it by the potency of the numberbase, based on the position
 * and then adding it to the result
 *
 * example:
 * input: 120 (base 10)
 *
 * tempnum = 1
 * finalnum = 1 * 10^(stringsize - i - 1)
 * finalnum = 1 * 10^2
 * finalnum = 100
 *
 * result = 100
 *
 * tempnum = 2
 * finalnum = 2 * 10^(stringsize - i - 1)
 * finalnum = 2 * 10^1
 * finalnum = 20
 *
 * result = 100 + 20
 * result = 120
 *
 * tempnum = 0;
 * finalnum = 0 * 10^(stringsize - i - 1)
 * finalnum = 0 * 10^0
 * finalnum = 0;
 *
 * result = 120 + 0
 *
 * result = 120
 *
 */
int toint(const char *string) {

	int result = 0;
	int tempnum = 0;
	int finalnum = 0;
	for (int i = 0; i < getsize(string); i++) {
		tempnum = string[i] - '0';
		finalnum = tempnum * power(10, getsize(string) - i - 1);
		result += finalnum;
	}

	return result;

}

//Still figuring out how to return the split string. Maybe as an struct array
char **strsplit(const char *inputstring, const char *splitchar) {
	char **splitarr = NULL;
	int size = 0;
	int bufpos = 0;
	int splitarrsize = 0;
	int splitarrpos = 0;
	int endsize = 0;
	char *buf = malloc(sizeof(char) * 1024);
	for(int i = 0; i < getsize(inputstring); i++) {
		if (inputstring[i] == splitchar) {
			if (splitarr == 0) {
				splitarr = malloc(sizeof(char) * getsize(buf));
				splitarr[0] = malloc(sizeof(char) * getsize(buf));
				strcpy(splitarr[splitarrpos], buf);
				splitarrsize = getsize(buf);
				splitarrpos++;
				endsize++;
				
				size = splitarrsize;
				//omit splitchar
				i++;
			} else {
				splitarr = realloc(splitarr, sizeof(char) * (size + getsize(buf)));
				splitarr[splitarrpos] = malloc(sizeof(char) * getsize(buf));
				strcpy(splitarr[splitarrpos], buf);
				splitarrpos++;
				endsize++;
				
				size += getsize(buf);
			}
			free(buf);
			buf = malloc(sizeof(char) * 1024);
			bufpos = 0;
		} else {
			buf[bufpos] = inputstring[i];
			bufpos++;
		}
	}
	
	splitarr = realloc(splitarr, sizeof(char) * (size + getsize(buf)));
	splitarr[splitarrpos] = malloc(sizeof(char) * getsize(buf));
	strcpy(splitarr[splitarrpos], buf);
	free(buf);
	endsize++;
	
	return endsize;
}

int isnumber( const char *string ) {
	int isnumber = 1;
	for (int i = 0; i < getsize(string); i++ ) {
		if (string[i] < 48 || string[i] > 57) {
			isnumber = 0;
		}
	}

	return isnumber;
}
