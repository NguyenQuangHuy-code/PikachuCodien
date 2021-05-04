#include "game.h"

using namespace std;

TTF_Font* fontt;
SDL_Color fgg;
SDL_Rect sourcerect,desrect;

void initiate(SDL_Renderer* renderer,SDL_Surface* surface,SDL_Texture* texture,
              vector<vector<int> > &pokemonx,vector<vector<int> > &pokemony,vector<vector<int> > &l,int mix,int help,int stage,int point,int timer)
{
    SDL_SetRenderDrawColor(renderer,128,128,128,255);  //gray
    SDL_RenderClear(renderer);

    desrect.x=0;
    desrect.y=c_pad;
    desrect.w=SCREEN_WIDTH-2*desrect.x;
    desrect.h=SCREEN_HEIGHT-2*desrect.y;
    load_image(renderer,surface,texture,NULL,&desrect,"pikachu2.bmp");

    for (int i=1;i<=number_pokemons;i++)
    {
        pokemonx[i].clear();
        pokemony[i].clear();
    }

    vector<int> sl(number_pokemons+1,number_max);
    for (int i=1;i<=sizeh;i++)
        for (int j=1;j<=sizew;j++)
        {
            int temp;
            do temp=rand()%number_pokemons+1;
            while (sl[temp]==0);

            pokemonx[temp].push_back(i);
            pokemony[temp].push_back(j);

            l[i][j]=temp;
            sl[temp]--;
            stringstream ss;
            ss<<temp;
            desrect.x=r_pad+(j-1)*cell_size;
            desrect.y=c_pad+(i-1)*cell_size;
            desrect.w=cell_size-1;
            desrect.h=cell_size-1;
            load_image(renderer,surface,texture,NULL,&desrect,ss.str()+".bmp");
        }

    thanhtren(renderer,surface,texture,mix,help);
    thanhduoi(renderer,surface,texture,stage,point,timer);

}

bool checkLineX(int y1, int y2, int x,vector<vector<int> > &l)
{
    int min1=min(y1,y2),max1=max(y1,y2);
    for (int i=min1+1;i<max1;i++)
        if (l[x][i]!=0) return 0;
    return 1;
}

bool checkLine2X(int y1, int y2, int x,vector<vector<int> > &l)
{
    int min1=min(y1,y2),max1=max(y1,y2);
    if (min1==y1)
    for (int i=min1+1;i<=max1;i++)
        if (l[x][i]!=0) return 0;

    if (max1==y1)
    for (int i=min1;i<max1;i++)
        if (l[x][i]!=0) return 0;
    return 1;
}

bool checkLineY(int x1, int x2, int y,vector<vector<int> > &l)
{
    int min1=min(x1,x2),max1=max(x1,x2);
    for (int i=min1+1;i<max1;i++)
        if (l[i][y]!=0) return 0;
    return 1;
}

bool checkLine2Y(int x1, int x2, int y,vector<vector<int> > &l)
{
    int min1=min(x1,x2),max1=max(x1,x2);
    if (min1==x1)
    for (int i=min1+1;i<=max1;i++)
        if (l[i][y]!=0) return 0;

    if (max1==x1)
    for (int i=min1;i<max1;i++)
        if (l[i][y]!=0) return 0;
    return 1;
}

bool checkRectX(Point p1, Point p2,vector<vector<int> > &l,int &thu)
{
    thu=p2.y;
    if (checkLine2X(p1.y,p2.y,p1.x,l)&&checkLine2Y(p2.x,p1.x,p2.y,l)) return 1;
    thu=p1.y;
    if (checkLine2X(p2.y,p1.y,p2.x,l)&&checkLine2Y(p1.x,p2.x,p1.y,l)) return 1;

    if (p1.x>p2.x) swap(p1,p2);
    for (int i=p1.y+1;i<p2.y;i++)
    if (checkLineY(p1.x-1,p2.x+1,i,l) && checkLine2X(p1.y,i,p1.x,l) && checkLine2X(p2.y,i,p2.x,l))
    {
        thu=i;
        return 1;
    }

    for (int i=p1.y-1;i>=0;i--)
    if (checkLineY(p1.x-1,p2.x+1,i,l) && checkLine2X(p1.y,i,p1.x,l) && checkLine2X(p2.y,i,p2.x,l))
    {
        thu=i;
        return 1;
    }

    for (int i=p2.y+1;i<=sizew+1;i++)
    if (checkLineY(p1.x-1,p2.x+1,i,l) && checkLine2X(p1.y,i,p1.x,l) && checkLine2X(p2.y,i,p2.x,l))
    {
        thu=i;
        return 1;
    }

    return 0;
}

