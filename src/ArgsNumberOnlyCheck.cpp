#include "ArgsNumberOnlyCheck.h"

#include <string>
#include <iostream>

bool ArgsNumberOnlyCheck::check(char *c)
{
    std::string s(c);
    for(auto& ch: s)
    {
        if(ch < '0' || ch > '9')
        {
            std::cerr << "Passed in parameter contains 'non-digit' numbers! "
                "Please pass in a natural number!" << std::endl;
            return false;
        }
    }
    return true;
}
