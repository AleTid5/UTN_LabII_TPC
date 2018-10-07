#ifndef CLSMOTOR_H
#define CLSMOTOR_H
#include <clsEvent.h>
#include <clsMode.h>
#include <clsScreen.h>
#include <clsError.h>
#include <clsText.h>
#include <clsAudio.h>
#include <clsMusic.h>
#include <adnConsts.h>
#include <clsScene.h>
#include <clsMucus.h>
#include <clsBug.h>

class clsMotor
{
public:
    int init();
    int run();
    int keyCommand(Uint16);

protected:
    clsEvent event;
    clsMode mode;
    clsScreen screen;
    clsError error;
    clsText text;
    clsAudio audio;
    clsMusic music;
    clsScene scene;
    clsBug bug;
    clsMucus mucus;

private:
};

#endif // CLSMOTOR_H
