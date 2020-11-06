#ifndef TRANSACTIONCLASS_H_INCLUDED
#define TRANSACTIONCLASS_H_INCLUDED
#include "functions/functions.h"
using namespace std;
class Transaction
{
    public:
    string transactionID;
    string sender_key;
    string receiver_key;
    int sum;
    string CreateHashTrans();
};


#endif // TRANSACTIONCLASS_H_INCLUDED
