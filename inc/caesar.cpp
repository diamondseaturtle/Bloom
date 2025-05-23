#include <stdlib.h>
#include <stdio.h> 
#include <string>
#include <iostream>
#include <cctype>
#include <sstream> 
#include <fstream>

using namespace std; 

namespace Caesar {

bool Encode(string& ptext, int key) {
    for (auto& c : ptext) {
        if (isalpha(c)) {
            c = (tolower(c) + key - 'a') % 26 + 'a'; 
        }
    }
    return true;
}

bool Decode(string& ctext, int key) {
    return Encode(ctext, (-key % 26)); // lol
}

// i am avoiding classes for now 
// Perhaps a struct?

void Usage(char* prog) {
    cout << "Usage: " << prog << " [options] [file.txt] [shift]" << endl 
        << "    Options: " << endl << 
            "       -e     Encode plaintext" << endl << 
            "       -d    Decode ciphertext" << endl;
} 
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        Caesar::Usage(argv[0]); 
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
        Caesar::Encode(text, key); 
        cout << text << endl;
    } else {
        cout << "Decoding " << text << endl; 
        Caesar::Decode(text, key); 
        cout << text << endl;
    }
}