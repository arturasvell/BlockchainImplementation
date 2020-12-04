//
// Created by Dave Nash on 20/10/2017.
//

#include "Blockchain.h"
bc::hash_digest create_merkle(bc::hash_list& merkle)
{
// Stop if hash list is empty or contains one element
    if (merkle.empty())
        return bc::null_hash;
    else if (merkle.size() == 1)
        return merkle[0];
// While there is more than 1 hash in the list, keep looping...
    while (merkle.size() > 1)
    {
// If number of hashes is odd, duplicate last hash in the list.
        if (merkle.size() % 2 != 0)
            merkle.push_back(merkle.back());
// List size is now even.
        assert(merkle.size() % 2 == 0);
// New hash list.
        bc::hash_list new_merkle;
// Loop through hashes 2 at a time.
        for (auto it = merkle.begin(); it != merkle.end(); it += 2)
        {
// Join both current hashes together (concatenate).
            bc::data_chunk concat_data(bc::hash_size * 2);
            auto concat = bc::serializer<
                          decltype(concat_data.begin())>(concat_data.begin());
            concat.write_hash(*it);
            concat.write_hash(*(it + 1));
// Hash both of the hashes.
            bc::hash_digest new_root = bc::bitcoin_hash(concat_data);
// Add this to the new list.
            new_merkle.push_back(new_root);
        }
// This is the new list.
        merkle = new_merkle;
// DEBUG output -------------------------------------
        std::cout << "Current merkle hash list:" << std::endl;
        for (const auto& hash: merkle)
            std::cout << " " << bc::encode_base16(hash) << std::endl;
        std::cout << std::endl;
// --------------------------------------------------
    }
// Finally we end up with a single item.
    return merkle[0];
}
Blockchain::Blockchain()
{
    blockVector.emplace_back(Block(0, "Genesis Block"));
    difficultyTarget = 1;
}

void Blockchain::AddBlock(Block bNew)
{
    bNew.tailHash = GetLast().hashCreated;
    //bNew.MineBlock(difficultyTarget);
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
Block::Block(short indexInput, vector<Transaction> blockDataInput)
{
    index=indexInput;
    blockData=blockDataInput;
    nonce = 0;
    timeElapsed = time(nullptr);
    bc::hash_list tx_hashes;
    for(auto it=blockData.begin();it!=blockData.end();++it)
    {
        std::array<unsigned char, 32> hash;
        std::string tx_hash=it->CreateHashTrans();
        for(int i=0;i<32;i++)
        {
            hash[i]=tx_hash[i];
        }
        tx_hashes.push_back(hash);
    }
    merkleRootHash=bc::encode_base16(create_merkle(tx_hashes));
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
    int counter=0;
    do
    {
        nonce++;
        hashCreated = BuildHash();
        counter++;
        if(counter==mine_times)
        {
            hashCreated="-1";
            break;
        }
    }
    while (hashCreated.substr(0, difficultyTarget) != str);

    //cout << "Block mined: " << hashCreated << endl;
}

inline string Block::BuildHash() const
{
    stringstream ss;
    ss << index << tailHash << timeElapsed << nonce << merkleRootHash;
    for(int i=0; i<blockData.size(); i++)
    {
        ss<<blockData[i].transactionID;
    }
    return ArturoHash(ss.str());
}
