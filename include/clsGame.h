#ifndef CLSGAME_H
#define CLSGAME_H

#include <stdio.h>
#include <clsBug.h>

class clsGame
{
    public:
    int enemiesKilled;
    int evolutionEnergy;
    int life;
    int time;
    int enemies[36][2];
    bool wasRead = false;
    void save(const char*, const char*);
    void read(const char*, const char*);
    void removeFile(const char*);

    protected:

    private:
};

#endif // CLSGAME_H
