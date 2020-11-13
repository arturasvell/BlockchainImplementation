#include "transactionClass.h"
using namespace std;
string Transaction::CreateHashTrans()
{
    return ArturoHash(sender_key+receiver_key+to_string(sum));
}
