#include<SDL.h>
#include<iostream>
#include<limits>
#include<time.h>
using namespace std;

class World
{
private:
    const int WORLD_WIDTH=750;
    const int WORLD_HEIGHT=750;
    bool released=false;
    bool isItEmptyWorld=false;
    bool renderInitial=false;
    char** temp1=NULL;
    int** temp2=NULL;
    char** world=new char*[WORLD_HEIGHT];
    char** next=new char*[WORLD_HEIGHT];
    char** drawing=new char*[WORLD_HEIGHT];
    int** neighbours=new int*[WORLD_HEIGHT];
    int** nextNeighbours=new int*[WORLD_HEIGHT];
    void calculateNeighbours();
    int getNeighbourAliveCount(int i, int j);
    void setNextNeighboursAdjacents(int i, int j, bool state);
    void renderGens();
    void pause();
public:
    World();
    ~World();
    void gameOfLife();
    void randomInit();
    void preset1();
    void preset2();
    void preset3();
    void preset4();
    void preset5();
    void preset6();
    void preset7();
    void gosperGliderGuns();
    void emptyWorld();
};

SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;

bool init()
{
    bool success=true;
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        cout<<"Couldn't initialize SDL. SDL_Error: "<<SDL_GetError();
        success=false;
    }
    else
    {
        if(!(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0")))
        {
            cout<<"Warning: Nearest Pixel Sampling not enabled.\n";
        }

        window=SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 750, 750, SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            cout<<"Couldn't create window. SDL_Error: "<<SDL_GetError();
            success=false;
        }
        else
        {
            renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer==NULL)
            {
                cout<<"Couldn't create renderer. SDL_Error: "<<SDL_GetError();
                success=false;
            }
        }
    }

    return success;
}

void close()
{
    SDL_DestroyRenderer(renderer);
    renderer=NULL;

    SDL_DestroyWindow(window);
    window=NULL;

    SDL_Quit();
}

void intro()
{
    cout<<"=============================================JOHN CONWAY'S GAME OF LIFE=============================================\n\n";
    cout<<"The Game of Life is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input.\n\n";
    cout<<"RULES: The universe of the Game of Life is an infinite, two-dimensional orthogonal grid of square cells (However, we'll be using a finite 750x750 finite map here), each of which is in one of two possible states, live or dead. Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:\n\n";
    cout<<"    - Any live cell with fewer than two live neighbours dies, as if by underpopulation.\n";
    cout<<"    - Any live cell with two or three live neighbours lives on to the next generation.\n";
    cout<<"    - Any live cell with more than three live neighbours dies, as if by overpopulation.\n";
    cout<<"    - Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.\n\n";

    cout<<"CONTROLS:-\n\n";
    cout<<"- In a running simulation, you can use LEFT MOUSE BUTTON to draw cells. As soon as you release the left mouse button, those drawn cells will become live.\n\n";
    cout<<"- If you choose the option to draw cells in an empty map(i.e. Option 9), you'll have to use RIGHT MOUSE BUTTON to draw the pixelated cells that will initialize the map. Then, press ENTER to start the simulation with those drawn cells.\n\n";
    cout<<"- Press q or close the simulation window to exit out of the simulation...but if you chose to draw on an empty map(i.e., Option 9), you'll have to press q twice OR close the simulation window twice to quit.\n\n";
    cout<<"- Press SPACE to pause the running simulation at any time and press SPACE again to continue.\n\n\n";

    cout<<"Press ENTER to show the main menu...";
    char c='$';
    while(c!='\n') c=cin.get();
}

void mainMenu()
{
    cout<<"Choose a map initializer from options given below:-\n\n";
    cout<<"    0) Randomly Initialize map\n";
    cout<<"    1) Preset 1\n";
    cout<<"    2) Preset 2\n";
    cout<<"    3) Preset 3\n";
    cout<<"    4) Preset 4\n";
    cout<<"    5) Preset 5\n";
    cout<<"    6) Preset 6\n";
    cout<<"    7) Preset 7\n";
    cout<<"    8) Gosper's Glider Guns\n";
    cout<<"    9) Draw pixelated cells yourself on an Empty Map\n\n";
    cout<<"   -1) To exit the program\n";
}

