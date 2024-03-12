#include"raylib.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct{
    Texture2D img;
    Vector2 pos;
}cursor;

typedef struct {
    Color color;
} pixel;

typedef struct
{
    Vector2 top_left;
    Vector2 bottom_right;
    void (*func)(void* a,void*b,void* c);
    Color color;
}button;

typedef struct{
    int screenwidth;
    int screenheight;

    Vector2 CanvasTopLeft;
    Vector2 CanvasBottomRight;
    int CanvasBorderThickness;

    button* buttons;
    int num_nuttons;
}Gui;

typedef struct{
    Vector2* arr;
    int len;
    int cap;
}vector;

void MyDrawRectangle(pixel* screen,Vector2 top_left,Vector2 bottom_right,Color color);
void ClearScreen(pixel* screen);
void DrawScreen(pixel* screen);
void AddGuiBase(pixel* screen);
void DrawQSplines(vector* qsplines);
void DrawLines(vector* lines);

vector GiveVector();
void Vector_Grow50(vector* vec,int index);
void Vector_Add50(vector* vec,Vector2 point,int index);
void Vector_Add50e(vector* vec,Vector2 point);
void Vector_Grow(vector* vec,int index);
void Vector_Add(vector* vec,Vector2 point,int index);
Vector2 Vector_pop(vector* vec);
void Vector_Empty(vector* vec);

void Button_Ifpressed(button but,Vector2 cur_pos,void* a,void* b,void* c);

void ScreenClearButton(void* a,void* b,void* c);



