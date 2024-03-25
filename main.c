#include"things.h"
extern Gui gui;
extern Pen pen;
extern enum State state;
int main(){
    
    InitWindow(gui.screenwidth,gui.screenheight,"paint");

    Vector2 pos1,pos2;
    int stateflag = 0,isreleased = 0;

    Vector2 pos = {0,0};  
    bool curdown = false;
    int moveslider = 0;
    int uptextbox = 0;

    Button_LoadTextures();

    vector qsplines = GiveVector();
    vector lines = GiveVector();
    vector points = GiveVector();    

    pixel* screen = (pixel*)malloc(gui.screenwidth*gui.screenheight*sizeof(pixel));
    ClearScreen(screen,&qsplines,&lines,&points);
    CanvasFitDim(screen,600,600);
    
    SetTargetFPS(60);
    while(!WindowShouldClose()){   
        pos = GetMousePosition();

        switch (state){
        case rect:
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){isreleased = 1;}
        if(CheckCollisionPointRec(pos,(Rectangle){gui.buttons[3].top_left.x,gui.buttons[3].top_left.y,gui.buttons[3].dim.x,gui.buttons[3].dim.y}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isreleased){
            state = normal;
            stateflag = 0;    
        }
        if(stateflag == 1 && pos.x-1 < gui.CanvasBottomRight.x && pos.x-1 > gui.CanvasTopLeft.x && pos.y-1 > gui.CanvasTopLeft.y && pos.y < gui.CanvasBottomRight.y && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isreleased){
            pos2 = pos;
            stateflag = 2;
        }
        if(stateflag == 0 && pos.x-1 < gui.CanvasBottomRight.x && pos.x-1 > gui.CanvasTopLeft.x && pos.y-1 > gui.CanvasTopLeft.y && pos.y < gui.CanvasBottomRight.y && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isreleased){
            pos1 = pos;
            stateflag = 1;
        }
        if(stateflag == 2){
            MyDrawRectangle(screen,pos1,pos2,pen.color);
            state = normal;
            stateflag = 0;
            isreleased = 0;
        }
        break;
        case ellipse:
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){isreleased = 1;}
        if(CheckCollisionPointRec(pos,(Rectangle){gui.buttons[5].top_left.x,gui.buttons[5].top_left.y,gui.buttons[5].dim.x,gui.buttons[5].dim.y}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isreleased){
            state = normal;
            stateflag = 0;    
        }
        if(stateflag == 1 && pos.x-1 < gui.CanvasBottomRight.x && pos.x-1 > gui.CanvasTopLeft.x && pos.y-1 > gui.CanvasTopLeft.y && pos.y < gui.CanvasBottomRight.y && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isreleased){
            pos2 = pos;
            stateflag = 2;
        }
        if(stateflag == 0 && pos.x-1 < gui.CanvasBottomRight.x && pos.x-1 > gui.CanvasTopLeft.x && pos.y-1 > gui.CanvasTopLeft.y && pos.y < gui.CanvasBottomRight.y && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isreleased){
            pos1 = pos;
            stateflag = 1;
        }
        if(stateflag == 2){
            MyDrawEllipse(screen,pos1,pos2,pen.color);
            state = normal;
            stateflag = 0;
            isreleased = 0;
        }
        break;

        case normal:

        // text boxes
        for(int i = 0;i<gui.num_textboxes;i++){
            textbox t = gui.textboxes[i];
            if(CheckCollisionPointRec(pos,(Rectangle){t.top_left.x,t.top_left.y,t.dim.x,t.dim.y})){
                uptextbox = i + 1;
            }
        }
        
        //on click
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            curdown = true;

            //buttons
            Button_Ifpressed(gui.buttons[0],pos,screen,&qsplines,&lines,&points);
            Button_Ifpressed(gui.buttons[1],pos,screen,gui.textboxes[1].text,NULL,NULL);
            Button_Ifpressed(gui.buttons[2],pos,screen,gui.textboxes[2].text,NULL,NULL);
            Button_Ifpressed(gui.buttons[3],pos,screen,&curdown,NULL,NULL);
            Button_Ifpressed(gui.buttons[4],pos,screen,gui.textboxes[3].text,gui.textboxes[4].text,NULL);
            Button_Ifpressed(gui.buttons[5],pos,screen,&curdown,NULL,NULL);
            //sliders
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

        if(uptextbox){
            if(uptextbox == 1){
                int key = GetKeyPressed();
                    if(key == KEY_BACKSPACE && gui.textboxes[0].len != 0 ){
                        gui.textboxes[0].text[gui.textboxes[0].len-1] = '\0';
                        gui.textboxes[0].len = gui.textboxes[0].len - 1;
                    }
                    if(key>= 48 && key<=57 && gui.textboxes[0].len != 3){
                        gui.textboxes[0].text[gui.textboxes[0].len] = (char)key;
                        gui.textboxes[0].len = gui.textboxes[0].len + 1;
                    }
                    if(atoi(gui.textboxes[0].text)>150){
                        gui.textboxes[0].text[0] = '1';
                        gui.textboxes[0].text[1] = '5';
                        gui.textboxes[0].text[2] = '0';
                    }
                    pen.thickness = atoi(gui.textboxes[0].text);
                    uptextbox = 0;
            }
            if(uptextbox == 2){
                int key = GetKeyPressed();
                    if(key == KEY_BACKSPACE && gui.textboxes[1].len != 0 ){
                        gui.textboxes[1].text[gui.textboxes[1].len-1] = '\0';
                        gui.textboxes[1].len = gui.textboxes[1].len - 1;
                    }
                    if(key>= 32 && key<=126 && gui.textboxes[1].len != 40){
                        gui.textboxes[1].text[gui.textboxes[1].len] = (char)key;
                        gui.textboxes[1].len = gui.textboxes[1].len + 1;
                    }
                    uptextbox = 0;
            }
            if(uptextbox == 3){
                int key = GetKeyPressed();
                    if(key == KEY_BACKSPACE && gui.textboxes[2].len != 0 ){
                        gui.textboxes[2].text[gui.textboxes[2].len-1] = '\0';
                        gui.textboxes[2].len = gui.textboxes[2].len - 1;
                    }
                    if(key>= 32 && key<=126 && gui.textboxes[2].len != 40){
                        gui.textboxes[2].text[gui.textboxes[2].len] = (char)key;
                        gui.textboxes[2].len = gui.textboxes[2].len + 1;
                    }
                    uptextbox = 0;
            }
            if(uptextbox == 4){
                int key = GetKeyPressed();
                    if(key == KEY_BACKSPACE && gui.textboxes[3].len != 0 ){
                        gui.textboxes[3].text[gui.textboxes[3].len-1] = '\0';
                        gui.textboxes[3].len = gui.textboxes[3].len - 1;
                    }
                    if(key>= 48 && key<=57 && gui.textboxes[3].len != 3){
                        gui.textboxes[3].text[gui.textboxes[3].len] = (char)key;
                        gui.textboxes[3].len = gui.textboxes[3].len + 1;
                    }
                    if(atoi(gui.textboxes[3].text)>900){
                        gui.textboxes[3].text[0] = '9';
                        gui.textboxes[3].text[1] = '0';
                        gui.textboxes[3].text[2] = '0';
                    }
                    uptextbox = 0;
            }
            if(uptextbox == 5){
                int key = GetKeyPressed();
                    if(key == KEY_BACKSPACE && gui.textboxes[4].len != 0 ){
                        gui.textboxes[4].text[gui.textboxes[4].len-1] = '\0';
                        gui.textboxes[4].len = gui.textboxes[4].len - 1;
                    }
                    if(key>= 48 && key<=57 && gui.textboxes[4].len != 3){
                        gui.textboxes[4].text[gui.textboxes[4].len] = (char)key;
                        gui.textboxes[4].len = gui.textboxes[4].len + 1;
                    }
                    if(atoi(gui.textboxes[4].text)>650){
                        gui.textboxes[4].text[0] = '6';
                        gui.textboxes[4].text[1] = '5';
                        gui.textboxes[4].text[2] = '0';
                    }
                    uptextbox = 0;
            }
        }     
        AddLines(screen,&lines);
        AddQSplines(screen,&qsplines);
        break;
        }

        


        BeginDrawing();
            DrawScreen(screen);
   

            //.DrawQSplines(&qsplines);
            //.DrawLines(&lines);
        EndDrawing();


    }
    CloseWindow();
    return 0;


}