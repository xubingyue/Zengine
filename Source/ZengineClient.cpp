/*
  Class Declaration
*/

class ZengineClient {
    private:
        bool    Running;
 
    public:
        ZengineClient();
 
        int Run();
 
    private:
 
        bool Initialize();
 
        void OnEvent(SDL_Event* Event); 
 
        //Non-Server related things
        void Loop();
 
        //Get messages from Server and Render
        void Render();

        void Exit();
};


/*
  Function Implementation
*/
bool ZengineClient::Initialize()
{
  return true;
}

void ZengineClient::OnEvent(SDL_Event* Event)
{
  
}

void ZengineClient::Loop()
{

}

void ZengineClient::Exit()
{

}

ZengineClient::ZengineClient()
{
  Running = true;
}

int ZengineClient::Run()
{
  if(Initialize() == false)
    {
      return -1;
    }

  SDL_Event Event;

  while(Running)
    {
      while(SDL_PollEvent(&Event)) 
	{
	  OnEvent(&Event);
	}

      Loop();

      Render();

    }

  Exit();
  
  return 0;
}
