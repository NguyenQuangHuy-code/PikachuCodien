#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include"game.h"

using namespace std;

int point=0,pre_point=0;

int mix=5,help=5;

int tong=sizew*sizeh;

vector<vector<int> > pokemonx(number_pokemons+1,vector<int>());
vector<vector<int> > pokemony(number_pokemons+1,vector<int>());

vector<vector<int> > l(sizeh+2,vector<int>(sizew+2,0));

int thu;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* surface;
SDL_Texture* texture;
Mix_Chunk* nope;
SDL_Rect sourceRect;
SDL_Rect desRect;
TTF_Font* font;
SDL_Color fg;
int timer=0;
int timee;
int stage=1;
int kt=1;
SDL_Event e;

int main(int argc,char* argv[])
{
    srand(time(NULL));

    initSDL(window, renderer);

    start:

    stage=1;
    tong=sizeh*sizew;
    mix=help=5;
    point=0;
    pre_point=0;

    SDL_SetRenderDrawColor(renderer,128,128,128,255);  //gray
    SDL_RenderClear(renderer);

    desRect.x=0;
    desRect.y=c_pad;
    desRect.w=SCREEN_WIDTH;
    desRect.h=SCREEN_HEIGHT-2*c_pad;
    load_image(renderer,surface,texture,NULL,&desRect,"back1.bmp");
    SDL_RenderPresent(renderer);

    int play_button=0, high_button=0, mix_button=0, help_button=0, pause_button=0, resume_button=0, back_button=0;
    while (kt==1)
    {
        //SDL_Delay(10);

        SDL_RenderPresent(renderer);

        if ( SDL_PollEvent(&e) == 0) continue;

        if (e.type == SDL_QUIT)
        {
            kt=0;
            break;
        }

        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
        {
            kt=0;
            break;
        }

        if ( e.type == SDL_MOUSEMOTION )
        {
            int x = e.motion.x;
            int y = e.motion.y;
            if (2209*pow(x-726,2)+16129*pow(y-417,2)<=35628961)
            {
                play_button=1;
                load_image(renderer,surface,texture,NULL,&desRect,"back2.bmp");

            }
            else
            if (play_button==1)
            {
                play_button=0;
                load_image(renderer,surface,texture,NULL,&desRect,"back1.bmp");
            }

            if (x>=0 && x<=300 && y>=100 && y<=190)
            {
                high_button=1;
                load_image(renderer,surface,texture,NULL,&desRect,"back1_point.bmp");
            }
            else
            if (high_button==1)
            {
                high_button=0;
                load_image(renderer,surface,texture,NULL,&desRect,"back1.bmp");
            }
        }
        if (play_button==1 && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) break;
        if (high_button==1 && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            desRect.w=300;

            load_image(renderer,surface,texture,NULL,&desRect,"high_point.bmp");
            load_high_point(renderer,surface,texture);

            desRect.x=250;
            desRect.y=c_pad;
            desRect.w=desRect.h=50;
            load_image(renderer,surface,texture,NULL,&desRect,"x1.bmp");

            int x_button=0;
            while (1)
            {
                SDL_RenderPresent(renderer);

                if ( SDL_PollEvent(&e) == 0) continue;

                if (e.type == SDL_QUIT)
                {
                    kt=0;
                    break;
                }

                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                {
                    kt=0;
                    break;
                }

                if ( e.type == SDL_MOUSEMOTION )
                {
                    int x = e.motion.x;
                    int y = e.motion.y;

                    if (x>=250 && x<=300 && y>=100 && y<=150)
                    {
                        x_button=1;
                        load_image(renderer,surface,texture,NULL,&desRect,"x2.bmp");
                    }
                    else
                    if (x_button==1)
                    {
                        x_button=0;
                        load_image(renderer,surface,texture,NULL,&desRect,"x1.bmp");
                    }

                }
                if (x_button==1 && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                {
                    desRect.x=0;
                    desRect.y=c_pad;
                    desRect.w=SCREEN_WIDTH;
                    desRect.h=SCREEN_HEIGHT-2*c_pad;
                    load_image(renderer,surface,texture,NULL,&desRect,"back1_point.bmp");
                    break;
                }
            }

        }

    }

    if (kt==1) initiate(renderer,surface,texture,pokemonx,pokemony,l,mix,help,stage,point,timer);

    //load_time();

    SDL_RenderPresent(renderer);

    int dem=-1;
    Point a[2],b[2];
    b[0].x=0;b[0].y=0;
    a[0]=b[0];
    timer=SDL_GetTicks()/1000;

    while (kt==1)
    {

        //SDL_Delay(10);

        thanhduoi(renderer,surface,texture,stage,point,timer);

        if (helping(renderer,l,pokemonx,pokemony)==0)
        {
            while (helping(renderer,l,pokemonx,pokemony)==0) mixing(l,pokemonx,pokemony);
            SDL_Delay(100);
            redraw(renderer,surface,texture,l,pokemonx,pokemony,mix,help,stage,point,timer);
        }

        SDL_RenderPresent(renderer);

        if (time_game-SDL_GetTicks()/1000+timer==0)
        {
            thanhduoi(renderer,surface,texture,stage,point,timer);
            load_wav(nope,"FAIL.mp3");
            SDL_Delay(3500);
            kt=0;
            break;
        }

        if ( SDL_PollEvent(&e) == 0) continue;

        if (e.type == SDL_QUIT)
        {
            kt=0;
            break;
        }

        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
        {
            kt=0;
            break;
        }

        /*if (helping()==0)
        {
            mixing();
            redraw(stage);
            SDL_RenderPresent(renderer);
            SDL_Delay(200);
            SDL_RenderPresent(renderer);
        }*/

//toa do
        /*if ( e.type == SDL_MOUSEMOTION )
        {
            redraw(stage);
            font= TTF_OpenFont("font/SigmarOne.ttf",c_pad*3/4);
            stringstream s1,s2;
            s1<<e.motion.x;
            s2<<e.motion.y;
            string text=s1.str()+' '+s2.str();


            fg={255,255,255,255};
            surface = TTF_RenderText_Blended(font, text.c_str(), fg);
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
            TTF_SizeText(font,text.c_str() , &sourceRect.w, &sourceRect.h);

            desRect.x=0;
            desRect.y=SCREEN_HEIGHT-2*c_pad;
            desRect.w = sourceRect.w;
            desRect.h = sourceRect.h;
            SDL_RenderCopy(renderer,texture,&sourceRect,&desRect);

            SDL_RenderPresent(renderer);
        }*/

//mix
        if ( e.type == SDL_MOUSEMOTION )
        {
            int x = e.motion.x;
            int y = e.motion.y;

            desRect.w=SCREEN_WIDTH;
            desRect.h=c_pad*3/5;
            desRect.x=0;
            desRect.y=10;

            if (pow(x-420,2)+pow(y-40,2)<=784)
            {
                mix_button=1;
                load_image(renderer,surface,texture,NULL,&desRect,"thanhtren_mix.bmp");
                thanhtren_(renderer,surface,texture,mix,help);

            }
            else
            if (mix_button==1)
            {
                mix_button=0;
                load_image(renderer,surface,texture,NULL,&desRect,"thanhtren.bmp");
                thanhtren_(renderer,surface,texture,mix,help);
            }
        }
        if (mix_button==1 && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            if (mix>0)
            {
                mixing(l,pokemonx,pokemony);
                redraw(renderer,surface,texture,l,pokemonx,pokemony,mix,help,stage,point,timer);
                mix--;
                SDL_RenderPresent(renderer);
                SDL_Delay(200);
                SDL_RenderPresent(renderer);
            }

//help
        if ( e.type == SDL_MOUSEMOTION )
        {
            int x = e.motion.x;
            int y = e.motion.y;

            desRect.w=SCREEN_WIDTH;
            desRect.h=c_pad*3/5;
            desRect.x=0;
            desRect.y=10;

            if (pow(x-696,2)+pow(y-40,2)<=784)
            {
                help_button=1;
                load_image(renderer,surface,texture,NULL,&desRect,"thanhtren_help.bmp");
                thanhtren_(renderer,surface,texture,mix,help);

            }
            else
            if (help_button==1)
            {
                help_button=0;
                load_image(renderer,surface,texture,NULL,&desRect,"thanhtren.bmp");
                thanhtren_(renderer,surface,texture,mix,help);
            }
        }
        if (help_button==1 && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        if (help>0)
        {
            help--;
            int i=helping(renderer,l,pokemonx,pokemony);
            int j=pokemonx[i].size();
            SDL_SetRenderDrawColor(renderer,255,0,0,10);

            SDL_Rect temp1,temp2,temp3,temp4;
            temp1.x=r_pad + (pokemony[i][j-1]-1)*cell_size + 1;
            temp1.y=c_pad + (pokemonx[i][j-1]-1)*cell_size + 1;
            temp2.x=r_pad + (pokemony[i][j-2]-1)*cell_size + 1;
            temp2.y=c_pad + (pokemonx[i][j-2]-1)*cell_size + 1;
            temp1.w=temp1.h=temp2.w=temp2.h=cell_size-3;

            temp3.x=r_pad+(pokemony[i][j-1]-1)*cell_size;
            temp3.y=c_pad+(pokemonx[i][j-1]-1)*cell_size;
            temp4.x=r_pad+(pokemony[i][j-2]-1)*cell_size;
            temp4.y=c_pad+(pokemonx[i][j-2]-1)*cell_size;
            temp3.w=temp3.h=temp4.w=temp4.h=cell_size-1;
            stringstream ss;
            ss<<i;

            while (1)
            {
                if (e.type == SDL_QUIT)
                {
                    kt=0;
                    break;
                }

                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                {
                    kt=0;
                    break;
                }

                SDL_RenderDrawRect(renderer,&temp1);
                SDL_RenderDrawRect(renderer,&temp2);
                SDL_RenderPresent(renderer);
                SDL_Delay(200);

                load_image(renderer,surface,texture,NULL,&temp3,ss.str()+".bmp");
                load_image(renderer,surface,texture,NULL,&temp4,ss.str()+".bmp");

                SDL_RenderPresent(renderer);

                if (SDL_PollEvent(&e)!=0 && e.type==SDL_MOUSEBUTTONDOWN) break;
            }
        }

//back
    if ( e.type == SDL_MOUSEMOTION )
        {
            int x = e.motion.x;
            int y = e.motion.y;

            desRect.w=SCREEN_WIDTH;
            desRect.h=c_pad*3/5;
            desRect.x=0;
            desRect.y=10;

            if (pow(x-1125,2)+pow(y-40,2)<=784)
            {
                back_button=1;
                load_image(renderer,surface,texture,NULL,&desRect,"thanhtren_back.bmp");
                thanhtren_(renderer,surface,texture,mix,help);

            }
            else
            if (back_button==1)
            {
                back_button=0;
                load_image(renderer,surface,texture,NULL,&desRect,"thanhtren.bmp");
                thanhtren_(renderer,surface,texture,mix,help);
            }
        }
        if (back_button==1 && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            goto start;
        }

//hieu ung chuyen dong
        if ( e.type == SDL_MOUSEMOTION )
        {
            int x = floor(double(e.motion.y-c_pad) / cell_size)+1;
            int y = floor(double(e.motion.x-r_pad) / cell_size)+1;

            if (x>=1 && x<=sizeh && y>=1 && y<=sizew && l[x][y]!=0)
            {
                    b[1].x=x;
                    b[1].y=y;
                    if ((b[0].x != b[1].x || b[0].y != b[1].y ) )//&& l[b[0].x][b[0].y] != 0)
                    {
                        SDL_SetRenderDrawColor(renderer,255,0,0,10);
                        SDL_Rect temp;
                        temp.x=r_pad + (y-1)*cell_size + 1;
                        temp.y=c_pad + (x-1)*cell_size + 1;
                        temp.w=temp.h=cell_size-3;
                        SDL_RenderDrawRect(renderer,&temp);

                        if (dem==-1 || (dem==0 && (a[0].x!=b[0].x || a[0].y!=b[0].y) ))
                        {
                            stringstream ss;
                            ss<<l[b[0].x][b[0].y];
                            desRect.x=r_pad+(b[0].y-1)*cell_size;
                            desRect.y=c_pad+(b[0].x-1)*cell_size;
                            desRect.w=cell_size-1;
                            desRect.h=cell_size-1;
                            load_image(renderer,surface,texture,NULL,&desRect,ss.str()+".bmp");
                            SDL_RenderPresent(renderer);
                        }

                    }
                    b[0]=b[1];
            }
            else if (dem==-1 || (dem==0 && (a[0].x!=b[0].x || a[0].y!=b[0].y) ))
                        {
                            stringstream ss;
                            ss<<l[b[0].x][b[0].y];
                            desRect.x=r_pad+(b[0].y-1)*cell_size;
                            desRect.y=c_pad+(b[0].x-1)*cell_size;
                            desRect.w=cell_size-1;
                            desRect.h=cell_size-1;
                            load_image(renderer,surface,texture,NULL,&desRect,ss.str()+".bmp");
                            SDL_RenderPresent(renderer);
                        }
        }

//check
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            b[0].x=0;b[0].y=0;

            int x = floor(double(e.button.y-c_pad) / cell_size)+1;
            int y = floor(double(e.button.x-r_pad) / cell_size)+1;
            if (dem==0 && (x<1 || x>sizeh || y<1 || y>sizew || l[x][y]==0))
            {
                redraw(renderer,surface,texture,l,pokemonx,pokemony,mix,help,stage,point,timer);
                dem=-1;
            }

            if (x>=1 && x<=sizeh && y>=1 && y<=sizew && l[x][y]!=0)
            {
                dem++;
                a[dem].x=x;
                a[dem].y=y;

                SDL_SetRenderDrawColor(renderer,255,0,0,10);
                SDL_Rect temp;
                temp.x=r_pad + (y-1)*cell_size + 1;
                temp.y=c_pad + (x-1)*cell_size + 1;
                temp.w=temp.h=cell_size-3;
                SDL_RenderDrawRect(renderer,&temp);
                SDL_RenderPresent(renderer);

                if (dem==1 && a[0].x==a[1].x && a[0].y==a[1].y)
                {
                    redraw(renderer,surface,texture,l,pokemonx,pokemony,mix,help,stage,point,timer);
                    SDL_RenderPresent(renderer);
                    dem=-1;
                }
                else
                if (dem==1 && l[a[0].x][a[0].y]!=l[a[1].x][a[1].y])
                {
                    load_wav(nope,"NOPE.mp3");

                    redraw(renderer,surface,texture,l,pokemonx,pokemony,mix,help,stage,point,timer);

                    SDL_RenderPresent(renderer);
                    dem=-1;
                }
                else if (dem==1 && l[a[0].x][a[0].y]==l[a[1].x][a[1].y])
                {
                    if (!check(renderer,a[0],a[1],l,thu))
                    {
                        load_wav(nope,"NOPE.mp3");
                        redraw(renderer,surface,texture,l,pokemonx,pokemony,mix,help,stage,point,timer);
                    }
                    else
                    {
                        tong-=2;
                        point+=10;
                        load_wav(nope,"DING.mp3");
                        points_out(renderer,surface,texture);

                        for (int i=0;i<2;i++)
                        {
                            int value=l[a[i].x][a[i].y];
                            int j=pokemonx[value].size()-1;
                            for (j=pokemonx[value].size()-1;j>=0;j--)
                                if (pokemonx[value][j]==a[i].x && pokemony[value][j]==a[i].y) break;

                            /*swap(pokemonx[value][j],pokemonx[value].back());
                            swap(pokemony[value][j],pokemony[value].back());
                            pokemonx[value].pop_back();
                            pokemony[value].pop_back();*/
                            pokemonx[value].erase(pokemonx[value].begin()+j);
                            pokemony[value].erase(pokemony[value].begin()+j);
                            l[a[i].x][a[i].y]=0;
                        }

                        SDL_Delay(200);
                        redraw(renderer,surface,texture,l,pokemonx,pokemony,mix,help,stage,point,timer);
                        SDL_RenderPresent(renderer);

                    }
                    SDL_RenderPresent(renderer);
                    if (tong==0)
                    {

                        //SDL_Delay(500);

                        SDL_RenderPresent(renderer);

                        /*load_wav(nope,"VICTORY.mp3");
                        SDL_Delay(5000);*/

                        timee=time_game-SDL_GetTicks()/1000+timer;
                        point+=timee*10;
                        end_game(renderer,surface,texture,e,kt,timee,point,pre_point);

                        tong=sizew*sizeh;
                        stage++;
                        timer=SDL_GetTicks()/1000;
                        mix++;
                        help++;
                        initiate(renderer,surface,texture,pokemonx,pokemony,l,mix,help,stage,point,timer);
                    }
                    dem=-1;
                }
            }

        }

//pause
    if ( e.type == SDL_MOUSEMOTION )
        {
            int x = e.motion.x;
            int y = e.motion.y;

            desRect.w=SCREEN_WIDTH;
            desRect.h=c_pad*3/5;
            desRect.x=0;
            desRect.y=10;

            if (pow(x-1049,2)+pow(y-40,2)<=784)
            {
                pause_button=1;
                load_image(renderer,surface,texture,NULL,&desRect,"thanhtren_pause.bmp");
                thanhtren_(renderer,surface,texture,mix,help);

            }
            else
            if (pause_button==1)
            {
                pause_button=0;
                load_image(renderer,surface,texture,NULL,&desRect,"thanhtren.bmp");
                thanhtren_(renderer,surface,texture,mix,help);
            }
        }
        if (pause_button==1 && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            int timer2=SDL_GetTicks()/1000;
            redraw(renderer,surface,texture,l,pokemonx,pokemony,mix,help,stage,point,timer);
            desRect.w=SCREEN_WIDTH;
            desRect.h=SCREEN_HEIGHT-2*c_pad;
            desRect.x=0;
            desRect.y=c_pad;
            load_image(renderer,surface,texture,NULL,&desRect,"pause1.bmp");
            while (1)
            {
                SDL_RenderPresent(renderer);

                if ( SDL_PollEvent(&e) == 0) continue;

                if (e.type == SDL_QUIT)
                {
                    kt=0;
                    break;
                }

                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                {
                    kt=0;
                    break;
                }

                if (e.type == SDL_MOUSEMOTION )
                {
                    int x=e.motion.x,y=e.motion.y;
                    if (x>=500 && x<=725 && y>=487 && y<=523)
                    {
                        resume_button=1;
                        load_image(renderer,surface,texture,NULL,&desRect,"pause2.bmp");

                    }
                    else
                    if (resume_button==1)
                    {
                        resume_button=0;
                        load_image(renderer,surface,texture,NULL,&desRect,"pause1.bmp");
                    }
                }

                if (resume_button==1 && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                    {
                        timer+=SDL_GetTicks()/1000-timer2;
                        redraw(renderer,surface,texture,l,pokemonx,pokemony,mix,help,stage,point,timer);
                        resume_button=0;
                        break;
                    }

            }
        }

    }
    //waitUntilKeyPressed();
    quitSDL(window, renderer,texture,font);
    return 0;
}