bool checkRectY(Point p1, Point p2,vector<vector<int> > &l,int &thu)
{
    thu=p2.y;
    if (checkLine2X(p1.y,p2.y,p1.x,l)&&checkLine2Y(p2.x,p1.x,p2.y,l)) return 1;
    thu=p1.y;
    if (checkLine2X(p2.y,p1.y,p2.x,l)&&checkLine2Y(p1.x,p2.x,p1.y,l)) return 1;

    if (p1.y>p2.y) swap(p1,p2);
    for (int i=p1.x+1;i<p2.x;i++)
    if (checkLineX(p1.y-1,p2.y+1,i,l) && checkLine2Y(p1.x,i,p1.y,l) && checkLine2Y(p2.x,i,p2.y,l))
    {
        thu=i;
        return 1;
    }

    for (int i=p1.x-1;i>=0;i--)
    if (checkLineX(p1.y-1,p2.y+1,i,l) && checkLine2Y(p1.x,i,p1.y,l) && checkLine2Y(p2.x,i,p2.y,l))
    {
        thu=i;
        return 1;
    }
    for (int i=p2.x +1;i<=sizeh+1;i++)
    if (checkLineX(p1.y-1,p2.y+1,i,l) && checkLine2Y(p1.x,i,p1.y,l) && checkLine2Y(p2.x,i,p2.y,l))
    {
        thu=i;
        return 1;
    }

    return 0;
}

bool check(SDL_Renderer* renderer,Point p1, Point p2,vector<vector<int> > &l,int &thu)
{
    if (p1.x==p2.x && p1.y==p2.y) return 0;
    if ((p1.x==p2.x && checkLineX(p1.y,p2.y,p1.x,l)) || (p1.y==p2.y && checkLineY(p1.x,p2.x,p1.y,l)))
    {
        draw(renderer,p1.x,p1.y,p2.x,p2.y);
        SDL_RenderPresent(renderer);

        return 1;
    }
    if ((p1.y<p2.y && checkRectX(p1,p2,l,thu)) || (p1.y>=p2.y && checkRectX(p2,p1,l,thu)))
    {
        draw(renderer,p1.x,p1.y,p1.x,thu);
        draw(renderer,p1.x,thu,p2.x,thu);
        draw(renderer,p2.x,thu,p2.x,p2.y);
        SDL_RenderPresent(renderer);

        return 1;
    }
    if ((p1.x<p2.x && checkRectY(p1,p2,l,thu)) || (p1.x>=p2.x && checkRectY(p2,p1,l,thu)))
    {
        draw(renderer,p1.x,p1.y,thu,p1.y);
        draw(renderer,thu,p1.y,thu,p2.y);
        draw(renderer,thu,p2.y,p2.x,p2.y);
        SDL_RenderPresent(renderer);

        return 1;
    }
    return 0;
}

bool check2(SDL_Renderer* renderer,Point p1, Point p2,vector<vector<int> > &l,int thu)
{
    if (p1.x==p2.x && p1.y==p2.y) return 0;
    if ((p1.x==p2.x && checkLineX(p1.y,p2.y,p1.x,l)) || (p1.y==p2.y && checkLineY(p1.x,p2.x,p1.y,l))) return 1;

    if ((p1.y<p2.y && checkRectX(p1,p2,l,thu)) || (p1.y>=p2.y && checkRectX(p2,p1,l,thu))) return 1;

    if ((p1.x<p2.x && checkRectY(p1,p2,l,thu)) || (p1.x>=p2.x && checkRectY(p2,p1,l,thu))) return 1;

    return 0;
}

