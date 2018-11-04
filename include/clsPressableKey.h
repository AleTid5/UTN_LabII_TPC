#ifndef CLSPRESSABLEKEY_H
#define CLSPRESSABLEKEY_H

class clsPressableKey
{
    public:
        void operator=(int);
        void operator>(bool);
        bool isKeyPressed();
        int getKey();

    protected:

    private:
        int pressedKey;
        bool isPressed = false;
};

#endif // CLSPRESSABLEKEY_H
