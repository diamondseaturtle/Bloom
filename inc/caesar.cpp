#include <stdlib.h>
#include <stdio.h> 
#include <string>
#include <iostream>
#include <cctype>
#include <sstream> 
#include <fstream>

using namespace std; 

namespace Caesar {

bool encode(string& ptext, int key) {
    for (auto& c : ptext) {
        if (isalpha(c)) {
            c = (tolower(c) + key - 'a') % 26 + 'a'; 
        }
    }
    return true;
}

bool decode(string& ctext, int key) {
    return encode(ctext, (-key % 26)); // lol
}

// i am avoiding classes for now 
// Perhaps a struct?

void usage(char* prog) {
    cout << "Usage: " << prog << " [options] [file.txt] [shift]" << endl 
        << "    Options: " << endl << 
            "       -e     Encode plaintext" << endl << 
            "       -d    Decode ciphertext" << endl;
} 
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        Caesar::usage(argv[0]); 
        return 0;
    }

    ifstream t(argv[2]);
    stringstream buf;
    buf << t.rdbuf(); 

    string option = argv[1];
    string text = buf.str(); 
    int key = atoi(argv[3]);

    if (option == "-e") {
        cout << "Encoding " << text << endl;
        Caesar::encode(text, key); 
        cout << text << endl;
    } else {
        cout << "Decoding " << text << endl; 
        Caesar::decode(text, key); 
        cout << text << endl;
    }
}