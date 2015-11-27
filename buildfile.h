/* 
 * File:   buildfile.h
 * Author: Toni.Bolduan
 *
 * Created on 17. November 2015, 11:48
 */

#ifndef BUILDFILE_H
#define	BUILDFILE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdint.h>
#include "md5.h"

using namespace std;

class BuildFile {
    
    private:
        string f_path;
        string f_hash;
        vector<string> block_hashes;
        int blocksize;
        
    public:
        BuildFile(string path);
        BuildFile(string path, int blocksize);
        string getHash();
        string getFilePath();
        vector<string> getHashes();
        void printBuildfile();
        
};



#endif	/* BUILDFILE_H */

