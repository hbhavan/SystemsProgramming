#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

string prompt(){

	string result = "1730sh:";
	char cwd[1024]; 
	if(getcwd(cwd, sizeof(cwd)) == NULL){
	
		perror("getcwd");
		exit(EXIT_FAILURE);

	}
	
	result.append(cwd);
	result += "$ ";

	return result;

}

int main(){

	bool ex = false;
	pid_t pid;


	while(!ex){

		cout << prompt();
		
		//Variables for I/O redirection
		int fd = 0, lastArg = 0;
		bool stin = false, stoutTrunc = false, stoutApp = false;

		string input;
		getline(cin, input);
		
		if(input.compare("exit") == 0 ){

			ex = true;
			return 0;
		
		}

		//Convert input string into character array for execvp to use
		char * cmd = new char[input.length()+1];			
		strcpy(cmd, input.c_str());

		//Splits each command into tokens split by white space for exevcp
		char * token = strtok(cmd, " ");
		
		char * arg[12];
		unsigned int count = 0;

		//Populate character array of tokens
		while(token != 0 && count < 12){

			arg[count] = token;
			count++;
			token = strtok(NULL, " ");

		}
	
		//Set last element of array to NULL
		arg[count] = NULL;
		
		//Adding environment variables 
		if(strcmp(arg[0], "export") == 0){
			putenv((char*) arg[1]);
			continue;	//This continue prevents issues from occuring
		}	

		//Redirecting I/O
		for(uint i = 0; i < count; i++){
		
			//Changes redirect standard input to true
			if(*arg[i] == '<'){
				stin = true;
				lastArg = i - 1;
			}

			//Changes append std output to true
			else if(strcmp(arg[i], ">>") == 0){
				stoutApp = true;
				lastArg = i - 1;
			}
			
			//Changes truncate std output to true
			else if(*arg[i] == '>'){
				stoutTrunc = true;
				lastArg = i - 1;
			}
			
		}
		
		//New character array if redirection is involved
		char * arg2[12];
		
		//This fills the new character array with arguments up until
		//the redirection symbol so the symbol isn't passed as an argument
		if(lastArg != 0){
			for(int i = 0; i < lastArg + 2; i++){
				if(i + 1 == lastArg + 2){
					arg2[i] = nullptr;
					break;
				}
				arg2[i] = arg[i];
			}
		}
	
		if((pid = fork()) == -1){
			perror("fork");
		}

		else if(pid == 0){
		
			cout << arg[0];
			
			//Opens file and redirects standard input to come from file
			if(stin == true){
				if((fd = open(arg[lastArg+2], O_RDONLY, 0777)) < 0){
					perror("open1");
				}	

				if(dup2(fd, STDIN_FILENO) < 0){
					perror("dup2in");	
				}
				stin = false;
			}
			
			//Opens file and redirects standard output to overwrite file
			else if(stoutTrunc == true){
				if((fd = open(arg[lastArg+2], O_TRUNC | O_WRONLY | O_CREAT, 0777)) < 0){
					perror("open2");
				}	

				if(dup2(fd, STDOUT_FILENO) < 0){
					perror("dup2out");	
				}
				stoutTrunc = false;
			}
			
			//Opens file and redirects standard output to append to file
			else if(stoutApp == true){
				if((fd = open(arg[lastArg+2], O_APPEND | O_WRONLY | O_CREAT, 0777)) < 0){
					perror("open");
				}	

				if(dup2(fd, STDOUT_FILENO) < 0){
					perror("dup2out");	
				}
				stoutApp = false;	
			}
			
			//If redirection is involved, uses arg2 to prevent unnecessary arguments
			//from being passed. Also closes file descriptor
			if(lastArg != 0){
				execvp(arg2[0], arg2);
				if(close(fd) < 0){
					perror("close");
				}
			}
			
			//Executes commands not related to redirection
			else{
				execvp(arg[0], arg);
				perror("execvp");
			}

		}

		else
			wait(0);
		
		delete[] cmd;
	
	}

	return 0;

}

