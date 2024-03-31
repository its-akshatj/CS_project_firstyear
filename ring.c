#include"things.h"

Ring GenerateRing(){
    Ring ret;
    ret.radius = 700;
    int r = rand()%1;
    switch(r){
        case 0:
            ret.start_angle = rand()%360;
            ret.end_angle = ret.start_angle +240 +rand()%60;
            //ret.end_angle = ret.start_angle + rand()%(360-(int)ret.start_angle);
            ret.segments = 40;
        break;
    }
    return ret;
}

void DrawRings(VectorRing* rings){
    
    for(int i = 0;i<rings->len;i++){
        //printf("ring to be printed %f %f %f %f %d\n",(rings->arr)[i].radius,(rings->arr)[i].radius + 3,(rings->arr)[i].start_angle,(rings->arr)[i].end_angle,(rings->arr)[i].segments);
        DrawRing((Vector2){640,360},(rings->arr)[i].radius,(rings->arr)[i].radius + 3,(rings->arr)[i].start_angle,(rings->arr)[i].end_angle,(rings->arr)[i].segments,BLUE);
    }
}

void DrawPlayer(Player p){
    //printf("player to be printed %f %f %f\n",Vector2Sum((Vector2){640,360},(Vector2){cosf(p.angle)*p.distance,sinf(p.angle)*p.distance}).x,Vector2Sum((Vector2){640,360},(Vector2){cosf(p.angle)*p.distance,sinf(p.angle)*p.distance}).y,p.radius);
    DrawCircleV(Vector2Sum((Vector2){640,360},(Vector2){cosf(p.angle)*p.distance,sinf(p.angle)*p.distance}),p.radius,RED);
}

void DrawBackground(){
    DrawCircle(640,360,50,(Color){12,110,225,255});
}

void ShouldDie(Player p,Ring r,VectorRing* rings,enum Window* w,int* score,VectorRing* dead_rings,float* speed ){
        float end = (r.end_angle>360) ? r.end_angle - 360 : r.end_angle;
        if(end > r.start_angle && (p.angle/(2*PI))*360>r.start_angle && (p.angle/(2*PI))*360<r.end_angle){
           
            *w = paint;
         
            VectorRing_Empty(rings);
           
            VectorRing_Empty(dead_rings);
         
            *score = 0;
            *speed = 100;
            VectorRing_Add(rings,GenerateRing(),0);
          
        }
        if(end<r.start_angle && !((p.angle/(2*PI))*360>end && (p.angle/(2*PI))*360 < r.start_angle)){
         
            *w = paint;
            VectorRing_Empty(rings);
            VectorRing_Empty(dead_rings);
            *score = 0;
            *speed = 100;
            VectorRing_Add(rings,GenerateRing(),0);
            
        }
}