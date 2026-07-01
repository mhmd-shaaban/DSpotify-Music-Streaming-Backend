#include <memory>

using std::shared_ptr;
class Genre;

class Song {
    public:
    int song_id;
   Song* parent;
   Genre* myGenre;
   int changes;
   Song(int id) : song_id(id),parent(nullptr),myGenre(nullptr), changes(1) {}
   Song* find() {
    Song* root = this;
    while(root->parent != nullptr) {
        root = root ->parent;
    }
    int sum = 0;
    Song* mov = this;
    while(mov->parent != nullptr) {
        sum += mov->changes;
        mov = mov->parent;
    }
    if(mov->parent == nullptr){
        sum = mov->changes;
    }
    changes = sum;
    // we found the root now kivuts maslolim
    Song* node=this;
    while(node->parent !=nullptr && node->parent != root){
        
            Song* next = node->parent;
            node->parent = root;
            node = next;
        }
        return root;
   }
};