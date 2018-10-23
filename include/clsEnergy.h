#ifndef CLSENERGY_H
#define CLSENERGY_H
#include <clsScene.h>

class clsEnergy : public clsScene
{
    public:
        clsEnergy(unsigned int life);
        void initialize(clsScreen*);
        void updateStatusBar(clsScreen*, clsScene*, unsigned int);
        unsigned int getDamage();
        int getEvolution();
        unsigned int getPlusEnergy();
        int getLife();
        void setEvolution(int);
        void setLife(int);

    protected:

    private:
        int life;
        int evolution;
        unsigned const int damage = 25;
        unsigned const int plusEnergy = 10;
};

#endif // CLSENERGY_H
