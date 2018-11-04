#include "clsPressableKey.h"

void clsPressableKey::operator=(int pressedKey) {
    this->pressedKey = pressedKey;
}

void clsPressableKey::operator>(bool isPressed) {
    this->isPressed = isPressed;
}

bool clsPressableKey::isKeyPressed() {
    return this->isPressed;
}

int clsPressableKey::getKey() {
    return this->pressedKey;
}
