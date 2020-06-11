#include "BSTNode.hpp"
/****************************************************************************************/
/*                            BinarySearchTree Prototype                                */
/****************************************************************************************/



template <class NODE,typename ITEM>
class BinarySearchTree
{
    protected:
        NODE * root;
        int count;
        void traverseASC(NODE * n);
        void traverseDESC(NODE * n);
        NODE * insert(NODE * n, const ITEM & p_item);
    public:
        BinarySearchTree();
        virtual NODE * insert(const ITEM & item); //O(n) Average O(log n)
        bool remove(const ITEM & item);//O(n)  Average O(log n)
        void traverseDESC();//O(n)
        void traverseASC();// O(n)
        NODE * findMax(NODE * n =NULL);// O(n) Average O(log n)
        NODE * findMin(NODE * n =NULL);// O(n) Average O(log n)
        bool contains(const ITEM item);//O(n) Average O(log n)
        NODE  * find (const ITEM item);//O(n) Average O(log n)
        int getCount();//O(1)
        NODE * getRoot();//O(1)
        virtual ~BinarySearchTree();
};

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                        BinarySearchTree Implementation                               */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


template <class NODE,typename ITEM> void BinarySearchTree<NODE,ITEM>::traverseASC(NODE * n)
{
    if ( n == NULL) return; // recursivly looping until reach a leaf
    traverseASC(n->getLeft());// recursion from the left tree to get the minimum
    cout << n->getItem() << endl;// then print items
    traverseASC(n->getRight());// recursion from the right tree
}
template <class NODE,typename ITEM> void BinarySearchTree<NODE,ITEM>::traverseDESC(NODE * n)
{
    if ( n == NULL) return;// recursiely looping until reach a leaf
    traverseDESC((NODE *)n->getRight());// recursion from the right of the tree to get the minimum
    cout << n->getItem() <<endl; // then print items
    traverseDESC((NODE *)n->getLeft());// recursion from the left of the tree
}

template <class NODE,typename ITEM> NODE * BinarySearchTree<NODE,ITEM>::insert(NODE * n, const ITEM & p_item)
{
    if (n->getItem() > p_item) {// compare the item if it's greater that item of n
        if (n->getLeft() == NULL)  {// check if the the left child is  slot empty
            NODE * new_node = new NODE (p_item); // create a node with the item
            n->setLeft(new_node);// set the node to the left of n
            new_node->setParent(n);// set the parent to n
            return new_node;// return the new node
        } return NULL;
    }
    else if (n->getItem() < p_item) // compare the item if it's less that item of n
    {
        if (n->getRight() == NULL) { // check if right child slot is empty
            NODE * new_node = new NODE (p_item); // create a node with the item
            n->setRight(new_node);// set the node to the right
            new_node->setParent(n);// set the parent to n
            return new_node;// return the node
        }else return NULL;
    }
    else return NULL;
}

template <class NODE,typename ITEM> BinarySearchTree<NODE,ITEM>::BinarySearchTree()// constructor
{
    root = NULL;// setting root to NULL
    count = 0; // setting count to 0
}

template <class NODE,typename ITEM> NODE * BinarySearchTree<NODE,ITEM>::insert(const ITEM & item)
{
    NODE * new_node = NULL;// create a new node
    if ( root == NULL) // if the tree is empty
    {
        new_node = root = new NODE(item);// set the new node to the root
    }
    else 
    {
        NODE * parent = root;// else set the parent to the root
        NODE * next = (NODE *) parent->compareAndAdvance(item);// call function to compare
        while ( next != parent) //
        {
            if ( next == NULL ) {  new_node = (NODE *) insert(parent,item); break;}// if next is empty insert the item
            else parent = next; // else set parent to next
            next = (NODE *) parent->compareAndAdvance(item); // then compare
        }
    }
    if (new_node != NULL )// if the node isn't null
        count++; // increase count
    return new_node;// return the node
}

