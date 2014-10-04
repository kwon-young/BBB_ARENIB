#ifndef utils.hpp
#define utils.hpp

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>



#define RESTART_SYSCALL(result,syscall) \
        do { (result)=(syscall);} \
        while (((result)<0)&&(errno==EINTR));


#endif
