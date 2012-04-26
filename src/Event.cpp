#include "Event.h"

Event::Event(){}
Event::~Event() {}

void Event::Handle(SDL_Event* Event) {
    switch(Event->type) {
        case SDL_ACTIVEEVENT: {
            switch(Event->active.state) {
                case SDL_APPMOUSEFOCUS: {
                    if ( Event->active.gain )
                        OnMouseFocus();
                    else
                        OnMouseBlur();
                    break;
                }
                case SDL_APPINPUTFOCUS: {
                    if ( Event->active.gain )    OnInputFocus();
                    else                OnInputBlur();

                    break;
                }
                case SDL_APPACTIVE:    {
                    if ( Event->active.gain )    OnRestore();
                    else                OnMinimize();

                    break;
                }
            }
            break;
        }

        case SDL_KEYDOWN: {
            OnKeyDown(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
            break;
        }

        case SDL_KEYUP: {
            OnKeyUp(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
            break;
        }

        case SDL_MOUSEMOTION: {
            OnMouseMove(Event->motion.x,Event->motion.y,Event->motion.xrel,Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
            break;
        }

        case SDL_MOUSEBUTTONDOWN: {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonDown(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonDown(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonDown(Event->button.x,Event->button.y);
                    break;
                }
            }
            break;
        }

        case SDL_MOUSEBUTTONUP:    {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonUp(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonUp(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonUp(Event->button.x,Event->button.y);
                    break;
                }
            }
            break;
        }

        case SDL_JOYAXISMOTION: {
            OnJoyAxis(Event->jaxis.which,Event->jaxis.axis,Event->jaxis.value);
            break;
        }

        case SDL_JOYBALLMOTION: {
            OnJoyBall(Event->jball.which,Event->jball.ball,Event->jball.xrel,Event->jball.yrel);
            break;
        }

        case SDL_JOYHATMOTION: {
            OnJoyHat(Event->jhat.which,Event->jhat.hat,Event->jhat.value);
            break;
        }
        case SDL_JOYBUTTONDOWN: {
            OnJoyButtonDown(Event->jbutton.which,Event->jbutton.button);
            break;
        }

        case SDL_JOYBUTTONUP: {
            OnJoyButtonUp(Event->jbutton.which,Event->jbutton.button);
            break;
        }

        case SDL_QUIT: {
            Exit();
            break;
        }

        case SDL_SYSWMEVENT: {
            //Ignore
            break;
        }

        case SDL_VIDEORESIZE: {
            OnResize(Event->resize.w,Event->resize.h);
            break;
        }

        case SDL_VIDEOEXPOSE: {
            OnExpose();
            break;
        }

        default: {
            OnUser(Event->user.type,Event->user.code,Event->user.data1,Event->user.data2);
            break;
        }
    }
}

void Event::OnInputFocus() {}
void Event::OnInputBlur() {}
void Event::OnKeyDown(SDLKey key, SDLMod mod, Uint16 unicode) {
    switch(key) {
        case SDLK_UP:
            if (ViewY < 0) ViewY+=3;
        break;
        case SDLK_DOWN:
            if (abs(ViewY) + VIEWPORT_HEIGHT <= MAP_HEIGHT*BLOCK_SIZE) ViewY-=3;
        break;
        case SDLK_LEFT:
            if (ViewX < 0) ViewX+=3;
        break;
        case SDLK_RIGHT:
            if (abs(ViewX) + VIEWPORT_WIDTH <= MAP_WIDTH*BLOCK_SIZE) ViewX-=3;
        break;
        case SDLK_SPACE:
            SDL_Delay(100);
        break;
        default:
        break;
    }
}
void Event::OnKeyUp(SDLKey key, SDLMod mod, Uint16 unicode) {}
void Event::OnMouseFocus() {}
void Event::OnMouseBlur() {}
void Event::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) {}
void Event::OnMouseWheel(bool Up, bool Down) {}
void Event::OnLButtonDown(int mX, int mY) {}
void Event::OnLButtonUp(int mX, int mY) {}
void Event::OnRButtonDown(int mX, int mY) {}
void Event::OnRButtonUp(int mX, int mY) {}
void Event::OnMButtonDown(int mX, int mY) {}
void Event::OnMButtonUp(int mX, int mY) {}
void Event::OnJoyAxis(Uint8 which,Uint8 axis,Sint16 value) {}
void Event::OnJoyButtonDown(Uint8 which,Uint8 button) {}
void Event::OnJoyButtonUp(Uint8 which,Uint8 button) {}
void Event::OnJoyHat(Uint8 which,Uint8 hat,Uint8 value) {}
void Event::OnJoyBall(Uint8 which,Uint8 ball,Sint16 xrel,Sint16 yrel) {}
void Event::OnMinimize() {}
void Event::OnRestore() {}
void Event::OnResize(int w,int h) {}
void Event::OnExpose() {}
void Event::Exit() {}
void Event::OnUser(Uint8 type, int code, void* data1, void* data2) {}
