#include <stdlib.h>
#include <stdio.h> 
#include <string>
#include <iostream>
#include <cctype>
#include <sstream> 
#include <fstream>

#include "caesar.cpp"

using namespace std; 
//using namespace Vigenere;


namespace Vigenere {
bool Encode(string& ptext, string& key) {
    for (int i = 0; i < ptext.length(); i++) {
        string code = string(1, tolower(ptext[i]));
        Caesar::Encode(code, key[i % key.length()] - 'a');
        ptext[i] = code[0];
    }
    return true;
}

bool Decode(string& ctext, string& key) {
}

void Usage(char* prog) {
    cout << "Usage: " << prog << " [options] [file.txt] [keyword]" << endl 
        << "    Options: " << endl << 
            "       -e     Encode plaintext" << endl << 
            "       -d    Decode ciphertext" << endl;
}
} 

int main(int argc, char* argv[]) {
    if (argc != 4) {
        Vigenere::Usage(argv[0]); 
        return 0;
    }

    ifstream t(argv[2]);
    stringstream buf;
    buf << t.rdbuf(); 

    string option = argv[1];
    string text = buf.str(); 
    string key = argv[3];

    if (option == "-e") {
        cout << "Encoding " << text << endl;
        Vigenere::Encode(text, key); 
        cout << text << endl;
    } else {
        cout << "Decoding " << text << endl; 
        // Decode(text, key); 
        cout << text << endl;
    }
}