#include <stdio.h>
#include <stdlib.h>
#include "felixlib.h"


int main( void ) {
	char *input = "1337\0";
	char *teststring = "This is a test!";
	//char **split = strsplit( "Felix, Felix, Hallo!", ',' );


	printf( "%s -> %d\n", input, toint( input ) );
	printf( "2^12 = %d\n", power( 2, 12 ) );
	printf( "%s -> %d\n", teststring, getsize( teststring ) );
	//printf( "Felix, Felix, Hallo! -> %s %s %s\n", split[0], split[1], split[2] );
	printf( "12 -> %d\n12f -> %d\n3231233 -> %d\n4h4355j3d -> %d\n", isnumber("12"), isnumber("12f"), isnumber("3231233"), isnumber("4h4355j3d") );

	//free( input );
	//free( teststring );
	//free( split );

	return 0;
}

