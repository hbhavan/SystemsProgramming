#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

using namespace std;

/**
 * accesscmp compares the access time of two files
 * @param int fd1, int fd2: The file descriptors to be compared
 * @return: true if fd1's access time is larger than fd2's, false otherwise
 */
bool accesscmp(int fd1, int fd2){

	struct stat buf1;
	fstat(fd1, &buf1);

	struct stat buf2;
	fstat(fd2, &buf2);

	return buf1.st_atime > buf2.st_atime;

}

/**
 * modifycmp compares the modify time of two files
 * @param int fd1, int fd2: The file descriptors to be compared
 * @return: true if fd1's modify time is larger than fd2's, false otherwise
 */
bool modifycmp(int fd1, int fd2){

	struct stat buf1;
	fstat(fd1, &buf1);

	struct stat buf2;
	fstat(fd2, &buf2);

	return buf1.st_mtime > buf2.st_mtime;

}

/**
 * createcmp compares the create time of two files
 * @param int fd1, int fd2: The file descriptors to be compared
 * @return: true if fd1's create time is larger than fd2's, false otherwise
 */
bool createcmp(int fd1, int fd2){

	struct stat buf1;
	fstat(fd1, &buf1);
	
	struct stat buf2;
	fstat(fd2, &buf2);

	return buf1.st_ctime > buf2.st_ctime;

}

/**
 * The main method compares the access, modify, or create time of two files
 * It takes three parameters: an option to specify what is being compared,
 * the access, modify, or create time, and the two files to be compared
 */
int main(int argc, char** argv){

	if(argc != 4){

		cout << "USAGE: " << argv[0] << " (-a | -m | -c) [FILE1] [FILE2]\n";
		exit(EXIT_FAILURE);
	
	}

	if(!(strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "-m") == 0 || strcmp(argv[1], "-c") == 0)){

		cout << "Please specify a command option: (-a | -m | -c)\n";
		exit(EXIT_FAILURE);

	}

	int fd1 = open(argv[2], O_RDONLY);
	int fd2 = open(argv[3], O_RDONLY);

	if(fd1 < 0 || fd2 < 0){

		perror("open");
		exit(EXIT_FAILURE);

	}

	if(strcmp(argv[1], "-a") == 0){

		if(accesscmp(fd1, fd2))
			cout << argv[2] << " is newer than " << argv[3] << "\n";
		
		else
			cout << argv[3] << " is newer than " << argv[2] << "\n";

	}

	if(strcmp(argv[1], "-m") == 0){

		if(modifycmp(fd1, fd2))
			cout << argv[2] << " is newer than " << argv[3] << "\n";
		
		else
			cout << argv[3] << " is newer than " << argv[2] << "\n";	

	}

	if(strcmp(argv[1], "-c") == 0){
	
		if(createcmp(fd1, fd2))
			cout << argv[2] << " is newer than " << argv[3] << "\n";

		else 
			cout << argv[3] << " is newer than " << argv[2] << "\n";

	}

	if(close(fd1) < 0 || close(fd2) < 0){

		perror("close");
		exit(EXIT_FAILURE);
	
	}

	return 0;

}
