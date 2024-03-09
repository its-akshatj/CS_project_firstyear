#include"pixel.h"


int main(){

    InitWindow(screenwidth,screenheight,"paint");

    Vector2 pos = {0,0};  
    bool curdown = false;

    pixel* screen = (pixel*)malloc(screenwidth*screenheight*sizeof(pixel));
    ClearScreen(screen);
    SetTargetFPS(60);


    int count = 0;

    while(!WindowShouldClose()){   
        BeginDrawing();

            //ClearBackground(RAYWHITE);
            DrawScreen(screen);

            pos = GetMousePosition();
            if(curdown){
                if(pos.x <1200 && pos.x > 400 && pos.y > 200 && pos.y < 650){
                    screen[(int)(pos.y * screenwidth + pos.x)].color = (Color){0,0,0,255};
                }
            } 
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                curdown = true;
            }
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                curdown = false;
            }
            // count = 0;
            // for(int i = 0;i<screenwidth*screenheight;i++){
            //     if(screen[i].color.r == 0 && screen[i].color.g == 0 && screen[i].color.b == 0 ){
            //         count+=1;
            //     }        
            // }
            //printf("%d\n",count);

        EndDrawing();
    }
    CloseWindow();
    return 0;


}