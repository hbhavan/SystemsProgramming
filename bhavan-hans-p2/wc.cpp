/**
 * This program simulates the "wc" command in Linux by
 * providing the number of bytes, newlines, and/or words within
 * a file or within the standard input. If no files are specified,
 * then it will simply report the data on the standard input.
 *
 * @author Kenny Huang
 * @version 1.0
 *
 */
#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<cstdlib>
#include<string.h>
#include<cstdio>
#include<ctype.h>
using namespace std;

int numWords = 0, numNewlines = 0, numBytes = 0;
bool isWord;

/**
 * This method takes in a character array that represents
 * the file that will be examined, and it counts the number of
 * newlines, words, and bytes of it, incrementing the totals
 * for the global variables by 1 at specific points.
 * @param *file This is the file that is passed as a param in the command line
 * @return nothing
 */
void count(char *file)
{
   char buf[1];
   int fd = open(file, O_RDONLY); 

   /*checks to see if open() works */
   if(fd < 0)
   {
      perror("Error opening input file");
      exit(EXIT_FAILURE);
   }      
   
   /* reads the file one bit at a time */
   while(int n = read(fd, buf, 1) == 1)
   {
      if(n == -1)
      {
         perror("Read1");
         exit(EXIT_FAILURE);
      }
      numBytes++;	  
      if(isspace(buf[0])) // checks if the chracter is a space of some sort
      {
         isWord = false;  //change "word" status to false
         if(buf[0] == '\n')
         {
            numNewlines++;
         }
      }
      else
      {
	 if(isWord == false) // if it is a space character, increment numWords
	 {
            numWords++;
         }
	 isWord = true;
      }
   }
   if(close(fd) == -1)
   {
      perror("Close");
   }
}

/**
 * This method overloads the previous count() method, allowing for
 * an integer parameter. This is to allow standard input to be
 * examined for words, bytes, and newlines.
 * @param file This is the number that represents standard input
 * @return nothing
 */
void count(int file)
{
   int fd = file; // "file" is usually 0 in this case (STDIN_FILENO)     
   char buf[1];
   
   /* reads the standard input one bit at a time */
   while(int n = read(fd, buf, 1) == 1)
   {
      if(n == -1)
      {
         perror("Read2");
         exit(EXIT_FAILURE);
      }
      numBytes++;
      if(isspace(buf[0])) // checks if character is a space of some sort
      {
         isWord = false;  // change "word" status to false
         if(buf[0] == '\n')
         {
            numNewlines++;
         }
      }
      else
      {
	 if(isWord == false) // if it is a space character, increment numWords
	 {
            numWords++;
         }
	 isWord = true;
      }
   }
}

/**
 * This is the main method, which utilizes the previously defined methods
 * to take in the user's command line input and perform tasks based on
 * what was sppecified. By the end of it all, the number of bytes,
 * newlines, or words will be printed.
 * @param argc This is the number of arguments passed in the command line
 * @param argv This is a character array of arguments passed by the user
 * @return nothing
 */
int main(int argc, char** argv)
{
   cout.setf(ios::unitbuf);
   /*returns error if there are no parameters */
   if(argc < 2)
   {
      cout << "Usage: ./wc [-c | -l | -w] [File...] \n";
      exit(EXIT_FAILURE);
   }
   else
   {
      /* if the first argument is "-c" */
      if(strcmp(argv[1], "-c") == 0)
      {

         /* if there are no arguments after -c */
	 if(argc == 2)
	 {
	    count(0);	// 0 for STDIN_FILENO
	    cout << numBytes << "\n";
	    exit(EXIT_SUCCESS);
         }

	 /* cycles through the arguments */
         for(int i = 2; i < argc; i++)
         {
	    int temp = numBytes;

            if(*argv[i] == '-')    // if there is a '-'
            {
	       count(0);
               temp = numBytes - temp;
	       cout << temp << " -\n";
            }
	    else
	    {          
               count(argv[i]);
	       temp = numBytes - temp;
               cout << temp << " " << argv[i] << "\n";
            }
	 }
         if(argc > 3) // for more than one file, output the total
	 {
            cout << numBytes << " total \n";
         }
      }
      /* if the first argument is "-l" */
      else if(strcmp(argv[1], "-l") == 0)
      {	 
         /* if there are no arguments after -l */
	 if(argc == 2)
	 {
	    count(0);
	    cout << numNewlines << "\n";
	    exit(EXIT_SUCCESS);
         }

	 /* cycles through the arguments */
         for(int i = 2; i < argc; i++)
         { 
            int temp = numNewlines;

            if(*argv[i] == '-')   // if there is a '-'
            {
	       count(0);
               temp = numNewlines - temp;
	       cout << temp << " -\n";
            }
	    else
	    {                     
               count(argv[i]);
	       temp = numNewlines - temp;
               cout << temp << " " << argv[i] << "\n";
            }
         }
         if(argc > 3) // for more than one file, output the total
	 {
            cout << numNewlines << " total \n";
         }
      }
      /* if the first argument is "-w" */
      else if(strcmp(argv[1], "-w") == 0)
      {	 
	 /* if there are no arguments after -w */
	 if(argc == 2)
	 {
	    count(0);
	    cout << numWords << "\n";
	    exit(EXIT_SUCCESS);
         }

	 /* cycles through the arguments */
         for(int i = 2; i < argc; i++)
         {  
	    int temp = numWords;
          
            if(*argv[i] == '-')   // if there is a '-'
            {
	       count(0);
               temp = numWords - temp;
	       cout << temp << " -\n";
            }
	    else
	    {                     
               count(argv[i]);
	       temp = numWords - temp;
               cout << temp << " " << argv[i] << "\n";
            }
         }
         if(argc > 3) // for more than one file, output the total
	 {
            cout << numWords << " total \n";
         }
      }
      /* if there is no specification [-c | -l | -w] */
      else
      {
	 /* cycles throgh the arguments */	 
         for(int i = 1; i < argc; i++)
         {  
	    int tempBytes = numBytes;
            int tempLines = numNewlines;
            int tempWords = numWords;
          
            if(*argv[i] == '-')   // if there is a '-'
            {
	       count(0);
  	       
	       tempBytes = numBytes - tempBytes;
               tempLines = numNewlines - tempLines;
               tempWords = numWords - tempWords;

               cout << tempLines << " ";
               cout << tempWords << " ";
               cout << tempBytes << " -\n";
               
            }
 	    else
	    {
               count(argv[i]);

  	       tempBytes = numBytes - tempBytes;
               tempLines = numNewlines - tempLines;
               tempWords = numWords - tempWords;

               cout << tempLines << " ";
               cout << tempWords << " ";
               cout << tempBytes << " " << argv[i] << "\n";
            }
	 }
         if(argc > 2)	// for more than one file, output the total
	 {
               cout << numNewlines << " ";
	       cout << numWords << " ";
               cout << numBytes << " total\n";
         }
      }
   }
}
