#ifndef CLSGAMEDATA_H
#define CLSGAMEDATA_H

#include <stdio.h>
#include <clsBug.h>

class clsGameData
{
    public:
    int enemiesKilled = 0;
    int evolutionEnergy = 0;
    int life = 100;
    int time = 0;
    int enemies[36][2];
    int bossLife;
    char playierName[5];
    bool wasRead = false;
    void arrangedSave(const char*, const char*);
    void save(const char*, const char*);
    void read(const char*, const char*);
    void read(const char*, const char*, unsigned int);
    void removeFile(const char*);

    protected:

    private:
};

#endif // CLSGAMEDATA_H
