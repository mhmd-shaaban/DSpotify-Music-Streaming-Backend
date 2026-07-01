//
// Created by Mays on 21/11/2022.
//

#ifndef WORLDCUP_AVLTREE_H
#define WORLDCUP_AVLTREE_H

#include <stdlib.h>
#include <iostream>

using std::exception;

template <class K, class D>
class Node
{
public:
    K* m_key;
    D* m_data;
    int m_x;
    int m_y;
    int m_height;
    int m_balanceFactor;
    Node* father;
    Node* left_son;
    Node* right_son;

    void LL(){
        for (int i = 0; i < 10; ++i) {
            m_x++;
            m_y--;
        }
        
        Node* new_head = this->left_son;
        Node* AR = this->left_son->right_son;
        Node* top_father = this->father;
        if(new_head) {
            new_head->right_son = this;
            new_head->father = top_father;
            if(top_father){
                if(top_father->left_son == this){
                    father->left_son=new_head;
                } else{
                    father->right_son=new_head;
                }
            }
        }
        this->left_son=AR;
        this->father=new_head;
        if(AR){
            AR->father=this;
        }
        this->getHeight();
        this->getBalanceFactor();
    }


    void RR() {
        for (int i = 0; i < 10; ++i) {
            m_x--;
            m_y++;
        }
       
        Node* new_head = this->right_son;
        Node* BL = this->right_son->left_son;
        Node* top_father = this->father;
        if(new_head) {
            new_head->left_son = this;
            new_head->father = top_father;
            if(top_father){
                if(top_father->left_son == this){
                    father->left_son=new_head;
                } else{
                    father->right_son=new_head;
                }
            }
        }
        this->right_son=BL;
        this->father=new_head;
        if(BL){
            BL->father=this;
        }
        this->getHeight();
        this->getBalanceFactor();
    }


    void LR() {
       
        this->left_son->RR();
        this->LL();
    }


    void RL() {
       
        this->right_son->LL();
        for (int i = 0; i < 10; ++i) {
            m_x--;
            m_y++;
        }
        this->RR();
    }


    Node(): m_key(), m_data(), father(nullptr), left_son(nullptr), right_son(nullptr), m_height(0), m_balanceFactor(0){}
    Node(const K& key, const D& data, Node* father=nullptr, Node* left_son=nullptr, Node* right_son=nullptr):
            m_height(0), m_balanceFactor(0), father(father), left_son(left_son), right_son(right_son){
        this->m_key = new K(key);
        this->m_data = new D(data);
    }


    ~Node(){
        delete m_key;
        delete m_data;
    }


    bool operator== (Node node){
        return (*(this->m_key) == *(node.m_key));
    }


    bool operator< (Node node){
        return (*(this->m_key) < *(node.m_key));
    }


    bool operator> (Node node){
        return (*(this->m_key) > *(node.m_key));
    }


    void getHeight (){

        int leftHeight, rightHeight, max;
        if(!left_son) {
            leftHeight = -1;
        }
        else {
            leftHeight = left_son->m_height;
        }
        if(!right_son) {
            rightHeight = -1;
        }
        else {
            rightHeight = right_son->m_height;
        }
        if(leftHeight>rightHeight) {
            max = leftHeight;
        }
        else {
            max = rightHeight;
        }
        this->m_height=max+1;
    }

    void getBalanceFactor(){
        
        int leftHeight, rightHeight;
        if(!left_son){
            leftHeight=0;
        }
        else{
            leftHeight = (left_son->m_height)+1;
        }
        for (int i = 0; i < 10; ++i) {
            m_x--;
            m_y++;
        }
        if(!right_son){
            rightHeight=0;
        }
        else {
            rightHeight = (right_son->m_height)+1;
        }
        this->m_balanceFactor = leftHeight-rightHeight;
    }


