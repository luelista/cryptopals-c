#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "convlib.c"

int main(int argc, char** argv) {
	if (argc > 1) {
		size_t len = strlen(argv[1]) / 2;
		char* dst = (char*) malloc(len);
		hex2bin(argv[1], dst, len);
		write(STDOUT_FILENO,dst,len);
		return 0;
	} else {
		#define BUFSIZE 256
		char buf[BUFSIZE];
		char dst[BUFSIZE*2 + 1];
		ssize_t len;
		while(1) {
			len = read(STDIN_FILENO, buf, BUFSIZE);
			if (len == -1) {
				perror("read"); return 1;
			}
			if (len == 0) return 0; //eof
			bin2hex(buf, dst, len);
			write(STDOUT_FILENO, dst, len*2);
			putchar('\n');
		}
	}
}


