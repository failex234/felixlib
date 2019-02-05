#include <stdio.h>
#include <stdlib.h>
#include "felixlib.h"


int main( void ) {
	char *input = "1337\0";
	char *teststring = "This is a test!";
	char b64test[] = "Base64!";
	char *b64bin = malloc(sizeof(char) * strlen(b64test) * 8);


	printf("strsplit not yet working!\n");
	printf( "%s -> %d\n", input, toint( input ) );
	printf( "2^12 = %d\n", power( 2, 12 ) );
	printf( "%s -> %d\n", teststring, getsize( teststring ) );
	printf( "12 -> %d\n12f -> %d\n3231233 -> %d\n4h4355j3d -> %d\n", isnumber("12"), isnumber("12f"), isnumber("3231233"), isnumber("4h4355j3d") );
	
	for (int i = 0; i < strlen(b64test); i++) {
        char *temp = tobinary(b64test[i]);
        if (i == 0) {
            strcpy(b64bin, temp);
        } else {
            strcat(b64bin, temp);
        }
    }
	
	printf("%s as binary number string -> %s\n", b64test, b64bin);
	printf("%s encoded as base64 -> %s\n", b64test, tobase64(b64bin));

	return 0;
}

