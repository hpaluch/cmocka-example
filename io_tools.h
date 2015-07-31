#ifndef IO_TOOLS_H
#define IO_TOOLS_H

#include <unistd.h>

/* ensures full write(2) */
extern ssize_t io_tools_write(int fd, const void *buf, size_t count);

/* ensures full read(2) */
extern ssize_t io_tools_read(int fd, void *buf, size_t count);

#endif
