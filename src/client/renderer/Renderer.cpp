#include <Renderer.h>



bool Renderer::Initialize(SDL_Window* sdlWindow)
{

	 /* Create GL context with SDL window */
    sdlGlContext = SDL_GL_CreateContext(sdlWindow);
    if(sdlGlContext == NULL)
    {
        printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    /* Set OpenGL Version, Major and Minor */
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		  
    /* Use Vsync */
    if(SDL_GL_SetSwapInterval(1) < 0)
    {
        printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    /*************************/
    /* OpenGL Initialization */
    /*************************/
    
    error = GL_NO_ERROR;

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

    /* Initialize GLEW */
    error = glewInit();
    if (error != GLEW_OK)
    {
        printf("Error initializing GLEW! %s\n", gluErrorString( error ) );
        return false; // or handle the error in a nicer way
    }
    if (!GLEW_VERSION_2_1) 
    {
        printf("Cannot support GLEW_VERSION_2_1 API");
        return false;
    }
    /*******************************/
    /* End of OpenGL initializaion */
    /*******************************/
}

void Renderer::Render()
{
	//Test out our new Shader.h
    Shader testShader(  "../src/client/renderer/shaders/simpleVertexShader.vs",
                        "../src/client/renderer/shaders/simpleFragmentShader.fs"
                        );       






    /* Clear color buffer */
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT );
}

void Renderer::Close()
{
	SDL_GL_DeleteContext( sdlGlContext );



    /* Destroy window and context */
    //SDL_DestroyWindow( window );
}