#include <iostream>
#include <fstream>
#include <string.h>
#include "md5.h"

// Constants for MD5-Transformation routine.
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

// F, G, H and I are basic MD5 functions.
inline uint32_t MD5::F(uint32_t x, uint32_t y, uint32_t z) {
  return x&y | ~x&z;
}
 
inline uint32_t MD5::G(uint32_t x, uint32_t y, uint32_t z) {
  return x&z | y&~z;
}
 
inline uint32_t MD5::H(uint32_t x, uint32_t y, uint32_t z) {
  return x^y^z;
}
 
inline uint32_t MD5::I(uint32_t x, uint32_t y, uint32_t z) {
  return y ^ (x | ~z);
}
 
// rotate_left rotates x left n bits.
inline uint32_t MD5::rotate_left(uint32_t x, int n) {
  return (x << n) | (x >> (32-n));
}
 
// FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
// Rotation is separate from addition to prevent recomputation.
inline void MD5::FF(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) {
  a = rotate_left(a+ F(b,c,d) + x + ac, s) + b;
}
 
inline void MD5::GG(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) {
  a = rotate_left(a + G(b,c,d) + x + ac, s) + b;
}
 
inline void MD5::HH(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) {
  a = rotate_left(a + H(b,c,d) + x + ac, s) + b;
}
 
inline void MD5::II(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) {
  a = rotate_left(a + I(b,c,d) + x + ac, s) + b;
}

using namespace std;

MD5::MD5() {
    init();
}


MD5::MD5(const char* path) {
    
    ifstream is(path, ios::binary | ios::in | ios::ate);
    count = is.tellg();
    is.seekg(0, is.beg);
    
    // MD5 STARTS HERE
    // Initialization
    init();
       
    // Update state for each 64-Byte Block of file
    while (is.read((char *)data, BLOCKSIZE)) {
        update();
        memset(data, 0, sizeof(data));
    }
    
    addPadding(is.gcount());
    
    // MD5 ENDS HERE
    
    is.close();
    
}

