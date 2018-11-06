#ifndef CLSMOTOR_H
#define CLSMOTOR_H
#include <adnConsts.h>
#include <clsAudio.h>
#include <clsError.h>
#include <clsEvent.h>
#include <clsMode.h>
#include <clsMusic.h>
#include <clsRandom.h>
#include <clsScreen.h>
#include <clsText.h>

#include <clsPressableKey.h>
#include <clsScene.h>
#include <clsGame.h>
#include <clsBug.h>

class clsMotor
{
public:
    void init();
    void run(bool playAgain = false);
    void keyCommand();
    void stopRun();

protected:
    clsAudio audio;
    clsError error;
    clsEvent event;
    clsMode mode;
    clsMusic music;
    clsRandom random;
    clsScreen screen;
    clsText text;
    clsPressableKey pressableKey[10];
    clsScene scene;
    clsBug bug;
    clsBug enemie[36];

private:
    void bringGameToLife(clsScreen*, clsScene*, clsMusic*, clsRandom*, clsBug*, clsBug*);
    void initializeGame();
    bool setKeyPressed(Uint16, bool);
    void saveOnExit();
    void gameOver();
};

#endif // CLSMOTOR_H
