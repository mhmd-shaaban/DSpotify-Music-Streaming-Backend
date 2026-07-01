// You can edit anything you want in this file.
// However you need to implement all public DSpotify function, as provided below as a template

#include "dspotify25b1.h"


DSpotify::DSpotify(){


}

DSpotify::~DSpotify(){

}

StatusType DSpotify::add_playlist(int playlistId){
     if(playlistId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if(my_lists.doesExist(playlistId)) {
        return StatusType::FAILURE;
    }
    try {
        shared_ptr<PlayList> toAdd = make_shared<PlayList> (playlistId);
        my_lists.addLeaf(playlistId, toAdd);
    }
    catch(const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;  
}

StatusType DSpotify::delete_playlist(int playlistId){
    if(playlistId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if(!my_lists.doesExist(playlistId)) {
        return StatusType::FAILURE;
    }
     try {
        shared_ptr<PlayList> l = *(my_lists.getData(playlistId));
        if((l->size() > 0)) {
            return StatusType::FAILURE;
        }
        my_lists.remove(playlistId);
        return StatusType::SUCCESS;
    }
    catch(const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType DSpotify::add_song(int songId, int plays){
    if(songId <= 0 || plays < 0) {
        return StatusType::INVALID_INPUT;
    }
    if(All_songs.doesExist(songId)) {
        return StatusType::FAILURE;
    }
    try {
        shared_ptr<Song> toAdd = make_shared<Song>(songId,plays);
        All_songs.addLeaf(songId, toAdd);
         return StatusType::SUCCESS;
    }
    catch(const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType DSpotify::add_to_playlist(int playlistId, int songId){
    if(songId <= 0 || playlistId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if((!All_songs.doesExist(songId)) || (!my_lists.doesExist(playlistId)) ) {
        return StatusType::FAILURE;
    }
    if(my_lists.getData(playlistId)->get()->id_songs.doesExist(songId)) {
                return StatusType::FAILURE;
    }
    try{
    shared_ptr<PlayList> listAdd = *my_lists.getData(playlistId);
    shared_ptr<Song> toAdd = *All_songs.getData(songId);
    listAdd.get()->id_songs.addLeaf(songId,toAdd);
    listAdd.get()->play_songs.addLeaf(myPair(All_songs.getData(songId)->get()->plays(),songId),toAdd);
    my_lists.getData(playlistId)->get()->changeSize(1);
    All_songs.getData(songId)->get()->raiseNum(1);
    return StatusType::SUCCESS;
    }
    catch(const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType DSpotify::delete_song(int songId){
    if(songId <= 0 ) {
        return StatusType::INVALID_INPUT;
    }
     if(!All_songs.doesExist(songId)) {
        return StatusType::FAILURE;
    }
    if(All_songs.getData(songId)->get()->NumLists() > 0 ) {
        return StatusType::FAILURE;
    }
    try {
        All_songs.remove(songId);
        return StatusType::SUCCESS;
    }
    catch(const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType DSpotify::remove_from_playlist(int playlistId, int songId){
    if(playlistId <=0 || songId <= 0 ) {
        return StatusType::INVALID_INPUT;
    }
    if((!All_songs.doesExist(songId)) || (!my_lists.doesExist(playlistId))) {
        return StatusType::FAILURE;
    }
    if(!my_lists.getData(playlistId)->get()->id_songs.doesExist(songId)) {
        return StatusType::FAILURE;
    }
    try {
    int p = All_songs.getData(songId)->get()->plays();
    my_lists.getData(playlistId)->get()->id_songs.remove(songId);
    my_lists.getData(playlistId)->get()->play_songs.remove(myPair(p,songId));
    my_lists.getData(playlistId)->get()->changeSize(-1);
    All_songs.getData(songId)->get()->raiseNum(-1);
    return StatusType::SUCCESS;
    }
    catch(const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> DSpotify::get_plays(int songId){
    if( songId <= 0 ) {
        return output_t<int> (StatusType::INVALID_INPUT);
    }
    if((!All_songs.doesExist(songId))) {
        return output_t<int> (StatusType::FAILURE);
    }
    try{
    output_t<int> num = All_songs.getData(songId)->get()->plays();
    return num;
    }
    catch(const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> DSpotify::get_num_songs(int playlistId){
    if( playlistId <= 0 ) {
        return output_t<int> (StatusType::INVALID_INPUT);
    }
    if((!my_lists.doesExist(playlistId))) {
        return output_t<int> (StatusType::FAILURE);
    }
    output_t<int> num = my_lists.getData(playlistId)->get()->size();
    return num;
}

output_t<int> DSpotify::get_by_plays(int playlistId, int plays){
    if(playlistId <=0 || plays < 0 ) {
        return output_t<int> (StatusType::INVALID_INPUT);
    }
    if((!my_lists.doesExist(playlistId)) || my_lists.getData(playlistId)->get()->size() == 0) {
        return output_t<int> (StatusType::FAILURE);
    }

    try {
        Node<myPair,shared_ptr<Song>>* Root = my_lists.getData(playlistId)->get()->play_songs.findRoot() ;
        Node<myPair,shared_ptr<Song>>* toRet;
        toRet = my_lists.getData(playlistId)->get()->play_songs.findNext(Root,myPair(plays,0));
    if(toRet == nullptr || toRet->m_data->get()->plays() < plays) {
        return output_t<int> (StatusType::FAILURE);
    }
    output_t<int> min = toRet->m_data->get()->getId();
    return min;
}
catch(const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType DSpotify::unite_playlists(int playlistId1, int playlistId2) {
    if (playlistId1 <= 0 || playlistId2 <= 0 || playlistId1 == playlistId2) {
        return StatusType::INVALID_INPUT;
    }

    if (!my_lists.doesExist(playlistId1) || !my_lists.doesExist(playlistId2)) {
        return StatusType::FAILURE;
    }
    try {
        shared_ptr<PlayList> p1 = *my_lists.getData(playlistId1);
        shared_ptr<PlayList> p2 = *my_lists.getData(playlistId2);
        if(p2.get()->size() == 0) {
            my_lists.remove(playlistId2);
            return StatusType::SUCCESS;
        }
        int size2 = p2->size();
        int* arr1 = new int[size2];
        p2.get()->id_songs.inOrderKeyArray(arr1,size2);
        for (int i = 0; i < size2; i++) 
        {
           StatusType res = add_to_playlist(playlistId1, arr1[i]);
            if(res == StatusType::SUCCESS ) {
                (*All_songs.getData(arr1[i]))->raiseNum(-1);
        }
        if (res == StatusType::ALLOCATION_ERROR) {
                delete[] arr1;
                return res;
            }
        if (res == StatusType::FAILURE) {
            (*All_songs.getData(arr1[i]))->raiseNum(-1);
        } 
        }
        delete[] arr1;
        my_lists.remove(playlistId2);
        return StatusType::SUCCESS;
}
    catch(const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}
