#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "io_tools.h"

ssize_t __wrap_write(int fd, const void *buf, size_t count){
	ssize_t n;

	check_expected(fd);
	check_expected_ptr(buf);
	check_expected(count);

	n=mock_type(ssize_t);
//	printf("write n=%d fd=%d,buf=%s,count=%d\n",n,fd,buf,count);
	return n;
}

ssize_t __wrap_read(int fd, const void *buf, size_t count){
	ssize_t n;
	char *read_data;

	check_expected(fd);
	check_expected_ptr(buf);
	check_expected(count);

	read_data = mock_type(char*);
	// check for possible buffer overflows
	assert_in_range(strlen(read_data),1,count);
	// NOTE: real buf must have size + 1 for terminating '\0' char!!!
	strcpy((char*)buf, read_data );

	n=mock_type(ssize_t);
//	printf("read: n=%d fd=%d,buf=%s,count=%u\n",(int)n,fd,(char*)buf,(unsigned)count);
	return n;
}


static void test_io_tools_write(void **state){
	int n;
	(void) state; /* unused */

	char *xbuf = "abc12345";

	expect_value(__wrap_write, fd, 1);
	expect_string(__wrap_write, buf, xbuf);
	expect_value(__wrap_write, count, 8);
	will_return(__wrap_write, 3);

	expect_value(__wrap_write, fd, 1);
	expect_string(__wrap_write, buf, xbuf+3);
	expect_value(__wrap_write, count,5);
	will_return(__wrap_write, 5);

	n = io_tools_write(1,xbuf,strlen(xbuf));
	assert_int_equal(n,strlen(xbuf));


}

static void test_io_tools_read(void **state){
	int n;
	(void) state; /* unused */

	char xbuf[9]; // 8 + '\0'

	expect_value(__wrap_read, fd, 1);
	expect_value(__wrap_read, buf, xbuf);
	expect_value(__wrap_read, count, 8);
        will_return(__wrap_read,
		cast_ptr_to_largest_integral_type("xyz"));
	will_return(__wrap_read, 3);

	expect_value(__wrap_read, fd, 1);
	expect_value(__wrap_read, buf, xbuf+3);
	expect_value(__wrap_read, count,5);
        will_return(__wrap_read,
		cast_ptr_to_largest_integral_type("54321"));
	will_return(__wrap_read, 5);

	n = io_tools_read(1,xbuf,8);
	assert_int_equal(n,strlen(xbuf));
	assert_string_equal("xyz54321",xbuf);
}



int main(int argc, char **argv){

	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_io_tools_write),
		cmocka_unit_test(test_io_tools_read)
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}