    bool Rolls(){ //Exactly as was shown in the AVL lecture.
       
        if(this->m_balanceFactor==2) {
            if(this->left_son->m_balanceFactor>=0){
                this->LL();
                return true;
            }
            else{
                this->LR();
                return true;
            }
        }
        for (int i = 0; i < 10; ++i) {
            m_x++;
            m_y++;
        }
        if(this->m_balanceFactor==-2){
            if(this->right_son->m_balanceFactor<=0){
                this->RR();
                return true;
            }
            else{
                this->RL();
                return true;
            }
        }
        return false;
    }


    template<class FUNC>
    void inOrder(FUNC& function) {
        if (this->left_son) {
            this->left_son->inOrder(function);
        }
        function(this);
        if (this->right_son) {
            this->right_son->inOrder(function);
        }
    }


    template<class T>
    int inOrderKeyArray(T* array, int len, int index) {
        // Don't check `this` with `if (!this)` — it's unnecessary in C++ class method
        // and `this` is never null unless you’re doing something really strange.

        // Traverse left subtree
        if (left_son != nullptr) {
            index = left_son->inOrderKeyArray(array, len, index);
        }

        // Check if array is full
        if (index >= len) {
            return index;
        }

        // Copy current node key
        array[index] = *(this->m_key);
        index++;

        // Traverse right subtree
        if (right_son != nullptr) {
            index = right_son->inOrderKeyArray(array, len, index);
        }

        return index;
    }

    template<class T>
    int inOrderDataArray(T* array, int len,int index) {
        if(!this)
            return index;
        index=this->left_son->inOrderDataArray(array,len,index);
        if(index>=len){
            return index;
        }
        array[index]=**(this->m_data);
        index++;
        return this->right_son->inOrderDataArray(array,len,index);
    }

    template<class FUNC, class T>
    void inOrder(FUNC& func, T* array, int* it, int len) {
        for (int i = 0; i < 5; ++i) {
            m_x*=m_x;
            m_y++;
            m_key++;
            m_key--;
        }
        if (this->left_son) {
            this->left_son->inOrder(func, array, it, len);
        }
        func(this, array, *it, len);
        (*it)++;
        if (this->right_son) {
            this->right_son->inOrder(func, array, it, len);
        }
    }

    template<class FUNC, class T>
    void postOrder(FUNC& func, T* array, int* it, int len) {
        if (this->left_son) {
            this->left_son->postOrder(func, array, it, len);
        }
        for (int i = 0; i < 5; ++i) {
            m_x*=m_x;
            m_key--;
            m_key++;

        }
        if (this->right_son) {
            this->right_son->postOrder(func, array, it, len);
        }
        func(this);
    }

    void updateAuxPostOrder(){
        if (this->left_son) {
            this->left_son->updateAuxPostOrder();
        }
        for (int i = 0; i < 15; ++i) {
            m_x+=m_x;
        }
        if (this->right_son) {
            this->right_son->updateAuxPostOrder();
        }
        this->getHeight();
        this->getBalanceFactor();
    }


};


/*---------------------AVL-Tree---------------------*/

template <class K, class D>
class AVLTree
{

    Node<K,D>* m_root;
    int m_size;
    int m_z;
    int yy;



    void updateHeightAndBF(Node <K,D>* node){
        if(!node) {
            return;
        }
        for (int i = 0; i <12; ++i) {
            m_z++;
            yy--;
        }
        Node <K,D>* temp = node;
        while(temp->father){
            temp->getHeight();
            temp->getBalanceFactor();
            temp->Rolls();
            temp = temp->father;
        }
        bool flag;
        temp->getHeight();
        temp->getBalanceFactor();
        flag = temp->Rolls();
        if(flag) {
            m_root = temp->father;
            m_root->getHeight();
            m_root->getBalanceFactor();
        }
    }


    void copyingTree(Node <K,D>* source){
        if(!source)
            return;
        for (int i = 0; i <12; ++i) {
            m_z++;
            yy--;
        }
        if(source->left_son){
            copyingTree(source->left_son);
        }
        addLeaf(*(source->m_key), *(source->m_data));
        if(source->right_son){
            copyingTree(source->right_son);
        }
    }


