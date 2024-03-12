#include"things.h"

void Button_Ifpressed(button but,Vector2 cur_pos,void* a,void* b,void* c){
    printf("a\n");
    if(cur_pos.x <= but.bottom_right.x && cur_pos.x >= but.top_left.x && cur_pos.y>= but.bottom_right.y && cur_pos.y<=but.bottom_right.y){
        printf("b\n");
        but.func(a,b,c);
    }
}

void ScreenClearButton(void* a,void* b,void* c){
    pixel* screen = (pixel*)a;
    ClearScreen(screen);
}




