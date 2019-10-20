/**
 * This program prints its process id, as well as its parent's
 * process id. Then, it forks a child process and prints the child
 * process's id, as well as the child's parent's process id.
 *
 * @author Kenny Huang
 * @version 1.0
 *
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

using namespace std;

/**
 * This is the main method, which utilizes the fork() system call
 * to fork a child process and allow for all the process id's to
 * be printed out
 * @return nothing
 */
int main()
{
   pid_t pid;

   cout << "Current process info: " << endl;
   cout << "Process ID: " << getpid() << endl; 
   cout << "Parent Process ID: " << getppid() << endl;
   if((pid = fork()) == -1)	// checks if fork() works
   {
      perror("Fork error");
   }
   else if(pid == 0)	// only prints out child process info instead of both child and parent info
   {
      cout << endl;
      cout << "Child process info: " << endl;
      cout << "fork() = " << pid << endl;
      cout << "Process ID: " << getpid() << endl;
      cout << "Parent Process ID: " << getppid() << endl;
   }
   else
   {
      sleep(1);		// makes sure parent process doesn't finish too early
   }   
   return EXIT_SUCCESS;
}
