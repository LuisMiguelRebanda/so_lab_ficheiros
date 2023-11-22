/*
 * open-read.c
 *
 * Simple example of opening and reading to a file.
 *
 */

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{  
      if (argv[1] == NULL) {
         fprintf(stderr, "usage: %s [1|2|3]\n", argv[0]);
         return -1;
      }

      char command_str[2] = { (*argv[1]), '\0'};
      int command = atoi(command_str);


   if (command == 1) {
      /*
      *
      * the attributes are:
      * - O_RDONLY: open the file for reading
      *
      */
      int fd = open("test.txt", O_RDONLY);

      if (fd < 0){
         fprintf(stderr, "open error: %s\n", strerror(errno));
         return -1;
      }

      char buffer[128];
      memset(buffer,0,sizeof(buffer));

      /* read the contents of the file */
      int bytes_read = read(fd, buffer, sizeof(buffer));
      if (bytes_read < 0){
         fprintf(stderr, "read error: %s\n", strerror(errno));
         return -1;
      }

      printf("%s",buffer);

      /* close the file */
      close(fd);

   } else if (command == 2) {

      FILE *fp = fopen("test.txt", "r");

      if (!fp) {
         fprintf(stderr, "open error: %s\n", strerror(errno));
         return -1;
      }

      char buffer[128];

      size_t bytes_read = fread(buffer, sizeof(char), sizeof(buffer), fp);

      if (bytes_read <= 0)
         fprintf(stderr, "read error: %s\n", strerror(errno));

      printf("%s", buffer);
      
      fclose(fp);

   } else if (command == 3) {

      FILE *fp = fopen("output.txt", "r");
      size_t size = 128;
      size_t bytes_read = 0;
      size_t total_bytes_read = 0;
      size_t size_available = size - total_bytes_read;

      char *buffer = (char *)malloc(sizeof(char) * size);
      
      if (!fp) {
         fprintf(stderr, "open error: %s\n", strerror(errno));
         return -1;
      }

      while ((bytes_read = fread(buffer + total_bytes_read, sizeof(char), size_available, fp)) > 0) {
         total_bytes_read += bytes_read;
         size *= 2;
         buffer = realloc(buffer, sizeof(char) * size);
         size_available = size - total_bytes_read;
      } 

      FILE *fp2 = fopen("test-out.txt", "w");

      if (!fp2) {
         fprintf(stderr, "open error: %s\n", strerror(errno));
         return -1;
      }

   
      int bytes_written = 0;

      if ((bytes_written = fwrite(buffer, sizeof(char), total_bytes_read, fp2)) < 0)
         fprintf(stderr, "write error: %s\n", strerror(errno));

      free(buffer);
      fclose(fp);
      fclose(fp2);
   }

   return 0;
}
