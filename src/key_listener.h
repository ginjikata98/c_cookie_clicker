//
// Created by DUNG.VM on 18/11/2022.
//

#ifndef KEYLISTENER_KEY_LISTENER_H
#define KEYLISTENER_KEY_LISTENER_H

#include <stdbool.h>

typedef enum KeyCode {
  KEY_W,
  KEY_D,
} KeyCode;


typedef struct KeyEvent {
  KeyCode keyCode;
  bool shiftPressed;
  bool ctrlPressed;
  bool cmdPressed;
} KeyEvent;

typedef void *(*KeyPressedCallBack)(KeyEvent *event);

typedef struct KeyListener KeyListener;

KeyListener *KeyListenerInit(KeyPressedCallBack callBack);
void KeyListenerRun(KeyListener *keyListener);

#endif //KEYLISTENER_KEY_LISTENER_H
