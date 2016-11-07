#include "StringFunction.h"

//! replaces all occurances of toReplace with replaceWith in theReplace
std::string 
replaceAll (std::string toReplace, std::string theReplace, 
            std::string replaceWith)
{
    std::string output=toReplace;
    int theReplaceLen, replaceWithLen, pos=0;

    theReplaceLen=theReplace.size();
    replaceWithLen=replaceWith.size();

    while((pos+theReplaceLen)<=output.size())
    {
         if(output.substr(pos,theReplaceLen)==theReplace)
         {
           output.replace(pos,theReplaceLen,replaceWith);
           pos+=replaceWithLen-1;
         }
         pos++;
    }

    return output;
}


//! replaces all occurances of toReplace with replaceWith in theReplace
//! without replace x11 with x1's value
std::string 
replaceAll (std::string toReplace, std::string theReplace, 
            std::string replaceWith, bool bTemp)
{
  std::string output=toReplace;
  std::string ch;
  int theReplaceLen, replaceWithLen, pos=0;

  theReplaceLen=theReplace.size();
  replaceWithLen=replaceWith.size();

  while((pos+theReplaceLen)<=output.size())
    {
  	  ch = output.substr(pos+theReplaceLen, 1);
      if(output.substr(pos,theReplaceLen)==theReplace 
         && ch!="1" && ch!="2" && ch!="3" && ch!="4"&& ch!="5"&& ch!="6"
         && ch!="7"&& ch!="8" && ch!="9"&& ch!="0")
        {
          output.replace(pos,theReplaceLen,replaceWith);
          pos+=replaceWithLen-1;
        }
      pos++;
    }
  return output;
}


//returns a string in Maple format of the variable list
std::string getVarString(List<std::string>& vars)
{
   std::string output="{";
   int length, i;

   length=vars.returnLen();

   for(i=1;i<=length;i++)
   {
      if(i!=1) output+=",";
      output+=vars.retrieve(i);
   }

   output+="}";
   return output;
}

//converts a long to a string
std::string toString(long a)
{
   long temp;
   std::string theNumber, outString;

   if(a==0) return "0";

   temp = a;
   outString = "";

   while (temp>=1)
   {
      switch (temp%10)
      {
          case 1: theNumber = "1";
                  break;
          case 2: theNumber = "2";
                  break;
          case 3: theNumber = "3";
                  break;
          case 4: theNumber = "4";
                  break;
          case 5: theNumber = "5";
                  break;
          case 6: theNumber = "6";
                  break;
          case 7: theNumber = "7";
                  break;
          case 8: theNumber = "8";
                  break;
          case 9: theNumber = "9";
                  break;
          case 0: theNumber = "0";
                  break;
      }
      outString=theNumber+outString;
      temp/=10;
   }
   if(a>=0) return outString;
   else return("-"+outString);
}

//! converts a int to a string
std::string toString(int a)
{
    return toString((long) a);
}

//! converts a double to a string
std::string toString(double a)
{ 
    std::string output;
    char temp[100];
    
    sprintf(temp,"%f",a);   

    output.assign(temp);
 
    return output;
}

//! converts a float to a string
std::string toString(float a)
{
    return toString((double) a);
}
