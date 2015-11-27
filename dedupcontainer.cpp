#include "dedupcontainer.h"

/**
 * Default Constructor
 * @param b_size = blocksize of the container
 */
DedupContainer::DedupContainer(int b_size) {
    this->bl_size = b_size;
}

void DedupContainer::addFile(string path) {
    
    // load file
    ifstream ifs(path.c_str(), ios::binary | ios::in);
    // for each data block sizeof bl_size do hash 
    
    
    
    // write data block to file and increment position_counter
    
    ifs.close();
}