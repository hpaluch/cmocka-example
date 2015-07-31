CMocka example - simple io_tools library
========================================

Here is an example how to mock write(2) and read(2) calls to
verify proper function of local io_tools library (that 
uses such functions)

Setup
-----

Tested on CentOS 6.x

* install EPEL repo:

	rpm -ivh https://dl.fedoraproject.org/pub/epel/6/x86_64/epel-release-6-8.noarch.rpm

* install required packages

	yum install libcmocka-devel gcc glibc-devel make binutils


Run
---

To just run example (without mock/tests):

	make run

To run CMocka test

	make test_mocka

