//ZengineServer.h
#include <stdio.h>
#include <network/Network.h>


/*
  Class Declaration
*/

class ZengineServer {
    private:
        bool    Running;
 
    public:
        ZengineServer();
 
        int Run();
 
    public:
 
        bool Initialize();
 
        //Get>Execute>Tell players' results
        void OnEvent(); 
 
        //Simulate world and broadcast to all players
        void Loop();
 
        //Note, no Render loop, rendering is handled by the client.

        void Exit();

    private:

        char * message;
        UDP_Network clientChannel;
        
};