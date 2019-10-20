/**
 * This program lists all of the files in the current working
 * directory, printing one on each line by utilizing the opendir()
 * and readdir() system calls.
 *
 * @author Kenny Huang
 * @version 1.0
 *
 */
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <dirent.h>

using namespace std;

/**
 * This is the main method, which uses the system calls readdir()
 * and opendir() to print out the files (hidden files included)
 * of the current working directory.
 * @return nothing
 */
int main()
{
   struct dirent *entry = nullptr;	// pointer for entry
   DIR *pwd = opendir(".");	// opens directory
   
   if(pwd == nullptr)	// checks to see if opendir() works
   {
      perror("Opendir");
   }
   else
   {
      while((entry = readdir(pwd)) != nullptr)	// reads entries
      {
         cout << entry->d_name << endl;
      }
   }
   closedir(pwd);	// closes directory
   return EXIT_SUCCESS;
}
