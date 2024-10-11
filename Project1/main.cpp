//
// Data Processing Project
// Miguel Perez
//
// Reads data from file, processes data, removes excess space
// and comments, tokenizes remaining, and prints in table
//

#include <iostream>
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
  string prep = "using|namespace|std";
  regex preproc(prep);
  smatch match;
  bool myBool;
  //Getting rid of newline chars
  for(int i = 0; i < code.size(); i++)
    {
      myBool = regex_search(code[i], match, preproc);
      if(code[i].compare("\n") == 0)
	{
	  code.erase(code.begin() + i);
	  --i;
	}
      else if(myBool)
	{
	  code.erase(code.begin() + i);
	  --i;
	}
    }
  //Printing nice code
  for(string s : code)
    {
      cout << s;
    }
  
  //Code is now sorted and stored in vector code
  //Planning to use regex to identify tokens
  //finalList[0] = keywords, 1 = identif, 2 = operators, 3 = delim
  //          4 = literals
  vector<string> finalList;
  finalList.resize(MAX_LINES);
  
  string keywords = "if|else|for|int|return|main|cout|endl";
  regex reg_key(keywords);

  string identifiers = "[A-Za-z][A-Za-z0-9_]*";
  regex reg_id(identifiers);

  string operators = "\\+|\\-|\\%|\\+\\+|\\-\\-|\\=\\=|\\=|\\*|>>|<<|!=";
  regex reg_op(operators);

  string delim = R"(\(|\)|;|,|\{|\})";
  regex reg_delim(delim);

  //Just for string literals
  string sliterals = "[\"].*?[\"]";
  regex reg_litS(sliterals);
  string dliterals = "[!A-Za-z][0-9]*";
  regex reg_litD(dliterals);

  for(int i = 0; i < code.size(); i++)
    {
      sregex_iterator last;
      
      sregex_iterator keywordIT(code[i].begin(), code[i].end(), reg_key);
      sregex_iterator identifierIT(code[i].begin(), code[i].end(), reg_id);
      sregex_iterator operatorIT(code[i].begin(), code[i].end(), reg_op);
      sregex_iterator delimIT(code[i].begin(), code[i].end(), reg_delim);
      sregex_iterator literalIT(code[i].begin(), code[i].end(), reg_litS);
      sregex_iterator literalDIT(code[i].begin(), code[i].end(), reg_litD);

      while(keywordIT != last)
	{
	  finalList[0].append(keywordIT->str() + ", ");
	  ++keywordIT;
	}
      while(identifierIT != last)
        {
          string s =  identifierIT->str(); 
	  if(s != "if" && s != "else" && s != "for" && s!= "int" &&
	     s != "return" && s != "main" && s != "cout" && s != "endl")
	    {
	     finalList[1].append(identifierIT->str() + ", ");   
	     ++identifierIT;
	    }
	  else
	    {
	      ++identifierIT;
	    }
	}
      while(operatorIT != last)
	{
	  finalList[2].append(operatorIT->str() + ", ");
	  ++operatorIT;
	}
      while(delimIT != last)
	{
	  finalList[3].append(delimIT->str() + ", ");
	  ++delimIT;
	}
      while(literalIT != last)
	{
	  finalList[4].append(literalIT->str() + ", ");
	  ++literalIT;
	}
      while(literalDIT != last)
	{
	  finalList[4].append(literalDIT->str() + ", ");
	  ++literalDIT;
	}
    }

  cout << "~~KEYWORDS~~\n" << finalList[0];
  cout << "\n~~IDENTIFIERS~~\n" << finalList[1];
  cout << "\n~~OPERATORS~~\n" << finalList[2];
  cout << "\n~~DELIMITERS~~\n" << finalList[3];
  cout << "\n~~LITERALS~~\n" << finalList[4]
       << endl;
  
  

  return 0;
}
