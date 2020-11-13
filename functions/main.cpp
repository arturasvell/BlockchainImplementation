#include "functions.h"
#include "userClass.h"
#include "transactionClass.h"
#include "blockchainClass.h"
using namespace std;

int main()
{
    Blockchain bChain=Blockchain();
    cout << "Mining block 1..." << endl;
    bChain.AppendBlockchain(Block(1,"Block 1 data"));
    return 0;
}

