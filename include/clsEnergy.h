#ifndef CLSENERGY_H
#define CLSENERGY_H
#include <clsScene.h>

class clsEnergy : public clsScene
{
    public:
        clsEnergy();
        void initialize(clsScreen*);
        void updateEvolution(clsScreen*);
        void updateLife(clsScreen*);
        int getEvolution();
        int getLife();
        void setEvolution(int);
        void setLife(int);

    protected:

    private:
        int life;
        int evolution;
        unsigned const int damage = 25;
        unsigned const int plus = 10;
};

#endif // CLSENERGY_H
