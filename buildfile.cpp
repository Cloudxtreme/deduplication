#include "buildfile.h"

BuildFile::BuildFile(string path) {

    blocksize = 64;
    
    f_path = path;
    f_hash = MD5().getHexDigest(path);
    
    ifstream is(path.c_str(), ios::binary | ios::in);
    
    uint8_t block[64] = {};
    
    while (is.read((char *)block, 64)) {
        block_hashes.push_back(MD5().getHexDigest(block));
    }
    
    if (is.gcount() > 0) {
        block_hashes.push_back(MD5().getHexDigest(block));
    }
    
    is.close();
}

BuildFile::BuildFile(string path, int blocksize) {
    
    this->blocksize = blocksize;
    
    f_path = path;
    f_hash = MD5().getHexDigest(path);
    
    ifstream is(path.c_str(), ios::binary | ios::in);
    
    uint8_t block[blocksize] = {};
    
    while (is.read((char *)block, blocksize)) {
        block_hashes.push_back(MD5().getHexDigest(block, blocksize));
    }
    
    if (is.gcount() > 0) {
        block_hashes.push_back(MD5().getHexDigest(block, blocksize));
    }
    
    is.close();
}


string BuildFile::getHash() {
    
    return f_hash;
    
}

string BuildFile::getFilePath() {
    return f_path;
}

vector<string> BuildFile::getHashes() {
    return this->block_hashes;
}

void BuildFile::printBuildfile() {
    
    cout << " ----------------------------------------------------- " << endl;
    cout << "|                      Build-File                     |" << endl;
    cout << " ----------------------------------------------------- " << endl;
    cout << "|                                                     |" << endl;
    cout << "| File-Information:                                   |" << endl;
    cout << " ----------------------------------------------------- " << endl;
    cout << "|                                                     |" << endl;
    cout << "| File: \t" << f_path << endl;
    cout << "| File-Hash:\t" << f_hash << "      |" << endl;
    cout << "|                                                     |" << endl;
    cout << " ----------------------------------------------------- " << endl << "|" << endl;
    cout << "| Block-Information:   \t\t" << this->blocksize << "\t\t      |" << endl;
    cout << " ----------------------------------------------------- " << endl << "|" << endl;
    for (vector<string>::iterator it = this->block_hashes.begin(); it != block_hashes.end(); it++) {
        cout << "| " << it-block_hashes.begin() << ": \t\t" << *it << "      |" << endl;
    }
    cout << "|                                                     |" << endl;
    cout << " ----------------------------------------------------- " << endl;
    
}