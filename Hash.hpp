#ifndef _Hash_hpp
#define _Hash_hpp
#include "ChainItem.hpp"
#include "LogItem.hpp"

template<typename CHAINITEM, typename DATAITEM>
class Hash{// HashTable
    private:

    int TableSize;// Table Size of the HashTable
    int primenumbers[7]={3,1009,2027,4054,8111,16217,32432};// Array that has doubled primenumbers for resizing when rehashing
    AVLTree<CHAINITEM> ** hashtable;// pointer of the HashTable

    int BalanceFactor=0;// Balance factor to check for half of the HashTable
    int elements=0;// Number of elements
    int count=0;// counter for the number of rehashing to move through the array of primenumbers

    public:
    Hash();// Constructor - O(TableSize)
    CHAINITEM* getkey(DATAITEM it);
    void Insert(DATAITEM item);// Insert into the Hashing Table- Best-> O(1), worst O(log n), where n is number of elements at a specific slot
    void rehash();// Rehashing into a larger Hashing Table - O(n^2)
    void traverse(AVLNode<CHAINITEM> *n);// Traversing for rehashing - O(n)
    void traverse();
    bool search(DATAITEM item);// searching for the item in the hash table- Best O(1), worst O(log n), where n is number of elements at a specific slot
    void Insert_Chain(AVLNode<CHAINITEM>* a,AVLTree<CHAINITEM> **HashTable2);
    ~Hash();// Deconstructor
};

template<typename CHAINITEM,typename DATAITEM>
CHAINITEM* Hash<CHAINITEM,DATAITEM> :: getkey(DATAITEM it)
{
    CHAINITEM* c= new CHAINITEM(it);
    return c;
}

template<typename CHAINITEM,typename DATAITEM>
Hash<CHAINITEM,DATAITEM>::Hash()
{// Constructor

    TableSize=primenumbers[count];// Setting the the TableSize
    hashtable=(AVLTree<CHAINITEM>**) malloc(sizeof(AVLTree<CHAINITEM>*)*TableSize);// Allocating memory for the HashTable
    for(int i=0;i<TableSize;i++)// Looping through the HashTable 
    hashtable[i]=NULL;// Setting each one to NULL

}
template<typename CHAINITEM, typename DATAITEM>
void Hash<CHAINITEM,DATAITEM>::traverse()//-> (The root to the ChainItem tree)
// Traversing the ChainItems Tree 
{
    for(int i=0;i<TableSize;i++)
    {
        if(hashtable[i]!=NULL)
        {
            traverse(hashtable[i]->getRoot());
        }
    }
    
}
template<typename CHAINITEM, typename DATAITEM>
void Hash<CHAINITEM,DATAITEM>::traverse(AVLNode<CHAINITEM> *n)
{
     if ( n == NULL) return; // recursivly looping until reach a leaf
    traverse(n->getLeft());// recursion from the left tree to get the minimum
    cout << n->getItem().get_ip() << endl;// then print items
    traverse(n->getRight());// recursion from the right tree
}

template<typename CHAINITEM,typename DATAITEM>
void Hash<CHAINITEM,DATAITEM>::Insert(DATAITEM item)
{// inserting into the HashTable

    
    BalanceFactor=TableSize/2;
    if(elements < BalanceFactor)// checking if it's less than half size of the table
    {
        int h = item.hash(TableSize);// hash the ip address
        CHAINITEM*c;
        c= getkey(item);// pointer to the key 
        AVLNode<CHAINITEM> * node= new AVLNode<CHAINITEM> ;// creating an avl node to pass for find

        if(hashtable[h]==NULL)// if the slot at the hashtable is empty
        {
            hashtable[h]= new AVLTree<CHAINITEM>;// create an avl tree of chainitem
            hashtable[h]->insert(*c);// insert the key, which would refrence the ip
            c->InsertData(item);
        }

        else if((node=hashtable[h]->find(*c))== NULL)// else if the slot is not empty and there's no similar ip
        {     
                hashtable[h]->insert(*c);// add a new tkey 
                c->InsertData(item);//insert the data into the datatree in chainitem tree
        }

        else if((node=hashtable[h]->find(*c))!=NULL)
        {
            CHAINITEM getitem= (node->getItem());// else if the ip is already there
            getitem.InsertData(item);// insert into the datatree of this key
        }
       
    }
   
    else // else if the balance factor is greater than 1
    {
        printf("rehashpls\n");
        rehash();// rehash
        Insert(item);// insert the item
       
    }
    elements++;// increment the number of item
}
    
template<typename CHAINITEM,typename DATAITEM>
void Hash<CHAINITEM,DATAITEM>:: rehash ()
{
    AVLTree<CHAINITEM> **HashTable2;// pointer for reallocing bigger hashtable
    count++;// incrementing the count to go for the next primenumber in the array
    TableSize =primenumbers[count]; //setting the TableSize to double the size 
    HashTable2=(AVLTree<CHAINITEM>**)realloc(hashtable,sizeof(AVLTree<CHAINITEM>*)*TableSize);
    if(HashTable2==NULL)
    {
        cout<<"realloc failed yasta"<<endl;
        abort();
        
    }
    else
    {
        hashtable=HashTable2;   
    }
}


template<typename CHAINITEM, typename DATAITEM>
Hash<CHAINITEM,DATAITEM>::~Hash()
{// deconstructor
    delete(hashtable);// delete the HashTable
}

#endif