void start(int choice)
{
    if(!init())
    {
        cout<<"SDL Initialization Failed\n";
    }
    else
    {
        World w;
        switch(choice)
        {
            case(0):
                w.randomInit();
                break;
            case(1):
                w.preset1();
                break;
            case(2):
                w.preset2();
                break;
            case(3):
                w.preset3();
                break;
            case(4):
                w.preset4();
                break;
            case(5):
                w.preset5();
                break;
            case(6):
                w.preset6();
                break;
            case(7):
                w.preset7();
                break;
            case(8):
                w.gosperGliderGuns();
                break;
            case(9):
                w.emptyWorld();
        }
        cout<<"\nMAP INITIALIZED\n";
        w.gameOfLife();
    }
    close();
    cout<<"\nSIMULATION STOPPED\n";
}

int main(int argc, char* args[])
{
    intro();

    bool go=true;
    while(go)
    {
        cout<<'\n';
        mainMenu();
        int choice;
        cout<<"\nType an option and then press Enter: ";
        cin>>choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if(choice==-1)
        {
            go=false;
            cout<<"\nEXITING PROGRAM\n";
        }
        else if(choice>=0 && choice<=9)
        {
            cout<<"\nINITIALIZING MAP\n";
            if(choice==9)
            {
                cout<<"\nYou have chosen option 9. Note some input rules:-\n- You have to use RIGHT MOUSE BUTTON to draw pixelated cells.\n- When you are done drawing, press ENTER to start simulation.\n- To exit out of simulation, press q twice OR close the simulation window twice.\n- And of course, once the simulation starts, you can then use the LEFT MOUSE BUTTON to draw cells as mentioned before.\n";
            }
            start(choice);
        }
    }

    return 0;
}

World::World()
{
    for(int i=0; i<WORLD_HEIGHT; i++)
    {
        world[i]=new char[WORLD_WIDTH];
        next[i]=new char[WORLD_WIDTH];
        drawing[i]=new char[WORLD_WIDTH];
        neighbours[i]=new int[WORLD_WIDTH];
        nextNeighbours[i]=new int[WORLD_WIDTH];
        for(int j=0; j<WORLD_WIDTH; j++)
        {
            world[i][j]='0';
            next[i][j]='0';
            drawing[i][j]='0';
            neighbours[i][j]=0;
            nextNeighbours[i][j]=0;
        }
    }
}

World::~World()
{
    for(int i=0; i<WORLD_HEIGHT; i++)
    {
        delete []world[i];
        delete []next[i];
        delete []drawing[i];
        delete []neighbours[i];
        delete []nextNeighbours[i];
    }
    delete []world;
    delete []next;
    delete []drawing;
    delete []neighbours;
    delete []nextNeighbours;
}

