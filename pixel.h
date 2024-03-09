#include"raylib.h"
#include<stdio.h>
#include<stdlib.h>

#define screenwidth  1280
#define screenheight  720

typedef struct{
    Texture2D img;
    Vector2 pos;

}cursor;

typedef struct {
    Color color;
} pixel;


void ClearScreen(pixel* screen){
    for(int i = 0;i<screenwidth*screenheight;i++){
        screen[i] = (pixel){WHITE};
    }
}

void DrawScreen(pixel* screen){
    for(int i = 0;i<screenwidth*screenheight;i++){
        DrawRectangle(i%screenwidth,i/screenwidth,1,1,(screen[i]).color);
    }
            
}