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
	int n;

	check_expected(fd);
	check_expected_ptr(buf);
	check_expected(count);


	n=mock_type(int);
//	printf("n=%d fd=%d,buf=%s,count=%d\n",n,fd,buf,count);
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


int main(int argc, char **argv){

	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_io_tools_write)
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}

