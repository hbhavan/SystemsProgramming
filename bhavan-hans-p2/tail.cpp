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
			if(fd < 0 && strcmp(argv[i],"-")==0)
				readstdin = true;
		
			else if (fd < 0){

				perror("open");
				exit(EXIT_FAILURE);

			}

		}

		//Read from standard input
		if(readstdin){

			int numRead = 0;
			int linecount = 0;
			int k = 0;
			char temp[2048*10];

			while((numRead = read(STDIN_FILENO, buf, BUFFSIZE)) > 0){

				for(int j=0;j<numRead;j++){

					if(buf[j] == '\n')
						linecount++;
											
					temp[k] = buf[j];
					k++;

				}

			}

			int len = strlen(temp);

			int skip = linecount - numlines;
			
			//If the number of lines writter to stdin is less than the number of lines specified
			if(skip < 0){

				if(write(STDOUT_FILENO, temp, len) != len){

					perror("write");
					exit(EXIT_FAILURE);
				
				}

			}	

			else{

				int count = 0;

				for(int j=0;j<len;j++){
					
					if(count >= skip){
						
						if(write(STDOUT_FILENO, &temp[j], 1) != 1){

							perror("write");
							exit(EXIT_FAILURE);

						}
			
					}
					
					if(temp[j] == '\n')
						count++;

				}
				
			}

			readstdin = false;			
	
		}

		//Read from file
		if(fd > 0){

			int numRead = 0;
			int linecount = 0;

			//count number of lines in file
			while((numRead = read(fd, buf, BUFFSIZE)) > 0){

				for(int j=0;j<numRead;j++){

					if(buf[j] == '\n')
						linecount ++;
						
				}

			}
			
			if(numRead < 0){

				perror("read1");
				exit(EXIT_FAILURE);

			}

			int skip = linecount - numlines;
				
			int end = lseek(fd, 0, SEEK_END);
			lseek(fd, -end, SEEK_CUR);
				
			//If there are less lines in the file than the specified amount, print the whole file
			if(skip <= 0){
					
				numRead = 0;
				while((numRead = read(fd, buf, BUFFSIZE)) > 0){

					if(write(STDOUT_FILENO, buf, numRead) != numRead){

						perror("write");
						exit(EXIT_FAILURE);

					}
					
				}					
			
				if(numRead < 0){

					perror("read2");
					exit(EXIT_FAILURE);	

				}

			}

			else{

				int count = 0;				
				int bytes = 0;

				//This while loop determines how many bytes to start reading from
				numRead = 0;
				while((numRead = read(fd, buf, BUFFSIZE)) > 0){
					
					for(int j=0;j<numRead;j++){

						if(buf[j] == '\n')
							count ++;

						if(count >= skip)
							bytes ++;

						}		
					
				}
	
				//The third and final while loop for reading reads from the last x lines of the file using an offset
				lseek(fd, -bytes + 1, SEEK_END);

				while((numRead = read(fd, buf, BUFFSIZE)) > 0){

					if(write(STDOUT_FILENO, buf, numRead) != numRead){

						perror("write");
						exit(EXIT_FAILURE);

					}

				}			

			}

			if(close(fd) < 0)
				perror("close");

		}

	}

}

