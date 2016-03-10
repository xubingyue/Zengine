 /*
   Include Files
*/ 
#include <ZengineClient.h>

#include <vector>

using namespace std;


/*
  Function Implementation
*/
bool ZengineClient::Initialize()
{
 
    /* Initialize window */
    zengineWindow.Initialize();

    /* Start server connection */
    serverConnection.Initialize();

    /* Start renderer*/
    renderer.Initialize(zengineWindow.getWindow());

    return true; 
} 

void ZengineClient::OnEvent() 
{

    zengineWindow.handleEvents();

    windowMessageList = zengineWindow.getMessageList();
    zengineWindow.clearMessageList();

    for ( auto &message : windowMessageList) 
    {  
        serverConnection.sendMessage(message.c_str());
        if (message == "quit")
            Running = false;
    }
 

    windowMessageList.clear();

}

void ZengineClient::Loop()
{
  
    serverConnection.getGameState();





}

void ZengineClient::Render()
{

    renderer.Render(); // <-- pass gamestate



    zengineWindow.updateWindow();

}

void ZengineClient::Exit()
{
 
    /* Close renderer */
    renderer.Close();

    /* Close window */
    zengineWindow.Close();

    /* Close connection to server */
    serverConnection.Close();

}

ZengineClient::ZengineClient()
{
  Running = true;
}









/* ******************************************************************* */

int ZengineClient::Run()
{
    if(!Initialize())
         return -1;


    

    while(Running)
    {

       

        OnEvent();

        Loop();

        Render();

    }

    Exit();
  
    return 0;
}


