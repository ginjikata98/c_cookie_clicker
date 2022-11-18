//
// Created by Tony Vu on 18/11/2022.
//

#include "robot.h"

void mouseMove(double x, double y) {
  CGEventRef move = CGEventCreateMouseEvent(
      NULL, kCGEventMouseMoved,
      CGPointMake(x, y),
      kCGMouseButtonRight
  );
  CGEventPost(kCGHIDEventTap, move);
  CFRelease(move);
}

void mouseClickPoint(CGPoint point) {
  CGEventRef leftDown = CGEventCreateMouseEvent(
      NULL, kCGEventLeftMouseDown,
      point,
      kCGMouseButtonLeft
  );
  CGEventRef leftUp = CGEventCreateMouseEvent(
      NULL, kCGEventLeftMouseUp,
      point,
      kCGMouseButtonLeft
  );
  CGEventPost(kCGHIDEventTap, leftDown);
  CGEventPost(kCGHIDEventTap, leftUp);
  CFRelease(leftDown);
  CFRelease(leftUp);
}

void mouseClick(double x, double y) {
  CGPoint point = CGPointMake(x, y);
  mouseClickPoint(point);
}

void mouseClickCurrent() {
  CGEventRef e = CGEventCreate(NULL);
  CGPoint cursor = CGEventGetLocation(e);
  mouseClickPoint(cursor);
  CFRelease(e);
};
