

class Song{
    int song_id;
    int m_plays;
    int num_lists;

    public :
    Song(int id , int plays) : song_id(id), m_plays(plays), num_lists(0) {}
    Song(const Song& other ) : song_id(other.song_id),m_plays(other.m_plays) , num_lists(other.num_lists) {}

    bool operator==(const Song& other) {
        return this->song_id == other.song_id;
    }
    int raiseNum(int factor) {
        return num_lists += factor;
    }
    int NumLists() const {
        return num_lists;
    }
    int plays() const {
        return m_plays;
    }
    int getId() const {
        return song_id;
    }
};