void draw(SDL_Renderer* renderer,int x1,int y1,int x2,int y2)
{

    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderDrawLine(renderer,r_pad+(y1-1)*cell_size+cell_size/2,c_pad+(x1-1)*cell_size+cell_size/2,
                       r_pad+(y2-1)*cell_size+cell_size/2,c_pad+(x2-1)*cell_size+cell_size/2);

}

void mixing(vector<vector<int> > &l,vector<vector<int> > &pokemonx,vector<vector<int> > &pokemony)
{
    vector<vector<int> > poke=pokemonx;
    for (int i=1;i<=number_pokemons;i++)
    {
        pokemonx[i].clear();
        pokemony[i].clear();
    }
    for (int i=1;i<=sizeh;i++)
    for (int j=1;j<=sizew;j++)
        if (l[i][j]!=0)
        {
            int temp;
            do temp=rand()%number_pokemons+1;
            while (poke[temp].size()==0);
            l[i][j]=temp;
            poke[temp].pop_back();
            pokemonx[temp].push_back(i);
            pokemony[temp].push_back(j);
        }
}

int thu2=0;

int helping(SDL_Renderer* renderer,vector<vector<int> > &l,vector<vector<int> > &pokemonx,vector<vector<int> > &pokemony)
{
    for (int i=1;i<=number_pokemons;i++)
    {
        if (pokemonx[i].size()!=0)
        for (int k=0;k<pokemonx[i].size()-1;k++)
            for (int j=k+1;j<pokemonx[i].size();j++)
            {
                Point p1,p2;
                p1.x=pokemonx[i][k];
                p1.y=pokemony[i][k];
                p2.x=pokemonx[i][j];
                p2.y=pokemony[i][j];
                if (check2(renderer,p1,p2,l,thu2) )
                {

                    if (k<j) swap(k,j);
                    pokemonx[i].push_back(pokemonx[i][k]);
                    pokemony[i].push_back(pokemony[i][k]);
                    pokemonx[i].push_back(pokemonx[i][j]);
                    pokemony[i].push_back(pokemony[i][j]);
                    pokemonx[i].erase(pokemonx[i].begin()+k);
                    pokemony[i].erase(pokemony[i].begin()+k);
                    pokemonx[i].erase(pokemonx[i].begin()+j);
                    pokemony[i].erase(pokemony[i].begin()+j);

                    /*redraw(stage);
                    SDL_RenderPresent(renderer);*/
                    return i;
                }
            }
    }
    return 0;
}

void redraw(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,
            vector<vector<int> > &l,vector<vector<int> > &pokemonx,vector<vector<int> > &pokemony,int mix,int help,int stage,int point,int timer)
{
    switch (stage%10)
    {
    case 2:
        down(1,sizeh,1,sizew,l,pokemonx,pokemony);
        break;
    case 3:
        left(1,sizeh,1,sizew,l,pokemonx,pokemony);
        break;
    case 4:
        up(1,sizeh,1,sizew,l,pokemonx,pokemony);
        break;
    case 5:
        right(1,sizeh,1,sizew,l,pokemonx,pokemony);
        break;
    case 6:
        down(sizeh/2+1,sizeh,1,sizew,l,pokemonx,pokemony);
        up(1,sizeh/2,1,sizew,l,pokemonx,pokemony);
        break;
    case 7:
        down(1,sizeh/2,1,sizew,l,pokemonx,pokemony);
        up(sizeh/2+1,sizeh,1,sizew,l,pokemonx,pokemony);
        break;
    case 8:
        left(1,sizeh,1,sizew/2,l,pokemonx,pokemony);
        right(1,sizeh,sizew/2+1,sizew,l,pokemonx,pokemony);
        break;
    case 9:
        left(1,sizeh,sizew/2+1,sizew,l,pokemonx,pokemony);
        right(1,sizeh,1,sizew/2,l,pokemonx,pokemony);
        break;
    }
    SDL_SetRenderDrawColor(renderer,128,128,128,255);
    SDL_RenderClear(renderer);
    desrect.x=0;
    desrect.y=c_pad;
    desrect.w=SCREEN_WIDTH-2*desrect.x;
    desrect.h=SCREEN_HEIGHT-2*desrect.y;
    load_image(renderer,surface,texture,NULL,&desrect,"pikachu2.bmp");

    for (int i=1;i<=sizeh;i++)
        for (int j=1;j<=sizew;j++)
        if (l[i][j]!=0)
        {
            stringstream ss;
            ss<<l[i][j];
            desrect.x=r_pad+(j-1)*cell_size;
            desrect.y=c_pad+(i-1)*cell_size;
            desrect.w=cell_size-1;
            desrect.h=cell_size-1;
            load_image(renderer,surface,texture,NULL,&desrect,ss.str()+".bmp");
        }

    thanhtren(renderer,surface,texture,mix,help);
    thanhduoi(renderer,surface,texture,stage,point,timer);

}

