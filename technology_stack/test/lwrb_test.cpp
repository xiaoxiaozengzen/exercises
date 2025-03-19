#include <stdint.h>
#include <stdlib.h>

#include "lwrb/lwrb.h"

#include <stdio.h>

void lwrb_write_test() {
  uint8_t data_to_write1[] = {1};
  size_t data_size1 = sizeof(data_to_write1);
  uint8_t data_to_write2[] = {2, 3};
  size_t data_size2 = sizeof(data_to_write2);
  uint8_t data_to_write3[] = {4, 5, 6};
  size_t data_size3 = sizeof(data_to_write3);
  uint8_t data_to_write4[] = {7, 8, 9, 10};
  size_t data_size4 = sizeof(data_to_write4);

  // Initialize ring buffer
  uint8_t buffer_data[5] = {0}; // 5 bytes buffer用于存储数据
  lwrb_t ring_buffer = {0};
  uint8_t ret = lwrb_init(&ring_buffer, buffer_data, sizeof(buffer_data));
  if(ret != 1) {
    printf("Failed to initialize ring buffer\n");

  }
  ret = lwrb_is_ready(&ring_buffer);
  if(ret != 1) {
    printf("Ring buffer is not ready\n");

  }

  printf("======================write first=======================\n");
  // Write data to ring buffer
  size_t n_written = lwrb_write(&ring_buffer, data_to_write2, data_size2); // 写入2个字节
  printf("Wrote %ld bytes\n", n_written);
  for(size_t i = 0; i < 5; i++) {
    printf("Buffer data[%ld] = %d\n", i, buffer_data[i]);
  }

  printf("======================write second=======================\n");
  n_written = lwrb_write(&ring_buffer, data_to_write1, data_size1); // 写入1个字节
  printf("Wrote %ld bytes\n", n_written);
  for(size_t i = 0; i < 5; i++) {
    printf("Buffer data[%ld] = %d\n", i, buffer_data[i]);
  }

  printf("======================write third=======================\n");
  n_written = lwrb_write(&ring_buffer, data_to_write2, data_size2); // 只写了一个字节，因为buffer已经满了
  printf("Wrote %ld bytes\n", n_written);
  for(size_t i = 0; i < 5; i++) {
    printf("Buffer data[%ld] = %d\n", i, buffer_data[i]);
  }

  uint8_t data_to_read[4] = {0};
  printf("======================read first=======================\n");
  size_t n_read = lwrb_read(&ring_buffer, data_to_read, 1); // 读取1个字节
  printf("Read %ld bytes\n", n_read);
  for(size_t i = 0; i < 4; i++) {
    printf("Read data[%ld] = %d\n", i, data_to_read[i]);
  }

  printf("======================read second=======================\n");
  n_read = lwrb_read(&ring_buffer, data_to_read, 2); // 读取2个字节
  printf("Read %ld bytes\n", n_read);
  for(size_t i = 0; i < 4; i++) {
    printf("Read data[%ld] = %d\n", i, data_to_read[i]);
  }

  printf("======================read third=======================\n");
  n_read = lwrb_read(&ring_buffer, data_to_read, 2); // 只读了一个字节，因为buffer已经空了
  printf("Read %ld bytes\n", n_read);
  for(size_t i = 0; i < 4; i++) {
    printf("Read data[%ld] = %d\n", i, data_to_read[i]);
  }

  printf("======================write fourth=======================\n");
  n_written = lwrb_write(&ring_buffer, data_to_write4, data_size4); // 写入3个字节，因为buffer又满了
  printf("Wrote %ld bytes\n", n_written);
  for(size_t i = 0; i < 5; i++) {
    printf("Buffer data[%ld] = %d\n", i, buffer_data[i]);
  }

  printf("======================read fourth=======================\n");
  n_read = lwrb_read(&ring_buffer, data_to_read, 4); // 读取4个字节
  printf("Read %ld bytes\n", n_read);
  for(size_t i = 0; i < 4; i++) {
    printf("Read data[%ld] = %d\n", i, data_to_read[i]);
  }

  printf("======================read fifth=======================\n");
  n_read = lwrb_read(&ring_buffer, data_to_read, 4); // 读取0个字节，因为buffer已经空了
  printf("Read %ld bytes\n", n_read);
  for(size_t i = 0; i < 4; i++) {
    printf("Read data[%ld] = %d\n", i, data_to_read[i]);
  }
}

void lwrb_overwrite_test() {
  uint8_t data_to_write1[] = {1};
  size_t data_size1 = sizeof(data_to_write1);
  uint8_t data_to_write2[] = {2, 3};
  size_t data_size2 = sizeof(data_to_write2);
  uint8_t data_to_write3[] = {4, 5, 6};
  size_t data_size3 = sizeof(data_to_write3);
  uint8_t data_to_write4[] = {7, 8, 9, 10};
  size_t data_size4 = sizeof(data_to_write4);

  // Initialize ring buffer
  uint8_t buffer_data[5] = {0}; // 5 bytes buffer
  lwrb_t ring_buffer = {0};
  uint8_t ret = lwrb_init(&ring_buffer, buffer_data, sizeof(buffer_data));
  if(ret != 1) {
    printf("Failed to initialize ring buffer\n");
  }
  ret = lwrb_is_ready(&ring_buffer);
  if(ret != 1) {
    printf("Ring buffer is not ready\n");
  }

  printf("======================write overwrite first=======================\n");
  size_t n_written = lwrb_overwrite(&ring_buffer, data_to_write3, data_size3); // 写入3个字节
  printf("Wrote %ld bytes\n", n_written);
  for(size_t i = 0; i < 5; i++) {
    printf("Buffer data[%ld] = %d\n", i, buffer_data[i]);
  }

  printf("======================write overwrite second=======================\n");
  n_written = lwrb_overwrite(&ring_buffer, data_to_write4, data_size4); // 写入4个字节，覆盖旧的数据
  printf("Wrote %ld bytes\n", n_written);
  for(size_t i = 0; i < 5; i++) {
    printf("Buffer data[%ld] = %d\n", i, buffer_data[i]);
  }

  uint8_t data_to_read[4] = {0};
  printf("======================read overwrite first=======================\n");
  size_t n_read = lwrb_read(&ring_buffer, data_to_read, 3); // 读取3个字节,且若写入时超了buffer的大小，则读取开始为point_write+1位置
  printf("Read %ld bytes\n", n_read);
  for(size_t i = 0; i < 4; i++) {
    printf("Read data[%ld] = %d\n", i, data_to_read[i]);
  }

  printf("======================read overwrite second=======================\n");
  n_read = lwrb_read(&ring_buffer, data_to_read, 4); // 读取1个字节，读取位置开始，到point_write-1位置
  printf("Read %ld bytes\n", n_read);
  for(size_t i = 0; i < 4; i++) {
    printf("Read data[%ld] = %d\n", i, data_to_read[i]);
  }


}

int main() {
  printf("++++++++++++++++++++++++++++++++lwrb_write_test++++++++++++++++++++++++++++++++\n");
  lwrb_write_test();
  printf("++++++++++++++++++++++++++++++++lwrb_overwrite_test++++++++++++++++++++++++++++++++\n");
  lwrb_overwrite_test();

  return 0;
}