//
// Data Processing Project
// Miguel Perez
//
// Reads data from file, processes data, removes excess space
// and comments, tokenizes remaining, and prints in table
//

#include <iostream>
//To read from file
#include <fstream>

using namespace std;

int main()
{
  //Step 1: Read data from file
  ifstream myFile ("code.txt");
  string buffer;
  vector<string> code;
  if(myFile.is_open())
    {
      while(getline(myFile, buffer))
	{
	  //Step 2: Remove excess space and comments
	  for(int i = 0; i < buffer.size(); i++)
	    {
	      //If char == /, is comment, skip
	      if(buffer[i] == '/')
		{
		  //Do nothing (Will not add to final code)
		  
		}
	      //If char is whitespace
	      else if(isspace(buffer[i]))
		{
		  
		}
	      //Char is normal char, write to code
	      else
		{

		}
	    }
	  cout << buffer << endl;
	}
      myFile.close();
    }
  else
    {
      cout << "unable to open file!";
    }



  return 0;
}
