#ifndef MERKLETREE_H_INCLUDED
#define MERKLETREE_H_INCLUDED
#include "Blockchain.h"
#include "functions/functions.h"
#include "transactionClass.h"
using namespace std;
struct Node
{
    int id;
    Transaction value;
    string hashValue;
    Node *left, *right, *parent;
};
class BinaryHashTree
{
    public:
    Node* root;
    int blockNumber,level;

    BinaryHashTree()
    {
        level=0;
        blockNumber=-1;
    }
    bool build(vector<Transaction> transactions)
    {
        vector<Node*> listChild, listParent;
        Node *leftNode=nullptr, *rightNode=nullptr;
        for(int i=0;i<transactions.size();i++)
        {
            Node* n=new Node;
            n->value=transactions[i];
            n->hashValue=transactions[i].CreateHashTrans();
            cout<<n->hashValue<<endl;
            n->id=++blockNumber;
            n->left=n->right=n->parent=nullptr;
            listChild.push_back(n);
        }
        do
        {
            level++;
        }while(pow(2,level)<=blockNumber);
        do
        {
            auto iterative=listParent.begin();
            auto done=listParent.end();
            while(iterative!=done)
                listChild.push_back(*iterative);
            listParent.clear();

            auto iterative2=listChild.begin();
            auto done2=listChild.end();
            leftNode=rightNode=nullptr;
            while(iterative2!=done2)
            {
                if(!leftNode)
                    leftNode=*iterative2++;
                else
                {
                    rightNode=*iterative2++;
                    Node *parentNode=new Node;
                    parentNode->value=leftNode->value;
                    parentNode->hashValue=ArturoHash(leftNode->hashValue+rightNode->hashValue);
                    parentNode->left=leftNode;
                    parentNode->right=rightNode;
                    parentNode->parent=nullptr;
                    parentNode->id=-1;
                    listParent.push_back(parentNode);
                    leftNode->parent=rightNode->parent=parentNode;
                    leftNode=rightNode=nullptr;
                }
            }
            if(leftNode)
            {
                rightNode=new Node;
                rightNode->hashValue="";
                rightNode->id=-1;
                rightNode->left=rightNode->right=nullptr;

                Node *parentNode=new Node;
                parentNode->hashValue=ArturoHash(leftNode->hashValue+rightNode->hashValue);
                parentNode->left=leftNode;
                parentNode->right=rightNode;
                parentNode->parent=nullptr;
                parentNode->id=-1;
                listParent.push_back(parentNode);
                leftNode->parent=rightNode->parent=parentNode;
                leftNode=rightNode=nullptr;
            }
            listChild.clear();
        }while(listParent.size()>1);

        root=listParent[0];
        return true;
    }
    void VerifyHash(Node* leftNode)
    {
        Node *parentNode=leftNode->parent, *rightNode=nullptr;
        while(parentNode)
        {
            if(parentNode->left==leftNode)
                rightNode=parentNode->right;
            else
            {
                rightNode=leftNode;
                leftNode=parentNode->left;
            }

            parentNode->hashValue=ArturoHash(leftNode->hashValue+rightNode->hashValue);
            leftNode=parentNode;
            parentNode=parentNode->parent;
        }
    }
    bool Append(Transaction data)
    {
        blockNumber++;
        Node *parentN = nullptr, *leftN = nullptr, *rightN = nullptr;
        if(blockNumber == pow(2, level))
        {
            // Make a new root node.
            parentN = new Node;
            parentN->hashValue = "";
            parentN->id = -1;
            parentN->left = root;
            parentN->right = parentN->parent = nullptr;
            root->parent = parentN;
            root = parentN;

            parentN = new Node;
            parentN->hashValue = "";
            parentN->id = -1;
            parentN->left = parentN->right = nullptr;
            parentN->parent = root;
            root->right = parentN;

            for(int i = 0; i < level ; i++)
            {
                leftN = new Node;
                leftN->hashValue = ArturoHash("NULL");
                leftN->id = -1;
                leftN->left = leftN->right = nullptr;

                rightN = new Node;
                rightN->id = -1;
                rightN->hashValue = ArturoHash("NULL");
                rightN->left = rightN->right = nullptr;

                parentN->left = leftN;
                parentN->right = rightN;
                leftN->parent = rightN->parent = parentN;
                parentN = leftN;
            }

            leftN->id = blockNumber;
            leftN->hashValue = ArturoHash(data.CreateHashTrans());
            level++;
        }else
        {
            parentN = root;
            int tempN = blockNumber;
            if(blockNumber % 2)
            {
                cout << "2: blockNumber: " << blockNumber << endl;
                for(int i = level-1 ; i >= 0 ; i--)
                {
                    if(tempN < pow(2, i)) // Go left
                        parentN = parentN->left;
                    else
                    {
                        tempN -= pow(2, i);
                        parentN = parentN->right;
                    }
                }

                leftN = parentN;
                leftN->id = blockNumber;
                leftN->hashValue = ArturoHash(data.CreateHashTrans());
            }else
            {
                cout << "3: blockNumber: " << blockNumber << endl;
                int i = level;
                for( ; i >= 0 ; i--)
                {
                    if(tempN < pow(2, i-1)) // Go left
                        if(parentN->left)
                            parentN = parentN->left;
                        else
                            break;
                    else
                    {
                        tempN -= pow(2, i-1);
                        if(parentN->right)
                            parentN = parentN->right;
                        else
                            break;
                    }
                }

                // Now add the required part of the path:
                while(i > 0)
                {
                    leftN = new Node;
                    leftN->id = -1;
                    leftN->hashValue = "";
                    leftN->left = leftN->right = nullptr;

                    rightN = new Node;
                    rightN->id = -1;
                    rightN->hashValue = ArturoHash("NULL");
                    rightN->left = rightN->right = nullptr;

                    parentN->left = leftN;
                    parentN->right = rightN;
                    leftN->parent = rightN->parent = parentN;
                    parentN = leftN;
                    i--;
                }

                leftN->id = blockNumber;
                leftN->hashValue = ArturoHash(data.CreateHashTrans());
            }
        }

        // Now update the hash values from buttom up.
        VerifyHash(leftN);
        return false;
    }
};
#endif // MERKLETREE_H_INCLUDED
