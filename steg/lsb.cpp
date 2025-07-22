#include <stdlib.h>
#include <stdio.h> 
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <cassert>

using namespace std;

#define CHECK "XY" //tbd on usage!!!!

typedef unsigned char byte;

typedef enum img_type {
    PPM, 
    UNKNOWN
} img_type;

const vector<string> magics {
    "P6", 
    "UNKNOWN"
};

typedef struct ppm_data{
    int w; 
    int h; 
    int max; 
    vector<byte> data;
} ppm_data;

typedef struct img {
    img_type type; 
    int datasize;
    ppm_data ppm;
} img; // screw your variants (to be heap allocated)

typedef struct txt {
    int size; 
    vector<byte> data;
} txt; // redundant fields :heart_eyes:

img read_img(const char* filename);

// debug ---------------------------------------------------
template<class T>
void vecify(vector<T>& vec) {
    for (auto& v : vec) {
        cout << hex << static_cast<int>(v) << " "; 
    }

    cout << endl;
}

// utils ------------------------------------------------------------------
bool check(int src, int dst) {
    return src + sizeof(CHECK) < dst / 3;
}

string strline(FILE* file, char delim) {
    char* buf = nullptr; 
    string line;
    int c; 
    
    do { // ah yes bad style
        c = fgetc(file); 
        line += c;
    } while (c != delim); 

    line.pop_back();
    return line;
}

// "just stat it"
int file_size(FILE* file) {
    fseek(file, 0, SEEK_END); 
    int size = ftell(file);
    rewind(file);

    return size;
}

// ppm ops ------------------------------------------------
bool decode_ppm(const char* filename) {
    vector<byte> out;
    img image = read_img(filename); 

    for (int i = 2; i < image.datasize && image.ppm.data[i]; i += 3) {
        out.push_back(image.ppm.data[i]);
    }

    FILE* output = fopen("msg.txt", "wb");
    fwrite(out.data(), sizeof(byte), out.size() * sizeof(byte), output);
    fclose(output);
    return true;
}

bool encode_ppm(const txt& src, const ppm_data& ppm) {
    vector<byte> out(ppm.data);
    int s = 0; 
    int i = 2; 

    for (int s = 0, i = 2; s < src.data.size(); s++, i += 3) {
        out[i] = src.data[s]; 
    }

    vecify(out);

    FILE* output = fopen("output.ppm", "wb"); 
    string header = magics[PPM] + '\n' + to_string(ppm.w) + ' ' + to_string(ppm.h) + '\n' + to_string(ppm.max) + '\n';
    fwrite(header.data(), sizeof(byte), header.size() * sizeof(byte), output);
    fwrite(out.data(), sizeof(byte), out.size() * sizeof(byte), output);
    fclose(output);
    
    decode_ppm("output.ppm");
    return true;
}

bool set_ppm(FILE* file, img& image) {
    ppm_data ppm = {-1, -1, -1, {}};

    ppm.w = stoi(strline(file, ' '));
    ppm.h = stoi(strline(file, '\n'));
    ppm.max = stoi(strline(file, '\n'));
    // error handle needed

    cout << "Img dims: " << ppm.w << " x " << ppm.h << endl;
    cout << "Max RGB: " << ppm.max << endl;

    ppm.data.resize(ppm.w * ppm.h * 3);
    fread(&ppm.data[0], sizeof(byte), ppm.data.size() * sizeof(byte), file);
    
    image.datasize = ppm.data.size();
    image.ppm = ppm;

    return true;
}

// readers -----------------------------------------------------------
txt read_txt(const char* filename) {
    txt input = {-1, {}};

    FILE* file = fopen(filename, "rb"); 
    if (!file) {
        fclose(file);
        return input;
    }
    input.size = file_size(file) + 1; 
    input.data.resize(input.size);
    fread(&input.data[0], sizeof(byte), input.size * sizeof(byte), file);
    fclose(file);

    input.data[input.size - 1] = '\0';

    return input;
}

img read_img(const char* filename) {
    img image = {UNKNOWN, {}};

    FILE* file = fopen(filename, "rb"); 
    if (!file) {
        fclose(file);
        return image; 
    }

    string magic = strline(file, '\n');
    cout << magic << endl;
    if (magic == "P6") {
        if (!set_ppm(file, image)) {
            fclose(file);
            return image;
        }
        image.type = PPM; 
    } 
    fclose(file);

    return image;
}

// main --------------------------------------------------------------------
void usage(char* prog) {
    // not how it should work
    cout << "Usage: " << prog << " [options] [file.txt] [img.ppm]" << endl 
        << "    Options: " << endl << 
            "       -e     Encode message into image" << endl << 
            "       -d    Decode message from image" << endl;
}

int main(int argc, char* argv[]) {
    txt input = read_txt(argv[1]); 
    if (input.size < 0) {
        cerr << "input file read error" << endl;
        return EXIT_FAILURE;
    }
    cout << input.size << endl;

    img image = read_img(argv[2]); 
    if (image.type == UNKNOWN) {
        cerr << "image file read error" << endl;
        return EXIT_FAILURE;
    }
    cout << image.datasize << endl;

    if (!check(input.size, image.datasize)) {
        cerr << "input size " << input.size << " too large for encoding into img size " << image.datasize << endl;
        return EXIT_FAILURE;
    }
    
    if (image.type == PPM) {
        encode_ppm(input, image.ppm);
    }

    vecify(input.data);
    vecify(image.ppm.data);
    return EXIT_SUCCESS;
}