#include"things.h"
extern Gui gui;
extern Pen pen;
extern enum State state;
extern Sym sym;

void MyDrawPixelCanvas(pixel* screen,Vector2 pos,Color color){
    if(pos.x-1 < gui.CanvasBottomRight.x && pos.x-1 > gui.CanvasTopLeft.x && pos.y-1 > gui.CanvasTopLeft.y && pos.y < gui.CanvasBottomRight.y){
        screen[(int)(gui.screenwidth)*(int)pos.y + (int)(pos.x)] = (pixel){color};
    }
}

bool InCanvas(Vector2 pos){
    if(pos.x-1 < gui.CanvasBottomRight.x && pos.x-1 > gui.CanvasTopLeft.x && pos.y-1 > gui.CanvasTopLeft.y && pos.y < gui.CanvasBottomRight.y){
        return true;
    }
    return false;
}

void MyDrawRectangle(pixel* screen,Vector2 top_left,Vector2 bottom_right,Color color){
    if(bottom_right.x < top_left.x){
        float temp = bottom_right.x;
        bottom_right.x = top_left.x;
        top_left.x = temp;
    }
    if(bottom_right.y < top_left.y){
        float temp = bottom_right.y;
        bottom_right.y = top_left.y;
        top_left.y = temp;
    }
    for(int i = 0;i<=bottom_right.x-top_left.x;i++){
        for(int j = 0;j<=bottom_right.y-top_left.y;j++){
            screen[(int)(top_left.x + top_left.y*gui.screenwidth + i + j*gui.screenwidth)].color = color;
        }
    }

}

void DrawHollowRectangle(pixel* screen,Vector2 top_left,Vector2 bottom_right,int thickness,Color color){
    if(bottom_right.x < top_left.x){
        float temp = bottom_right.x;
        bottom_right.x = top_left.x;
        top_left.x = temp;
    }
    if(bottom_right.y < top_left.y){
        float temp = bottom_right.y;
        bottom_right.y = top_left.y;
        top_left.y = temp;
    }
    MyDrawRectangle(screen,top_left,(Vector2){bottom_right.x,top_left.y+thickness-1},color);
    MyDrawRectangle(screen,(Vector2){top_left.x,bottom_right.y-thickness+1},bottom_right,color);

    MyDrawRectangle(screen,top_left,(Vector2){top_left.x+thickness-1,bottom_right.y},color);
    MyDrawRectangle(screen,(Vector2){bottom_right.x - thickness + 1,top_left.y},bottom_right,color);
}

