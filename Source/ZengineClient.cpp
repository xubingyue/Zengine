 /*
   Include Files
*/

//Using SDL2 and OpenGL
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>
#include<GL/glu.h>
#include<stdio.h>
#include<string>
#include<fstream>

/*
  Constants
*/
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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
 
        //Get messages from Server and Render
        void Render();

        void Exit();

    private:
   
        SDL_Window* window;
        SDL_GLContext context;

};


/*
  Function Implementation
*/
bool ZengineClient::Initialize()
{
  //INITIALIZE SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
      printf( "SDL COULD NOT INITIALIZE! SDL_ERROR: %S\N", SDL_GetError() );
      return false;
    }
	
	    
  //CREATE WINDOW
  this->window = SDL_CreateWindow(
     			  "You should probably be studying", //Window Title
       			  SDL_WINDOWPOS_UNDEFINED,           //Initial x position
       			  SDL_WINDOWPOS_UNDEFINED,           //Initial y position
       			  SCREEN_WIDTH,                      //Width, in pixels
       			  SCREEN_HEIGHT,                     //Height, in pixels
       			  SDL_WINDOW_OPENGL                  //Flags
       			  | SDL_WINDOW_SHOWN
       			  );

  if( this->window == NULL )
    {
      printf( "WINDOW COULD NOT BE CREATED! SDL_ERROR: %S\N", SDL_GetError() );
      return false;
     }
	 	    
  //Create Context
  this->context = SDL_GL_CreateContext(window);
  if(this->context == NULL)
    {
      printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
      return false;
    }
	     		
  //Set OpenGL Version, Major and Minor
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		  
  //Use Vsync
  if(SDL_GL_SetSwapInterval(1) < 0)
    {
      printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
      return false;
    }

  GLenum error = GL_NO_ERROR;

  //Initialize Projection Matrix
  glMatrixMode( GL_PROJECTION ); 
  glLoadIdentity();

  //Check for error
  error = glGetError();
  if( error != GL_NO_ERROR )
    {
      printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) ); 
      return false;
    }

  //Initialize Modelview Matrix
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity(); 

  //Check for error
  error = glGetError(); 
  if( error != GL_NO_ERROR )
    {
      printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
      return false;
    }

  //Initialize clear color
  glClearColor( 0.f, 0.f, 0.f, 1.f );

  //Check for error 
  error = glGetError();
  if( error != GL_NO_ERROR )
    {
      printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
      return false;
    }

  return true;
}

void ZengineClient::OnEvent(SDL_Event* Event)
{
    //User requests quit
    if( Event->type == SDL_QUIT)
      {
        Running = false;
      }
}

void ZengineClient::Loop()
{

}

void ZengineClient::Render()
{
  //Clear color buffer
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear( GL_COLOR_BUFFER_BIT );

  //Update screen
  SDL_GL_SwapWindow( window );
}

void ZengineClient::Exit()
{
  //Destroy window and context
  SDL_DestroyWindow( window );
  SDL_GL_DeleteContext( context );

  //Quit SDL subsystems
  SDL_Quit();
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

int main (int argc, char* args[])
{
  ZengineClient TestClient;

  TestClient.Run();

  return 0;
}

