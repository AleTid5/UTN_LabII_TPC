#include "clsGame.h"

void clsGame::save(const char * filename, const char * mode) {
    FILE * file;
    file = fopen(filename, mode);
    fwrite(this, sizeof * this, 1, file);
    fclose(file);
}

void clsGame::read(const char * filename, const char * mode) {
    FILE * file;
    file = fopen(filename, mode);
    this->wasRead = (bool) fread(this, sizeof * this, 1, file);
    fclose(file);
}
