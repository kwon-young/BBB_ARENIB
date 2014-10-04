
#include "utils.hpp"


int main (int argc, char *argv[]) {
  for (int i=0; i<argc; i++) {
    if (i==1) {
      printf ("argc = %d : %s\n", i, argv[i]);
    }
    else if (i==2) {
      printf ("argc = %d : %s\n", i, argv[i]);
    }
  }
  int i2c_bus=1;
  int i2c_addr=0x48;
  char name_bus[42];
  int i2c_file;
  int r;
  char err_str[10+strlen(name_bus)]; 
  char buff[1]={ 0x0 };
  char temp[2];
  int temp_int;
  float temp_float;

  snprintf(name_bus, sizeof(name_bus), "/dev/i2c-%d", i2c_bus);

  RESTART_SYSCALL(i2c_file, open(name_bus, O_RDWR));
  if (i2c_file==-1) {
    sprintf(err_str, "open %s", name_bus);
    perror(err_str);
    return -1;
  }
  
  RESTART_SYSCALL(r, ioctl(i2c_file, I2C_SLAVE, i2c_addr));
  if (r==-1) {
    sprintf(err_str, "ioctl %s", name_bus);
    perror(err_str);
    return -1;
  }

  while(1) {
  RESTART_SYSCALL(r, write(i2c_file, buff, 1));
  if (r==-1) {
    perror("write start bit");
  }

  RESTART_SYSCALL(r, read(i2c_file, temp, sizeof(temp)));
  if (r!=sizeof(temp)) {
    perror("read temp");
  }

  temp_int=temp[0];
  if (temp[0]>>7) {
    temp_int*=-1;
    temp_int&=~(1<<7);
  }
  temp_float=temp_int;
  if (temp[1]>>7) temp_float+=0.5;
  printf("il fait %.1f degree celsius\n", temp_float);

  sleep(1);
  }
  RESTART_SYSCALL(r, close(i2c_file));
  if (r==-1) {
    sprintf(err_str, "close %s", name_bus);
    perror(err_str);
  }
  return 0;

}