void DrawSymHollowRectangle(pixel* screen,pixel* mask,Vector2 top_left,Vector2 bottom_right,int thickness,Color color){
    if(bottom_right.x < top_left.x){
        float temp = bottom_right.x;
        bottom_right.x = top_left.x;
        top_left.x = temp;
    }
    if(bottom_right.y < top_left.y){
        float temp = bottom_right.y;
        bottom_right.y = top_left.y;
        top_left.y = temp;
    }

    Vector2 a = GetSymPoint(top_left),b=GetSymPoint((Vector2){bottom_right.x,top_left.y}),c = GetSymPoint(bottom_right),d = GetSymPoint((Vector2){top_left.x,bottom_right.y});
    int x_y  = (((a.x > b.x) ? a.x - b.x : b.x - a.x) > ((a.y > b.y) ? a.y - b.y : b.y - a.y) ) ? ((a.x > b.x) ? a.x - b.x : b.x - a.x) : ((a.y > b.y) ? a.y - b.y : b.y - a.y);
    for(int i = 0;i<x_y*1.2;i++){
       MyDrawPixelCanvas(screen,GetSplinePointLinear(a,b,i/(x_y*1.2)),pen.color);
       MyDrawPixelCanvas(mask,GetSplinePointLinear(a,b,i/(x_y*1.2)),pen.color);
    }
    x_y  = (((b.x > c.x) ? b.x - c.x : c.x - b.x) > ((b.y > c.y) ? b.y - c.y : c.y - b.y) ) ? ((b.x > c.x) ? b.x - c.x : c.x - b.x) : ((b.y > c.y) ? b.y - c.y : c.y - b.y);
    for(int i = 0;i<x_y*1.2;i++){
       MyDrawPixelCanvas(screen,GetSplinePointLinear(b,c,i/(x_y*1.2)),pen.color);
       MyDrawPixelCanvas(mask,GetSplinePointLinear(b,c,i/(x_y*1.2)),pen.color);
    }
    x_y  = (((c.x > d.x) ? c.x - d.x : d.x - c.x) > ((c.y > d.y) ? c.y - d.y : d.y - c.y) ) ? ((c.x > d.x) ? c.x - d.x : d.x - c.x) : ((c.y > d.y) ? c.y - d.y : d.y - c.y);
    for(int i = 0;i<x_y*1.2;i++){
       MyDrawPixelCanvas(screen,GetSplinePointLinear(d,c,i/(x_y*1.2)),pen.color);
       MyDrawPixelCanvas(mask,GetSplinePointLinear(d,c,i/(x_y*1.2)),pen.color);
    }
    x_y  = (((d.x > a.x) ? d.x - a.x : a.x - d.x) > ((d.y > a.y) ? d.y - a.y : a.y - d.y) ) ? ((d.x > a.x) ? d.x - a.x : a.x - d.x) : ((d.y > a.y) ? d.y - a.y : a.y - d.y);
    for(int i = 0;i<x_y*1.2;i++){
       MyDrawPixelCanvas(screen,GetSplinePointLinear(a,d,i/(x_y*1.2)),pen.color);
       MyDrawPixelCanvas(mask,GetSplinePointLinear(a,d,i/(x_y*1.2)),pen.color);
    }

    a = GetSymPoint(Vector2Sum(top_left,(Vector2){pen.thickness,pen.thickness})),
    b = GetSymPoint(Vector2Sum((Vector2){bottom_right.x,top_left.y},(Vector2){-1*pen.thickness,pen.thickness})),
    c = GetSymPoint(Vector2Sum(bottom_right,(Vector2){-1*pen.thickness,-1*pen.thickness})),
    d = GetSymPoint(Vector2Sum((Vector2){top_left.x,bottom_right.y},(Vector2){pen.thickness,-1*pen.thickness}));
    x_y  = (((a.x > b.x) ? a.x - b.x : b.x - a.x) > ((a.y > b.y) ? a.y - b.y : b.y - a.y) ) ? ((a.x > b.x) ? a.x - b.x : b.x - a.x) : ((a.y > b.y) ? a.y - b.y : b.y - a.y);
    for(int i = 0;i<x_y*1.2;i++){
       MyDrawPixelCanvas(screen,GetSplinePointLinear(a,b,i/(x_y*1.2)),pen.color);
       MyDrawPixelCanvas(mask,GetSplinePointLinear(a,b,i/(x_y*1.2)),pen.color);
    }
    x_y  = (((b.x > c.x) ? b.x - c.x : c.x - b.x) > ((b.y > c.y) ? b.y - c.y : c.y - b.y) ) ? ((b.x > c.x) ? b.x - c.x : c.x - b.x) : ((b.y > c.y) ? b.y - c.y : c.y - b.y);
    for(int i = 0;i<x_y*1.2;i++){
       MyDrawPixelCanvas(screen,GetSplinePointLinear(b,c,i/(x_y*1.2)),pen.color);
       MyDrawPixelCanvas(mask,GetSplinePointLinear(b,c,i/(x_y*1.2)),pen.color);
    }
    x_y  = (((c.x > d.x) ? c.x - d.x : d.x - c.x) > ((c.y > d.y) ? c.y - d.y : d.y - c.y) ) ? ((c.x > d.x) ? c.x - d.x : d.x - c.x) : ((c.y > d.y) ? c.y - d.y : d.y - c.y);
    for(int i = 0;i<x_y*1.2;i++){
       MyDrawPixelCanvas(screen,GetSplinePointLinear(d,c,i/(x_y*1.2)),pen.color);
       MyDrawPixelCanvas(mask,GetSplinePointLinear(d,c,i/(x_y*1.2)),pen.color);
    }
    x_y  = (((d.x > a.x) ? d.x - a.x : a.x - d.x) > ((d.y > a.y) ? d.y - a.y : a.y - d.y) ) ? ((d.x > a.x) ? d.x - a.x : a.x - d.x) : ((d.y > a.y) ? d.y - a.y : a.y - d.y);
    for(int i = 0;i<x_y*1.2;i++){
       MyDrawPixelCanvas(screen,GetSplinePointLinear(a,d,i/(x_y*1.2)),pen.color);
       MyDrawPixelCanvas(mask,GetSplinePointLinear(a,d,i/(x_y*1.2)),pen.color);
    }

    FillMaskBucket(screen,mask,Vector2Mult(0.5,Vector2Sum(GetSymPoint(top_left),a)));

    MyDrawRectangle(screen,top_left,(Vector2){bottom_right.x,top_left.y+thickness-1},color);
    MyDrawRectangle(screen,(Vector2){top_left.x,bottom_right.y-thickness+1},bottom_right,color);
    MyDrawRectangle(screen,top_left,(Vector2){top_left.x+thickness-1,bottom_right.y},color);
    MyDrawRectangle(screen,(Vector2){bottom_right.x - thickness + 1,top_left.y},bottom_right,color);
}

