#include <Window.h>

bool Window::Initialize()
{
	/* Start SDL */
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL COULD NOT INITIALIZE! SDL_ERROR: %s\n", SDL_GetError() );
        return false;
    }	
	SCREEN_WIDTH = 640;
	SCREEN_HEIGHT = 480;     
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
}

char* Window::handleEvents()
{


	while(SDL_PollEvent(Event))
	{
		/* User requests quit */
    	if( Event->type == SDL_QUIT)
    	{
    	    // Running = false;
    	    // serverConnection.sendMessage("quit");
    	    strcpy(message, "quit");
    	    return message;
    	}

	    if (Event->type == SDL_TEXTINPUT)
	        strcat(buffer, Event->text.text);

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

        	    // /* Quit if packet contains "quit" */
        	    // if (!strcmp(message, "quit"))
        	    //     Running = false;

            	// /*Send message to server */
           		// serverConnection.sendMessage(message);

        		strcpy(message, buffer);

            	/* Clear message */
            	memset(buffer, 0, sizeof(buffer));

            	return message;

        	} 
    	}
    }
}

void Window::updateScreen()
{
	SDL_GL_SwapWindow( window );
}

SDL_Window* Window::getWindow()
{
	return window;
}

char* Window::getMessage()
{
	return message;
}

void Window::Close()
{
	// /* Destroy window and context */
 //    SDL_DestroyWindow( window );

    /* Quit SDL subsystems */
    SDL_Quit();
    SDL_StopTextInput();
}