 /*
   Include Files
*/ 

//Using SDL2 and OpenGL 
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_net.h> 
#include <GL/glu.h>

  

//Standard libraries
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <fstream>

//UDP headers
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>


/*
  Constants (Should be temporary)
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
 
        void Render();

        void Exit();

    private:
   
        SDL_Window* window;
        SDL_GLContext context;

        // //Server Stuff
        // int sockfd, portno;
        // struct sockaddr_in serv_addr;
        // socklen_t servlen;
        // struct hostent *server;
        // char buffer[256];

        char message[256];
        char *composition;
        Sint32 cursor;
        Sint32 selection_len;


        //UDP Stuff
        UDPsocket sd;
        IPaddress srvadd;
        UDPpacket *p;

};


/*
  Function Implementation
*/





bool ZengineClient::Initialize()
{
  //Start SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
      printf( "SDL COULD NOT INITIALIZE! SDL_ERROR: %s\n", SDL_GetError() );
      return false;
    }
	
	    
  //Create Window
  this->window = SDL_CreateWindow(
     			    "Zengine Client", //Window Title
       			  SDL_WINDOWPOS_UNDEFINED,           //Initial x position
       			  SDL_WINDOWPOS_UNDEFINED,           //Initial y position
       			  SCREEN_WIDTH,                      //Width, in pixels currently CONSTANT
       			  SCREEN_HEIGHT,                     //Height, in pixels currently CONSTANT
       			  SDL_WINDOW_OPENGL                  //Flags
       			  | SDL_WINDOW_SHOWN
       			  );

  if( this->window == NULL )
    {
      printf( "WINDOW COULD NOT BE CREATED! SDL_ERROR: %s\n", SDL_GetError() );
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

  // //Server connection stuff
  // portno = 5050;
  // sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  // if(sockfd < 0)
  //   perror("ERROR opening socket");
  // server = gethostbyname("localhost");
  // if(server == NULL)
  //   {
  //     fprintf(stderr, "ERROR, no such host\n");
  //     exit(0);
  //   }
  // bzero((char *) &serv_addr, sizeof(serv_addr));
  // serv_addr.sin_family = AF_INET;
  // bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
  // serv_addr.sin_port = htons(portno);
  // servlen = sizeof(serv_addr);

  SDL_StartTextInput();
  



  /* UDP SERVER STUFF +_AS(DF_A(SD_F)) */
  /* Initialize SDL_net */
  if (SDLNet_Init() < 0)
  {
    fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
    exit(EXIT_FAILURE);
  }
 
  /* Open a socket on random port */
  if (!(sd = SDLNet_UDP_Open(0)))
  {
    fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
    exit(EXIT_FAILURE);
  }
  int port = 3000;
  /* Resolve server name  */
  if (SDLNet_ResolveHost(&srvadd, "localhost", port) == -1)
  {
    fprintf(stderr, "SDLNet_ResolveHost(%s %d): %s\n", "localhost", port, SDLNet_GetError());
    exit(EXIT_FAILURE);
  }
 
  /* Allocate memory for the packet */
  if (!(p = SDLNet_AllocPacket(512)))
  {
    fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
    exit(EXIT_FAILURE);
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

    if (Event->type == SDL_TEXTINPUT)
    {
      strcat(message, Event->text.text);
    }
    if(Event->type == SDL_TEXTEDITING)
    {
       /*
        Update the composition text.
        Update the cursor position.
        Update the selection length (if any).
        */
        composition = Event->edit.text;
        cursor = Event->edit.start;
        selection_len = Event->edit.length;
    }
    if(Event->type == SDL_KEYDOWN)
    {

       if( Event->key.keysym.sym == SDLK_RETURN )
         {
           strcpy((char *)p->data, message);
           /* Quit if packet contains "quit" */
           if (!strcmp((char *)p->data, "quit"))
              Running = false;

            p->address.host = srvadd.host;  /* Set the destination host */
            p->address.port = srvadd.port;  /* And destination port */
 
            p->len = strlen((char *)p->data) + 1;
            SDLNet_UDP_Send(sd, -1, p); /* This sets the p->channel */
            memset(message,0,sizeof(message));
          }
      
    }
}

void ZengineClient::Loop()
{
  // printf("Please enter the message: ");
  // bzero(buffer, 256);
  // fgets(buffer, 255, stdin);
  // if((sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr * )&serv_addr, servlen )) < 0)
  //   perror("ERROR writing to socket, sendto()");
  // if(strcmp(buffer, "quit\n") == 0 )
  //   Running = false;
  // bzero(buffer, 256);
  // if(Running)   //This makes sure that we don't wait for a message from a Server that was shut down by another client
  //   if((recvfrom(sockfd, buffer, 255, 0, (struct sockaddr *)&serv_addr, &servlen )) < 0 )
  //     perror("ERROR reading from socket, recvfrom()");
  // printf("%s\n", buffer);

    //printf("Fill the buffer\n>");
    //scanf("%s", (char *)p->data);
 
    // p->address.host = srvadd.host;  /* Set the destination host */
    // p->address.port = srvadd.port;  /* And destination port */
 
    // p->len = strlen((char *)p->data) + 1;
    // SDLNet_UDP_Send(sd, -1, p); /* This sets the p->channel */
 
    // /* Quit if packet contains "quit" */
    // if (!strcmp((char *)p->data, "quit"))
    //   Running = false;


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

  // //Close socket
  // close(sockfd);



  SDLNet_FreePacket(p);
  SDLNet_Quit();
  SDL_StopTextInput();
}

ZengineClient::ZengineClient()
{
  Running = true;
}









/* ******************************************************************* */

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