void MyDrawSymRectangle(pixel* screen,pixel* mask,Vector2 top_left,Vector2 bottom_right,Color color){
    if(bottom_right.x < top_left.x){
        float temp = bottom_right.x;
        bottom_right.x = top_left.x;
        top_left.x = temp;
    }
    if(bottom_right.y < top_left.y){
        float temp = bottom_right.y;
        bottom_right.y = top_left.y;
        top_left.y = temp;
    }
    Vector2 a = GetSymPoint(top_left),b=GetSymPoint((Vector2){bottom_right.x,top_left.y}),c = GetSymPoint(bottom_right),d = GetSymPoint((Vector2){top_left.x,bottom_right.y});
    
    float x_y  = 1.1*(((a.x > b.x) ? a.x - b.x : b.x - a.x) > ((a.y > b.y) ? a.y - b.y : b.y - a.y) ) ? ((a.x > b.x) ? a.x - b.x : b.x - a.x) : ((a.y > b.y) ? a.y - b.y : b.y - a.y);
    float len = 1.1*(((b.x > c.x) ? b.x - c.x : c.x - b.x) > ((b.y > c.y) ? b.y - c.y : c.y - b.y) ) ? ((b.x > c.x) ? b.x - c.x : c.x - b.x) : ((b.y > c.y) ? b.y - c.y : c.y - b.y);
    vector points = GiveVector();
    for(int j = 0;j < len;j++){
        Vector_Add50e(&points,GetSplinePointLinear(b,c,j/len));
    }
    Vector2 cur = b;
    for(int i = 1;i<x_y-1;i++){
        Vector2 next = GetSplinePointLinear(b,a,i/x_y);
        for(int it = 0;it<points.len;it++){
            MyDrawPixelCanvas(screen,points.arr[it],pen.color);
        }

        if(next.x - cur.x != 0){
            for(int it = 0;it<points.len;it++){
                points.arr[it] = Vector2Sum(points.arr[it],(Vector2){next.x-cur.x,0});
                MyDrawPixelCanvas(screen,points.arr[it],pen.color);
            }
        }

        if(next.y - cur.y != 0){
            for(int it = 0;it<points.len;it++){
                points.arr[it] = Vector2Sum(points.arr[it],(Vector2){0,next.y - cur.y});
                MyDrawPixelCanvas(screen,points.arr[it],pen.color);
            }
        }
        printf("{%f,%f}\n",next.x - cur.x,next.y - cur.y);
        cur = next;
    }


    for(int i = 0;i<=bottom_right.x-top_left.x;i++){
        for(int j = 0;j<=bottom_right.y-top_left.y;j++){
            screen[(int)(top_left.x + top_left.y*gui.screenwidth + i + j*gui.screenwidth)].color = color;
        }
    }
}

