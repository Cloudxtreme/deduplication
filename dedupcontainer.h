/* 
 * File:   dedupcontainer.h
 * Author: Toni.Bolduan
 *
 * Created on 26. November 2015, 12:21
 */

#ifndef DEDUPCONTAINER_H
#define	DEDUPCONTAINER_H


#include <string>
#include <map>
#include <vector>
#include <stdint.h>
#include <fstream>
#include "buildfile.h"

using namespace std;

class DedupContainer {

    private:    
        int blocksize;
        vector<BuildFile> buildfiles;
        map<string, uint8_t(*)[512]> table;
        
    public:
        DedupContainer(int bl_size);
        void addFile(string path);
        void listFiles();
        int countBlocks();
        void restoreFile(string path_in, string path_out);
        
        
};


#endif	/* DEDUPCONTAINER_H */

