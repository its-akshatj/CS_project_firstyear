#include"things.h"

char t1[40] = {'1','5'}; 
char t2[40];
char t3[40];
char t4[40];
char t5[40];


textbox textboxes[5] = {(textbox){t1,2,(Vector2){20,570},(Vector2){100,30}}, // pen size
                        (textbox){t2,0,(Vector2){20,500},(Vector2){200,20}}, // savename
                        (textbox){t3,0,(Vector2){20,540},(Vector2){200,20}}, // load name
                        (textbox){t4,0,(Vector2){20,620},(Vector2){100,30}},  // new width
                        (textbox){t5,0,(Vector2){130,620},(Vector2){100,30}}}; // new height

slider sliders[3] = {(slider){(Vector2){20,200},0,(Vector2){300,30},(Color){255,0,0,255},(Vector2){20,70}},
                     (slider){(Vector2){20,310},0,(Vector2){300,30},(Color){0,255,0,255},(Vector2){20,70}},
                     (slider){(Vector2){20,420},0,(Vector2){300,30},(Color){0,0,255,255},(Vector2){20,70}}};

button buttons[13] = {(button){(Vector2){20,20},(Vector2){20,20},&ScreenClearButton,"textures\\clearscreenbutton.png"},
                     (button){(Vector2){240,500},(Vector2){20,20},&SaveAsPpm6,"textures\\savebutton.png"},
                     (button){(Vector2){240,540},(Vector2){20,20},&LoadPpm6,"textures\\loadbutton.png"},
                     (button){(Vector2){41,20},(Vector2){20,20},&RectTool,"textures\\clearscreenbutton.png","textures\\p.png",0,1},
                     (button){(Vector2){177,655},(Vector2){53,20},&NewButton,"textures\\newbutton.png"},
                     (button){(Vector2){41,41},(Vector2){20,20},&EllipseTool,"textures\\ellipsetool.png","textures\\p.png",0,1},
                     
                     (button){(Vector2){20,41},(Vector2){20,20},&LineTool,"textures\\linetool.png","textures\\p.png",0,1},
                     (button){(Vector2){147,655},(Vector2){20,20},&RatioLock,"textures\\ratiochain.png","textures\\p.png",0,1},
                     (button){(Vector2){60,20},(Vector2){100,20},&Bored,"textures\\bored.png"},
                     (button){(Vector2){20,61},(Vector2){20,20},&Eraser,"textures\\eraser.png","textures\\p.png",0,1},
                     (button){(Vector2){41,61},(Vector2){20,20},&HollowRectTool,"textures\\hollowrect.png","textures\\p.png",0,1},
                     (button){(Vector2){20,81},(Vector2){20,20},&FillToolActivation,"textures\\bucket.png"},
                     (button){(Vector2){41,81},(Vector2){20,20},&HollowEllipseTool,"textures\\ellipsetool.png","textures\\p.png",0,1}
                     };
Gui gui = {1280,720,
            (Vector2){814,359},
            (Vector2){400,100},(Vector2){1200,650},4,
            buttons,13,
            sliders,3,
            textboxes,5};

Pen pen = {15,BLACK};
Sym sym = {.pos1 = (Vector2){200,20},
           .pos2 = (Vector2){400,20},
           .r1 = 7,
           .r2 = 13,
           .thick = 3,
           .color = LIME
};

enum State state = normal;
enum Window window = paint; 
