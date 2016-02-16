//ZengineClient.h
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_net.h> 
#include <GL/glu.h>

#include <Network.h>


//Standard libraries
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <fstream>

/*
  Class Declaration
*/

class ZengineClient {
    private:
        bool    Running;
 
    public:
        ZengineClient();
 
        int Run();
 
    public:
 
        bool Initialize();
 
        void OnEvent(SDL_Event* Event); 
 
        //Non-Server related things
        void Loop();
 
        void Render();

        void Exit();

    private:
   
        SDL_Window* window;
        SDL_GLContext context;

        char message[256];
        char *composition;
        Sint32 cursor;
        Sint32 selection_len;


        UDP_ServerConnection serverConnection;

};