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

#define MAGIC "XY95"

typedef unsigned char uchar;

bool encode() {
    // twiddle bits
    return false;
}

bool decode() {
    // somehow get the file from the image
    return false;
}

bool check(const string& msg, const string& img) {
    // does file fit into image?
    return false;
}

// Dude what version of cpp am i using
int file_size(ifstream& file) {
    file.seekg(0, ios::end); 
    auto size = file.tellg(); 
    file.seekg(0, ios::beg); 

    return size;
}

vector<uchar> bin(ifstream& file, int size) {
    // extract file
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
        cout << "Incorrect img file format" << endl; 
        return {};
}

template<class T>
void vecify(vector<T>& vec) {
    for (auto& v : vec) {
        cout << hex << static_cast<int>((v)) << " "; 
    }

    cout << endl;
}

void usage(char* prog) {
    // not how it should work
    cout << "Usage: " << prog << " [options] [file.txt] [img.png/jpg]" << endl 
        << "    Options: " << endl << 
            "       -e     Encode message into image" << endl << 
            "       -d    Decode message from image" << endl;
}

int main(int argc, char* argv[]) {
    // error check this 
    ifstream file(argv[1], ifstream::binary); 
    auto size = file_size(file); 
    cout << size << endl;

    auto b = ppm_bin(file, size); 

    vecify(b);
}