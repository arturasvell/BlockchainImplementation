# BlockchainImplementation
An implementation of a simple Blockchain, POW method and a Merkle Hash Tree by yours truly.

# How it works

- 1000 Users and 10 000 Transactions, referring to said Users, are created.
- The program created five Block candidates. Each block, aside from the usual attributes, stores a vector<Transaction> pool(A,B,C,D or E), which contains 100 randomly picked Transactions from the shared pool of 10 000 Transactions. Additionally, each invalid transaction (not enough funds in the sender account or a mismatch of Transaction hashes) is removed from the pool.
- The program copies the candidates into a temporary vector (for resetting purposes later)
- A candidate is chosen randomly. The block-candidate will now mine for a hash of a suitable difficulty. If within 100 000 tries the hash is not yet mined, the candidate is deleted from the copy vector and another is chosen
- If a hash hasn't been found, and all candidates have been removed, the vector is repopulated with the same candidates, which now have twice the amount of attempts to successfully mine.
- After the block is mined, the transactions are completed and subsequently removed from the shared pool.
- Repeat until no transactions remain.
  
# How to compile

*g++ -std=c++11 -o merkle main.cpp Blockchain.cpp transactionClass.cpp userClass.cpp functions/functions.cpp $(pkg-config --cflags --libs libbitcoin)*

# Screenshot of results

