#ifndef USERCLASS_H_INCLUDED
#define USERCLASS_H_INCLUDED
#include "functions.h"
using namespace std;
class UserClass
{
private:
    string name;
public:
    string public_key;
    int balance=0;
    UserClass()
    {
        name="Vardenis Pavardenis"+to_string(indexCounter);
        public_key=ArturoHash(name);
        indexCounter++;
    }
    UserClass(string,string,int);
};


#endif // USERCLASS_H_INCLUDED
