#include"pixel.h"

int main(){
    

    InitWindow(gui.screenwidth,gui.screenheight,"paint");

    Vector2 pos = {0,0};  
    bool curdown = false;

    vector qsplines = GiveVector();
    vector lines = GiveVector();
    vector points = GiveVector();    

    pixel* screen = (pixel*)malloc(gui.screenwidth*gui.screenheight*sizeof(pixel));
    ClearScreen(screen);
    AddGuiBase(screen);
    
    SetTargetFPS(60);
    while(!WindowShouldClose()){   
        
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            curdown = true;
        }
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            curdown = false;
        }
        pos = GetMousePosition();
        if(curdown){
            
            if(pos.x < gui.CanvasBottomRight.x && pos.x > gui.CanvasTopLeft.x && pos.y > gui.CanvasTopLeft.y && pos.y < gui.CanvasBottomRight.y){
                screen[(int)(pos.y * gui.screenwidth + pos.x)].color = (Color){0,0,0,255};
                Vector_Add50e(&points,(Vector2){pos.x,pos.y});
            }
        }
        if(!curdown){
            if(points.len != 0){
                int i  = 0;
                for(;points.len-i>=3;i+=2){               
                    Vector_Add50e(&qsplines,(points.arr)[i]);                    
                    Vector_Add50e(&qsplines,(points.arr)[i+1]);                    
                    Vector_Add50e(&qsplines,(points.arr)[i+2]);                    
                }
                
                if(points.len - i == 2){
                    Vector_Add50e(&lines,(points.arr)[i]);
                    Vector_Add50e(&lines,(points.arr)[i+1]);
                }
           
                Vector_Empty(&points);
            }
        }
        
        BeginDrawing();
        
            DrawScreen(screen);
            DrawQSplines(&qsplines);
            DrawLines(&lines);
        
        EndDrawing();
    }
    CloseWindow();
    return 0;


}