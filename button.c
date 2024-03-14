#include"things.h"
extern Gui gui;

void Button_LoadTextures(){
    for(int i = 0;i<gui.num_buttons;i++){
        gui.buttons[i].texture = LoadTexture(gui.buttons[i].texture_path);
    }
}

void Button_Ifpressed(button but,Vector2 cur_pos,void* a,void* b,void* c,void* d){
    printf("a\n");
    printf("%d%d%d%d\n",cur_pos.x <= but.bottom_right.x,cur_pos.x >= but.top_left.x,cur_pos.y<= but.bottom_right.y, cur_pos.y>=but.top_left.y);
    if(cur_pos.x <= but.bottom_right.x && cur_pos.x >= but.top_left.x && cur_pos.y<= but.bottom_right.y && cur_pos.y>=but.top_left.y){
        printf("b\n");
        but.func(a,b,c,d);
    }
}

void ScreenClearButton(void* a,void* b,void* c,void* d){
    printf("b\n");
    pixel* screen = (pixel*)a;
    vector* qsplines = (vector*)b;
    vector* lines = (vector*)c;
    vector* points = (vector*)d;
    ClearCanvas(screen,qsplines,lines,points);
}




