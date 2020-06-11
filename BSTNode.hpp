#include <iostream>
using namespace std;


#define MAX(X,Y) ((X>Y) ? X : Y)
#define HEIGHT(n) (n == NULL? 0 : n->getHeight())
#define ISLEAF(n) (n->getLeft() == NULL && n->getRight() == NULL? true :false)

/****************************************************************************************/
/*                                 BSTNode Prototype                                    */
/****************************************************************************************/

template <typename ITEM>
class BSTNode
{
    protected:
        ITEM item;
        BSTNode <ITEM> * left;
        BSTNode <ITEM> * right;
        BSTNode <ITEM> * parent;
		bool cascade_delete;
    public:
        BSTNode ();//O(1)
        BSTNode(ITEM p_item);//O(1)
        void setLeft(BSTNode <ITEM> * l);//O(1)
        void setRight(BSTNode <ITEM> * r);//O(1)
        void setParent(BSTNode <ITEM> * p);//O(1)
        BSTNode<ITEM> * getLeft();//O(1)
        BSTNode<ITEM> * getRight();//O(1)
        BSTNode<ITEM> * getParent();//O(1)
        BSTNode<ITEM> * compareAndAdvance(const ITEM & p_item);//O(n)
        ITEM & getItem(); //O(1)
		void setCascadeDelete(bool p_cascade_delete);//O(1)
		bool getCascadeDelete();// O(1)
		virtual ~BSTNode();

};
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                                 BSTNode Implementation                               */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


template <typename ITEM> BSTNode<ITEM>::BSTNode () {left=right=parent=NULL;}// constructor
template <typename ITEM> BSTNode<ITEM>::BSTNode(ITEM p_item):BSTNode() {item = p_item;}// constructor with item to set an item
template <typename ITEM> void BSTNode<ITEM>::setLeft(BSTNode <ITEM> * l) {left = l;} // left setter
template <typename ITEM> void BSTNode<ITEM>::setRight(BSTNode <ITEM> * r) {right =r;}  // right setter
template <typename ITEM> void BSTNode<ITEM>::setParent(BSTNode <ITEM> * p) {parent =p;} // parent setter
template <typename ITEM> BSTNode<ITEM> * BSTNode<ITEM>::getLeft() {return left;}//  left getter
template <typename ITEM> BSTNode<ITEM> * BSTNode<ITEM>::getRight() {return right;}// right getter
template <typename ITEM> BSTNode<ITEM> * BSTNode<ITEM>::getParent() {return parent;}// parent getter
template <typename ITEM> BSTNode<ITEM> * BSTNode<ITEM>::compareAndAdvance(const ITEM & p_item)// comparing items recursivly according to the value of item
{
    if (item > p_item)  return left;
    else if (item < p_item)  return right;
    else return this;
}
template <typename ITEM> ITEM & BSTNode<ITEM>::getItem(){return item;}//getter of item
template <typename ITEM> void BSTNode<ITEM>::setCascadeDelete(bool p_cascade_delete) { cascade_delete = p_cascade_delete; } // setter to cascade delete
template <typename ITEM> bool BSTNode<ITEM>::getCascadeDelete(){ return cascade_delete; }// getter to cascade delete

template <typename ITEM> BSTNode<ITEM>::~BSTNode()// deconstructor
{
	if (!cascade_delete) return;
	if (left != NULL) delete(left);
	if (right != NULL) delete(right);
}
