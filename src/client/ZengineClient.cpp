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
    window = SDL_CreateWindow(
            "Zengine Client",                  //Window Title
       		SDL_WINDOWPOS_UNDEFINED,           //Initial x position
       		SDL_WINDOWPOS_UNDEFINED,           //Initial y position
       		SCREEN_WIDTH,                      //Width, in pixels currently CONSTANT
       		SCREEN_HEIGHT,                     //Height, in pixels currently CONSTANT
       		SDL_WINDOW_OPENGL                  //Flags
       		| SDL_WINDOW_SHOWN
       		);

    if( window == NULL )
    {
        printf( "Window could not be created! SDL_ERROR: %s\n", SDL_GetError() );
        return false;
    }

    //windower.Initialize();

    /* Enable SDL text input */
    SDL_StartTextInput(); 
  
    /* Start server connection */
    serverConnection.Initialize();


    /* Start renderer*/
    renderer.Initialize(window);

    /* Clear message */
    memset(message, 0, sizeof(message));


    return true; 
} 

void ZengineClient::OnEvent(SDL_Event* Event) //SDL_Event* Event
{
    /* User requests quit */
    if( Event->type == SDL_QUIT)
    {
        Running = false;
        serverConnection.sendMessage("quit");
    }

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
            memset(message, 0, sizeof(message));

        } 
    }

    // /* Clear message */
    // memset(message, 0, sizeof(message));

    // /* Get new message */
    // strcpy(message, windower.handleEvents());

    // //message = windower.handleEvents();

    // if(!strcmp(message, "quit"))
    // {
    //     Running = false;
    // }

    // /*Send message to server */
    // serverConnection.sendMessage(message);

}

void ZengineClient::Loop()
{
  
    serverConnection.getGameState();




}

void ZengineClient::Render()
{

    renderer.Render();

    //windower.updateScreen();

    /* Update screen */
     SDL_GL_SwapWindow( window );

}

void ZengineClient::Exit()
{
    /* Destroy window and context */
    SDL_DestroyWindow( window );

    /* Quit SDL subsystems */
    SDL_Quit();
    SDL_StopTextInput();
 
    /* Close renderer */
    renderer.Close();

    //windower.Close();

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

        //OnEvent();

        Loop();

        Render();

    }

    Exit();
  
    return 0;
}


