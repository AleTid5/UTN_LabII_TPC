#ifndef CLSMOTOR_H
#define CLSMOTOR_H
#include <adnConsts.h>
#include <clsAudio.h>
#include <clsError.h>
#include <clsEvent.h>
#include <clsMode.h>
#include <clsMusic.h>
#include <clsScreen.h>
#include <clsText.h>

#include <clsScene.h>
#include <clsBug.h>

class clsMotor
{
public:
    void init();
    void run();
    void keyCommand(Uint16);
    void stopRun();
    bool isKeyPressable(Uint16);

protected:
    clsAudio audio;
    clsError error;
    clsEvent event;
    clsMode mode;
    clsMusic music;
    clsScreen screen;
    clsText text;
    clsScene scene;
    clsBug bug;
    clsBug enemie[35];
    //clsMucus mucus;

private:
};

#endif // CLSMOTOR_H