void thanhtren_(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,int mix,int help)
{
    int i=0;
    if (mix>0) i=log10(mix);
    fontt= TTF_OpenFont("font/SigmarOne.ttf",40-3*i);
    fgg={255,128,0};
    stringstream sss;
    sss<<mix;
    //string text=sss.str();
    TTF_SizeText(fontt,sss.str().c_str(), &sourcerect.w, &sourcerect.h);

    desrect.x=563-13*i;
    desrect.y=5;
    desrect.w =sourcerect.w;
	desrect.h =sourcerect.h;
    load_ttf(renderer,surface,texture,NULL,&desrect,fontt,sss.str(),fgg);

    int j=0;
    if (help>0) j=log10(help);
    fontt= TTF_OpenFont("font/SigmarOne.ttf",40-3*j);
    fgg={255,128,0};
    stringstream ss;
    ss<<help;
    //string text=sss.str();
    TTF_SizeText(fontt,ss.str().c_str(), &sourcerect.w, &sourcerect.h);

    desrect.x=860-13*j;
    desrect.y=5;
    desrect.w =sourcerect.w;
	desrect.h =sourcerect.h;
    load_ttf(renderer,surface,texture,NULL,&desrect,fontt,ss.str(),fgg);
}

void thanhtren(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,int mix,int help)
{
    desrect.w=SCREEN_WIDTH;
    desrect.h=c_pad*3/5;
    desrect.x=0;
    desrect.y=10;  //c_pad-desrect.h;

    load_image(renderer,surface,texture,NULL,&desrect,"thanhtren.bmp");
    thanhtren_(renderer,surface,texture,mix,help);

}

void thanhduoi(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,int stage,int point,int timer)
{
    desrect.w=SCREEN_WIDTH;
    desrect.h=c_pad*2/3;
    desrect.x=0;
    desrect.y=SCREEN_HEIGHT-desrect.h;

    load_image(renderer,surface,texture,NULL,&desrect,"thanhduoi.bmp");

    load_stage(renderer,surface,texture,stage);

    load_points(renderer,surface,texture,point);

    load_time(renderer,surface,texture,timer);

}

 bool sosanh(int a,int b)
{
    return a>b;
}

