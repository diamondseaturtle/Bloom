#include <stdlib.h>
#include <stdio.h> 
#include <string>
#include <iostream>
#include <cctype>
#include <sstream> 
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;

#define MAGIC "XY"

typedef unsigned char uchar;
typedef unsigned int uint;

// hmmmmmmmmmmmm.
typedef struct rgb {
    uint r; 
    uint b;
    uint g;
} rgb, *prgb;

bool encode(ifstream& dfile, ifstream& ifile) {
    // twiddle bits
    return false;
}

bool decode(ifstream& ifile) {
    // somehow get the file from the image
    return false;
}

bool check(int dsize, int isize) {
    // does file fit into image?
    return dsize + sizeof(MAGIC) < isize / 3;
}

// Dude what version of cpp am i using
int file_size(ifstream& file) {
    file.seekg(0, ios::end); 
    auto size = file.tellg(); 
    file.seekg(0, ios::beg); 

    return size;
}

vector<uchar> bin(ifstream& file, int size) {
    vector<uchar> bytes(size); 
    if (file.read(reinterpret_cast<char*>(bytes.data()), size)) {
        return bytes;
    }

    return {};
}

vector<uchar> ppm_bin(ifstream& file, int size) {
    string magic;
    int w, h, max; 
    vector<char> bytes;

    file >> magic; 
    if (magic != "P6") {
        cout << magic << endl;
        goto error;
    }
    cout << "P6 detected" << endl; 

    file >> w >> h >> max; 
    assert (file.get() == '\n');
    if (max > 255) {
        cout << max << endl;
        goto error; // TODO: Don't do this
    }
    cout << "Img dims: " << w << " x " << h << endl;
    cout << "Max RGB: " << max << endl;

    return bin(file, w * h * 3); 

    error:
        cout << "Unable to read image" << endl; 
        return {};
}

template<class T>
void vecify(vector<T>& vec) {
    for (auto& v : vec) {
        cout << hex << static_cast<int>(v) << " "; 
    }

    cout << endl;
}

void usage(char* prog) {
    // not how it should work
    cout << "Usage: " << prog << " [options] [file.txt] [img.ppm]" << endl 
        << "    Options: " << endl << 
            "       -e     Encode message into image" << endl << 
            "       -d    Decode message from image" << endl;
}

int main(int argc, char* argv[]) {
    // need function 
    ifstream dfile(argv[1], ifstream::binary); 
    auto dsize = file_size(dfile); 
    cout << dsize << endl;
    auto d = bin(dfile, dsize); 
    vecify(d);

    ifstream ifile(argv[2], ifstream::binary);
    auto isize = file_size(ifile);
    cout << isize << endl;
    auto i = ppm_bin(ifile, isize); 
    vecify(i);

    if (!check(d.size(), i.size())) {
        cout << "Size error" << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}