template <class NODE,typename ITEM> bool BinarySearchTree<NODE,ITEM>::remove(const ITEM & item)// remove item
{
    NODE * search_node = find(item);// search for the item
    if (search_node != NULL) // if the search was successful
    {
        search_node->setCascadeDelete(false);// set cascadeDelete to false to not delete the whole tree
        NODE * parent = (NODE *) search_node->getParent();// set parent to the parent of search node
        bool left_child = false; // a flag for the left child
        if ( parent != NULL && parent->getLeft() == search_node) left_child = true;
        // if the left child of parent is the node we searching then set left child equal true
        if (parent == NULL) { // If root
            if (search_node->getRight() == NULL ) root = search_node->getLeft();
            // if searching for the node in the right side is unsuccessful then root equals the search node left side
            else if (search_node->getLeft() == NULL ) root = search_node->getRight();
            // if searching for the node in the left side is unsuccesful then root equals the search node from the right then search again
            
            else {
                NODE * min = findMin((NODE *)search_node->getRight());// find the minimum item
                if ( min == NULL) exit(1);// if minimum is empty then exit
                if ( min->getParent()!= NULL) { // if min's parent is not empty
                    if ( min->getParent()->getLeft() == min ) // if the left child of parent = min
                        min->getParent()->setLeft(min->getRight());// set the right of min to the left of the parent
                    else if ( min->getParent()->getRight() == min ) // else if the right of the parent equals min
                        min->getParent()->setRight(min->getRight());// set the min of right to the parent of right
                    if ( min->getRight() != NULL) min->getRight()->setParent(min->getParent());// if min of right is not empty, then set the parent of min to the right of min
                }
                min->setParent(parent);// set parent to be min's parent
                min->setLeft(search_node->getLeft()); // set left of min to the left of search
                min->setRight(search_node->getRight());// set right of min to the right of min
                if (min->getLeft() != NULL) min->getLeft()->setParent(min); // if min of left is not empty then set min as the parent of min's left
                if (min->getRight() != NULL)  min->getRight()->setParent(min);
                root = min; //if min of right is not empty then set min as the parent of min's right
            }
            if ( root != NULL) root->setParent(NULL);// if root is not empty then set root of the parent to NULL
        }
        else if (search_node->getLeft()!= NULL && search_node->getRight()!=NULL)  // Two Children
        {
            NODE * min = findMin((NODE *)search_node->getRight());
            if ( search_node->getRight() == min )
            {
                min->setParent(search_node->getParent());
                if ( left_child ) search_node->getParent()->setLeft(min);
                else search_node->getParent()->setRight(min);
                min->setLeft(search_node->getLeft());
                if (min->getLeft() != NULL) min->getLeft()->setParent(min);
                if (min->getRight() != NULL)  min->getRight()->setParent(min);
            }
            else
            {
                if ( min->getParent() != NULL ) min->getParent()->setLeft(min->getRight());
                if ( min->getRight() != NULL ) min->getRight()->setParent(min->getParent());
                if ( left_child ) parent->setLeft (min);
                else parent->setRight(min);
                min->setParent(parent);
                min->setRight(search_node->getRight());
                min->setLeft(search_node->getLeft());
                if (min->getLeft() != NULL) min->getLeft()->setParent(min);
                if (min->getRight() != NULL)  min->getRight()->setParent(min);
            }
        }
        else if (search_node->getLeft()!= NULL ){          // One Left Children
            if ( left_child ) parent->setLeft(search_node->getLeft());
            else parent->setRight(search_node->getLeft());
            search_node->getLeft()->setParent(parent);
        }
        else if (search_node->getRight()!=NULL){             // One Right Children
            if ( left_child ) parent->setLeft(search_node->getRight());
            else parent->setRight(search_node->getRight());
            search_node->getRight()->setParent(parent);
        }
        else {                   // Leaf Node
            if (left_child) parent->setLeft(NULL);
            else parent->setRight(NULL);
        }
        count --;
        search_node->setLeft (NULL);
        search_node->setRight (NULL);
        delete (search_node);
        return true;
    }
    return false;
}

template <class NODE,typename ITEM> NODE * BinarySearchTree<NODE,ITEM>::findMax(NODE  * n )
{
    if ( root == NULL ) return NULL; // if the tree is empty return Null
    if ( n == NULL ) return findMax(root); // if n is null return with the root to search
    else if ( n->getRight() == NULL) return n; // if n of right is empty return n, which means we reach to the end of right
    else return findMax((NODE *)n->getRight()); // else recursvly go to the next right
}
template <class NODE,typename ITEM> NODE * BinarySearchTree<NODE,ITEM>::findMin(NODE * n )
{
    if ( root == NULL ) return NULL; // if the tree is empty return NULL
    if ( n == NULL ) return findMin(root);// if n is null return with the root to search
    else if ( n->getLeft() == NULL) return n; // if n of left is empty return n, which means we reached to the end of the left that is the least item
    else return findMin((NODE *)n->getLeft());// else recursivly go to the next left of n
}

template <class NODE,typename ITEM> void BinarySearchTree<NODE,ITEM>::traverseASC()
{
    traverseASC(root);// traverse ascending calling the helper method with the root
}
template <class NODE,typename ITEM> void BinarySearchTree<NODE,ITEM>::traverseDESC()
{
    traverseDESC(root);// traverse desencding calling the helper method
}
template <class NODE,typename ITEM> bool BinarySearchTree<NODE,ITEM>::contains(const ITEM item)
{
    if ( find (item) == NULL) return false;// if the item is available or not
    else return true;
}

template <class NODE,typename ITEM> NODE * BinarySearchTree<NODE,ITEM>::find (const ITEM item)
{
    if ( root != NULL) // if tree is not empty
    {
        NODE * parent = root;// new node parent equal to root
        NODE * next = (NODE *) parent->compareAndAdvance(item);// new node of next and compare and advance through the tree
        while ( next != parent)
        {
            if ( next == NULL ) break;// if next is NULL
            else parent = next; // set parent to next
            next = (NODE *) parent->compareAndAdvance(item); // then next equals to parent and then compare and advance
        }
        if ( next == parent ) return next; // if item is found return next
    }
    return NULL;// else return NULL
}

template <class NODE,typename ITEM> int BinarySearchTree<NODE,ITEM>::getCount()
{
    return count;// getter of count
}

template <class NODE,typename ITEM> NODE * BinarySearchTree<NODE,ITEM>::getRoot()
{
    return root;// getter for the root
}

template <class NODE,typename ITEM> BinarySearchTree<NODE,ITEM>::~BinarySearchTree()
{
    if ( root != NULL) delete (root);// deconstructor
}
