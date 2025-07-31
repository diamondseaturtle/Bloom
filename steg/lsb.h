#ifndef _LSB_H_
#define _LSB_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define CHECK "XY" //tbd on usage!!!!

typedef unsigned char byte;

typedef enum img_type {
    PPM, 
    UNKNOWN
} img_type;

typedef struct ppm_data{
    int w; 
    int h; 
    int max;  
    byte* data;
} ppm_data;

typedef struct img {
    img_type type; 
    int datasize;
    void* data;
} img; // screw your variants (to be heap allocated)

typedef struct txt {
    int size; 
    byte* data;
} txt; // redundant fields :heart_eyes:

const char* magics[] = {
    "P6", 
    "UNKNOWN"
};

// utils --------------------------
void bprintf(const byte* data); 
bool check(int src, int dst); 
char* strline(FILE* file, char delim); 
char* strapp(char* src, char* tail); 
int file_size(FILE* file); 
void usage(char* prog); 

// ppm ops (to be moved into own module) ---------------- 
bool decode_ppm(const char* filename); 
bool encode_ppm(const txt* src, const ppm_data* ppm); 
bool set_ppm(FILE* file, img* image); 

// readers -----------------------------
txt* read_txt(const char* filename);
img* read_img(const char* filename); 

#endif // _LSB_H_ 