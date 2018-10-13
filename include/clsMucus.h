#ifndef CLSMUCUS_H
#define CLSMUCUS_H
#include <clsScene.h>
#include <clsAudio.h>
#include <clsMusic.h>

class clsMucus : public clsScene
{
public:
    void spit(clsMusic*);
    void move(clsScreen*, int, int);

private:

protected:

};

#endif // MUCUS_H

