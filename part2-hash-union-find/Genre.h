#include "Song.h"

class Genre {
    public:
    int genre_id;
    int size;
    Song* first;
    Genre(int id) : genre_id(id), size(0), first(nullptr) {}
};