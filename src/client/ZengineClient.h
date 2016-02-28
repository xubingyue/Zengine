
#include <Window.h>
#include <Network.h>
#include <Renderer.h>

#include <vector>
#include <string>
using namespace std;

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
 
        void OnEvent();
 
        void Loop();
 
        void Render();

        void Exit();

    private:
   
        SDL_Window* window;
        SDL_Event Event;

        //char message[256];
        char *composition;
        Sint32 cursor;
        Sint32 selection_len;

        vector<string> windowMessageList;

        UDP_ServerConnection serverConnection;
        Renderer renderer;
        Window zengineWindow;

};