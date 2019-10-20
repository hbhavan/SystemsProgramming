#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define BUFFSIZE 1024
#define DEFAULT 10

using namespace std;

int main(int argc, char ** argv){

	char buf[BUFFSIZE];
	int numlines = DEFAULT;

	bool readstdin = false;

	//Check to see what the arguments are
	int arg = 1;
	if(argc == 1)
		readstdin = true;

	else if(argc > 2){

		if(strcmp(argv[1], "-n") == 0){

			numlines = atoi(argv[2]);
			arg += 2;
		
			if(argc == 3)
				readstdin = true;	
				
		}

	}

	for(int i=arg;i<argc || readstdin;i++){

		int fd = -1;
		if(argc > 1 && argc != 3){
			
			fd = open(argv[i], O_RDONLY);

			if(fd < 0 && strcmp(argv[i],"-") == 0)
				readstdin = true;
	
			else if(fd < 0){

				perror("open");
				exit(EXIT_FAILURE);

			}

		}

		//Read from standard input	
		if(readstdin){
			
			int numRead = 0;
			int count = 0;
	
			while((numRead = read(STDIN_FILENO, buf, BUFFSIZE)) > 0){

				int bytes = 0;
					
				for(int j=0;j<numRead && count<numlines;j++){

					if(buf[j] == '\n')
						count++;
		
					bytes++;

				}	

				if(write(STDOUT_FILENO, buf, bytes) != bytes){

					perror("write");
					exit(EXIT_FAILURE);

				}
				
				if(count == numlines)
					break;

			}

			if(numRead < 0){

				perror("read");
				exit(EXIT_FAILURE);

			}
		
			readstdin = false;	

		}
			
		//Read from a file
		if(fd > 0){

			int numRead = 0;
			int count = 0;
	
			while((numRead = read(fd, buf, BUFFSIZE)) > 0 && count < numlines){

				int bytes = 0;

				for(int j=0;j<numRead && count<numlines;j++){
						
					if(buf[j] == '\n')
						count ++;
						
					bytes ++;					
						
				}
	
				if(write(STDOUT_FILENO, buf, bytes) != bytes){

					perror("write");
					exit(EXIT_FAILURE);
					break;
	
				}			

			}

			if(numRead < 0){

				perror("read");
				exit(EXIT_FAILURE);

			}

			if(close(fd) < 0)
				perror("close");
		
			
		}

	}
	
}

