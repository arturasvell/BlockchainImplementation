//
// Created by Dave Nash on 20/10/2017.
//

#include "Blockchain.h"

Blockchain::Blockchain()
{
    blockVector.emplace_back(Block(0, "Genesis Block"));
    difficultyTarget = 0;
}

void Blockchain::AddBlock(Block bNew)
{
    bNew.tailHash = GetLast().hashCreated;
    bNew.MineBlock(difficultyTarget);
    blockVector.push_back(bNew);
}

Block Blockchain::GetLast()
{
    return blockVector.back();
}
Block::Block(short indexInput, const string &dataInput) : index(indexInput), hashData(dataInput)
{
    nonce = 0;
    timeElapsed = time(nullptr);
    hashCreated = BuildHash();
}
Block::Block(short indexInput, vector<Transaction> blockDataInput):index(indexInput),blockData(blockDataInput)
{
    nonce = 0;
    timeElapsed = time(nullptr);
    hashCreated = BuildHash();
}
void Block::MineBlock(short difficultyTarget)
{
    char charArray[difficultyTarget + 1];
    for (short i = 0; i < difficultyTarget; ++i)
    {
        charArray[i] = '0';
    }
    charArray[difficultyTarget] = '\0';

    string str(charArray);

    do
    {
        nonce++;
        hashCreated = BuildHash();
    }
    while (hashCreated.substr(0, difficultyTarget) != str);

    cout << "Block mined: " << hashCreated << endl;
}

inline string Block::BuildHash() const
{
    stringstream ss;
    ss << index << tailHash << timeElapsed << nonce;
    for(int i=0;i<blockData.size();i++)
    {
        ss<<blockData[i].transactionID;
    }
    return ArturoHash(ss.str());
}