void end_game(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,SDL_Event e,int &kt,int timee,int point,int pre_point)
{
    load_end_game(renderer,surface,texture,"end.bmp",timee,point);
    int continue_button=0,save_button=0;
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

            if (1600*pow(x-595,2)+24025*pow(y-500,2)<=38440000)
            {
                continue_button=1;
                load_end_game(renderer,surface,texture,"continue.bmp",timee,point);

            }
            else
            if (continue_button==1)
            {
                continue_button=0;
                load_end_game(renderer,surface,texture,"end.bmp",timee,point);
            }

            if (1600*pow(x-595,2)+24025*pow(y-610,2)<=38440000)
            {
                save_button=1;
                load_end_game(renderer,surface,texture,"save.bmp",timee,point);

            }
            else
            if (save_button==1)
            {
                save_button=0;
                load_end_game(renderer,surface,texture,"end.bmp",timee,point);
            }

        }
        if (continue_button==1 && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) break;

        if (save_button==1 && pre_point!=point && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            ifstream f("file/point.txt");
            int p[6];
            for (int i=0;i<5;i++) f>>p[i];
            p[5]=point;
            sort(p,p+6,sosanh);
            f.close();

            ofstream f2("file/point.txt",ios::trunc);
            /*time_t hientai=time(0);
            char *dt=ctime(&hientai);*/
            for (int i=0;i<5;i++) f2<<p[i]<<endl;
            f2.close();


            load_end_game(renderer,surface,texture,"saved.bmp",timee,point);
            SDL_RenderPresent(renderer);
            SDL_Delay(500);
            load_end_game(renderer,surface,texture,"saved.bmp",timee,point);
            SDL_RenderPresent(renderer);

            pre_point=point;
        }

    }

}

void load_end_game(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,string s,int timee,int point)
{
    desrect.h=SCREEN_HEIGHT-2*c_pad;
    desrect.w=desrect.h*10/13;
    desrect.x=(SCREEN_WIDTH-desrect.w)/2;
    desrect.y=c_pad;

    load_image(renderer,surface,texture,NULL,&desrect,s.c_str());

    sourcerect.w=23;
    sourcerect.h=60;

//load point
    fontt= TTF_OpenFont("font/ARCADE.ttf",c_pad*3/5);
    fgg={0,0,0};
    stringstream sss;
    sss<<(sizew*sizeh)*5;
    //string text=sss.str();
    desrect.x=SCREEN_WIDTH*11/24;
    desrect.y=SCREEN_HEIGHT*35/160;
    desrect.w =sourcerect.w*sss.str().size();
	desrect.h =sourcerect.h;
    load_ttf(renderer,surface,texture,NULL,&desrect,fontt,sss.str(),fgg);

//load reward
    sss.str("");
    sss<<timee<<"x10="<<timee*10;
    desrect.y=SCREEN_HEIGHT*49/160;
    desrect.w=sourcerect.w*sss.str().size();
    load_ttf(renderer,surface,texture,NULL,&desrect,fontt,sss.str(),fgg);

//load point
    sss.str("");
    sss<<timee*10+(sizew*sizeh)*5;
    desrect.y=SCREEN_HEIGHT*63/160;
    desrect.w=sourcerect.w*sss.str().size();
    load_ttf(renderer,surface,texture,NULL,&desrect,fontt,sss.str(),fgg);

//load points
    sss.str("");
    sss<<point;
    desrect.x=SCREEN_WIDTH*12/24;
    desrect.y=SCREEN_HEIGHT*76/160;
    desrect.w=sourcerect.w*sss.str().size();
    load_ttf(renderer,surface,texture,NULL,&desrect,fontt,sss.str(),fgg);

}

void down(int i1,int i2,int j1,int j2,vector<vector<int> > &l,vector<vector<int> > &pokemonx,vector<vector<int> > &pokemony)
{
    int j=j1;
    while (j<=j2)
    {
        int i=i2,demso=0;
        while (i>i1+demso)
        {
            if (l[i][j]==0)
            {
                for (int k=i;k>i1+demso;k--)
                {
                    l[k][j]=l[k-1][j];
                    if (l[k-1][j]!=0)
                    {
                        int m;
                        for (m=0;m<pokemonx[l[k-1][j]].size();m++)
                            if (pokemonx[l[k-1][j]][m]==k-1 && pokemony[l[k-1][j]][m]==j) break;
                        pokemonx[l[k-1][j]][m]=k;
                    }
                }
                demso++;
                l[i1+demso-1][j]=0;
            }
            else i--;
        }
        j++;
    }
}

