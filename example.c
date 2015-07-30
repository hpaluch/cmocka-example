/**
 * Example usage of io_tools library
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "io_tools.h"



int main(int argc, char **argv){
	int fd;
        int n;	
	const char *test_write = "abcdefghijklmnopqrstuv012346";
	char buf[16];

	n = io_tools_write(1,test_write,strlen(test_write));
        if ( n != strlen(test_write) ){
		fprintf(stderr,"Unexpected written bytes %d <> %d\n",
			n,(int)strlen(test_write));
		return 1;
        }
	// reading - open Makefile for reading
	fd = open("Makefile",O_RDONLY);
        if ( fd == -1 ){
		perror("open");
		return 1;
        }

	n = io_tools_read(fd,buf,sizeof(buf));
        if ( n != sizeof(buf) ){
		fprintf(stderr,"Error on io_tools_read got %d <> %d\n",
			n,(int)sizeof(buf));
		return 1;
        }



	return EXIT_SUCCESS;
}



