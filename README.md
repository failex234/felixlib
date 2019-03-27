
# Felixlib

My own simple C library with the following functions:


* int toint(const char *string) - Converts a string to an int
* int pow(const int base, int exp) - Calculates base to the power of exp
* int getsize(const char *string) - Returns the size of the input string
* **char strsplit(const char *string, const char *splitchar) - Splits the input string every time splitchar is found
* char *tobinary(int dec) - Convert a number from decimal to binary
* int todecimal(const char *bin) - Convert a number from binary to decimal
* char *tobase64(const char *bin) - Converts a string of binary numbers to base64 (This function is not completed yet. It doesn't work for every string)

# Convert a String to base64
First you need to convert every character of the string to binary. So you take the ascii numbers and convert them to binary with the function `tobinary()`. Then you have to combine all binary numbers into one string and call the `tobase64()` function with it.

**Example**

    int main(void) {
	    char buf[256], *binbuf, *b64string;
	    
	    //Read input string
	    scanf("%s", buf);

		//As the binary strings are 8 characters each we need to multiply
		//the number of characters with 8
		binbuf = malloc(sizeof(char) * strlen(buf) * 8);

		//Convert every character to a binary string
		//and add all binary representations to a string
		for (int i = 0; i < strlen(buf); i++) {
			if (i == 0) {
				strcpy(binbuf, tobinary(buf[i]));
			} else {
				strcat(binbuf, tobinary(buf[i]));
			}
		}
		
		//Convert the long binary string to base64 and print it
		b64string = tobase64(binbuf);
		printf("%s -> %s\n", buf, b64string);
	
		return 0;
    }
