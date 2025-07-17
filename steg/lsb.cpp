#include <stdlib.h>
#include <stdio.h> 
#include <string>
#include <iostream>
#include <cctype>
#include <sstream> 
#include <fstream>
#include <vector>
#include <cassert>
#include <iterator>

using namespace std;

#define MAGIC "XY" //tbd on usage!!!!

typedef unsigned char uchar;
typedef unsigned int uint;

template<class T>
void vecify(vector<T>& vec) {
    for (auto& v : vec) {
        cout << hex << static_cast<int>(v) << " "; 
    }

    cout << endl;
}

bool encode(const vector<uchar>& data, const vector<uchar>& img) {
    vector<uchar> out(img);
    int d = 0; 
    int i = 2; 

    for (; d < data.size(); d++, i += 3) {
        out[i] = data[d]; 
    }

    vecify(out);
    ofstream output_img; 
    int dims = 16; 
    int max = 255;
    output_img.open("output.ppm", std::ios::binary | std::ios::out);
    output_img << "P6\n16 16\n255\n";
    output_img.write(reinterpret_cast<char*>(out.data()), out.size());
    return true;
}

bool decode(const vector<uchar>& img) {
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
        cerr << magic << endl;
        return {};
    }
    cout << "P6 detected" << endl; 

    file >> w >> h >> max; 
    assert (file.get() == '\n');
    if (max > 255) {
        cerr << max << endl;
        return {}; 
    }

    cout << "Img dims: " << w << " x " << h << endl;
    cout << "Max RGB: " << max << endl;

    return bin(file, w * h * 3); 
}



void usage(char* prog) {
    // not how it should work
    cout << "Usage: " << prog << " [options] [file.txt] [img.ppm]" << endl 
        << "    Options: " << endl << 
            "       -e     Encode message into image" << endl << 
            "       -d    Decode message from image" << endl;
}

int main(int argc, char* argv[]) {
    // need function for reading inputs
    ifstream dfile(argv[1], ifstream::binary); 
    auto dsize = file_size(dfile); 
    cout << dsize << endl;
    auto d = bin(dfile, dsize); 
    if (d.empty()) {
        cerr << "Data file read error" << endl;
        return EXIT_FAILURE;
    }

    ifstream ifile(argv[2], ifstream::binary);
    auto isize = file_size(ifile);
    cout << isize << endl;
    auto i = ppm_bin(ifile, isize); 
    if (i.empty()) {
        cerr << "Image file read error" << endl;
        return EXIT_FAILURE;
    }

    if (!check(d.size(), i.size())) {
        cerr << "Data size " << d.size() << " too large for encoding into img size " << i.size() << endl;
        return EXIT_FAILURE;
    }
    encode(d, i);
    vecify(d);
    vecify(i);
    return EXIT_SUCCESS;
}