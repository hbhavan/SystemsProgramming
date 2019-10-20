/**
 * This program prints out all of the currently
 * set environment variables.
 *
 * @author Kenny Huang
 * @version 1.0
 *
 */
#include <iostream>
using namespace std;

/**
 * This is the main method, which utilizes its parameters
 * to print out all of the environment variables.
 * @param argc This is the number of arguments passed
 * @param argv This is a character array of all the arguments
 * @param env This is a character array of all the environment variables
 * @return nothing
 */
int main(int argc, char** argv, char** env)
{  
   char** temp;  
   cout.setf(ios::unitbuf);	//disables output buffering

   for(temp = env; *temp != 0; temp++)
   {
      char* envHere = *temp;	//stores the environment variable into temp
      cout << envHere << "\n";
   }
}
