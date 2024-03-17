#include"things.h"

button buttons[2] = {(button){(Vector2){20,20},(Vector2){40,40},&ScreenClearButton,"textures\\clearscreenbutton.png"},
                    (button){(Vector2){41,20},(Vector2){61,40},&ScreenClearButton,"textures\\clearscreenbutton.png"}};
Gui gui = {1280,720,
            (Vector2){400,100},(Vector2){1200,650},4,
            buttons,2};

Pen pen = {15,BLUE};