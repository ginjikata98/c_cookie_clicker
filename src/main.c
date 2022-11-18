#include <stdio.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>
#include <pthread.h>
#include "key_listener.h"

bool running = true;
bool isQuit = false;

void *autoClick(void *var) {
  CGEventRef move = CGEventCreateMouseEvent(
      NULL, kCGEventMouseMoved,
      CGPointMake(500, 500),
      kCGMouseButtonRight
  );

  CGEventRef rightDown = CGEventCreateMouseEvent(
      NULL, kCGEventRightMouseDown,
      CGPointMake(500, 500),
      kCGMouseButtonRight
  );
  CGEventRef rightUp = CGEventCreateMouseEvent(
      NULL, kCGEventRightMouseUp,
      CGPointMake(500, 500),
      kCGMouseButtonRight
  );

  while (!isQuit) {
    printf("running %d\n", running);
    if (!running) {
      sleep(1);
      continue;
    }
    CGEventPost(kCGHIDEventTap, move);
    CGEventPost(kCGHIDEventTap, rightDown);
    CGEventPost(kCGHIDEventTap, rightUp);
    sleep(1);
  }
  return NULL;
}

void *keypressCallBack(KeyEvent *event) {
  if (event->keyCode == KEY_D) {
    if (event->shiftPressed) {
      isQuit = true;
      exit(-1);
    }
    running = !running;
    printf("running %d\n", running);
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