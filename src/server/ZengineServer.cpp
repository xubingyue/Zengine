 /*
   Include Files
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <ZengineServer.h>  
#include <network/UDPNetwork.h> 

//#include <SDL2/SDL_net.h>



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
        UDP_Connection clientConnection;
        
};


/*
  Function Implementation
*/




bool ZengineServer::Initialize()
{
  
    clientConnection.Initialize();

    return true;
}

void ZengineServer::OnEvent()
{

  
}

void ZengineServer::Loop()
{

    message = clientConnection.getMessage();


    /* Quit if packet contains "quit" */
    if (strcmp(message, "quit") == 0)
        Running = false;
    


}

void ZengineServer::Exit()
{

    clientConnection.Close();

}

ZengineServer::ZengineServer()
{

    Running = true;

}



int ZengineServer::Run()
{
    if(Initialize() == false)
      return -1;
    

    while(Running)
    {
      //while(true) //Infinite atm, need to loop through players vector
      //{
	   OnEvent();
      //}

        Loop();

    }

    Exit();
  
  return 0;
}

int main ( int argc, char* argv [] )
{
    ZengineServer TestServer;

    TestServer.Run();

  return 0;
}
