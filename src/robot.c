//
// Created by Tony Vu on 18/11/2022.
//

#include "robot.h"

void moveTo(double x, double y) {
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

void clickAt(double x, double y) {
  CGPoint point = CGPointMake(x, y);
  mouseClickPoint(point);
}

void click() {
  CGEventRef e = CGEventCreate(NULL);
  CGPoint cursor = CGEventGetLocation(e);
  mouseClickPoint(cursor);
  CFRelease(e);
}

void screenCapture() {
  system("screencapture -x test.png");
}

void getAllWindow() {
  CGWindowListOption option = kCGWindowListOptionAll;
  CGWindowID relativeToWindow = kCGNullWindowID;
  CFArrayRef ref = CGWindowListCopyWindowInfo(option, relativeToWindow);
  long count = CFArrayGetCount(ref);
  for (int i = 0; i < count; i++) {
    CFDictionaryRef dictionary = CFArrayGetValueAtIndex(ref, i);
    CFStringRef windowName = CFDictionaryGetValue(dictionary, kCGWindowOwnerName);
    CFIndex length = CFStringGetLength(windowName);
    CFIndex maxSize = CFStringGetMaximumSizeForEncoding(length, kCFStringEncodingUTF8);
    char *event = (char *) malloc(maxSize);
    CFStringGetCString(windowName, event, maxSize, kCFStringEncodingUTF8);
    printf("Event  %s\n", event);
  }
}
