#ifndef CLSENGINE_H
#define CLSENGINE_H
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
#include <clsGameData.h>
#include <clsBug.h>

class clsEngine
{
public:
    void init();
    void run(bool playAgain = false);
    void keyCommand();
    void stopRun();
    void comeBackSoon();

protected:
    clsAudio audio;
    clsError error;
    clsEvent event;
    clsMode mode;
    clsMusic music;
    clsRandom random;
    clsScreen screen;
    clsText text;
    clsPressableKey pressableKey[11];
    clsScene scene;
    clsBug bug;
    clsBug enemie[36];

private:
    void bringGameToLife();
    void gameOver();
    void initializeGame();
    void pause();
    bool setKeyPressed(Uint16, bool);
    void saveOnExit();
};

#endif // CLSENGINE_H