void World::gameOfLife()
{
    calculateNeighbours();
    cout<<"\nSIMULATION RUNNING\n";

    bool leftMouseButtonDown=false;
    SDL_Event e;
    bool quit=false;
    while(!quit)
    {
        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type==SDL_QUIT)
            {
                quit=true;
            }
            else if(e.type==SDL_KEYDOWN && e.key.keysym.sym==SDLK_q)
            {
                quit=true;
            }
            else if(e.type==SDL_KEYDOWN && e.key.keysym.sym==SDLK_SPACE)
            {
                pause();
            }
            else if(e.type==SDL_MOUSEBUTTONDOWN || e.type==SDL_MOUSEBUTTONUP || e.type==SDL_MOUSEMOTION)
            {
                switch(e.type)
                {
                    case(SDL_MOUSEBUTTONUP):
                        if(e.button.button==SDL_BUTTON_LEFT)
                        {
                            leftMouseButtonDown=false;
                            released=true;
                        }
                        break;
                    case(SDL_MOUSEBUTTONDOWN):
                        if(e.button.button==SDL_BUTTON_LEFT)
                        {
                            leftMouseButtonDown=true;
                            released=false;
                        }
                    case(SDL_MOUSEMOTION):
                        if(leftMouseButtonDown)
                        {
                            released=false;
                            drawing[e.motion.x][e.motion.y]='*';
                            break;
                        }
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        renderGens();
        SDL_RenderPresent(renderer);
    }
}

void World::renderGens()
{
    for(int i=0; i<WORLD_HEIGHT; i++)
    {
        for(int j=0; j<WORLD_WIDTH; j++)
        {
            if(renderInitial==false)
            {
                if(world[i][j]=='*')
                {
                    SDL_RenderDrawPoint(renderer, i, j);
                }
            }
            else
            {
                int alive=neighbours[i][j];
                if(world[i][j]=='0')
                {
                    if(alive==3)
                    {
                        next[i][j]='*';
                        setNextNeighboursAdjacents(i, j, true);
                    }
                }
                else
                {
                    if(alive<2)
                    {
                        next[i][j]='0';
                        setNextNeighboursAdjacents(i, j, false);
                    }
                    else if(alive==2 || alive==3)
                    {
                        next[i][j]='*';
                    }
                    else
                    {
                        next[i][j]='0';
                        setNextNeighboursAdjacents(i, j, false);
                    }
                }
            }
        }
    }

    if(renderInitial==false)
    {
        renderInitial=true;
        return;
    }

    for(int i=0; i<WORLD_HEIGHT; i++)
    {
        for(int j=0; j<WORLD_WIDTH; j++)
        {
            if(drawing[i][j]=='*' && !released)
            {
                SDL_RenderDrawPoint(renderer, i, j);
            }
            if(drawing[i][j]=='*' && released)
            {
                drawing[i][j]='0';
                next[i][j]='*';
                setNextNeighboursAdjacents(i, j, true);
            }
            if(next[i][j]=='*')
            {
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }
    }

    for(int i=0; i<WORLD_HEIGHT; i++)
    {
        for(int j=0; j<WORLD_WIDTH; j++)
        {
            world[i][j]='0';
            neighbours[i][j]=nextNeighbours[i][j];
        }
    }

    temp1=world;
    world=next;
    next=temp1;

    temp2=neighbours;
    neighbours=nextNeighbours;
    nextNeighbours=temp2;
}

void World::calculateNeighbours()
{
    for(int i=0; i<WORLD_HEIGHT; i++)
    {
        for(int j=0; j<WORLD_WIDTH; j++)
        {
            neighbours[i][j]=getNeighbourAliveCount(i, j);
            nextNeighbours[i][j]=neighbours[i][j];
        }
    }
}

int World::getNeighbourAliveCount(int i, int j)
{
    int count=0;
    for(int x=i-1, y=j-1; y<=j+1; y++)
    {
        if(x>=0 && y>=0 && y<=WORLD_WIDTH-1 && world[x][y]=='*')
        {
            count++;
        }
    }
    for(int x=i+1, y=j-1; y<=j+1; y++)
    {
        if(x<=WORLD_WIDTH-1 && y>=0 && y<=WORLD_WIDTH-1 && world[x][y]=='*')
        {
            count++;
        }
    }
    if(j-1>=0 && world[i][j-1]=='*')
    {
        count++;
    }
    if(j+1<=WORLD_WIDTH-1 && world[i][j+1]=='*')
    {
        count++;
    }
    return count;
}

void World::setNextNeighboursAdjacents(int i, int j, bool state)
{
    for(int x=i-1, y=j-1; y<=j+1; y++)
    {
        if(x>=0 && y>=0 && y<=WORLD_WIDTH-1)
        {
            if(state==true)
            {
                nextNeighbours[x][y]++;
            }
            else
            {
                nextNeighbours[x][y]--;
            }
        }
    }
    for(int x=i+1, y=j-1; y<=j+1; y++)
    {
        if(x<=WORLD_WIDTH-1 && y>=0 && y<=WORLD_WIDTH-1)
        {
            if(state==true)
            {
                nextNeighbours[x][y]++;
            }
            else
            {
                nextNeighbours[x][y]--;
            }
        }
    }
    if(j-1>=0)
    {
        if(state==true)
        {
            nextNeighbours[i][j-1]++;
        }
        else
        {
            nextNeighbours[i][j-1]--;
        }
    }
    if(j+1<=WORLD_WIDTH-1)
    {
        if(state==true)
        {
            nextNeighbours[i][j+1]++;
        }
        else
        {
            nextNeighbours[i][j+1]--;
        }
    }
}

void World::pause()
{
    bool ok=false;
    SDL_Event e;
    while(!ok)
    {
        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type==SDL_KEYDOWN && e.key.keysym.sym==SDLK_SPACE)
            {
                ok=true;
            }
        }
    }
}

void World::preset1()
{
    for(int i=0; i<WORLD_HEIGHT; i++)
    {
        for(int j=0; j<WORLD_WIDTH; j++)
        {
            if(i==0 || i==WORLD_HEIGHT-1 || j==0 || j==WORLD_WIDTH-1)
            {
                if(world[i][j]=='0')
                {
                    world[i][j]='*';
                }
            }
        }
    }
}

void World::preset2()
{
    for(int i=0; i<WORLD_HEIGHT; i++)
    {
        for(int j=0; j<WORLD_WIDTH; j++)
        {
            if(i==WORLD_WIDTH/2 || j==WORLD_WIDTH/2)
            {
                if(world[i][j]=='0')
                {
                    world[i][j]='*';
                }
            }
        }
    }
}

void World::preset3()
{
    for(int i=0; i<WORLD_HEIGHT; i++)
    {
        for(int j=0; j<WORLD_WIDTH; j++)
        {
            if(j%2==0 && world[i][j]=='0')
            {
                world[i][j]='*';
            }
        }
    }
}

