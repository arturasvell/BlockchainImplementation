#include "Blockchain.h"
#include "transactionClass.h"
#include "userClass.h"
#include "functions/functions.h"
using namespace std;
vector<UserClass> users;
vector<Transaction> transactions;
void CreateUsers();
void CreateTransactions();
void CreateBlockToAdd();
Blockchain bChain = Blockchain();
int main()
{
    srand(time(NULL));
    CreateUsers();
    CreateTransactions();
    CreateBlockToAdd();
    return 0;
}
void CreateUsers()
{
    UserClass user;
    for(int i=0;i<1000;i++)
    {

        user.name="Vardenis Pavardenis-"+to_string(i);
        user.public_key=ArturoHash(user.name);
        user.balance=rand()%10000;
    }
    users.push_back(user);
    cout<<"Created users."<<endl;
}
void CreateTransactions()
{
    Transaction transaction;
    for(int i=0;i<10000;i++)
    {
        transaction.receiver_key=users[rand()%users.size()].public_key;
        transaction.sender_key=users[rand()%users.size()].public_key;
        transaction.sum=rand()%100000;
        transaction.transactionID=transaction.CreateHashTrans();
        transactions.push_back(transaction);
    }
    cout<<"Created transactions"<<endl;
}
void CreateBlockToAdd()
{
    vector<Transaction> transactionsToUse;
    for(int i=0;i<100;i++)
    {
        int randIndex=rand()%transactions.size();
        Transaction tempTransaction=transactions[randIndex];
        transactionsToUse.push_back(tempTransaction);
        transactions.erase(transactions.begin()+randIndex);
    }
    bChain.AddBlock(Block(1,transactionsToUse));
    cout<<"Added"<<endl;
}
