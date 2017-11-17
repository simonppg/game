#ifndef _WINDOW_MANAGER_H_
#define _WINDOW_MANAGER_H_

typedef struct _window_manager Window_manager;

Window_manager* WM_new();
void WM_clean(Window_manager* wm);
SDL_Renderer*  WM_get_renderer(Window_manager* wm);
SDL_Window* WM_get_window(Window_manager* wm);

#endif