void World::preset4()
{
    for(int i=0; i<WORLD_HEIGHT; i++)
    {
        for(int j=0; j<WORLD_WIDTH; j++)
        {
            if(i%100==0 && world[i][j]=='0')
            {
                world[i][j]='*';
            }
        }
    }
}

void World::preset5()
{
    for(int i=0; i<WORLD_HEIGHT; i++)
    {
        for(int j=0; j<WORLD_WIDTH; j++)
        {
            if(i==j && world[i][j]=='0')
            {
                world[i][j]='*';
            }
            if(i+j==WORLD_WIDTH-1 && world[i][j]=='0')
            {
                world[i][j]='*';
            }
        }
    }
}

void World::preset6()
{
    for(int i=0; i<WORLD_HEIGHT; i++)
    {
        for(int j=0; j<WORLD_WIDTH; j++)
        {
            if(i%10==0 && world[i][j]=='0')
            {
                world[i][j]='*';
            }
        }
    }
}

void World::preset7()
{
    int i=373;
    for(int j=300; j<=307; j++)
    {
        world[i][j]='*';
    }
    for(int j=309; j<=313; j++)
    {
        world[i][j]='*';
    }
    for(int j=317; j<=319; j++)
    {
        world[i][j]='*';
    }
    for(int j=326; j<=332; j++)
    {
        world[i][j]='*';
    }
    for(int j=334; j<=338; j++)
    {
        world[i][j]='*';
    }
}

void World::gosperGliderGuns()
{
    world[200][200]='*';
    world[200][201]='*';
    world[201][200]='*';
    world[201][201]='*';

    world[200][210]='*';
    world[201][210]='*';
    world[202][210]='*';
    world[199][211]='*';
    world[198][212]='*';
    world[198][213]='*';
    world[203][211]='*';
    world[204][212]='*';
    world[204][213]='*';
    world[201][214]='*';
    world[199][215]='*';
    world[203][215]='*';
    world[200][216]='*';
    world[201][216]='*';
    world[202][216]='*';
    world[201][217]='*';

    world[200][220]='*';
    world[199][220]='*';
    world[198][220]='*';
    world[200][221]='*';
    world[199][221]='*';
    world[198][221]='*';
    world[201][222]='*';
    world[197][222]='*';
    world[197][224]='*';
    world[196][224]='*';
    world[201][224]='*';
    world[202][224]='*';

    world[199][234]='*';
    world[198][234]='*';
    world[199][235]='*';
    world[198][235]='*';
}

void World::emptyWorld()
{
    isItEmptyWorld=true;

    bool rightMouseButtonDown=false;
    bool done=false;
    SDL_Event e;
    while(!done)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type==SDL_QUIT)
            {
                done=true;
                break;
            }
            else if(e.type==SDL_KEYDOWN && isItEmptyWorld)
            {
                if(e.key.keysym.sym==SDLK_q || e.key.keysym.sym==SDLK_RETURN)
                {
                    done=true;
                    break;
                }
            }
            else if(e.type==SDL_MOUSEBUTTONDOWN || e.type==SDL_MOUSEBUTTONUP || e.type==SDL_MOUSEMOTION)
            {
                switch(e.type)
                {
                    case(SDL_MOUSEBUTTONUP):
                        if(e.button.button==SDL_BUTTON_RIGHT)
                            rightMouseButtonDown=false;
                        break;
                    case(SDL_MOUSEBUTTONDOWN):
                        if(e.button.button==SDL_BUTTON_RIGHT)
                            rightMouseButtonDown=true;
                    case(SDL_MOUSEMOTION):
                        if(rightMouseButtonDown)
                            world[e.motion.x][e.motion.y]='*';
                        break;
                }
            }
        }

        for(int i=0; i<WORLD_WIDTH; i++)
        {
            for(int j=0; j<WORLD_HEIGHT; j++)
            {
                if(world[i][j]=='*')
                {
                    SDL_RenderDrawPoint(renderer, i, j);
                }
            }
        }
        SDL_RenderPresent(renderer);
    }
}

void World::randomInit()
{
    int cells=(WORLD_HEIGHT*WORLD_WIDTH);
    unsigned int seed=(unsigned)time(NULL);
    srand(seed);

    for(int i=0; i<cells; i++)
    {
        int x=rand()%(WORLD_HEIGHT-1);
        int y=rand()%(WORLD_WIDTH-1);

        if(world[x][y]=='0')
        {
            world[x][y]='*';
        }
    }
}
