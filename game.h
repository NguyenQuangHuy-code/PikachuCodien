#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

using namespace std;

struct Point
{
    int x,y;
};

const int time_game=120; //second

const int SCREEN_WIDTH = 1200;

const int SCREEN_HEIGHT = 800;

const int r_pad=SCREEN_WIDTH/8,c_pad=SCREEN_HEIGHT/8;

const int sizew=12;   //12

const int sizeh=8;   //8

const int number_max=6;   //6

const int number_pokemons=sizeh * sizew/ number_max;

const int cell_size= (SCREEN_WIDTH-2*r_pad)/sizew;

const string WINDOW_TITLE = "Pikachu";

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void waitUntilKeyPressed();

void quitSDL(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture, TTF_Font* font);

void load_image(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,SDL_Rect* sourcerect,SDL_Rect* desrect,string s);

void load_wav(Mix_Chunk* nope,string s);

void load_ttf(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,SDL_Rect* sourcerect,
              SDL_Rect* desrect,TTF_Font* font,string s,SDL_Color fg);

void load_high_point(SDL_Renderer* renderer,SDL_Surface* surface,SDL_Texture* texture);

void load_stage(SDL_Renderer* renderer,SDL_Surface* surface,SDL_Texture* texture,int stage);

void points_out(SDL_Renderer* renderer,SDL_Surface* surface,SDL_Texture* texture);

void load_points(SDL_Renderer* renderer,SDL_Surface* surface,SDL_Texture* texture,int point);

void load_time(SDL_Renderer* renderer,SDL_Surface* surface,SDL_Texture* texture,int timer);

void initiate(SDL_Renderer* renderer,SDL_Surface* surface,SDL_Texture* texture,
              vector<vector<int> > &pokemonx,vector<vector<int> > &pokemony,vector<vector<int> > &l,int mix,int help,int stage,int point,int timer);

bool check(SDL_Renderer* renderer,Point p1, Point p2,vector<vector<int> > &l,int &thu);

void draw(SDL_Renderer* renderer,int x1,int y1,int x2,int y2);

void mixing(vector<vector<int> > &l,vector<vector<int> > &pokemonx,vector<vector<int> > &pokemony);

int helping(SDL_Renderer* renderer,vector<vector<int> > &l,vector<vector<int> > &pokemonx,vector<vector<int> > &pokemony);

void redraw(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,
            vector<vector<int> > &l,vector<vector<int> > &pokemonx,vector<vector<int> > &pokemony,int mix,int help,int stage,int point,int timer);

void thanhtren_(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,int mix,int help);

void thanhtren(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,int mix,int help);

void thanhduoi(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,int stage,int point,int timer);

bool sosanh(int a,int b);

void end_game(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,SDL_Event e,int &kt,int timee,int point,int pre_point);

void load_end_game(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,string s,int timee,int point);

void down(int i1,int i2,int j1,int j2,vector<vector<int> > &l,vector<vector<int> > &pokemonx,vector<vector<int> > &pokemony);

void left(int i1,int i2,int j1,int j2,vector<vector<int> > &l,vector<vector<int> > &pokemonx,vector<vector<int> > &pokemony);

void up(int i1,int i2,int j1,int j2,vector<vector<int> > &l,vector<vector<int> > &pokemonx,vector<vector<int> > &pokemony);

void right(int i1,int i2,int j1,int j2,vector<vector<int> > &l,vector<vector<int> > &pokemonx,vector<vector<int> > &pokemony);

#endif // GAME_H_INCLUDED
