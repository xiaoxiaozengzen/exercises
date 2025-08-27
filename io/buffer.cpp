#include <stdio.h>
#include <unistd.h>
#include <iostream>

/**
 * 三种缓冲类型：
 * 1. 无缓冲（_IONBF）：数据直接写入，不经过缓冲区。
 * 2. 行缓冲（_IOLBF）：缓冲区满或者调用flush时，或遇到\n换行符，才会写数据同步。
 * 3. 全缓冲（_IOFBF）：只有缓冲区满或者调用flush时，才会写数据同步
 */

/**
 * c中提供了以下函数来设置缓冲类型：
 * 1. void setbuf(FILE *stream, char *buf);
 *  - 该函数用于设置流的缓冲区。如果buf为NULL，则表示不使用缓冲区，即无缓冲模式(_IONBF)。
 * 2. void setbuffer(FILE *stream, char *buf, size_t size);
 *  - 该函数用于设置流的缓冲区和缓冲区的大小。如果buf为NULL，则表示不使用缓冲区，即无缓冲模式(_IONBF)
 * 3. void setlinebuf(FILE *stream);
 *  - 该函数用于将流设置为行缓冲模式(_IOLBF)。在这种模式下，只有在遇到换行符('\n')时，缓冲区才会被刷新。
 * 4. int setvbuf(FILE *stream, char *buf, int mode, size_t size);
 *  - 该函数用于设置流的缓冲区、缓冲模式和缓冲区的大小。
 *  - mode参数可以是以下三种之一：
 *    - _IONBF：无缓冲模式
 *    - _IOLBF：行缓冲模式
 *    - _IOFBF：全缓冲模式
 *  - 如果buf为NULL，则表示不使用缓冲区，即无缓冲模式(_IONBF)。
 *  - size参数指定缓冲区的大小，通常为BUFSIZ（标准库定义的缓冲区大小常量）。
 *  - 返回值为0表示成功，非0表示失败。
 */

/**
 * 注意，在linux下：
 * 1.stdin:
 *   如果输入来自终端，则是行缓冲的。
 *   如果输入来自文件或者管道，则是全缓冲的。
 * 2.stdout：
 *  如果输出到终端，则是行缓冲的。
 *  如果输出到文件或者管道，则是全缓冲的。
 * 3.stderr：
 * 	无论输出到哪里，都是无缓冲的。
 */
 
int main(int argc, char **args){
	if(argc != 2){
		std::cout << "Usage: " << args[0] << " <option>" << std::endl;
		return 1;
	}

	std::string option = args[1];

	printf("xxx-----01");
	sleep(1);
 
	printf(" xxx-----02\n");
    //fflush(NULL);
	sleep(2);

if(option == "1"){
		// No buffer
		setvbuf(stdout, NULL, _IONBF, 0);
	} else if(option == "2"){
		// Line buffer
		setvbuf(stdout, NULL, _IOLBF, 0);
	} else if(option == "3"){
		// Full buffer
		setvbuf(stdout, NULL, _IOFBF, 0);
	} else {
		setvbuf(stdout, NULL, _IONBF, 0);
	}
	
	printf("xxx-----03 ");
	sleep(2);
 
	printf("xxx-----04\n");
	return 0;
}