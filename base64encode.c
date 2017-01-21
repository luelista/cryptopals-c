#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "convlib.c"

int main(int argc, char** argv) {
	#define BUFSIZE 255
	char buf[BUFSIZE];
	char dst[BUFSIZE*4/3 + 1];
#if DEBUG
printf("inbuf %lu, outbuf %lu\n", sizeof(buf), sizeof(dst));
#endif
	char *ptr = buf;
	ssize_t len;
	while(1) {
		len = read(STDIN_FILENO, ptr, BUFSIZE - (ptr-buf));
#if DEBUG
		printf("read %zd bytes\n", len);
#endif
		if (len == -1) {
			perror("read"); return 1;
		}
		ptr += len;
		if ((ptr-buf) % 3 == 0 || len == 0) {
#if DEBUG
			printf("converting %lu bytes\n", ptr-buf);
#endif
			bin2base64(buf, dst, ptr-buf);
			printf("%s\n", dst);
			ptr = buf;
		}
		if (len == 0) return 0; //eof
	}
}


