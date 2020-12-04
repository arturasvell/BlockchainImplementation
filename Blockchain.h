#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <iostream>
#include "functions/functions.h"
#include "Block.h"
#include "transactionClass.h"
#include "userClass.h"
#include <cstdlib>
#include <ctime>
#include <bitcoin/bitcoin.hpp>
using namespace std;
class Block {
public:
    string hashCreated;
    string merkleRootHash; ///to be added
    string tailHash;
    int mine_times=100000;
    Block(short indexInput, const string &dataInput);
    Block(short indexInput, vector<Transaction> blockDataInput);
    vector<Transaction> blockData;
    void MineBlock(short difficultyTarget);
private:
    short index;
    short nonce;
    string version;

    string hashData;
    time_t timeElapsed;

    inline string BuildHash() const;
};
class Blockchain {
private:
    short difficultyTarget;
    vector<Block> blockVector;
    Block GetLast();
public:
    Blockchain();
    void AddBlock(Block toAdd);
};

#endif //BLOCKCHAIN_H