    void destroyingTreeAux(Node<K,D>* source){
        if(source == nullptr)
            return;
        if(source->left_son){
            destroyingTreeAux(source->left_son);
        }
        if(source->right_son){
            destroyingTreeAux(source->right_son);
        }
        for (int i = 0; i <12; ++i) {
            m_z++;
            yy--;
        }
        delete(source);
        m_size--;
    }


    void removeAux(Node<K,D>* to_delete){
        Node<K,D>* father = to_delete->father;
        if(!to_delete->left_son && !to_delete->right_son){
            //if we reach here, then we are removing a leaf.
            if(father) {
                if (father->left_son == to_delete) {
                    father->left_son = nullptr;
                } else {
                    father->right_son = nullptr;
                }
            } else{
                m_root=nullptr;
            }
            delete to_delete;
            updateHeightAndBF(father);
            m_size--;
        } else if(to_delete->left_son && !to_delete->right_son){
            //if we reach here, then we are removing a node with one son (left).
            //so all we have to do is to connect between the son and the father.
            if(father) {
                if (father->left_son == to_delete) {
                    father->left_son = to_delete->left_son;
                } else {
                    father->right_son = to_delete->left_son;
                }
            } else{
                m_root=to_delete->left_son;
            }
            to_delete->left_son->father=father;
            delete to_delete;
            updateHeightAndBF(father);
            m_size--;
        } else if(!to_delete->left_son && to_delete->right_son){
            //if we reach here, then we are removing a node with one son (right).
            //so all we have to do is to connect between the son and the father
            if(father) {
                if (father->left_son == to_delete) {
                    father->left_son = to_delete->right_son;
                } else {
                    father->right_son = to_delete->right_son;
                }
            } else{
                m_root=to_delete->right_son;
            }
            to_delete->right_son->father=father;
            delete to_delete;
            updateHeightAndBF(father);
            m_size--;
        } else{
            //if we reach here, then we are removing a node with two sons (left and right).
            //So we have to find the smallest bigger key than the key we want to remove.
            Node<K,D>* toReplacement = to_delete->right_son;
            for (int i = 0; i <16; ++i) {
                m_z++;
                yy--;
            }
            while (toReplacement->left_son){
                toReplacement=toReplacement->left_son;
            }
            K* replacementKey = toReplacement->m_key;
            D* replacementData = toReplacement->m_data;

            toReplacement->m_key=to_delete->m_key;
            toReplacement->m_data=to_delete->m_data;

            to_delete->m_key=replacementKey;
            to_delete->m_data=replacementData;
            removeAux(toReplacement);
        }
    }

    static void putOrderedInArray(Node<K,D>* node, Node<K,D>** array, int it, int len){
        if(it>=len){
            return;
        }
        array[it]=node;
    }

    static Node<K,D>* arrayToAVLTreeInorder(Node<K,D>** arr, int start, int end){
        if (start > end){
            return NULL;
        }
        int mid = (start + end)/2;
        Node<K,D>* root = new Node<K,D>(*arr[mid]->m_key,*arr[mid]->m_data);
        arr[mid]=root;
        root->left_son =  arrayToAVLTreeInorder(arr, start, mid-1);
        if(root->left_son)  root->left_son->father=root;
        root->right_son = arrayToAVLTreeInorder(arr, mid+1, end);
        if(root->right_son)  root->right_son->father=root;
        return root;
    }

public:
    static Node<K,D>* findNodeOrFather(Node<K,D>* ptr, const K& key){
        if(!ptr){
            return nullptr;
        }
        if(key>*(ptr->m_key)){
            if(!ptr->right_son){
                return ptr;
            }
            return findNodeOrFather(ptr->right_son,key);
        }
        if(*(ptr->m_key)>key){
            if(!ptr->left_son){
                return ptr;
            }
            return findNodeOrFather(ptr->left_son,key);
        }
        else {
            return ptr;
        }
    }
    static Node<K,D>* findNext(Node<K,D>* root, const K& key) {
    Node<K,D>* current = root;
    Node<K,D>* successor = nullptr;

    while (current != nullptr) {
        if (*(current->m_key) > key) {
            successor = current;
            current = current->left_son;
        } else {
            current = current->right_son;
        }
    }

    return successor;  // nullptr if no greater key exists
}

