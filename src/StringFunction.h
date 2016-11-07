#ifndef INCLUDE_STRINGFUNCTION_H
#define INCLUDE_STRINGFUNCTION_H

#include <string.h>
#include <string>

#include "mfa1List.h"

//String Functions
std::string replaceAll (std::string toReplace, std::string theReplace, 
                        std::string replaceWith);
std::string replaceAll (std::string toReplace, std::string theReplace, 
                        std::string replaceWith, bool bTemp);
std::string getVarString (List<std::string>& vars);
std::string toString (long a);
std::string toString (int a);
std::string toString (double a);
std::string toString (float a);

#endif // INCLUDE_STRINGFUNCTION_H