void MyDrawCircle(pixel* screen,Vector2 center,int radius,Color color){
    for(int i = 0;i<radius;i++){
        int k = radius*radius;
        for(int j = 0;i*i + j*j <= k;j++){
            MyDrawPixelCanvas(screen,Vector2Sum(center,(Vector2){j,i}),color);
            MyDrawPixelCanvas(screen,Vector2Sum(center,(Vector2){-j,-i}),color);
            MyDrawPixelCanvas(screen,Vector2Sum(center,(Vector2){j,-i}),color);
            MyDrawPixelCanvas(screen,Vector2Sum(center,(Vector2){-j,i}),color);
        }
    }
}

void MyDrawEllipse(pixel* screen,Vector2 top_left,Vector2 bottom_right,Color color){
    if(bottom_right.x < top_left.x){
        float temp = bottom_right.x;
        bottom_right.x = top_left.x;
        top_left.x = temp;
    }
    if(bottom_right.y < top_left.y){
        float temp = bottom_right.y;
        bottom_right.y = top_left.y;
        top_left.y = temp;
    }
    Vector2 center = (Vector2){(top_left.x+bottom_right.x)/2.0,(top_left.y+bottom_right.y)/2.0};
    float a_square = (bottom_right.x-center.x)*(bottom_right.x-center.x);
    float b_square = (bottom_right.y-center.y)*(bottom_right.y-center.y);
    for(int i = 0;i<(bottom_right.x-center.x);i++){
        for(int j  = 0;(i*i)/a_square + (j*j)/b_square < 1;j++){
            MyDrawPixelCanvas(screen,Vector2Sum(center,(Vector2){-i,j}),color);
            MyDrawPixelCanvas(screen,Vector2Sum(center,(Vector2){-i,-j}),color);
            MyDrawPixelCanvas(screen,Vector2Sum(center,(Vector2){i,-j}),color);
            MyDrawPixelCanvas(screen,Vector2Sum(center,(Vector2){i,j}),color);
        }
    } 

}

void DrawHollowEllipse(pixel* screen,Vector2 top_left,Vector2 bottom_right,int thickness,Color color){
    if(bottom_right.x < top_left.x){
        float temp = bottom_right.x;
        bottom_right.x = top_left.x;
        top_left.x = temp;
    }
    if(bottom_right.y < top_left.y){
        float temp = bottom_right.y;
        bottom_right.y = top_left.y;
        top_left.y = temp;
    }
    Vector2 center = (Vector2){(top_left.x+bottom_right.x)/2.0,(top_left.y+bottom_right.y)/2.0};
    float a_square = (bottom_right.x-center.x)*(bottom_right.x-center.x);
    float b_square = (bottom_right.y-center.y)*(bottom_right.y-center.y);

    for(int i = 0;i<(bottom_right.x-center.x);i++){
        for(int j  = 0;(i*i)/a_square + (j*j)/b_square < 1;j++){
            if((i*i)/a_square + (j*j)/b_square > ((bottom_right.x - center.x - thickness)*(bottom_right.x - center.x - thickness))/a_square){
            MyDrawPixelCanvas(screen,Vector2Sum(center,(Vector2){-i,j}),color);
            MyDrawPixelCanvas(screen,Vector2Sum(center,(Vector2){-i,-j}),color);
            MyDrawPixelCanvas(screen,Vector2Sum(center,(Vector2){i,-j}),color);
            MyDrawPixelCanvas(screen,Vector2Sum(center,(Vector2){i,j}),color);
            }
        }
    } 

}

