#include <string.h>
#include <stdio.h>
#include <ZengineServer.h>  


/*
   ZengineServer Implementation
*/
bool ZengineServer::Initialize()
{
  
    clientChannel.Initialize();

    zengineGame.Initialize();

    return true;
}

void ZengineServer::OnEvent()
{

  message = clientChannel.getMessage();

  /* game.handleMessage(message) */

}

void ZengineServer::Loop()
{

    

   


    
    zengineGame.Update();

    
    /* clientChannel.broadcastGameState(game.getGameState()); */


    /* Quit if packet contains "quit" */
    if (strcmp(message, "quit") == 0)
        Running = false;

}

void ZengineServer::Exit()
{

    clientChannel.Close();

    zengineGame.Close();

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

        OnEvent();

        Loop();

    }

    Exit();
  
  return 0;
}

