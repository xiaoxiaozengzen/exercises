/* FEOF example */
#include <stdio.h>

int main() {
  FILE* pFile;
  char buffer[100];

  pFile = fopen("/mnt/workspace/cgz_workspace/Exercise/exercises/file/file_example.cpp", "r");
  if (pFile == NULL)
    perror("Error opening file");
  else {
    while (!feof(pFile)) {
      if (fgets(buffer, 100, pFile) == NULL) break;
      fputs(buffer, stdout);
    }
    fclose(pFile);
  }
  return 0;
}