#include"things.h"

char t1[40] = {'1','5'};
char t2[40];
char t3[40];


textbox textboxes[3] = {(textbox){t1,2,(Vector2){20,600},(Vector2){100,30}},
                        (textbox){t2,0,(Vector2){20,500},(Vector2){200,20}},
                        (textbox){t3,0,(Vector2){20,540},(Vector2){200,20}}};

slider sliders[3] = {(slider){(Vector2){20,200},0,(Vector2){300,30},(Color){255,0,0,255},(Vector2){20,70}},
                     (slider){(Vector2){20,310},0,(Vector2){300,30},(Color){0,255,0,255},(Vector2){20,70}},
                     (slider){(Vector2){20,420},0,(Vector2){300,30},(Color){0,0,255,255},(Vector2){20,70}}};

button buttons[3] = {(button){(Vector2){20,20},(Vector2){40,40},&ScreenClearButton,"textures\\clearscreenbutton.png"},
                     (button){(Vector2){240,500},(Vector2){260,520},&SaveAsPpm6,"textures\\savebutton.png"},
                     (button){(Vector2){240,540},(Vector2){260,560},&LoadPpm6,"textures\\loadbutton.png"}};
Gui gui = {1280,720,
            (Vector2){814,359},
            (Vector2){400,100},(Vector2){1200,650},4,
            buttons,3,
            sliders,3,
            textboxes,3};

Pen pen = {15,BLACK};