#include <string.h>
#include <stdio.h>
#include <ZengineServer.h>  

/*
   ZengineServer Implementation
*/
bool ZengineServer::Initialize()
{
  
    clientChannel.Initialize();

    return true;
}

void ZengineServer::OnEvent()
{

  
}

void ZengineServer::Loop()
{

    message = clientChannel.getMessage();

   


    /* game.handleMessage(message) */

    
    /* clientChannel.broadcastGameState(game.getGameState()); */


    /* Quit if packet contains "quit" */
    if (strcmp(message, "quit") == 0)
        Running = false;

}

void ZengineServer::Exit()
{

    clientChannel.Close();

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

        Loop();

    }

    Exit();
  
  return 0;
}

