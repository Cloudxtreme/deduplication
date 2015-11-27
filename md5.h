/* 
 * File:   md5.h
 * Author: Toni.Bolduan
 *
 * Created on 12. November 2015, 08:53
 */

#ifndef MD5_H
#define	MD5_H

#include <stdint.h>
#include <string>

using namespace std;

class MD5 {
    
    public:
        const static int BLOCKSIZE = 64;
    
    private:        
        
        uint8_t data[BLOCKSIZE];
        uint32_t state[4];
        uint64_t count;   
        uint8_t digest[16];
        
        // MD5 functions
        void init();
        void update();
        void transform();
        void addPadding(int length);
        
        // helper functions
        void printDataBits(uint8_t block[], int length);
        void printDataBits(uint64_t value);
        static void decode(uint32_t output[], const uint8_t input[], int len);
        static void encode(uint8_t output[], const uint32_t input[], int len);
        static void encode(uint8_t output[], const uint64_t input);
        
        // low level logic operations
        static inline uint32_t F(uint32_t x, uint32_t y, uint32_t z);
        static inline uint32_t G(uint32_t x, uint32_t y, uint32_t z);
        static inline uint32_t H(uint32_t x, uint32_t y, uint32_t z);
        static inline uint32_t I(uint32_t x, uint32_t y, uint32_t z);
        static inline uint32_t rotate_left(uint32_t x, int n);
        static inline void FF(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
        static inline void GG(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
        static inline void HH(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
        static inline void II(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
        
    public:
        
        MD5();
        MD5(const char * path);
        string getHexDigest();
        string getHexDigest(uint8_t data[BLOCKSIZE]);
        string getHexDigest(string path);
        string getHexDigest(uint8_t data[], int blocksize);
        
};

#endif	/* MD5_H */

