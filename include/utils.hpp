#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>



#define RESTART_SYSCALL(result,syscall) \
        do { (result)=(syscall);} \
        while (((result)<0)&&(errno==EINTR)); \


#endif


