#include <stdlib.h>
#include <stdio.h> 
#include <string>
#include <iostream>
#include <cctype>
#include <sstream> 
#include <fstream>

using namespace std;

bool Encode() {
// twiddle bits
}

bool Decode() {
// somehow get the file from the image
}

bool Check() {
// does file fit into image?
}

int MBits() {
 // extract msg file bits
}

int IBits() {
// extract image bits
}

void Usage(char* prog) {
    // not how it should work
    cout << "Usage: " << prog << " [options] [file.txt] [img.png/jpg]" << endl 
        << "    Options: " << endl << 
            "       -e     Encode message into image" << endl << 
            "       -d    Decode message from image" << endl;
}

int main(int argc, char* argv[]) {

}