void MyDrawSymEllipse(pixel* screen,Vector2 top_left,Vector2 bottom_right,Color color){
    if(bottom_right.x < top_left.x){
        float temp = bottom_right.x;
        bottom_right.x = top_left.x;
        top_left.x = temp;
    }
    if(bottom_right.y < top_left.y){
        float temp = bottom_right.y;
        bottom_right.y = top_left.y;
        top_left.y = temp;
    }
    Vector2 center = (Vector2){(top_left.x+bottom_right.x)/2.0,(top_left.y+bottom_right.y)/2.0};
    float a_square = (bottom_right.x-center.x)*(bottom_right.x-center.x);
    float b_square = (bottom_right.y-center.y)*(bottom_right.y-center.y);
    for(int i = 0;i<(bottom_right.x-center.x);i++){
        for(int j  = 0;(i*i)/a_square + (j*j)/b_square < 1;j++){
            MyDrawPixelCanvas(screen,Vector2Sum(center,(Vector2){-i,j}),color);
            MyDrawPixelCanvas(screen,Vector2Sum(center,(Vector2){-i,-j}),color);
            MyDrawPixelCanvas(screen,Vector2Sum(center,(Vector2){i,-j}),color);
            MyDrawPixelCanvas(screen,Vector2Sum(center,(Vector2){i,j}),color);
            
            MyDrawPixelCanvas(screen,GetSymPoint(Vector2Sum(center,(Vector2){-i,j})),color);
            MyDrawPixelCanvas(screen,GetSymPoint(Vector2Sum(center,(Vector2){-i,-j})),color);
            MyDrawPixelCanvas(screen,GetSymPoint(Vector2Sum(center,(Vector2){i,-j})),color);
            MyDrawPixelCanvas(screen,GetSymPoint(Vector2Sum(center,(Vector2){i,j})),color);
        }
    } 

}

void ClearScreen(pixel* screen,vector* qsplines,vector* lines,vector* points){
    for(int i = 0;i<gui.screenwidth*gui.screenheight;i++){
        screen[i] = (pixel){WHITE};
    }
    Vector_Empty(qsplines);
    Vector_Empty(lines);
    Vector_Empty(points);
    
}

void ClearCanvas(pixel* screen,vector* qsplines,vector* lines,vector* points){
    for(int i = gui.CanvasTopLeft.y+1;i < gui.CanvasBottomRight.y;i++){
        for(int j = gui.CanvasTopLeft.x+1; j < gui.CanvasBottomRight.x;j++){
            screen[i*gui.screenwidth + j] = (pixel){WHITE};
        }
        
    }
    Vector_Empty(qsplines);
    Vector_Empty(lines);
    Vector_Empty(points);
    
}

void ClearCanvasPixels(pixel* screen){
    for(int i = gui.CanvasTopLeft.y+1;i < gui.CanvasBottomRight.y;i++){
        for(int j = gui.CanvasTopLeft.x+1; j < gui.CanvasBottomRight.x;j++){
            screen[i*gui.screenwidth + j] = (pixel){WHITE};
        }   
    }
}

void CanvasFitDim(pixel* screen,int width,int height){
    AddGuiBase(screen,WHITE);
    ClearCanvasPixels(screen);
    gui.CanvasTopLeft = Vector2Sum(gui.CanvasCenter,(Vector2){-1*width/2 - 1,-1*height/2 -1});
    gui.CanvasBottomRight = Vector2Sum(gui.CanvasTopLeft,(Vector2){width+1,height+1});
    AddGuiBase(screen,RED);
}

void DrawScreen(pixel* screen){
    ClearBackground(RAYWHITE);
    for(int i = gui.CanvasTopLeft.x-gui.CanvasBorderThickness+1;i<=gui.CanvasBottomRight.x+gui.CanvasBorderThickness-1;i++){
        for(int j = gui.CanvasTopLeft.y-gui.CanvasBorderThickness+1;j<=gui.CanvasBottomRight.y+gui.CanvasBorderThickness-1;j++){
            DrawRectangle(i,j,1,1,screen[gui.screenwidth*j + i].color);
        }
        
    }


    for(int i = 0;i<gui.num_buttons;i++){
        if(gui.buttons[i].ispressed){
       
            DrawTextureV(gui.buttons[i].ptexture,gui.buttons[i].top_left,WHITE);
        }
        else DrawTextureV(gui.buttons[i].texture,gui.buttons[i].top_left,WHITE);
    }

    for(int i = 0;i<gui.num_sliders;i++){
        DrawSlider(gui.sliders[i]);
    }

    for(int i = 0;i<gui.num_textboxes;i++){
        Draw_Textboxes(gui.textboxes[i]);
    }

}

void Draw_Textboxes(textbox t){
    DrawRectangle(t.top_left.x,t.top_left.y,t.dim.x,t.dim.y,BLUE);
    DrawText(t.text,t.top_left.x,t.top_left.y,t.dim.y,RED);
}

