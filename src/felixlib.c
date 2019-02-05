#include "felixlib.h"
#include <stdlib.h>
#include <string.h>

char base64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

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

//Convert a decimal number into a binary number string
char *tobinary(int decimal) {
    int tempdec = decimal;
    int binarynumlength = 0;
    int binarylong = 8;

    //Get the length of the binary number
    while (tempdec != 0) {
        binarynumlength++;
        tempdec /= 2;
    }

    tempdec = decimal;

    //Check how many zeroes are needed to fill up
    if (binarynumlength % 8 != 0) {
        float filledbinarydigits = binarynumlength / 8.0f;
        filledbinarydigits = (float) ceil(filledbinarydigits);
        binarylong = (int) filledbinarydigits * 8;
    } else {
        binarylong = binarynumlength;
    }


    char *binarynum = malloc(sizeof(char) * (binarylong));
    int strindex = binarylong - 1;

    while (tempdec != 0) {
        if (tempdec % 2 == 0) {
            binarynum[strindex] = '0';
        } else {
            binarynum[strindex] = '1';
        }
        strindex--;
        tempdec /= 2;
    }
    binarynum[binarylong] = '\0';

    //Fill in leading zeroes
    if (binarylong - binarynumlength != 0) {
        while(strindex > 0) {
            binarynum[strindex--] = '0';
        }
        binarynum[0] = '0';
    }


    return binarynum;
}

//Convert a binary number (string) to a decimal number
int todecimal(const char *bin) {
    int length = strlen(bin);
    int position = 0;
    int result = 0;

    while(position != length) {
        result += (bin[length - position - 1] - 48) * (int) pow(2, position);
        position++;
    }

    return result;
}


//Encode a "binary number string" to base64. Use toBinary to convert your ascii characters 
//into binary numbers. Use toBinary on all ascii characters in a string to get a "binary number string"
char *tobase64(const char *bin) {
    char *b64str = malloc(sizeof(char) * (strlen(bin) * 8 / 6 + 1 + strlen(bin) % 6));
    int b64index = 0;

    char *chrptr = (char *) bin;
    while(strlen(chrptr) != strlen(bin) % 6) {
        char substr[7];
        memcpy(substr, chrptr, 6);
        substr[6] = '\0';

        int num = todecimal(substr);
        b64str[b64index] = base64chars[num];
        b64index++;

        chrptr += 6;
    }
    //With fillings
    if (strlen(bin) % 6) {
        int missing = strlen(bin) % 6;
        int count = missing + 1;
        char remainder[7];
        memcpy(remainder, chrptr, (size_t) 6 - missing);
        while (count >= 0) {
            remainder[5 - count] = '0';
            count--;
        }
        remainder[6] = '\0';

        int num = todecimal(remainder);
        b64str[b64index] = base64chars[num];
        b64index++;

        while (missing != 0) {
            b64str[b64index] = '=';
            missing--;
            b64index++;
        }
    }

    b64str[b64index] = '\0';

    return b64str;
}