#include <Window.h>

bool Window::Initialize()
{
	SCREEN_WIDTH = 640;
	SCREEN_HEIGHT = 480;

	/* Start SDL */
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL COULD NOT INITIALIZE! SDL_ERROR: %s\n", SDL_GetError() );
        return false;
    }	
	    
    /* Create window */
    sdlWindow = SDL_CreateWindow(
            "Zengine Client",                  //Window Title
       		SDL_WINDOWPOS_UNDEFINED,           //Initial x position
       		SDL_WINDOWPOS_UNDEFINED,           //Initial y position
       		SCREEN_WIDTH,                      //Width, in pixels currently CONSTANT
       		SCREEN_HEIGHT,                     //Height, in pixels currently CONSTANT
       		SDL_WINDOW_OPENGL                  //Flags
       		| SDL_WINDOW_SHOWN
       		);

    if( sdlWindow == NULL )
    {
        printf( "Window could not be created! SDL_ERROR: %s\n", SDL_GetError() );
        return false;
    }

    /* Enable SDL text input */
    SDL_StartTextInput(); 
}

void Window::handleEvents()
{
	while(SDL_PollEvent(&sdlEvent)) 
	{
		/* User requests quit */
    	if( sdlEvent.type == SDL_QUIT)
    	{
        	//Running = false;
        	message = "quit";
        	//strcpy(message.c_str(), "quit");
        	messageList.push_back(message);
    	}

    	if (sdlEvent.type == SDL_TEXTINPUT)
    		message += sdlEvent.text.text;
    	   // strcat(message.c_str(), sdlEvent.text.text);

    	if(sdlEvent.type == SDL_TEXTEDITING)
    	{
    	   /*
    	    Update the composition text.
    	    Update the cursor position.
    	    Update the selection length (if any).
    	    */
    	    composition = sdlEvent.edit.text;
    	    cursor = sdlEvent.edit.start;
    	    selection_len = sdlEvent.edit.length;
    	}

    	if(sdlEvent.type == SDL_KEYDOWN)
    	{

        	if( sdlEvent.key.keysym.sym == SDLK_RETURN )
        	{
        	    /* Quit if packet contains "quit" */
        	   // if (!strcmp(message.c_str(), "quit"))
        	        //Running = false;

            	/* Send message to server */
            	//serverConnection.sendMessage(message);
        	    	messageList.push_back(message);

            	/* Clear message */
            	message.clear();
            	//memset(message.c_str(), 0, sizeof(message));

        	} 	
    	}	
	}	
}	
	
void Window::updateWindow()
{
	SDL_GL_SwapWindow( sdlWindow );
}

void Window::Close()
{
	/* Destroy window and context */
    SDL_DestroyWindow( sdlWindow );

    /* Quit SDL subsystems */
    SDL_Quit();
    SDL_StopTextInput();
}


vector<string> Window::getMessageList()
{
	return messageList;
}

SDL_Window* Window::getWindow()
{
	return sdlWindow;
}

void Window::clearMessageList()
{
	messageList.clear();

}