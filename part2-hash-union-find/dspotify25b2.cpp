// You can edit anything you want in this file.
// However you need to implement all public DSpotify function, as provided below as a template

#include "dspotify25b2.h"


DSpotify::DSpotify(){

}

DSpotify::~DSpotify(){
    
}

StatusType DSpotify::addGenre(int genreId){
    if(genreId <= 0 ) {
        return StatusType::INVALID_INPUT;
    }
    if(GenreHash.findKey(genreId) != nullptr ){
        return StatusType::FAILURE;
    }
    try{
        Genre genre(genreId);
        GenreHash.insert(genreId, genre);
        //  printf("Genre %d added\n", genreId);
        return StatusType::SUCCESS;
    }catch(std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType DSpotify::addSong(int songId, int genreId){
    if(songId <= 0 || genreId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if(songHash.Contains(songId) || (!GenreHash.Contains(genreId))) {
        return StatusType::FAILURE;
    }
    Song toAdd = Song(songId);
    toAdd.myGenre = GenreHash.findKey(genreId);
    songHash.insert(songId, toAdd);
    if(GenreHash.findKey(genreId)->size == 0) {
        GenreHash.findKey(genreId)->first = songHash.findKey(songId);
        GenreHash.findKey(genreId)->size++;
        return StatusType::SUCCESS;
    } else {
        // songHash.findKey(songId)->parent=GenreHash.findKey(genreId)->first;
        songHash.findKey(songId)->parent = GenreHash.findKey(genreId)->first;
        songHash.findKey(songId)->changes -= GenreHash.findKey(genreId)->first->changes;
        GenreHash.findKey(genreId)->size++;
        return StatusType::SUCCESS;
    }
    return StatusType::FAILURE;
}

StatusType DSpotify::mergeGenres(int genreId1, int genreId2, int genreId3){
    if(genreId1 <= 0 || genreId2 <= 0 || genreId3 <= 0 || genreId1 == genreId2 || genreId1 == genreId3 || genreId2 == genreId3) {
        return StatusType::INVALID_INPUT;
    }
    if(!GenreHash.Contains(genreId1) || !GenreHash.Contains(genreId2) || GenreHash.Contains(genreId3)) {
        return StatusType::FAILURE;
    }
    Genre* genre1 = GenreHash.findKey(genreId1);
    Genre* genre2 = GenreHash.findKey(genreId2);
    Genre genre3(genreId3);
    int size1 = genre1->size;
    int size2 = genre2->size;
    try {
    if(size1 == 0  && size2 == 0 ) {
        GenreHash.insert(genreId3, genre3);
        return StatusType::SUCCESS;
    } else if(size1 == 0) {
        genre3.size = size2;
        genre3.first = genre2->first;
        genre3.first->myGenre = &genre3;
        genre2->first = nullptr;
        genre2->size = 0;
        genre3.first->changes++;
        GenreHash.insert(genreId3, genre3);
        GenreHash.findKey(genreId3)->first->myGenre=GenreHash.findKey(genreId3);

        return StatusType::SUCCESS;
    }else if(size2 == 0) {
        genre3.size = size1;
        genre3.first = genre1->first;
        genre3.first->myGenre = &genre3;
        genre1->first = nullptr;
        genre1->size = 0;
        genre3.first->changes++;
        GenreHash.insert(genreId3, genre3);
        GenreHash.findKey(genreId3)->first->myGenre=GenreHash.findKey(genreId3);
        return StatusType::SUCCESS;
    } else if( size1 >= size2) {
        genre3.first = genre1->first;
        genre2->first->parent = genre3.first;
        genre2->first->changes -= genre3.first->changes;
        genre3.first->myGenre = &genre3;
        genre3.size = size1 + size2;
        genre2->first = nullptr;
        genre2->size = 0;
        genre1->first = nullptr;
        genre1->size = 0;
        genre3.first->changes++;
        GenreHash.insert(genreId3, genre3);
        GenreHash.findKey(genreId3)->first->myGenre=GenreHash.findKey(genreId3);
        return StatusType::SUCCESS;
    } else if (size1 < size2) {
        genre3.first = genre2->first;
        genre1->first->parent = genre3.first;
        genre1->first->changes -= genre3.first->changes;
        genre3.first->myGenre = &genre3;
        genre3.size = size1 + size2;
        genre2->first = nullptr;
        genre2->size = 0;
        genre1->first = nullptr;
        genre1->size = 0;
        genre3.first->changes++;

        GenreHash.insert(genreId3, genre3);
        GenreHash.findKey(genreId3)->first->myGenre=GenreHash.findKey(genreId3);
        return StatusType::SUCCESS;
    } else {
        return StatusType::FAILURE;
    }
}catch(std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> DSpotify::getSongGenre(int songId){
    if(songId <= 0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    if(!songHash.Contains(songId)) {
        return output_t<int>(StatusType::FAILURE);
    }
    try{
        Song* s = songHash.findKey(songId);
        while(s->parent != nullptr){
            s=s->parent;
        }
        return output_t<int>(s->myGenre->genre_id);
    } catch(std::bad_alloc&){
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }
    return output_t<int>(StatusType::FAILURE);
}

output_t<int> DSpotify::getNumberOfSongsByGenre(int genreId){
    if(genreId <= 0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    if(!GenreHash.Contains(genreId)) {
        return output_t<int>(StatusType::FAILURE);
    }
    Genre* g = GenreHash.findKey(genreId);
    return output_t<int>(g->size);
}

output_t<int> DSpotify::getNumberOfGenreChanges(int songId){
    if(songId <= 0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    if(!songHash.Contains(songId)) {
        return output_t<int>(StatusType::FAILURE);
    }
    int sum = 0;
    Song* s = songHash.findKey(songId);
    while(s != nullptr) {
        sum += s->changes;
        s = s->parent;
    }
    return output_t<int>(sum);
}
