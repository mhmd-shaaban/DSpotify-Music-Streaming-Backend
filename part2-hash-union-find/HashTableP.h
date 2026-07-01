#pragma once
#ifndef WET2_WINTER_HASHTABLEP_H
#define WET2_WINTER_HASHTABLEP_H
#include "iostream"
#include "AVLTree.h"


template <class T>
class HashTableP{
public:
    int size;
    int inUse;
    AVLTree<int,T>** array;


    explicit HashTableP(int size=10):size(size),inUse(0){
        array = new AVLTree<int, T> *[size];
        int i = 0;
        while (i < size) {
            array[i] = new AVLTree<int,T>();
            i++;
        }
    }

    ~HashTableP() {
        int i = 0;
        while (i < size) {
            if(array[i] != nullptr){
                delete array[i];
                array[i]= nullptr;
            }
            i++;
        }
        delete[] array;
    }

    T* findKey(int key) {
        int new_index = getPlace(key);
        if(array[new_index]== nullptr){
            return nullptr;
        }
        if(!array[new_index]->doesExist(key))
        {
            return nullptr;
        }
        return (array[new_index]->getData(key));
    }

    bool Contains(int key) {
        return (findKey(key)!= nullptr);
    }

    void removeFromTree(int key) {
        int index = getPlace(key);
        if(array[index] == nullptr || !array[index]->doesExist(key)){
            return;
        }
        array[index]->remove(key);
    }

    void insert(int key,T &Data) {
        int index = getPlace(key);
        if( array[index] != nullptr && array[index]->doesExist(key)){
            return;
        }
        if(array[index]== nullptr){
            auto* toAddTree=new AVLTree<int,T>();
            array[index]=toAddTree;
        }

        array[index]->addLeaf(key,Data);
        inUse++;
//        if(inUse>=size){
//            increaseArr();
//        }

    }

    void insertRecord(int record,T &Team,int teamId){
        int index = getPlace(record);
        if(array[index] != nullptr && !array[index]->doesExist(teamId)){
            array[index]->addLeaf(teamId,Team);
            return;
        }
        if(array[index] == nullptr){
            auto* toAddTree = new AVLTree<int,T>();
            array[index]=toAddTree;
        }
        array[index]->addLeaf(teamId,Team);
        inUse++;
        if(inUse>=size){
            increaseArr();
        }
    }

    void changeRecord(int record,T &team,int teamId,int factor){
        int index=getPlace(record);
        if(array[index]==nullptr)
            return;
        array[index]->remove(teamId);
        team.record+=factor;
        insertRecord(record+factor,team,teamId);
    }

    void deleteRecord(int record,int teamId){
        int index=getPlace(record);
        array[index]->remove(teamId);
    }

    int teamWithRecord(int record){             //now we get the teamId of the team with this record
        int index=getPlace(record);
        return *array[index]->m_root->m_key;
    }

    int sameRecord(int record){
        int index=getPlace(record);
        if(array[index]==nullptr)
            return 0;
        return array[index]->getSize();
    }

    int howManyAppears(int key){
        int count = 0;
        for (int i = 0; i < size ; ++i) {
            if(array[i] == nullptr){
                continue;
            }
            if(array[i]->find(key)){
                count++;
                continue;
            }
        }
        return count;
    }

    void increaseArr() {
        int changedSize=size;
        size = 10*size;
        auto** newArr = new  AVLTree<int, T>*[size];
        int i = 0;
        while (i < size) {
            newArr[i] = nullptr;
            i++;
        }
        moveArr(changedSize,newArr);
        delete[] this->array;
        this->array = newArr;
    }

    int getPlace(int key) {
        if(key>=0)
            return key % (size);
        key-=2*key;
        return size - (key % (size));
    }

    void moveArr(int changedSize, AVLTree<int,T>** new_arr) {
        for (int i = 0; i < changedSize ; ++i) {
            if(array[i] == nullptr){
                new_arr[i] = nullptr;
                continue;
            }
            Node<int,T>* ptr=array[i]->getRoot();
            while ( ptr != nullptr){
                int key = *(ptr->m_key);
                T movedData = *array[i]->getRoot()->m_data;
                array[i]->remove(key);
                int newPlace= getPlace(key);
                if( new_arr[newPlace] == nullptr){
                    auto* toAddTree = new AVLTree<int,T>();
                    new_arr[newPlace] = toAddTree;
                }
                new_arr[newPlace]->addLeaf(key,movedData);
                ptr=array[i]->getRoot();
            }
            delete array[i];
        }
    }
};

#endif //WET2_WINTER_HASHTABLE
