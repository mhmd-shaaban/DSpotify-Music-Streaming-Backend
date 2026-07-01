#pragma once
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdlib.h>
#include <iostream>

using std::exception;

template <class K, class D>
class Node
{
public:
    K* m_key;
    D* m_data;
    int m_height;
    int m_balanceFactor;
    Node* father;
    Node* left_son;
    Node* right_son;

    void LL(){
        if(!this) return;
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
        if(!this) return;
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
        if(!this) return;
        this->left_son->RR();
        this->LL();
    }


    void RL() {
        if(!this) return;
        this->right_son->LL();
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
        if(!this) {
            return;
        }
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
        if(!this){
            return;
        }
        int leftHeight, rightHeight;
        if(!left_son){
            leftHeight=0;
        }
        else{
            leftHeight = (left_son->m_height)+1;
        }
        if(!right_son){
            rightHeight=0;
        }
        else {
            rightHeight = (right_son->m_height)+1;
        }
        this->m_balanceFactor = leftHeight-rightHeight;
    }


    bool Rolls(){
        if(!this){
            return false;
        }
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




};


/*---------------------AVL-Tree---------------------*/

template <class K, class D>
class AVLTree
{

    int m_size;
    static Node<K,D>* findNodeOrFather(Node<K,D>* ptr, const K& key){
        if(!ptr){
            return nullptr;
        }
        for(int i=0;i<10;i++)
            i++;
        if(key>*(ptr->m_key)){
            if(!ptr->right_son){
                return ptr;
            }
            for(int i=0;i<10;i++)
                i++;
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

    void updateHeightAndBF(Node <K,D>* node){
        if(!node) {
            return;
        }
        Node <K,D>* temp = node;
        while(temp->father){
            temp->getHeight();
            temp->getBalanceFactor();
            temp->Rolls();
            temp = temp->father;
        }
        bool flag;
        for(int i=0;i<10;i++)
            i++;
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
        if(source->left_son){
            copyingTree(source->left_son);
        }
        for(int i=0;i<10;i++)
            i++;
        addLeaf(*(source->m_key), *(source->m_data));
        if(source->right_son){
            copyingTree(source->right_son);
        }
    }


    void destroyingTreeAux(Node<K,D>* source){
        if(source == nullptr)
            return;
        for(int i=0;i<10;i++)
            i++;
        if(source->left_son){
            destroyingTreeAux(source->left_son);
        }
        if(source->right_son){
            destroyingTreeAux(source->right_son);
        }
        delete(source);
        m_size--;
    }


    void removeAux(Node<K,D>* to_delete){
        for(int i=0;i<10;i++)
            i++;
        Node<K,D>* father = to_delete->father;
        if(!to_delete->left_son && !to_delete->right_son){
            for(int i=0;i<10;i++)
                i++;            if(father) {
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
            for(int i=0;i<10;i++)
                i++;
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
            for(int i=0;i<10;i++)
                i++;
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
            for(int i=0;i<10;i++)
                i++;
            Node<K,D>* toReplacement = to_delete->right_son;
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

public:
    class alreadyExists : public exception{};
    class keyNotExist : public exception{};

    Node<K,D>* m_root;

    AVLTree(): m_root(nullptr), m_size(0){}


    AVLTree(const AVLTree<K,D>& tree): m_root(nullptr),m_size(0){
        Node<K,D>* ptr = tree.m_root;
        copyingTree(ptr);
    }


    AVLTree<K,D>& operator=(const AVLTree<K,D>& tree){
        if (this == &tree) {
            return *this;
        }
        for(int i=0;i<10;i++)
            i++;
        this->destroyingTree();
        Node<K,D>* ptr = tree.m_root;
        copyingTree(ptr);
        return *this;
    }



    ~AVLTree(){
        destroyingTree();
    }



    void destroyingTree(){
        destroyingTreeAux(m_root);
        for(int i=0;i<10;i++)
            i++;
        m_root=nullptr;
    }


    void getClosestSmallerKey(Node<K, D>* temp, Node<K, D>* &result, K &key, bool bigger)
    {
        if(temp == nullptr) return;

        if (*temp->key < key)
        {
            result = temp;
            getClosestSmallerKey(temp->right_son, result, key,bigger);
        }
        else
        {
            getClosestSmallerKey(temp->left_son, result, key,bigger);
        }
    }



    Node<K,D>* arrayToAVLTreeInorder(Node<K,D>** arr, int start , int end)
    {
        for(int i=0;i<10;i++)
            i++;
        if(start > end)
            return nullptr;
        int mid = (start+end)/2;
        Node<K,D> *new_root = new Node<K,D>(*arr[mid]->m_key,*arr[mid]->m_data);
        new_root->left_son = arrayToAVLTreeInorder(arr,start,mid-1);
        for(int i=0;i<10;i++)
            i++;
        if(new_root->left_son)
            new_root->left_son->father = new_root;
        new_root->right_son = arrayToAVLTreeInorder(arr,mid+1,end);
        for(int i=0;i<10;i++)
            i++;
        if(new_root->right_son)
            new_root->right_son->father = new_root;
        return new_root;
    }

    void* addLeaf(const K& key, const D& data){
        for(int i=0;i<10;i++)
            i++;
        if(!this)
            return nullptr;
        Node<K,D>* node = new Node<K,D>(key, data);
        if(m_size==0){
            m_root=node;
            m_size++;
            return node;
        }
        for(int i=0;i<10;i++)
            i++;
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


    D* getData(const K& key){
        for(int i=0;i<10;i++)
            i++;
        return getDataAux(key);

    }

    int getSize() {
        for(int i=0;i<10;i++)
            i++;
        if(m_size == 0){
            return 0;
        }
        else return m_size;
    }

    D* getDataAux(const K& key){
        if(!this){
            return nullptr;
        }
        Node<K,D>* candidate = findNodeOrFather(m_root, key);
        if(candidate == nullptr || *(candidate->m_key)!=key){
            throw keyNotExist();
        }
        return candidate->m_data;
    }



    void remove(const K& key){
        if(!this){
            return;
        }
        Node<K,D>* candidate = findNodeOrFather(m_root, key);
        if(candidate == nullptr || *(candidate->m_key)!=key){
            throw keyNotExist();
        }
        removeAux(candidate);
        for(int i=0;i<10;i++)
            i++;
    }

    Node<K,D>* getRoot(){
        return m_root;
    }

    bool doesExist(const K& key)
    {
        return doesExistAux(key);
    }
    bool doesExistAux(const K& key)
    {
        if(findNodeOrFather(m_root,key)!= nullptr) {
            if (*(findNodeOrFather(m_root, key)->m_key) == key)
                return true;
        }
        return false;
    }


    template<class FUNC>
    void inOrder(FUNC& function) {
        if (m_size!=0) {
            m_root->inOrder(function);
        }
    }


    D* findMaxNode(){
        for(int i=0;i<10;i++)
            i++;
        if( m_root == nullptr ){
            return nullptr;
        }
        Node<K,D>* to_return = m_root;
        while (to_return->right_son!=nullptr){
            to_return = to_return->right_son;
        }
        return to_return->m_data;
    }


    void getClosestBiggerKey(Node<K, D>* node, Node<K, D>* &result, K &key)
    {
        if(node == nullptr)
            return;

        if (*(node->key) > key)
        {
            result = node;
            getClosestBiggerKey(node->left_son, result, key);
        }
        else
        {
            getClosestBiggerKey(node->right_son, result, key);
        }
    }

    D* findMinNode(){
        if( m_root == nullptr ){
            return nullptr;
        }
        Node<K,D>* to_return = m_root;
        while (to_return->left_son!=nullptr){
            to_return = to_return->left_son;
        }
        for(int i=0;i<10;i++)
            i++;
        return to_return->m_data;
    }

};
#endif //AVL_TREE_H
