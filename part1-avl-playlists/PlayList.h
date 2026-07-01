#include "AVL_Tree.h"
#include "Song.h"
#include <memory>
#include "myPair.h"

using std::shared_ptr;
using std::make_shared;

class PlayList {
    public:
    int list_id;
    AVLTree<int, shared_ptr<Song>> id_songs;
    AVLTree<myPair, shared_ptr<Song>> play_songs;
    int m_size;
    
    
    PlayList(int id) : list_id(id), id_songs(),play_songs(),m_size(0){}
    int size() const {
        return m_size;
    }
    void changeSize(int factor) {
        m_size += factor;
    }
    
};