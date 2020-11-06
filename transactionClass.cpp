#include "transactionClass.h"
using namespace std;
string Transaction::CreateHashTrans()
{
    return ArturoHash(transactionID+sender_key+receiver_key+to_string(sum));
}
