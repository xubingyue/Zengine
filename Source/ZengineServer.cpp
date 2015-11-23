 /*
   Include Files
*/
#include<stdio.h>
#include<string>
#include<fstream>


/*
  Class Declaration
*/

class ZengineServer {
    private:
        bool    Running;
 
    public:
        ZengineServer();
 
        int Run();
 
    private:
 
        bool Initialize();
 
        //Get>Execute>Tell players' results
        void OnEvent(); 
 
        //Simulate world and broadcast to all players
        void Loop();
 
        //Note, no Render loop, rendering is handled by the client.

        void Exit();
};


/*
  Function Implementation
*/
bool ZengineServer::Initialize()
{
  return true;
}

void ZengineServer::OnEvent()
{
  
}

void ZengineServer::Loop()
{
  Running = false;
}

void ZengineServer::Exit()
{

}

ZengineServer::ZengineServer()
{
  Running = true;
}

int ZengineServer::Run()
{
  if(Initialize() == false)
    {
      return -1;
    }

  while(Running)
    {
      //while(true) //Infinite atm, need to loop through players vector
	for(int i = 0; i < 10; i++) //Temp loop
	{
	  OnEvent();
	}

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
