#ifndef CLSBUG_H
#define CLSBUG_H
#include <clsMucus.h>
#include <clsScene.h>
#include <clsEvent.h>
#include <clsMusic.h>

class clsBug : public clsScene
{
private:
    bool canMove(direction, clsScene*, clsScreen*);

public:
    void move(direction, clsScene*, clsScreen*);
    void fire(clsMucus*, clsScene*, clsScreen*, clsEvent*, clsMusic*);

protected:
    unsigned int movement = 5;
};

#endif // CLSBUG_H
