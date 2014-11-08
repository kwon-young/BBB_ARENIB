#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <cstdint>
#include <climits>
#include <mutex> //requiert C++ 2011


#ifndef SIMULATION

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#endif

#define PI 3.14159265

#define RESTART_SYSCALL(result,syscall) \
        do { (result)=(syscall);} \
        while (((result)<0)&&(errno==EINTR)); \


#endif


