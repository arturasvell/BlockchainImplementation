#ifndef TRANSACTIONCLASS_H_INCLUDED
#define TRANSACTIONCLASS_H_INCLUDED
#include "functions.h"
using namespace std;
class Transaction
{
private:
    string transactionID;
    string sender_key;
    string receiver_key;
    int sum;
public:
    Transaction(string, string, string, int);
};


#endif // TRANSACTIONCLASS_H_INCLUDED
