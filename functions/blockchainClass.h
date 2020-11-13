#ifndef BLOCKCHAINCLASS_H_INCLUDED
#define BLOCKCHAINCLASS_H_INCLUDED
#include "functions.h"
#include "transactionClass.h"
class Block
{
private:
    int index;
    time_t timestamp;
    string version;
    string merkleRootHash;
    string hashToReturn;
    int nonce;
    vector<Transaction> blockData;
    string data;
    inline string MakeHash()
    {
        stringstream ss;
        ss<<index<<timestamp<<data<<nonce<<prevBlockHash;
        cout<<ArturoHash(ss.str());
        return ArturoHash(ss.str());
    }
public:
    string prevBlockHash;

    Block(int a,string b) ///replace with transactions
    {
        nonce=-1;
        timestamp=time(nullptr); ///set to current time
        index=a;
        data=b;
    }
    string GetHash()
    {
        return hashToReturn; ///CHANGE TO MERKLE HASH LATER
    }
    void Mine(int difficultyTarget)
    {
        char arrayMining[difficultyTarget+1];
        for(int i=0;i<difficultyTarget;i++)
        {
            arrayMining[i]='0';
        }
        string str(arrayMining);

        do{
            nonce++;
            hashToReturn=MakeHash();
        }while(hashToReturn.substr(0,difficultyTarget)!=str);

        cout<<"Block mined: "<<hashToReturn<<endl;
    }
};
class Blockchain
{
private:
    int difficultyTarget;
    vector<Block> blockChain;

    Block getLastBlock()
    {
        return blockChain.back();
    }
public:
    Blockchain()
    {
        blockChain.emplace_back(Block(0,"Genesis block")); ///replace with transactions
        difficultyTarget=1;
    }
    void AppendBlockchain(Block toAdd)
    {
        toAdd.prevBlockHash=getLastBlock().GetHash();
        toAdd.Mine(difficultyTarget);
        blockChain.push_back(toAdd);
    }
};
#endif // BLOCKCHAINCLASS_H_INCLUDED
