#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "key_listener.h"
#include "robot.h"

bool running = false;
bool isQuit = false;

void *keypressCallBack(KeyEvent *event) {
  if (event->keyCode == KEY_D && event->shiftPressed) {
    isQuit = true;
    exit(-1);
  }
  if (event->keyCode == KEY_W) {
    running = !running;
  }
  return NULL;
}

void *autoClick(void *var) {
  while (!isQuit) {
    if (!running) {
      sleep(1);
      continue;
    }
    mouseClickCurrent();
    usleep(10 * 1000);
  }
  return NULL;
}

int main() {
  pthread_t thread_id;
  pthread_create(&thread_id, NULL, autoClick, NULL);

  KeyListener *keyListener = KeyListenerInit(keypressCallBack);
  KeyListenerRun(keyListener);

  pthread_join(thread_id, NULL);
  return 0;
}