// Function is helper function and needs to be placed at helper function block below
void MD5::addPadding(int length) {
    count *= 8;
    if (length > 0) {
        if (64-length > 8) {
            // pad out in the same block
            uint8_t byte = 0x80;
            memcpy(&data[length], &byte, 1);    // maybe wrong memcpy
            memcpy(&data[56], &count, 8);       // maybe wrong memcpy
            update();
        }
        else {
            // pad out in the same AND following Block
            uint8_t byte = 0x80;
            memcpy(&data[length], &byte, 1);    // maybe wrong memcpy
            update();
            memset(&data, 0, sizeof(data));
            memcpy(&data[56], &count, 8);       // maybe wrong memcpy
            update();
        }
    }
    else {
        uint8_t PADDING[BLOCKSIZE] = {0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        
        //count = 65537;
        
        memcpy(&PADDING[56], &count, 8);        // maybe wrong memcpy
        //uint8_t counter[8] = {};
        //encode(counter, count);
        //for (int i=0; i<8; i++) {
        //    memcpy(&PADDING[56+i], &counter[i], 1);
        //}
        memcpy(&data, &PADDING, BLOCKSIZE);
        update();
    }
    
}



// -----------------------------------------------------------------------------
//
// MD5 functions


void MD5::init() {
    memset(data, 0, sizeof(data));
        
    state[0] = 0x67452301;
    state[1] = 0xefcdab89;
    state[2] = 0x98badcfe;
    state[3] = 0x10325476;
    
    for (int i=0; i<16; i++)
        digest[i] = 0;
}

void MD5::update() {
    transform();
}

void MD5::transform() {
    uint32_t a = state[0], b = state[1], c = state[2], d = state[3], x[16];
    
    decode(x, data, BLOCKSIZE);
    
    /* Round 1 */
    FF (a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
    FF (d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
    FF (c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
    FF (b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
    FF (a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
    FF (d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
    FF (c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
    FF (b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
    FF (a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
    FF (d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
    FF (c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
    FF (b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
    FF (a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
    FF (d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
    FF (c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
    FF (b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

    /* Round 2 */
    GG (a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
    GG (d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
    GG (c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
    GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
    GG (a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
    GG (d, a, b, c, x[10], S22,  0x2441453); /* 22 */
    GG (c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
    GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
    GG (a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
    GG (d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
    GG (c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
    GG (b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
    GG (a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
    GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
    GG (c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
    GG (b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

    /* Round 3 */
    HH (a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
    HH (d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
    HH (c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
    HH (b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
    HH (a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
    HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
    HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
    HH (b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
    HH (a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
    HH (d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
    HH (c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
    HH (b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
    HH (a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
    HH (d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
    HH (c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
    HH (b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */

    /* Round 4 */
    II (a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
    II (d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
    II (c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
    II (b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
    II (a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
    II (d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
    II (c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
    II (b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
    II (a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
    II (d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
    II (c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
    II (b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
    II (a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
    II (d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
    II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
    II (b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;

    // Zeroize sensitive information.
    memset(x, 0, sizeof x);
}

// -----------------------------------------------------------------------------
//
// helper functions

/**
 * prints out Bit-Order of a Byteblock
 * @param block - data represented as an array of bytes
 * @param length - length of array
 */
void MD5::printDataBits(uint8_t block[], int length) {
    
    for (int i=0; i<length; i++) { 
        for (int j=0; j<8; j++) 
            ((block[i] << j) & 0x80) ? (cout << 1) : (cout << 0);
        cout << endl;
    }
    cout << endl;
}

/**
 * 
 * @param value
 */
void MD5::printDataBits(uint64_t value) {
    
    for (int i=0; i<64; i++) {
        ((value << i) & 0x8000000000000000) ? (cout << 1) : (cout << 0);
    }
    cout << endl;    
}

void MD5::decode(uint32_t output[], const uint8_t input[], int len) {
    for (unsigned int i = 0, j = 0; j < len; i++, j += 4)
        output[i] = ((uint32_t)input[j]) | (((uint32_t)input[j+1]) << 8) |
          (((uint32_t)input[j+2]) << 16) | (((uint32_t)input[j+3]) << 24);
}

void MD5::encode(uint8_t output[], const uint32_t input[], int len)
{
  for (int i = 0, j = 0; j < len; i++, j += 4) {
    output[j] = input[i] & 0xff;
    output[j+1] = (input[i] >> 8) & 0xff;
    output[j+2] = (input[i] >> 16) & 0xff;
    output[j+3] = (input[i] >> 24) & 0xff;
  }
}

void MD5::encode(uint8_t output[], const uint64_t input) {
    output[7] = input & 0xff;
    output[6] = (input >> 8) & 0xff;
    output[5] = (input >> 16) & 0xff;
    output[4] = (input >> 24) & 0xff;
    output[3] = (input >> 32) & 0xff;
    output[2] = (input >> 40) & 0xff;
    output[1] = (input >> 48) & 0xff;
    output[0] = (input >> 56) & 0xff;
}


string MD5::getHexDigest() {
    
    encode(digest, state, 16);
    
    char buf[33];
    for (int i=0; i<16; i++)
        sprintf(buf+i*2, "%02x", digest[i]);
    buf[32]=0;
 
    return std::string(buf);
}

string MD5::getHexDigest(uint8_t data[MD5::BLOCKSIZE]) {
    init();
    memcpy(&this->data, data, BLOCKSIZE);
    
    int cnt = 0;
    for (int i=0; i<64; i++)
        if (data[i] != 0x00)
            cnt = i+1;
    
            
    count = cnt;
    
    if (cnt == 64) {
        cnt = 0;
        update();
    }
    
    addPadding(cnt);
    
    return getHexDigest();
    
}

string MD5::getHexDigest(string path) {
    ifstream is(path.c_str(), ios::binary | ios::in | ios::ate);
    count = is.tellg();
    is.seekg(0, is.beg);
    
    // MD5 STARTS HERE
    // Initialization
    init();
       
    // Update state for each 64-Byte Block of file
    while (is.read((char *)data, BLOCKSIZE)) {
        update();
        memset(data, 0, sizeof(data));
    }
    
    addPadding(is.gcount());
    
    // MD5 ENDS HERE
    
    is.close();
    return getHexDigest();
}

/**
 * 
 * @param data the data Block to be hashed
 * @param blocksize must be a multiple of 64
 * @return string representation of the hash
 */
string MD5::getHexDigest(uint8_t data[], int blocksize) {
    
    if (blocksize == 64)
        return getHexDigest(data);
    
    init();
 
    int cnt = blocksize/BLOCKSIZE;
 
    int dat_len = strlen((char*)data);
    count = dat_len;    
 
        
    for (int i=0; i<cnt; i++) {
        if (dat_len < BLOCKSIZE ) {
            memcpy(&this->data, &data[i*BLOCKSIZE], dat_len);
            break;
        }
        memcpy(&this->data, &data[i*BLOCKSIZE], BLOCKSIZE);
        update();
        memset(this->data, 0, sizeof(this->data));
        dat_len -= BLOCKSIZE;
    }
    
    addPadding(dat_len);
    
    return getHexDigest();
}