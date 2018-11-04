#ifndef CLSENERGY_H
#define CLSENERGY_H
#include <clsScene.h>

class clsEnergy : public clsScene
{
    public:
        clsEnergy(unsigned int life);
        void initialize(clsScreen*);
        void updateStatusBar(clsScreen*, clsScene*, unsigned int);
        int getEvolution();
        int getLife();
        unsigned int getDamage();
        unsigned int getPlusEnergy();
        void setDamage(unsigned int);
        void setEvolution(int);
        void setLife(int);

    protected:

    private:
        int life;
        int evolution;
        unsigned int damage = 25;
        unsigned const int plusEnergy = 10;
};

#endif // CLSENERGY_H
