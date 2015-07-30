/**
 * Sample I/O library - provides functions
 * to ensure full write on write(2)
 * and full read on read(2)
 */
#include<unistd.h>

size_t io_tools_write(int fd, const void *buf, size_t count){
	int n;
	size_t remainder = count ;

        if ( remainder <= 0 ){
		return 0;
        }

	while ( (n=write(fd,buf+(count-remainder),remainder))>0 ){
           remainder -= n;
        }
        if ( n < 0 ){
		return n;
        } 
	return count;
}
ssize_t io_tools_read(int fd, void *buf, size_t count){
	int n;
	size_t remainder = count;

	while ( (n=read(fd,buf+(count-remainder),remainder))>0 ){
           remainder -= n;
        }
        if ( n < 0 ){
		return n;
        } 
	return count;
}