void left(int i1,int i2,int j1,int j2,vector<vector<int> > &l,vector<vector<int> > &pokemonx,vector<vector<int> > &pokemony)
{
    int i=i1;
    while (i<=i2)
    {
        int j=j1,demso=0;
        while (j<j2-demso)
        {
            if (l[i][j]==0)
            {
                for (int k=j;k<j2-demso;k++)
                {
                    l[i][k]=l[i][k+1];
                    if (l[i][k+1]!=0)
                    {
                        int m;
                        for (m=0;m<pokemonx[l[i][k+1]].size();m++)
                            if (pokemonx[l[i][k+1]][m]==i && pokemony[l[i][k+1]][m]==k+1) break;
                        pokemony[l[i][k+1]][m]=k;
                    }
                }
                demso++;
                l[i][j2-demso+1]=0;
            }
            else j++;
        }
        i++;
    }
}

void up(int i1,int i2,int j1,int j2,vector<vector<int> > &l,vector<vector<int> > &pokemonx,vector<vector<int> > &pokemony)
{
    int j=j1;
    while (j<=j2)
    {
        int i=i1,demso=0;
        while (i<i2-demso)
        {
            if (l[i][j]==0)
            {
                for (int k=i;k<i2-demso;k++)
                {
                    l[k][j]=l[k+1][j];
                    if (l[k+1][j]!=0)
                    {
                        int m;
                        for (m=0;m<pokemonx[l[k+1][j]].size();m++)
                            if (pokemonx[l[k+1][j]][m]==k+1 && pokemony[l[k+1][j]][m]==j) break;
                        pokemonx[l[k+1][j]][m]=k;
                    }
                }
                demso++;
                l[i2-demso+1][j]=0;
            }
            else i++;
        }
        j++;
    }
}

void right(int i1,int i2,int j1,int j2,vector<vector<int> > &l,vector<vector<int> > &pokemonx,vector<vector<int> > &pokemony)
{
    int i=i1;
    while (i<=i2)
    {
        int j=j2,demso=0;
        while (j>j1+demso)
        {
            if (l[i][j]==0)
            {
                for (int k=j;k>j1+demso;k--)
                {
                    l[i][k]=l[i][k-1];
                    if (l[i][k-1]!=0)
                    {
                        int m;
                        for (m=0;m<pokemonx[l[i][k-1]].size();m++)
                            if (pokemonx[l[i][k-1]][m]==i && pokemony[l[i][k-1]][m]==k-1) break;
                        pokemony[l[i][k-1]][m]=k;
                    }
                }
                demso++;
                l[i][j1+demso-1]=0;
            }
            else j--;
        }
        i++;
    }
}

void load_image(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,SDL_Rect* sourcerect,SDL_Rect* desrect,string s)
{
    s="image/"+s;
    surface= SDL_LoadBMP(s.c_str());
    texture=SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    SDL_RenderCopy(renderer,texture,sourcerect,desrect);
    SDL_DestroyTexture(texture);
}

void load_wav(Mix_Chunk* nope,string s)
{
    s="sound/"+s;
    nope=Mix_LoadWAV(s.c_str());
    Mix_PlayChannel(-1,nope,0);
}

void load_ttf(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,SDL_Rect* sourcerect,
              SDL_Rect* desrect,TTF_Font* font,string s,SDL_Color fg)
{
    surface = TTF_RenderText_Blended(font, s.c_str(), fg);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_RenderCopy(renderer,texture,sourcerect,desrect);
    SDL_DestroyTexture(texture);
}

void load_high_point(SDL_Renderer* renderer,SDL_Surface* surface,SDL_Texture* texture)
{
    ifstream f("file/point.txt");

    fontt= TTF_OpenFont("font/SigmarOne.ttf",75);
    fgg={0,0,0};
    stringstream sss;

    sourcerect.w=25;

    desrect.x=110;
    desrect.y=120;
    desrect.w = 50;
	desrect.h = 75;

    for (int i=0;i<5;i++)
    {
        int n;
        f>>n;
        sss.str("");
        sss<<n;
        desrect.y+=80;
        desrect.w=sourcerect.w*sss.str().size();
        load_ttf(renderer,surface,texture,NULL,&desrect,fontt,sss.str(),fgg);

    }
    f.close();
}

