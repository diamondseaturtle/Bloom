#include "lsb.h"

void bprintf(const byte* data) {
    
}

bool check(int src, int dst) {
    return false;
}

int file_size(FILE* file) {
    return 0;
}

bool decode_ppm(const char* filename) {
    return false;
}

bool encode_ppm(const txt* src, const ppm_data* ppm) {
    return false;
}

txt* read_txt(const char* filename) {
    return NULL;
}

img* read_img(const char* filename) {
    return NULL;
}

int main(int argc, char* argv[]) {
    txt* input = read_txt(argv[1]); 
    if (input->size < 0) {
        fprintf(stderr, "input file read error\n");
        return EXIT_FAILURE;
    }
    printf("%d\n", input->size);

    img* image = read_img(argv[2]); 
    if (image->type == UNKNOWN) {
        fprintf(stderr, "image file read error\n");
        return EXIT_FAILURE;
    }
    printf("%d\n", image->datasize);

    if (!check(input->size, image->datasize)) {
        fprintf(stderr, "input size %d too large fpr encoding into img size %d\n", input->size, image->datasize);
        return EXIT_FAILURE;
    }
    
    if (image->type == PPM) {
        ppm_data* ppm = (ppm_data*) image->data;
        encode_ppm(input, ppm);
        bprintf(ppm->data);
    }

    bprintf(input->data);
    return EXIT_SUCCESS;
}