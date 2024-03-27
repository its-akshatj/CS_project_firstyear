#include"things.h"
extern Gui gui;
extern Pen pen;
extern enum State state;

Vector2 Vector2Sum(Vector2 a,Vector2 b){
    return (Vector2){a.x+b.x,a.y+b.y};
}

void Button_LoadTextures(){
    for(int i = 0;i<gui.num_buttons;i++){
        gui.buttons[i].texture = LoadTexture(gui.buttons[i].texture_path);
    }
}

void Button_Ifpressed(button but,Vector2 cur_pos,void* a,void* b,void* c,void* d){
    if(CheckCollisionPointRec(cur_pos,(Rectangle){but.top_left.x,but.top_left.y,but.dim.x,but.dim.y})){
        but.func(a,b,c,d);
    }
}

void ScreenClearButton(void* a,void* b,void* c,void* d){
    pixel* screen = (pixel*)a;
    vector* qsplines = (vector*)b;
    vector* lines = (vector*)c;
    vector* points = (vector*)d;
    ClearCanvas(screen,qsplines,lines,points);
}

void SaveAsPpm6(void* a,void* b,void* c,void* d){
    pixel* screen = (pixel*)a;
    char* filename = (char*)b;

    FILE *f = fopen(filename,"w");
    fprintf(f,"P6 %d %d 255\n",(int)gui.CanvasBottomRight.x-(int)gui.CanvasTopLeft.x-1,(int)gui.CanvasBottomRight.y-(int)gui.CanvasTopLeft.y -1);
    fclose(f);
    FILE *f1 = fopen(filename,"ab");
    for(int i = gui.CanvasTopLeft.y+1;i < gui.CanvasBottomRight.y;i++){
        for(int j = gui.CanvasTopLeft.x+1; j < gui.CanvasBottomRight.x;j++){
            char pixel[3] ={screen[i*gui.screenwidth + j].color.r,screen[i*gui.screenwidth + j].color.g,screen[i*gui.screenwidth + j].color.b}; 
            fwrite(pixel,1,3,f1);
        }
    }
    fclose(f1);
}

void LoadPpm6(void* a,void* b,void* c,void* d){
    pixel* screen = (pixel*)a;
    char* filename = (char*)b;

    FILE *f = fopen(filename,"r");
    char w[4] = {0},h[4] = {0},trash[4];
    fscanf(f,"%s %s %s %s",trash,w,h,trash);
    CanvasFitDim(screen,atoi(w),atoi(h));
    if(fgetc(f) == '\n'){
        printf("a");
    }
    for(int i = gui.CanvasTopLeft.y+1;i < gui.CanvasBottomRight.y;i++){
        for(int j = gui.CanvasTopLeft.x+1; j < gui.CanvasBottomRight.x;j++){
            screen[i*gui.screenwidth + j] = (pixel){(Color){fgetc(f),fgetc(f),fgetc(f),255}};
        }
    }
    fclose(f);
}

void DrawSlider(slider s){
    DrawRectangle(s.pos.x + s.slide * s.bar_dim.x - s.rect_dim.x/2,s.pos.y - (s.rect_dim.y - s.bar_dim.y)/2,s.rect_dim.x,s.rect_dim.y,BLACK);
    DrawRectangleGradientH(s.pos.x,s.pos.y,s.bar_dim.x,s.bar_dim.y,BLACK,s.color);
}

void RectTool(void* a,void* b,void* c,void* d){
    pixel* screen = (pixel*)a;
    bool* curdown = (bool*)b;
    *curdown = false;
    state = rect;
}

void NewButton(void* a,void* b,void* c,void* d){
    pixel* screen = (pixel*)a;
    char* width = (char*)b;
    char* height = (char*)c;
    CanvasFitDim(screen,atoi(width),atoi(height));
}

void EllipseTool(void* a,void* b,void* c,void* d){
    bool* curdown = (bool*)a;
    *curdown = false;
    state = ellipse;
}

void LineTool(void* a,void* b,void* c,void* d){
    bool* curdown = (bool*)a;
    *curdown = false;
    state = line;
}

void RatioLock(void* a,void* b,void* c,void* d){
    bool* ratiolock = (bool*)a;
    if(*ratiolock == true) *ratiolock = false;
    else *ratiolock = true;
}






