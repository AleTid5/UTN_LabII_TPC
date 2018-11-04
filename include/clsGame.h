#ifndef CLSGAME_H
#define CLSGAME_H

#include <clsBug.h>

class clsGame
{
    public:
    int enemiesKilled;
    int evolutionEnergy;
    int life;
    int time;
    int enemies[36][2];
    void save(const char*, const char*);
    void read(const char*, const char*);
    bool wasRead = false;

    protected:

    private:
};

#endif // CLSGAME_H
