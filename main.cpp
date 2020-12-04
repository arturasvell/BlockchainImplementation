#include "Blockchain.h"
#include "transactionClass.h"
#include "userClass.h"
#include "functions/functions.h"
#include <algorithm>
using namespace std;
vector<UserClass> users;
vector<Transaction> transactions;
void CreateUsers();
void CreateTransactions();
void CreateBlockToAdd();
void TakeRandomTransactions(vector<Transaction> &pool);
int FindUserIndexByKey(string key);
int ReturnRandomIndex(int vectorSize);
void PopulateCandidate(vector<Transaction> &pool, vector<Transaction> &candidate);
Blockchain bChain = Blockchain();
int blockIndex=1;
int main()
{
    srand(time(NULL));
    CreateUsers();
    CreateTransactions();
    while(transactions.size()>0)
    {
        CreateBlockToAdd();
    }

    return 0;
}
void CreateUsers()
{
    UserClass user;
    for(int i=0;i<1000;i++)
    {

        user.name="Vardenis Pavardenis-"+to_string(i);
        user.public_key=ArturoHash(user.name);
        user.balance=rand()%1000000;
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
        transaction.sum=rand()%10000;
        transaction.transactionID=transaction.CreateHashTrans();
        transactions.push_back(transaction);
    }
    cout<<"Created transactions"<<endl;
}
void CreateBlockToAdd()
{
    vector<Transaction> poolA,poolB,poolC,poolD,poolE;
    TakeRandomTransactions(poolA);
    TakeRandomTransactions(poolB);
    TakeRandomTransactions(poolC);
    TakeRandomTransactions(poolD);
    TakeRandomTransactions(poolE);
    Block blockA=Block(blockIndex,poolA),blockB=Block(blockIndex,poolB),blockC=Block(blockIndex,poolC)
    ,blockD=Block(blockIndex,poolD),blockE=Block(blockIndex,poolE);
    cout<<"Candidates generated."<<endl;
    vector<Block> blockCandidates;
    blockCandidates.push_back(blockA);
    blockCandidates.push_back(blockB);
    blockCandidates.push_back(blockC);
    blockCandidates.push_back(blockD);
    blockCandidates.push_back(blockE);
    vector<Block> copyCandidates=blockCandidates;
    int indexToSave;
    while(true)
    {
        if(copyCandidates.size()==0)
        {
            copyCandidates=blockCandidates;
            for(int i=0;i<copyCandidates.size();i++)
            {
                copyCandidates[i].mine_times*=2;
            }
        }
        int randomIndex=rand()%5;
        copyCandidates[randomIndex].MineBlock(1);
        if(copyCandidates[randomIndex].hashCreated=="-1")
        {
            copyCandidates.erase(copyCandidates.begin()+randomIndex);
        }
        else
        {
            cout<<"Block with "<<copyCandidates[randomIndex].blockData.size()<<" transactions with HASH \n"<<copyCandidates[randomIndex].hashCreated<<" found. Good job!"<<endl;
            bChain.AddBlock(copyCandidates[randomIndex]);
            cout<<copyCandidates[randomIndex].blockData[0].transactionID<<endl;


            indexToSave=randomIndex;
            blockIndex++;
            break;
        }

    }
    vector<Transaction> toRemove=copyCandidates[indexToSave].blockData;
    for(int i=0;i<toRemove.size();i++)
    {
        for(int j=0;j<transactions.size();j++)
        {
            if(toRemove[i].transactionID==transactions[j].transactionID)
            {
                transactions.erase(transactions.begin()+j);
            }
        }
    }
    cout<<"REMAINING TRANSACTIONS - "<<transactions.size()<<endl;
}
void TakeRandomTransactions(vector<Transaction> &pool)
{
    for(int i=0;i<100;i++)
    {
        int indexToTake=ReturnRandomIndex(transactions.size());
        pool.push_back(transactions[indexToTake]);
    }
    for(int i=0;i<pool.size();i++)
    {
        int sender_Index=FindUserIndexByKey(pool[i].sender_key);
        int receiver_Index=FindUserIndexByKey(pool[i].receiver_key);
        string hashCheck=ArturoHash(pool[i].sender_key+pool[i].receiver_key+to_string(pool[i].sum));
        if(users[sender_Index].balance-pool[i].sum<0||pool[i].transactionID!=hashCheck)
        {
            pool.erase(pool.begin()+i);
            i=-1;
        }

    }
    cout<<"TRANSACTION STATUS: "<<pool.size()<<" transactions left after cleanup."<<endl;
}

int ReturnRandomIndex(int vectorSize)
{
    return rand()%transactions.size();
}
int FindUserIndexByKey(string key)
{
    for(int i=0;i<users.size();i++)
    {
        if(key==users[i].public_key)
            return i;
    }
}
