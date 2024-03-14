#include"things.h"
// const button clear = {(Vector2){20,20},(Vector2){40,40},&ScreenClearButton,(Color){0,0,255,255}};
button buttons[1] = {(button){(Vector2){20,20},(Vector2){40,40},&ScreenClearButton,"textures\\clearscreenbutton.png"}};
Gui gui = {1280,720,
            (Vector2){400,100},(Vector2){1200,650},4,
            buttons,1};