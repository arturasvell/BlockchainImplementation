# BlockchainImplementation
An implementation of a simple Blockchain, POW method and a Merkle Hash Tree by yours truly.

# How it works

- 1000 Users and 10000 Transactions, referring to said Users, are created.
- The program created five Block candidates. Each block, aside from the usual attributes, stores a vector<Transaction> pool(A,B,C,D or E), which contains 100 randomly picked Transactions from the shared pool of 10000 Transactions.
- The program copies the candidates into a temporary vector (for resetting purposes later)
- 
