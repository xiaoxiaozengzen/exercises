#include <stdio.h>
#include <unistd.h>
#include <iostream>

/**
 * 
  三种缓冲类型，全缓冲，行缓冲，无缓冲。
  _IONBF ：unbuffered
  _IOLBF ：line buffered
  _IOFBF  ：fully buffered

  无缓冲(_IONBF)：直接写入并同步。
  行缓冲(_IOLBF)：缓冲区满或者调用flush时，或遇到\n换行符，才会写数据同步。
  全缓冲(_IOFBF)：只有缓冲区满或者调用flush时，才将缓冲区数据同步到磁盘。
  
 */

/**
  void setbuf(FILE *stream, char *buf);

  void setbuffer(FILE *stream, char *buf, size_t size);

  void setlinebuf(FILE *stream);

  int setvbuf(FILE *stream, char *buf, int mode, size_t size)

 */
 
int main(int argc, char **args){
	printf("xxx-----01");
	sleep(1);
 
	printf(" xxx-----02\n");
    //fflush(NULL);
	sleep(2);
 
	//1.No buffer
	setvbuf(stdout, NULL, _IONBF, 0);
 
	//2.line buffer
	// setvbuf(stdout, NULL, _IOLBF, 0);
 
	//3.full buffer
	// setvbuf(stdout, NULL, _IOFBF, 0); 
	
	printf("xxx-----03 ");
	sleep(2);
 
	printf("xxx-----04\n");
	return 0;
}