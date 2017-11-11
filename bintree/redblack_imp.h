#ifndef _REDBLACK_IMP_H_
#define _REDBLACK_IMP_H_


template <typename T, typename V>
int RedBlack<T, V>::updateHeight(node_pointer node){
    node->height2 = std::max(stature(node->leftChild), stature(node->rightChild));
    return IsBlack(node) ? node->height2++ : node->height2;
}

template <typename T, typename V>
typename RedBlack<T>::node_pointer 
RedBlack<T, V>::insert(const element_type & e){

}

template <typename T, typename V>
bool RedBlack<T, V>::remove(const T& e){

}

template <typename T, typename V>
void RedBlack<T, V>::solveDoubleRed(node_pointer node){

}

template <typename T, typename V>
void RedBlack<T, V>::solveDoubleBlack(node_pointer node){
    
}
#endif // _REDBLACK_IMP_H_