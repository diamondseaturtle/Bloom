#include <stdlib.h>
#include <stdio.h> 
#include <string>
#include <iostream>
#include <cctype>
#include <sstream> 
#include <fstream>
#include <vector>

using namespace std;

#define MAGIC 9595

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

vector<char> bin(ifstream& file, int size) {
 // extract file
 vector<char> bytes(size); 
 if (file.read(reinterpret_cast<char*>(bytes.data()), size)) {
    return bytes;
 }
 
 return {};
}

vector<char> img_bin(ifstream& file, int size) {

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

    auto b = bin(file, size); 

    vecify(b);
}