#ifndef CLSSCENE_H
#define CLSSCENE_H
#include <clsSprite.h>
#include <clsTimer.h>

class clsScene : public clsSprite
{
    public:
        int init(const char*, unsigned int posX = 0, unsigned int posY = 0);
        void loadWallpaper(clsScreen*);

    protected:
        void inherit(){};

    private:
};

#endif // CLSSCENE_H
