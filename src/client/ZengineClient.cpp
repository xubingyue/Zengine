 /*
   Include Files
*/ 
#include <ZengineClient.h>

/*
  Constants (temporary)
*/
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


/*
  Function Implementation
*/
bool ZengineClient::Initialize()
{
    /* Start SDL */
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL COULD NOT INITIALIZE! SDL_ERROR: %s\n", SDL_GetError() );
        return false;
    }
	
	    
    /* Create window */
    this->window = SDL_CreateWindow(
            "Zengine Client",                  //Window Title
       		SDL_WINDOWPOS_UNDEFINED,           //Initial x position
       		SDL_WINDOWPOS_UNDEFINED,           //Initial y position
       		SCREEN_WIDTH,                      //Width, in pixels currently CONSTANT
       		SCREEN_HEIGHT,                     //Height, in pixels currently CONSTANT
       		SDL_WINDOW_OPENGL                  //Flags
       		| SDL_WINDOW_SHOWN
       		);

    if( this->window == NULL )
    {
        printf( "Window could not be created! SDL_ERROR: %s\n", SDL_GetError() );
        return false;
    }
	 	    
    /* Create GL context with SDL window */
    this->context = SDL_GL_CreateContext(window);
    if(this->context == NULL)
    {
        printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
	     		
    /* Set OpenGL Version, Major and Minor */
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		  
    /* Use Vsync */
    if(SDL_GL_SetSwapInterval(1) < 0)
    {
        printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    /* OpenGL Initialization */
    GLenum error = GL_NO_ERROR;

    /* Initialize Projection Matrix */
    glMatrixMode( GL_PROJECTION ); 
    glLoadIdentity();

    /* Check for error */
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) ); 
        return false;
    }

    /* Initialize Modelview Matrix */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity(); 

    /* Check for error */
    error = glGetError(); 
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

    /* Initialize clear color */
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    /* Check for error */ 
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

    /* End of OpenGL initializaion */


    /* Enable SDL text input */
    SDL_StartTextInput();
  
    /* Start server connection */
    serverConnection.Initialize();

    return true;
}

void ZengineClient::OnEvent(SDL_Event* Event)
{
    /* User requests quit */
    if( Event->type == SDL_QUIT)
        Running = false;

    if (Event->type == SDL_TEXTINPUT)
        strcat(message, Event->text.text);

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
            /* Quit if packet contains "quit" */
            if (!strcmp(message, "quit"))
                Running = false;

            /* Send message to server */
            serverConnection.sendMessage(message);

            /* Clear message */
            memset(message,0,sizeof(message));

        } 
    }
}

void ZengineClient::Loop()
{
  
    serverConnection.getGameState();

}

void ZengineClient::Render()
{
    /* Clear color buffer */
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT );

    /* Update screen */
    SDL_GL_SwapWindow( window );

}

void ZengineClient::Exit()
{
    /* Destroy window and context */
    SDL_DestroyWindow( window );
    SDL_GL_DeleteContext( context );

    /* Quit SDL subsystems */
    SDL_Quit();
    SDL_StopTextInput();
 
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
    

    SDL_Event Event;

    while(Running)
    {
        while(SDL_PollEvent(&Event)) 
            OnEvent(&Event);

        Loop();

        Render();

    }

    Exit();
  
    return 0;
}


