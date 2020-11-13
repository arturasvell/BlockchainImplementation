#include "Blockchain.h"
#include "transactionClass.h"
#include "userClass.h"
#include "functions/functions.h"
#include "merkleTree.h"
using namespace std;
vector<UserClass> users;
vector<Transaction> transactions;
void CreateUsers();
void CreateTransactions();
void CreateCandidates();
void CreateBlockToAdd();
void Validate(vector<Transaction> &transPool);
Blockchain bChain;
int counter=0;
int main()
{

    srand(time(NULL));
    CreateUsers();
    CreateTransactions();
    while(transactions.size()>0)
    {
        CreateBlockToAdd();
    }
}
void CreateUsers()
{
    for(int i=0; i<1000; i++)
    {
        UserClass user;
        user.name="Vardenis Pavardenis "+to_string(i);
        user.balance=rand()%10000;
        user.public_key=ArturoHash(to_string(user.balance)+user.name);
        users.push_back(user);
    }
    cout<<"Created users."<<endl;
}
void CreateTransactions()
{
    for(int i=0; i<10000; i++)
    {
        Transaction transaction;
        transaction.sender_key=users[rand()%users.size()].public_key;
        transaction.receiver_key=users[rand()%users.size()].public_key;
        transaction.sum=rand()%10000;
        transaction.transactionID=transaction.CreateHashTrans();
    }
    cout<<"Created transactions"<<endl;
}
void Validate(vector<Transaction> &transPool)
{
    for(int i=0; i<transPool.size(); i++)
    {
        int senderIndex,receiverIndex;
        for(int j=0; j<users.size(); j++)
        {
            if(users[j].public_key==transPool[i].sender_key)
            {
                senderIndex=j;
            }
            else if(users[j].public_key==transPool[i].receiver_key)
            {
                receiverIndex=j;
            }
        }
        if(users[senderIndex].balance-transPool[i].sum>=0&&transPool[i].transactionID==ArturoHash(transPool[i].sender_key+transPool[i].receiver_key+to_string(transPool[i].sum)))
        {

        }
        else
        {
            transPool.erase(transPool.begin(),transPool.begin()+i);
        }
    }
}
void CreateBlockToAdd()
{
    vector<vector<Transaction>> candidates;
    vector<Transaction> a1,b1,c1,d1,e1;
    BinaryHashTree tree1,tree2,tree3,tree4,tree5;
    for(int i=0; i<100; i++)
    {
        int randIndex=rand()%transactions.size();
        a1.push_back(transactions[randIndex]);
    }
    Validate(a1);
    tree1.build(a1);
    candidates.push_back(a1);
    for(int i=0; i<100; i++)
    {
        int randIndex=rand()%transactions.size();
        b1.push_back(transactions[randIndex]);
    }
    Validate(b1);
    tree2.build(b1);
    candidates.push_back(b1);
    for(int i=0; i<100; i++)
    {
        int randIndex=rand()%transactions.size();
        c1.push_back(transactions[randIndex]);
    }
    Validate(c1);
    tree3.build(c1);
    candidates.push_back(c1);
    for(int i=0; i<100; i++)
    {
        int randIndex=rand()%transactions.size();
        d1.push_back(transactions[randIndex]);
    }
    Validate(d1);
    tree4.build(d1);
    candidates.push_back(d1);
    for(int i=0; i<100; i++)
    {
        int randIndex=rand()%transactions.size();
        e1.push_back(transactions[randIndex]);
    }
    Validate(e1);
    tree5.build(e1);
    candidates.push_back(e1);
    int difficultyTarget=0;
    vector<vector<Transaction>> candidatesCopy=candidates;
    while(true)
    {
        int indexOfChoice=rand()%candidatesCopy.size();
        vector<Transaction> attempt=candidatesCopy[indexOfChoice];
        Block blockTest(counter,attempt);

        if(indexOfChoice==0)
            blockTest.merkleRootHash=ArturoHash(tree1.root->hashValue);
        else if(indexOfChoice==1)
            blockTest.merkleRootHash=ArturoHash(tree2.root->hashValue);
        else if(indexOfChoice==2)
            blockTest.merkleRootHash=ArturoHash(tree3.root->hashValue);
        else if(indexOfChoice==3)
            blockTest.merkleRootHash=ArturoHash(tree4.root->hashValue);
        else if(indexOfChoice==4)
            blockTest.merkleRootHash=ArturoHash(tree5.root->hashValue);
        blockTest.MineBlock(0);
        if(blockTest.hashCreated=="")
        {
            if(candidatesCopy.size()>0)
            {
                candidatesCopy.erase(candidatesCopy.begin(),candidatesCopy.begin()+indexOfChoice);
            }
            else
            {
                candidatesCopy=candidates;
                blockTest.doubleTimeLimit();
            }
            continue;
        }
    }

}
