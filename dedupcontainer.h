/* 
 * File:   dedupcontainer.h
 * Author: tbol
 *
 * Created on 27. November 2015, 15:31
 */

#ifndef DEDUPCONTAINER_H
#define	DEDUPCONTAINER_H

#include <vector>
#include <map>
#include <fstream>
#include "md5.h"

/**
 * class DedupContainer controls handling of a Deduplication Container File
 */
class DedupContainer {
    private:
        int bl_size;
        string ddc_path;
        map<string, int> ddc_table;
        
    public:
        DedupContainer(int b_size);
        void addFile(string path);
        
};

/*
 * ----------------------------------------------------------------------------
 * |                                HEADER                                    |
 * ----------------------------------------------------------------------------
 * |
 * |    
 * |
 * |
 * 
 */

#endif	/* DEDUPCONTAINER_H */