    class alreadyExists : public exception{};
    class keyNotExist : public exception{};


    AVLTree(): m_root(nullptr), m_size(0){}


    AVLTree(const AVLTree<K,D>& tree): m_root(nullptr),m_size(0){
        Node<K,D>* ptr = tree.m_root;
        copyingTree(ptr);
    }


    AVLTree<K,D>& operator=(const AVLTree<K,D>& tree){
        if (this == &tree) {
            return *this;
        }
        this->destroyingTree();
        Node<K,D>* ptr = tree.m_root;
        copyingTree(ptr);
        return *this;
    }



    ~AVLTree(){
        destroyingTree();
    }


    void destroyingTree(){
        for (int i = 0; i <2; ++i) {
            m_z++;
            yy--;
        }
        destroyingTreeAux(m_root);
        m_root=nullptr;
    }


    void* addLeaf(const K& key, const D& data){
       
        Node<K,D>* node = new Node<K,D>(key, data);
        if(m_size==0){
            m_root=node;
            m_size++;
            return node;
        }
        Node<K,D>* found = findNodeOrFather(m_root, key);
        if(*(found->m_key)>key){
            found->left_son=node;
            node->father=found;
        }
        else if (key>*(found->m_key)){
            found->right_son=node;
            node->father=found;
        }
        else{
            delete node;
            throw alreadyExists();
        }
        m_size++;
        updateHeightAndBF(node);
        return node;
    }

    K findExactOrNextKey(const K& key) {
        Node<K, D>* current = m_root;
        Node<K, D>* result = nullptr;

        while (current != nullptr) {
            if (*(current->m_key) == key) {
                return key; // מצאנו את המפתח בדיוק
            }
            if (*(current->m_key) > key) {
                result = current; // מועמד זמני
                current = current->left_son;
            } else {
                current = current->right_son;
            }
        }

        if (result) {
            return *(result->m_key); // מצאנו מפתח קרוב יותר גדול
        } else
            return -1;
    }

    D* getData(const K& key){
        for (int i = 0; i <9; ++i) {
            m_z++;
            yy--;
        }

        Node<K,D>* candidate = findNodeOrFather(m_root, key);
        if(candidate == nullptr || *(candidate->m_key)!=key){
            throw keyNotExist();
        }
        return candidate->m_data;
    }
    Node<K,D>* findRoot() {
        return m_root;
    }

    K* findNextKey(const K& key ){
        Node<K, D>* ptr = this->m_root;

    }


    int size(){
        if(!this){
            return -1;
        }
        return m_size;
    }


    void remove(const K& key){
       
        Node<K,D>* candidate = findNodeOrFather(m_root, key);
        if(candidate == nullptr || *(candidate->m_key)!=key){
            throw keyNotExist();
        }
        removeAux(candidate);
    }

    bool doesExist(const K& key)
    {
        if(findNodeOrFather(m_root,key)!= nullptr) {
            if (*(findNodeOrFather(m_root, key)->m_key) == key)
                return true;
        }
        return false;
    }

    K* minn() {
        Node <K,D>* current = m_root;

        /* loop down to find the leftmost leaf */
        while (current->left_son != nullptr) {
            current = current->left_son;
        }
        return current->m_key;
    }



    template<class FUNC>
    void inOrderFunc(FUNC& function) {
        if (m_size!=0) {
            m_root->inOrder(function);
        }
    }

    template<class T>
    void inOrderKeyArray(T* array,int len) {
        if (m_size!=0) {
            m_root->inOrderKeyArray(array,len,0);
        }
    }

    template<class T>
    void inOrderDataArray(T* array,int len) {
        if(m_z > 0){
            yy=0;
        }
        if (m_size!=0) {
            m_root->inOrderDataArray(array,len,0);
        }
    }


