/* 
 * File:   main.cpp
 * Author: Toni.Bolduan
 *
 * Created on 12. November 2015, 08:52
 */

#include <map>
#include <string>
#include <string.h>
#include <stdint.h>

#include "md5.h"
#include "buildfile.h"
#include "dedupcontainer.h"


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    
    BuildFile bf("C:\\Users\\toni.bolduan\\desktop\\abc.dat", 512);
    //bf.printBuildfile();
    
    
    DedupContainer dc(512);
    
    dc.addFile("C:\\Users\\toni.bolduan\\desktop\\abc.dat");
    //dc.addFile("C:\\Users\\toni.bolduan\\desktop\\abc2.dat");
    
    dc.listFiles();
            
    cout << dc.countBlocks() << endl;
    
    dc.restoreFile("C:\\Users\\toni.bolduan\\desktop\\abc.dat", "C:\\Users\\toni.bolduan\\desktop\\abc5.dat");
    
    BuildFile bf3("C:\\Users\\toni.bolduan\\desktop\\abc5.dat", 512);
    
    return 0;
}

