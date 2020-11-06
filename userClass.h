#ifndef USERCLASS_H_INCLUDED
#define USERCLASS_H_INCLUDED
#include "functions/functions.h"
using namespace std;
class UserClass
{
public:
    string name;
    string public_key;
    int balance=0;
    UserClass()
    {
        name="Vardenis Pavardenis";
        public_key=ArturoHash(name);
    }
    UserClass(string,string,int);
};


#endif // USERCLASS_H_INCLUDED
