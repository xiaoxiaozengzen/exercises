#include <unistd.h>
#include <fcntl.h>
#include <iostream>

void lseek_example() {
    const char* filename = "/mnt/workspace/cgz_workspace/Exercise/exercises/linux/input/test.txt";
    int fd = open(filename, O_WRONLY);
    if (fd == -1) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    
    /**
     * off_t lseek(int fd, off_t offset, int whence);
     * @brief 重新调整打开文件的读写位置
     * @param fd     File descriptor of the file
     * @param offset Offset in bytes to move the file pointer
     * @param whence Position from where offset is added:
     *               SEEK_SET: Beginning of the file
     *               SEEK_CUR: Current position of the file pointer
     *               SEEK_END: End of the file
     * @return New offset from the beginning of the file, or -1 on error
     * @note 允许设置offest超过文件end的位置(这操作不会修改文件大小)。如果随后写入数据，文件会在中间产生一个空洞('\0'填充)
     */
    off_t offset = lseek(fd, 5, SEEK_SET);
    if(offset == -1) {
        std::cerr << "Error seeking in file" << std::endl;
        close(fd);
        return;
    }
    std::cout << "New offset: " << offset << std::endl;

    char buffer[20] = "nihao";
    size_t write_bytes = write(fd, buffer, 5);
    if(write_bytes == -1) {
        std::cerr << "Error writing to file" << std::endl;
    } else {
        std::cout << "Wrote " << write_bytes << " bytes to file." << std::endl;
    }

    offset = lseek(fd, 0, SEEK_END);
    std::cout << "Final offset (end of file): " << offset << std::endl;

    offset = lseek(fd, 5, SEEK_END);
    write_bytes = write(fd, buffer, 5);
    if(write_bytes == -1) {
        std::cerr << "Error writing to file" << std::endl;
    } else {
        std::cout << "Wrote " << write_bytes << " bytes to file at offset beyond end." << std::endl;
    }

    close(fd);
}

int main() {
    std::cout << "=========== lseek example ===========" << std::endl;
    lseek_example(); // Using stdin (fd = 0) for demonstration

    return 0;
}