#include <SDL2/SDL.h>

#include <Window.h>
#include <Network.h>
#include <Renderer.h>


/*
  Class Declaration
*/

class ZengineClient {
    
 
    public:
        ZengineClient();
 
        int Run();

    private:
        bool    Running;
 
    private:
 
        bool Initialize();
 
        void OnEvent(SDL_Event* Event); //SDL_Event* Event
 
        //Non-Server related things
        void Loop();
 
        void Render();

        void Exit();

    private:
   
        SDL_Window* window;
        //SDL_Event Event;

        char message[256];
        char *composition;
        Sint32 cursor;
        Sint32 selection_len;

        Window windower;
        UDP_ServerConnection serverConnection;
        Renderer renderer;

};