#ifndef CLSBUG_H
#define CLSBUG_H
#include <clsMucus.h>
#include <clsScene.h>
#include <clsEvent.h>
#include <clsMusic.h>

class clsBug : public clsScene
{
public:
    void fly(clsScreen*);
    void fly(clsScreen*, clsScene*);
    void move(direction, clsScene*, clsScreen*);
    void fire(clsMucus*, clsScene*, clsScreen*, clsEvent*, clsMusic*);

private:
    bool canMove(direction, clsScene*, clsScreen*);

protected:
    unsigned int movement = 5;
};

#endif // CLSBUG_H