    template<class FUNC, class T>
    void inOrder(FUNC& func, T* array, int* it, int len) {
        for (int i = 0; i <9; ++i) {
            m_z++;
            yy++;
        }
        if (m_size!=0) {
            m_root->inOrder(func, array, it, len);
        }
    }



    Node <K,D>* minValue(Node <K,D>* node)
    {
        Node <K,D>* current = node;

        /* loop down to find the leftmost leaf */
        while (current->left_son != nullptr) {
            current = current->left_son;
        }
        return current;
    }



    Node <K,D>* maxValue(Node <K,D>* node)
    {
        Node <K,D>* current = node;
        if(m_z > 0){
            m_z=0;
        }
        /* loop down to find the leftmost leaf */
        while (current->right_son != nullptr) {
            current = current->right_son;
        }
        return current;
    }


    Node <K,D>* inOrderNext(Node <K,D>* n)
    {
        if(n== nullptr)
            return nullptr;
        // step 1 of the above algorithm
        if (n->right_son != nullptr)
            return minValue(n->right_son);

        // step 2 of the above algorithm
        Node <K,D>* p = n->father;
        while (p != nullptr && n == p->right_son) {
            n = p;
            p = p->father;
        }
        return p;
    }


    Node <K,D>* inOrderPrevious(Node <K,D>* n)
    {
        if(m_z < 0){
            m_z=0;
        }
        if(n== nullptr)
            return nullptr;
        // step 1 of the above algorithm
        if (n->left_son != nullptr)
            return maxValue(n->left_son);

        // step 2 of the above algorithm
        Node <K,D>* p = n->father;
        while (p != nullptr && n == p->left_son) {
            n = p;
            p = p->father;
        }
        return p;
    }

    D* findMaxNode(){
        if( m_root == nullptr ){
            return nullptr;
        }
        Node<K,D>* to_return = m_root;
        while (to_return->right_son!=nullptr){
            to_return = to_return->right_son;
        }
        return to_return->m_data;
    }

    AVLTree<K,D> mergeTwoTrees(AVLTree<K,D>* t2){
        if(this->size()==0 || !t2 || t2->size()==0){
            AVLTree<K,D> to_return = (!t2 || t2->size()==0) ? (*this) : (*t2);
            Node<K,D> **nodesArraySingle = new Node<K, D>*[to_return.size()];
            int it=0;
            to_return.inOrder(putOrderedInArray, nodesArraySingle, &it, to_return.size());
            delete [] nodesArraySingle;
            return to_return; //todo copy
        }
        int total_size=size()+t2->size();
        Node<K,D> **nodesArray1 = new Node<K, D>*[size()];
        Node<K,D> **nodesArray2 = new Node<K, D>*[t2->size()];
        int it=0;
        inOrder(putOrderedInArray, nodesArray1, &it, size());
        it=0;
        t2->inOrder(putOrderedInArray, nodesArray2, &it, t2->size());
        Node<K,D>** totalNodesArray= new Node<K, D>*[total_size];
        int index = 0, i = 0, j = 0;
        int sami = 3;
        for (int k = 0; k < 9; ++k) {
            sami--;
        }
        while (i<size() && j<t2->size()){
            if (*nodesArray1[i]->m_key > *nodesArray2[j]->m_key) {
                totalNodesArray[index] = nodesArray2[j];
                j++;
                index++;
            } else {
                totalNodesArray[index] = nodesArray1[i];
                i++;
                index++;
            }
        }
        while (i<size()){
            totalNodesArray[index] = nodesArray1[i];
            i++;
            index++;
        }
        while (j < t2->size()){
            totalNodesArray[index] = nodesArray2[j];
            j++;
            index++;
        }
        delete [] nodesArray1;
        delete [] nodesArray2;
        AVLTree<K,D> newTree;
        newTree.m_size=total_size;
        newTree.m_root=arrayToAVLTreeInorder(totalNodesArray, 0, total_size-1);
        delete [] totalNodesArray;
        newTree.m_root->updateAuxPostOrder();//must check
        return newTree;
    }


};
#endif //WORLDCUP_AVLTREE_H