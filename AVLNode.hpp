#include "BinarySearchTree.hpp"
/****************************************************************************************/
/*                                 AVLNode Prototype                                    */
/****************************************************************************************/

template <typename ITEM>
class AVLNode : public BSTNode <ITEM>
{
    private:
        int height;
    public:
        AVLNode ();
        AVLNode(ITEM p_item);
        void setHeight(int p_height);
        int getHeight();
        AVLNode<ITEM> * getLeft();
        AVLNode<ITEM> * getRight();
        AVLNode<ITEM> * getParent();
        ~AVLNode();
};

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                               AVLNode Implementation                                 */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

template <typename ITEM> AVLNode<ITEM>::AVLNode ():BSTNode<ITEM>(){ height = 1;}// set Height
template <typename ITEM> AVLNode<ITEM>::AVLNode(ITEM p_item):BSTNode<ITEM>(p_item){ height = 1;}// constructor having item and implementing height
template <typename ITEM> void AVLNode<ITEM>::setHeight(int p_height) {height = p_height;}// Height setter
template <typename ITEM> int AVLNode<ITEM>::getHeight() {return height;}// Height getter
template <typename ITEM> AVLNode<ITEM> * AVLNode<ITEM>::getLeft() {return (AVLNode<ITEM> *) this->left;}// left getter
template <typename ITEM> AVLNode<ITEM> * AVLNode<ITEM>::getRight() {return (AVLNode<ITEM> *) this->right;}// right getter
template <typename ITEM> AVLNode<ITEM> * AVLNode<ITEM>::getParent() {return (AVLNode<ITEM> *) this->parent;}// parent getter
template <typename ITEM> AVLNode<ITEM>::~AVLNode() {}