void load_stage(SDL_Renderer* renderer,SDL_Surface* surface,SDL_Texture* texture,int stage)
{
    fontt= TTF_OpenFont("font/SigmarOne.ttf",c_pad*3/4);
    fgg={255,255,255};
    stringstream sss;
    sss<<stage;
    //string text=sss.str();
    TTF_SizeText(fontt,sss.str().c_str(), &sourcerect.w, &sourcerect.h);

    desrect.x=SCREEN_WIDTH/8;
    desrect.y=SCREEN_HEIGHT-c_pad;
    desrect.w =sourcerect.w;
	desrect.h =sourcerect.h;
    load_ttf(renderer,surface,texture,NULL,&desrect,fontt,sss.str(),fgg);
}

void points_out(SDL_Renderer* renderer,SDL_Surface* surface,SDL_Texture* texture)
{

    desrect.x=0;
    desrect.y=SCREEN_HEIGHT-2*c_pad;
    desrect.w = desrect.h = c_pad;
    load_image(renderer,surface,texture,NULL,&desrect,"point.bmp");

    SDL_RenderPresent(renderer);

    SDL_Delay(200);

    surface= SDL_LoadBMP("pikachu2.bmp");
    texture=SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture,NULL,NULL,&sourcerect.w,&sourcerect.h);

    desrect.x=0;
    desrect.y=c_pad;
    desrect.w=r_pad;
    desrect.h=SCREEN_HEIGHT-2*desrect.y;
    sourcerect.w=SCREEN_WIDTH/r_pad*sourcerect.w;
    sourcerect.h=SCREEN_HEIGHT-2*c_pad;

    SDL_RenderCopy(renderer,texture,&sourcerect,&desrect);

    SDL_DestroyTexture(texture);
    SDL_RenderPresent(renderer);


}

void load_points(SDL_Renderer* renderer,SDL_Surface* surface,SDL_Texture* texture,int point)
{
    fontt= TTF_OpenFont("font/SigmarOne.ttf",c_pad*3/4);
    fgg={255,255,255};
    stringstream sss;
    sss<<point;
    string text=sss.str();
    TTF_SizeText(fontt,text.c_str() , &sourcerect.w, &sourcerect.h);

    desrect.x=SCREEN_WIDTH*5/12;
    desrect.y=SCREEN_HEIGHT-c_pad;
    desrect.w = sourcerect.w;
	desrect.h = sourcerect.h;
    load_ttf(renderer,surface,texture,NULL,&desrect,fontt,text,fgg);
}

void load_time(SDL_Renderer* renderer,SDL_Surface* surface,SDL_Texture* texture,int timer)
{
    fontt= TTF_OpenFont("font/SigmarOne.ttf",c_pad*3/4);
    fgg={255,255,255};
    stringstream sss;
    sss<<time_game-SDL_GetTicks()/1000+timer;
    string text=sss.str();
    TTF_SizeText(fontt,text.c_str() , &sourcerect.w, &sourcerect.h);

    desrect.x=SCREEN_WIDTH*87/100;
    desrect.y=SCREEN_HEIGHT-c_pad;
    desrect.w = sourcerect.w;
	desrect.h = sourcerect.h;
    load_ttf(renderer,surface,texture,NULL,&desrect,fontt,text,fgg);

}

void logSDLError(std::ostream& os,const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    /*window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);*/

    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
    //Khi thông thường chạy với môi trường bình thường ở nhà

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    if(SDL_Init(SDL_INIT_AUDIO)==-1)
    {
        printf("SDL_Init: %s\n", SDL_GetError());
        exit(1);
    }
    // open 44.1KHz, signed 16bit, system byte order,
    //      stereo audio, using 1024 byte chunks
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1)
    {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        exit(2);
    }

    //if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );

    if (TTF_Init() < 0)
    {
        SDL_Log("%s", TTF_GetError());
        exit(3);
    }

}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
    if ( SDL_PollEvent(&e) != 0 &&
    (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
    return;
    SDL_Delay(100);
    }
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture, TTF_Font* font)
{
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}
