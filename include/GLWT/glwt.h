#ifndef GLWT_glwt_h
#define GLWT_glwt_h

#include <GLWT/glwt_keysym.h>

#ifdef _WIN32
#  define GLWTAPI __declspec( dllexport )
#else
#  define GLWTAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define GLWT_API_ANY                    0x00
#define GLWT_API_OPENGL                 0x01
#define GLWT_API_OPENGL_ES              0x02
#define GLWT_API_MASK                   0x0f

#define GLWT_PROFILE_CORE               0x00
#define GLWT_PROFILE_COMPATIBILITY      0x10
#define GLWT_PROFILE_DEBUG              0x20
#define GLWT_PROFILE_ROBUSTNESS         0x40
#define GLWT_PROFILE_MASK               0xf0

typedef struct GLWTConfig
{
    int red_bits, green_bits, blue_bits, alpha_bits;
    int depth_bits, stencil_bits;
    int samples, sample_buffers;
    int api;
    int api_version_major, api_version_minor;
} GLWTConfig;

typedef struct GLWTWindow GLWTWindow;

typedef enum GLWTWindowEventType {
    GLWT_WINDOW_NO_EVENT = 0,
    GLWT_WINDOW_CLOSE,
    GLWT_WINDOW_EXPOSE,
    GLWT_WINDOW_RESIZE,
    GLWT_WINDOW_SHOW,
    GLWT_WINDOW_HIDE,
    GLWT_WINDOW_FOCUS_IN,
    GLWT_WINDOW_FOCUS_OUT,
    GLWT_WINDOW_KEY_UP,
    GLWT_WINDOW_KEY_DOWN,
    GLWT_WINDOW_BUTTON_UP,
    GLWT_WINDOW_BUTTON_DOWN,
    GLWT_WINDOW_MOUSE_MOTION,
    GLWT_WINDOW_MOUSE_ENTER,
    GLWT_WINDOW_MOUSE_LEAVE,
    GLWT_WINDOW_CHARACTER_INPUT,
} GLWTWindowEventType;

typedef struct GLWTWindowEvent
{
    GLWTWindow *window;

    GLWTWindowEventType type;

    union {
        struct { int width, height; } resize;
        struct { int keysym, scancode, mod; } key;
        struct { int x, y, buttons; } motion;
        struct { int x, y, button, mod; } button;
        struct { unsigned int unicode; } character;
        struct { int dummy; } dummy;
    };
} GLWTWindowEvent;

GLWTAPI int glwtInit(
    const GLWTConfig *config,
    void (*error_callback)(const char *msg, void *userdata),
    void *userdata
    );
GLWTAPI void glwtQuit();

GLWTAPI GLWTWindow *glwtWindowCreate(
    const char *title,
    int width, int height,
    GLWTWindow *share,
    void (*win_callback)(GLWTWindow *window, const GLWTWindowEvent *event, void *userdata),
    void *userdata
    );
GLWTAPI void glwtWindowDestroy(GLWTWindow *window);

GLWTAPI int glwtWindowClosed(GLWTWindow *window);
GLWTAPI void glwtWindowShow(GLWTWindow *window, int show);
GLWTAPI void glwtWindowSetTitle(GLWTWindow *window, const char *title);

GLWTAPI int glwtMakeCurrent(GLWTWindow *win);
GLWTAPI int glwtSwapBuffers(GLWTWindow *win);
GLWTAPI int glwtSwapInterval(GLWTWindow *win, int interval);
GLWTAPI int glwtWindowGetSize(GLWTWindow *win, int *width, int *height);

GLWTAPI void glwtFullscreen(GLWTWindow *window, int mode);

GLWTAPI int glwtEventHandle(int wait);
GLWTAPI double glwtGetTime();

#ifdef __cplusplus
}
#endif

#endif
