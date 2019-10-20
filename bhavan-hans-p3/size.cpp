#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define BUFFSIZE 1024

using namespace std;

/**
 * The size method returns the size of a file
 * @param int fd: The file descriptor to obtain thesize of
 */
int size(int fd){

	struct stat buf;
	fstat(fd, &buf);

	return buf.st_size;	

}

/**
 * The main method returns the size of a file or standard input
 * Its arguments can be empty, in which case it will read from standard input
 * and return the size of it.
 * Otherwise, it will return the size of the file (or files) specified in its argumentts.
 * If multiply files are specified, it will also return the total size of each file.
 */
int main(int argc, char** argv){

	if(argc == 1){

		char* buf[BUFFSIZE];
		int n=0;
		int totalSize = 0;

		do{
			n = read(STDIN_FILENO, buf, BUFFSIZE);
			totalSize += n;
		}while(n > 0);

		if(n < 0){

			perror("read");
			exit(EXIT_FAILURE);

		}

		cout << "The size of this input is " << totalSize << "\n";

	}

	if(argc > 1){

		int totalSize = 0;

		for(int i=1;i<argc;i++){

			int fd = open(argv[i], O_RDONLY);

			if(fd < 0){

				perror("open");
				exit(EXIT_FAILURE);

			}

			int fsize = size(fd);
			
			cout << "Size of " << argv[i] << " is " << fsize << " bytes\n";
			
			totalSize += fsize;

			if(close(fd) < 0){

				perror("close");
				exit(EXIT_FAILURE);

			}

		}

		cout << "\nTotal size of all files: " << totalSize << " bytes\n";

	}

}
