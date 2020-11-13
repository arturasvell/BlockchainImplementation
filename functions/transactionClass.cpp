#include "transactionClass.h"
using namespace std;
Transaction::Transaction(string a, string b, string c, int d)
{
    Transaction::transactionID=a;
    Transaction::sender_key=b;
    Transaction::receiver_key=c;
    Transaction::sum=d;
}
