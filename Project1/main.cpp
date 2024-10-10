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
#include <vector>
#include <regex>

#define MAX_LINES 30

using namespace std;

int main()
{
  //Step 1: Read data from file
  ifstream myFile ("code.txt");
  string buffer;
  vector<string> code;
  code.resize(MAX_LINES);
  
  if(myFile.is_open())
    {
      int j = 0;
      int wscount = 0;
      while(getline(myFile, buffer))
	{
	  wscount = 0;
	  //Step 2: Remove excess space and comments
	  for(int i = 0; i < buffer.size(); i++)
	    {
	      //If char == /, is comment, skip
	      if(buffer[i] == '/')
		{
		  //Breaking early from for loop since whole
		  //line is comment
		  break;
		}
	      else if(buffer[i] == '#')
		{
		  //Preprocessor, so ignore
		  break;
		}
	      //If char is whitespace
	      else if(isspace(buffer[i]))
		{
		  if(wscount == 0)
		    {
		      code[j].push_back(buffer[i]);
		      ++wscount;
		    }
		  else
		    {
		      //ignore
		    }
		}
	      //Char is normal char, write to code
	      else
		{
		  code[j].push_back(buffer[i]);
		  if(wscount != 0)
		    wscount = 0;
		}
	    }
	  
	  code[j].push_back('\n');
	  ++j;
	   
	  
        }
      myFile.close();
    }
  else
    {
      cout << "unable to open file!";
    }

  //Getting rid of newline chars
  for(int i = 0; i < code.size(); i++)
    {
      if(code[i].compare("\n") == 0)
	{
	  code.erase(code.begin() + i);
	  --i;
	}
    }
  //Code is sorted and stored in vector code
  //Planning to use regex to identify tokens
  //                             #include?
  string keywords = "if|else|for|include|int|return|main|cout|endl|using|namespace";
  regex reg_key(keywords);
  int k = 1;

  smatch match_result;
  if(regex_search(code[k], match_result, reg_key))
    {
      cout << "Keyword found at line:" << k
	   << "Match result = " << match_result[0];
    }
  else
    {
      cout << "Keyword NOT found!\n";
    }

  
  for(string s : code)
    {
      cout << s;
    }
  

  return 0;
}
