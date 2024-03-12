#include"things.h"
extern Gui gui;



void MyDrawRectangle(pixel* screen,Vector2 top_left,Vector2 bottom_right,Color color){
    for(int i = 0;i<bottom_right.x-top_left.x;i++){
        for(int j = 0;j<bottom_right.y-top_left.y;j++){
            screen[(int)(top_left.x + top_left.y*gui.screenwidth + i + j*gui.screenwidth)].color = color;
        }
    }
}

void ClearScreen(pixel* screen){
    for(int i = 0;i<gui.screenwidth*gui.screenheight;i++){
        screen[i] = (pixel){WHITE};
    }
}

void DrawScreen(pixel* screen){
    for(int i = 0;i<gui.screenwidth*gui.screenheight;i++){
        DrawRectangle(i%gui.screenwidth,i/gui.screenwidth,1,1,(screen[i]).color);
    }
}

void AddGuiBase(pixel* screen){
    MyDrawRectangle(screen,(Vector2){gui.CanvasTopLeft.x-gui.CanvasBorderThickness,gui.CanvasTopLeft.y-gui.CanvasBorderThickness},(Vector2){gui.CanvasBottomRight.x+gui.CanvasBorderThickness,gui.CanvasTopLeft.y},RED);
    MyDrawRectangle(screen,(Vector2){gui.CanvasTopLeft.x-gui.CanvasBorderThickness,gui.CanvasBottomRight.y},(Vector2){gui.CanvasBottomRight.x+gui.CanvasBorderThickness,gui.CanvasBottomRight.y+gui.CanvasBorderThickness},RED);
    MyDrawRectangle(screen,(Vector2){gui.CanvasTopLeft.x-gui.CanvasBorderThickness,gui.CanvasTopLeft.y},(Vector2){gui.CanvasTopLeft.x,gui.CanvasBottomRight.y},RED);
    MyDrawRectangle(screen,(Vector2){gui.CanvasBottomRight.x,gui.CanvasTopLeft.y},(Vector2){gui.CanvasBottomRight.x+gui.CanvasBorderThickness,gui.CanvasBottomRight.y},RED);
    for(int i = 0;i<gui.num_nuttons;i++){
        MyDrawRectangle(screen,gui.buttons[i].top_left,gui.buttons[i].bottom_right,gui.buttons[i].color);
    }
}

void DrawQSplines(vector* qsplines){
    for(int i = 0;i<(qsplines->len);i+=3){
        DrawSplineSegmentBezierQuadratic((qsplines->arr)[i],(qsplines->arr)[i+1],(qsplines->arr)[i+2],1,BLACK);
    }
}

void DrawLines(vector* lines){
    for(int i = 0;i<lines->len;i+=2){
        DrawLineV((lines->arr)[i],(lines->arr)[i+1],BLACK);
    }
}







