#include "AVLNode.hpp"
#include "cmath"

/****************************************************************************************/
/*                                 AVLTree Prototype                                    */
/****************************************************************************************/


template <typename ITEM>
class AVLTree : public BinarySearchTree<AVLNode<ITEM>,ITEM> 
{
    private:
        AVLNode <ITEM> * updateHeightAndEvaluateBalance( AVLNode <ITEM> * n);
        void rotateWithLeftChild(AVLNode <ITEM> * p);//O(1)
        void rotateWithRightChild(AVLNode <ITEM> * p);//O(1)
        void doubleRotateWithLeftChild(AVLNode <ITEM> * p); //O(1)
        void doubleRotateWithRightChild(AVLNode <ITEM> * p);//O(1)
        int calcHeight (AVLNode <ITEM> * n); //O(n)
        bool isBalanced (AVLNode <ITEM> * n);// O(n)
    public:
        AVLTree();
        AVLNode <ITEM> * insert(const ITEM & item);//O(log n)
        int calcHeightpls ();  // O(n)
        bool isBalancedpls ();// O(n)
        ~AVLTree();
};

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                               AVLTree Implementation                                 */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

template <typename ITEM>  AVLNode <ITEM> * AVLTree<ITEM>::updateHeightAndEvaluateBalance( AVLNode <ITEM> * n)
{
   if (n==NULL) // checking n if null
       return NULL;
    
    
    n->setHeight(MAX(HEIGHT(n->getLeft()),HEIGHT(n->getRight()))+1);// updating Height
    if(abs(HEIGHT(n->getLeft()) - HEIGHT(n->getRight()))<=1) // checking balancing
        return (updateHeightAndEvaluateBalance(n->getParent())); // calling the function recursivley to find alpha
    
    return n;// returns alpha   
    
}

template <typename ITEM> AVLNode <ITEM> * AVLTree<ITEM>::insert(const ITEM & item) { // inserting into an AVL Tree
 
    AVLNode<ITEM> * n= BinarySearchTree<AVLNode<ITEM>,ITEM>::insert(item);// inserting into an AVL Tree using the insert function from BST
    
    n=updateHeightAndEvaluateBalance(n);// updating and evaluting balance everytime

    if(n!=NULL)
    { // Looping until reach the root
        
        int h;
        h=(HEIGHT(n->getLeft())) - (HEIGHT(n->getRight())); // getting the balance factor of n
        if(n->getLeft()!=NULL)
        {
            if (h>1)
            { //the balance factor is greater than 1, which makes it an unbalance situation in the left

                if(((HEIGHT(n->getLeft()->getLeft())) - (HEIGHT(n->getLeft()->getRight())))>=0) // checking the situation of the unbalancing
                    rotateWithLeftChild(n); // then it's a left left rotation
                else
                    doubleRotateWithLeftChild(n);// else it's a left Right rotation

            }
        }

        if(n->getRight()!=NULL) 
        {
            if (h<-1)
            { // the balance factor is less than -1, which makes it an unbalance situation in the ik,right
                if(((HEIGHT(n->getRight()->getLeft())) - (HEIGHT(n->getRight()->getRight())))<=0)
                    rotateWithRightChild(n); // right right rotation
                else
                    doubleRotateWithRightChild(n);// right left rotation
            }
        }
    //     n=n->getParent();// moving to the parent of n to reach the root

    }
    
    return n; // returning n
}

template <typename ITEM> void AVLTree<ITEM>::rotateWithLeftChild(AVLNode <ITEM> * p)// left left rotation
{
    AVLNode <ITEM> * n = p->getLeft();// temp is the child of the alpha
    AVLNode <ITEM> * parent = n->getParent();// parent pointer
    AVLNode <ITEM> * grand_parent = parent->getParent();//  grandparent pointer
    
    
    if( parent == this->root)// if parent is the root
        this->root = n;// rotate parent with the child
    else
    {
        if ( grand_parent->getLeft() == parent)// if parent is the left child of grandparent
            grand_parent->setLeft(n);// rotate the parent with its child and
        else
            grand_parent->setRight(n);// else set the grandparent's right child to the temp child
        
    }
    
    parent->setParent(n); // make the temp child to be the parent due to the rotation
    
    parent->setLeft(n->getRight());// set parents left to the right of the child
    
    if (parent->getLeft() != NULL)// if the parent has a child
        parent->getLeft()->setParent(parent);// setting the left child as the parent
    
    n->setRight(parent); // setting the parent to the right of n
    
    if (n->getRight() != NULL) // if n has a right child
        n->getRight()->setParent(n); // set n as the parent of right child
    
    n->setParent(grand_parent);// set grandparent as the parent of n
    
    parent->setHeight(MAX(HEIGHT(parent->getLeft()),HEIGHT(parent->getRight()))+1);// update height of the parent
    
    n->setHeight(MAX(HEIGHT(n->getLeft()),HEIGHT(n->getRight()))+1);// update height of n
    
}


