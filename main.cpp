/* 
 * File:   main.cpp
 * Author: Toni.Bolduan
 *
 * Created on 12. November 2015, 08:52
 */

#include <iostream>

#include "md5.h"
#include "dedupcontainer.h"


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    DedupContainer *dc = new DedupContainer(512);
    
    if (argc <= 1) {
        cout << "ddc [-a path] [-c dst] [-l src] [-r file dst]" << endl;
        cout << "\t-c : create deduplication container file" << endl;
        cout << "\t-l : load deduplication container file" << endl;
        cout << "\t-a : add file to container" << endl;
        cout << "\t-r : restore file from Container" << endl;
    }
    
    dc->addFile("C:\\Users\\tbol\\Desktop\\abc.dat");
    
    delete dc;
}