void AddGuiBase(pixel* screen,Color color){
    MyDrawRectangle(screen,(Vector2){gui.CanvasTopLeft.x-gui.CanvasBorderThickness,gui.CanvasTopLeft.y-gui.CanvasBorderThickness},(Vector2){gui.CanvasBottomRight.x+gui.CanvasBorderThickness,gui.CanvasTopLeft.y},color);
    MyDrawRectangle(screen,(Vector2){gui.CanvasTopLeft.x-gui.CanvasBorderThickness,gui.CanvasBottomRight.y},(Vector2){gui.CanvasBottomRight.x+gui.CanvasBorderThickness,gui.CanvasBottomRight.y+gui.CanvasBorderThickness},color);
    MyDrawRectangle(screen,(Vector2){gui.CanvasTopLeft.x-gui.CanvasBorderThickness,gui.CanvasTopLeft.y},(Vector2){gui.CanvasTopLeft.x,gui.CanvasBottomRight.y},color);
    MyDrawRectangle(screen,(Vector2){gui.CanvasBottomRight.x,gui.CanvasTopLeft.y},(Vector2){gui.CanvasBottomRight.x+gui.CanvasBorderThickness,gui.CanvasBottomRight.y},color); 
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

void AddQSplines(pixel* screen,vector* qsplines){
    Vector2 a = sym.pos1;
    Vector2 b = Vector2Minus(sym.pos2,sym.pos1);
    for(int i = 0;i<(qsplines->len);i+=3){
        for(int k = 0;k<100;k++){
            Vector2 p = GetSplinePointBezierQuad((qsplines->arr)[i],(qsplines->arr)[i+1],(qsplines->arr)[i+2],(float)k/100.0); //k is getting promoted
           if(InCanvas(sym.pos1) && InCanvas(sym.pos2)){
            MyDrawCircle(screen,
                        Vector2Minus(Vector2Mult(2,Vector2Sum(a,Vector2Mult(Vector2Dot(Vector2Minus(p,a),b)/Vector2Dot(b,b),b))),p),
                         pen.thickness,pen.color);
           }
            MyDrawCircle(screen,p,pen.thickness,pen.color);
        }
    }
    Vector_Empty(qsplines);
}

void AddLines(pixel* screen,vector* lines){
    Vector2 a = sym.pos1;
    Vector2 b = Vector2Minus(sym.pos2,sym.pos1);
    for(int i = 0;i<lines->len;i+=2){
        for(int k = 0;k<100;k++){
            Vector2 p = GetSplinePointLinear((lines->arr)[i],(lines->arr)[i+1],k/100.0); //k is getting type promoted
            if(InCanvas(sym.pos1) && InCanvas(sym.pos2)){
            MyDrawCircle(screen,
                        Vector2Minus(Vector2Mult(2,Vector2Sum(a,Vector2Mult(Vector2Dot(Vector2Minus(p,a),b)/Vector2Dot(b,b),b))),p),
                         pen.thickness,pen.color);
           }
            MyDrawCircle(screen,p,pen.thickness,pen.color);
        }
        Vector_Empty(lines);
    }
}

void DrawSymLine(){
    DrawLineEx(sym.pos1,sym.pos2,sym.thick,sym.color);
    DrawCircleV(sym.pos1,sym.r1,sym.color);
    DrawCircleV(sym.pos2,sym.r1,sym.color);
}

bool IsSymOn(){
    if(InCanvas(sym.pos1) && InCanvas(sym.pos2)){
        return true;
    }
   return false;
}

Vector2 GetSymPoint(Vector2 p){
    Vector2 a = sym.pos1;
    Vector2 b = Vector2Minus(sym.pos2,sym.pos1);
    return Vector2Minus(Vector2Mult(2,Vector2Sum(a,Vector2Mult(Vector2Dot(Vector2Minus(p,a),b)/Vector2Dot(b,b),b))),p);
}

void ClearMask(pixel* mask){
    for(int i = 0;i<gui.screenwidth*gui.screenheight;i++){
        mask[i] = (pixel){WHITE};
    }
}