template <typename ITEM> void AVLTree<ITEM>::rotateWithRightChild(AVLNode <ITEM> * p)// right right rotation
{
    AVLNode <ITEM> * n = p->getRight();// temp n to be the right of the alpha
    AVLNode <ITEM> * parent = n->getParent();// setting parent as the parent of n
    AVLNode <ITEM> * grand_parent = parent->getParent();// setting grandparent
    
    if( parent == this->root) // if the parent is the root
        this->root = n;// rotate the parent with n;
    else
    {
        if ( grand_parent->getRight() == parent) // if the parent is the right child of grandparent
            grand_parent->setRight(n); // rotate parent with the child, making n as the right child of the grandparent
        else
            grand_parent->setLeft(n);// set n as the left child of grandparent
        
    }
    
    parent->setParent(n);// due to the rotations we set n as the parent
    
    parent->setRight(n->getLeft());// setting the left child of n to become the right child of the parent
    
    if (parent->getRight() != NULL) // if the parent has a right child
        parent->getRight()->setParent(parent); // setting the parent as the parent of the right child
    
    n->setLeft(parent); // set the parent as the left child of n
    
    if (n->getLeft() != NULL) // if n has a left child
        n->getLeft()->setParent(n);//set n as the parent of the left child
    
    n->setParent(grand_parent);// set grandparent as the parent of n
    
    parent->setHeight(MAX(HEIGHT(parent->getLeft())+1,HEIGHT(parent->getRight())));// updating height of the parent
    
    n->setHeight(MAX(HEIGHT(n->getLeft())+1,HEIGHT(n->getRight())));// updating the height of n
    
}

template <typename ITEM> void AVLTree<ITEM>::doubleRotateWithLeftChild(AVLNode <ITEM> * p)
{
    rotateWithRightChild(p->getLeft());// right right rotation
    rotateWithLeftChild(p);// left left rotation
}
template <typename ITEM> void AVLTree<ITEM>::doubleRotateWithRightChild(AVLNode <ITEM> * p)
{
    rotateWithLeftChild(p->getRight()); //left left rotation
    rotateWithRightChild(p);// right right rotation
}
template <typename ITEM> int AVLTree<ITEM>::calcHeight (AVLNode <ITEM> * n)
{
    if (n== NULL) // stopping condition to reach the root
        return -1; // returning -1 to make a leaf = 0;
    
    return 1+(MAX(calcHeight(n->getLeft()),(calcHeight(n->getRight()))));// recursively calculating the height of the tree
}
template <typename ITEM> bool AVLTree<ITEM>::isBalanced (AVLNode <ITEM> * n) // helper method if isBalanced
{
    int h; // setting variable h
 
    if(n == NULL)// stopping condition when reaching a leaf
        return true;
    

    h = calcHeight(n->getLeft()) - calcHeight(n->getRight());// calculating height difference between left and right
    
    if((abs(h)) <= 1) // checking the balance factor between left and right
        return true; 
// if we finish the recursive functions from the left children and the right children while maintaing the balance factor, then the tree is balance
    else
    
    return false;// NOT BALANCED
}

template <typename ITEM> AVLTree<ITEM>::AVLTree():BinarySearchTree<AVLNode<ITEM>,ITEM>() {// constructor
    this->root= NULL;
    
}


template <typename ITEM> int AVLTree<ITEM>::calcHeightpls ()
{
    return calcHeight(this->root);// calling the helper method and sending the root to it
}


template <typename ITEM> bool AVLTree<ITEM>::isBalancedpls ()
{
    return isBalanced(this->root);//calling the helper method and sending the root to it
}

template <typename ITEM> AVLTree<ITEM>::~AVLTree(){ // deconstructor
    
}
