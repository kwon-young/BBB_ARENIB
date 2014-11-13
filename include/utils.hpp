#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <cstdint>
#include <climits>

#ifdef SIMULATION

#include <QMutex>
#include <QThread>
typedef QMutex Mutex;

#else

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <mutex> //requiert C++ 2011
typedef std::mutex Mutex;

#endif



#define PI 3.14159265

#define RESTART_SYSCALL(result,syscall) \
        do { (result)=(syscall);} \
        while (((result)<0)&&(errno==EINTR)); \


#endif


