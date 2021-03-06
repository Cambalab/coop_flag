#include<X11/X.h>
#include<X11/Xlib.h>
#include<X11/Xutil.h>

#define CANVAS_WIDTH 504
#define CANVAS_HEIGHT CANVAS_WIDTH * 2/3
#define COLOR(r, g, b) ((r << 16) + (g << 8) + b)

void _start() {
  //initialize the window
  Display* dpy = XOpenDisplay(NULL);

  //this is so the window isn't resizable
  static XSizeHints hints = {
    .flags = USPosition | PMinSize | PMaxSize,
    .width = CANVAS_WIDTH,     .height = CANVAS_HEIGHT,
    .max_width = CANVAS_WIDTH, .max_height = CANVAS_HEIGHT,
    .min_width = CANVAS_WIDTH, .min_height = CANVAS_HEIGHT,
  };

  //it seems like just keeping this as 0 is probs ok... lol
  const int s = 0;//DefaultScreen(dpy);
  Window win = XCreateSimpleWindow(dpy, RootWindow(dpy, s), 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, 0, 0, COLOR(255, 0, 0));

  XSelectInput(dpy, win, ExposureMask);
  XSetWMNormalHints(dpy, win, &hints);

  //this actually opens the window
  XMapWindow(dpy, win);

  XEvent xev;
  static XGCValues vals = {};
  while(1) {
    XNextEvent(dpy, &xev);

    if (xev.type == Expose) {
      GC gc = DefaultGC(dpy, s);

      vals.foreground = COLOR(255, 140, 25);
      XChangeGC(dpy, gc, GCForeground, &vals);
      XFillRectangle(dpy, win, gc, 0, CANVAS_HEIGHT/7, CANVAS_WIDTH, CANVAS_HEIGHT/7);

      vals.foreground = COLOR(255, 239, 0);
      XChangeGC(dpy, gc, GCForeground, &vals);
      XFillRectangle(dpy, win, gc, 0, CANVAS_HEIGHT* 2/7, CANVAS_WIDTH, CANVAS_HEIGHT/7);

      vals.foreground = COLOR(0, 255, 0);
      XChangeGC(dpy, gc, GCForeground, &vals);
      XFillRectangle(dpy, win, gc, 0, CANVAS_HEIGHT* 3/7, CANVAS_WIDTH, CANVAS_HEIGHT/7);

      vals.foreground = COLOR(135, 206, 235);
      XChangeGC(dpy, gc, GCForeground, &vals);
      XFillRectangle(dpy, win, gc, 0, CANVAS_HEIGHT* 4/7, CANVAS_WIDTH, CANVAS_HEIGHT/7);

      vals.foreground = COLOR(0, 0, 255);
      XChangeGC(dpy, gc, GCForeground, &vals);
      XFillRectangle(dpy, win, gc, 0, CANVAS_HEIGHT* 5/7, CANVAS_WIDTH, CANVAS_HEIGHT/7);

      vals.foreground = COLOR(143, 0, 255);
      XChangeGC(dpy, gc, GCForeground, &vals);
      XFillRectangle(dpy, win, gc, 0, CANVAS_HEIGHT* 6/7, CANVAS_WIDTH, CANVAS_HEIGHT/7);
    }
  }
}
