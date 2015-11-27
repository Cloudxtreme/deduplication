#include <iostream>
#include "dedupcontainer.h"

DedupContainer::DedupContainer(int bl_size) {
    this->blocksize = bl_size;
}

void DedupContainer::addFile(string path) {
    
    // BuildFile erstellen
    buildfiles.push_back(BuildFile(path, this->blocksize));
    
    // Table füllen
    ifstream is(path.c_str(), ios::binary | ios::in);
    
    uint8_t block[blocksize] = {};
    
    while (is.read((char*)block, blocksize)) {
        
        table[MD5().getHexDigest(block, blocksize)] = (uint8_t(*)[512])block;
    }
    
    if (is.gcount() > 0) {
        table[MD5().getHexDigest(block, blocksize)] = (uint8_t(*)[512])block;
        
    }
    
    is.close();
    
}

void DedupContainer::listFiles() {
    for (vector<BuildFile>::iterator it = buildfiles.begin(); it != buildfiles.end(); it++) {
        cout << ((BuildFile)*it).getFilePath() << endl;
    }
}

int DedupContainer::countBlocks() {
    return table.size();
}

void DedupContainer::restoreFile(string path_in, string path_out) {
    
    for (vector<BuildFile>::iterator it = buildfiles.begin(); it != buildfiles.end(); it++) {
        BuildFile bf = ((BuildFile)*it);
        if (bf.getFilePath().compare(path_in) == 0) {
            
            cout << "File gefunden" << endl;
            ofstream os(path_out.c_str(), ios::binary | ios::out);
            
            vector<string> t_hashes = bf.getHashes();
            
            for(vector<string>::iterator it2 = t_hashes.begin(); it2 != t_hashes.end(); it2++) {
                              
                // ########################### noch fehlerhaft
                string t_hash = (string)*it2; cout << t_hash << endl;
                uint8_t(*t_block)[512] = (uint8_t(*)[512])table[t_hash];
                os.write(((char*)t_block), this->blocksize);
                
            }
            
            os.close();
            break;
        }
    }
}