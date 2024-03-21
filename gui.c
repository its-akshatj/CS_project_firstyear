#include"things.h"

char t1[40] = {'1','5'};


textbox textboxes[1] = {(textbox){t1,2,(Vector2){20,600},(Vector2){300,30}}};

slider sliders[3] = {(slider){(Vector2){20,200},0,(Vector2){300,30},(Color){255,0,0,255},(Vector2){20,70}},
                     (slider){(Vector2){20,310},0,(Vector2){300,30},(Color){0,255,0,255},(Vector2){20,70}},
                     (slider){(Vector2){20,420},0,(Vector2){300,30},(Color){0,0,255,255},(Vector2){20,70}}};

button buttons[2] = {(button){(Vector2){20,20},(Vector2){40,40},&ScreenClearButton,"textures\\clearscreenbutton.png"},
                    (button){(Vector2){41,20},(Vector2){61,40},&SaveAsPpm6,"textures\\clearscreenbutton.png"}};
Gui gui = {1280,720,
            (Vector2){814,359},
            (Vector2){400,100},(Vector2){1200,650},4,
            buttons,2,
            sliders,3,
            textboxes,1};

Pen pen = {15,BLACK};