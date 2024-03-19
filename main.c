#include"things.h"
extern Gui gui;
extern Pen pen;

int main(){
    

    InitWindow(gui.screenwidth,gui.screenheight,"paint");

    Vector2 pos = {0,0};  
    bool curdown = false;
    int moveslider = 0;

    Button_LoadTextures();

    vector qsplines = GiveVector();
    vector lines = GiveVector();
    vector points = GiveVector();    

    pixel* screen = (pixel*)malloc(gui.screenwidth*gui.screenheight*sizeof(pixel));
    ClearScreen(screen,&qsplines,&lines,&points);
    AddGuiBase(screen);
    
    
    SetTargetFPS(60);
    while(!WindowShouldClose()){   
        pos = GetMousePosition();
        
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            curdown = true;
            Button_Ifpressed(gui.buttons[0],pos,screen,&qsplines,&lines,&points);
            Button_Ifpressed(gui.buttons[1],pos,screen,"test.ppm",NULL,NULL);
            for(int i = 0;i<gui.num_sliders;i++){
                slider s = gui.sliders[i];
                if(CheckCollisionPointRec(pos,(Rectangle){s.pos.x + s.slide * s.bar_dim.x - s.rect_dim.x/2,s.pos.y - (s.rect_dim.y - s.bar_dim.y)/2,s.rect_dim.x,s.rect_dim.y})){
                    moveslider = i+1;
                }
            }
        }
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            curdown = false;
        }

        

        if(curdown){

            if(moveslider){
                slider s = gui.sliders[moveslider-1];
                if(CheckCollisionPointRec(pos,(Rectangle){s.pos.x,s.pos.y - (s.rect_dim.y - s.bar_dim.y)/2,s.bar_dim.x,s.rect_dim.y})){
                    gui.sliders[moveslider-1].slide = (pos.x-s.pos.x)/s.bar_dim.x;
                }
                else{
                    char c[4] = {pen.color.r,pen.color.g,pen.color.b,pen.color.a};
                    c[moveslider - 1] = (int)(255 * s.slide); 
                    pen.color = (Color){c[0],c[1],c[2],c[3]};
                    moveslider = 0;
                }
            }

            if(pos.x < gui.CanvasBottomRight.x && pos.x > gui.CanvasTopLeft.x && pos.y > gui.CanvasTopLeft.y && pos.y < gui.CanvasBottomRight.y){
                screen[(int)(pos.y * gui.screenwidth + pos.x)].color = (Color){0,0,0,255};
                Vector_Add50e(&points,(Vector2){pos.x,pos.y});
            }

            if(points.len==3){
                Vector_Add50e(&qsplines,(points.arr)[0]);                    
                Vector_Add50e(&qsplines,(points.arr)[1]);                    
                Vector_Add50e(&qsplines,(points.arr)[2]);
                points.arr[0] = points.arr[2];
                Vector_pop(&points);
                Vector_pop(&points);
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
        
        AddLines(screen,&lines);
        AddQSplines(screen,&qsplines);
        BeginDrawing();
            DrawScreen(screen);
            //.DrawQSplines(&qsplines);
            //.DrawLines(&lines);
        EndDrawing();

    }
    CloseWindow();
    return 0;


}