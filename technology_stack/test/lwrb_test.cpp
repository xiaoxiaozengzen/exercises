#include <stdint.h>
#include <stdlib.h>

#include "lwrb/lwrb.h"

#include <stdio.h>

int main() {
  uint8_t buffer_to_write[10];
  lwrb_t ring_buffer = {0};
  uint8_t ret = lwrb_init(&ring_buffer, buffer_to_write, sizeof(buffer_to_write));
  if(ret != 1) {
    printf("Failed to initialize ring buffer\n");
    return 1;
  }

  ret = lwrb_is_ready(&ring_buffer);
  if(ret != 1) {
    printf("Ring buffer is not ready\n");
    return 1;
  }

  // size_t n_written = lwrb_write(&ring_buffer, data_to_write, data_size);

  return 0;
}