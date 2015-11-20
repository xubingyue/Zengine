
//Using SDL and standard IO
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>
#include<GL/glu.h>
#include<stdio.h>
#include<string>
#include<fstream>

#include "Shader.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool initGL();

// Initialize OpenGL
bool initGL()
{
  bool success = true; 
  GLenum error = GL_NO_ERROR;

  //Initialize Projection Matrix
  glMatrixMode( GL_PROJECTION ); 
  glLoadIdentity();

  //Check for error
  error = glGetError();
  if( error != GL_NO_ERROR )
    {
      printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) ); 
      success = false;
    }

  //Initialize Modelview Matrix
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity(); 

  //Check for error
  error = glGetError(); 
  if( error != GL_NO_ERROR )
    {
      printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
      success = false;
    }

  //Initialize clear color
  glClearColor( 0.f, 0.f, 0.f, 1.f );

  //Check for error 
  error = glGetError();
  if( error != GL_NO_ERROR )
    {
      printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
      success = false;
    }
  return success;

}

int main( int argc, char* args[] )
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;


	//OpenGL context SDL_GLContext gContext;
	SDL_GLContext context;

	//INITIALIZE SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL COULD NOT INITIALIZE! SDL_ERROR: %S\N", SDL_GetError() );
	}
	else
	  {
	    
	  //CREATE WINDOW
	  window = SDL_CreateWindow("You should probably be studying", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
	  if( window == NULL )
	    {
       		printf( "WINDOW COULD NOT BE CREATED! SDL_ERROR: %S\N", SDL_GetError() );
	    }
	  else
	    {
	      //Create Context
	      context = SDL_GL_CreateContext(window);
	      if(context == NULL)
		{
		  printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
		}
	      else
		{
		  //Set OpenGL Version, Major and Minor
		  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1);
		  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		  
		  //Use Vsync
		  if(SDL_GL_SetSwapInterval(1) < 0)
		    {
		      printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
		    }
		  //Initialize OpenGL
		  if(!initGL())
		    {
		      printf("Unable to initialize OpenGL!");
		    }
		}
		  


	      //Clear color buffer
	      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	      glClear( GL_COLOR_BUFFER_BIT );

	      //Test out our new Shader.h
	      Shader testShader("Source/Shaders/simpleVertexShader.vs", "Source/Shaders/simpleFragmentShader.fs");	     

	      //Triangle Data
	      GLfloat triangleVertices[] = {
		 0.0f,    0.75f,  0.0f,   //Top Corner
	 	 0.75f,  -0.75f,  0.0f,   //Bottom Right Corner
		-0.75f,  -0.75f,  0.0f    //Bottom Left Corner
	      };
	      
	      //Rectangle Data
	      GLfloat rectVertices[] = {
		0.5f, 0.5f, 0.0f,       //Top Right
		0.5f, -0.5f, 0.0f,      //Bottom Right
		-0.5f, -0.5f, 0.0f,      //Bottom Left
		-0.5f, 0.5f, 0.0f        //Top Left
	      };

	     GLuint rectIndices[] = {  // Note that we start from 0!
	       0, 1, 3,   // First Triangle
	       1, 2, 3    // Second Triangle
	     };  

	     //Generate Vertex Array and Buffer Object for Triangle
	     GLuint tVBO, tVAO;
	     glGenVertexArrays(1, &tVBO);
	     glGenBuffers(1, &tVAO);

	     //Bind tVAO and tVBO to Array Buffer
	     glBindVertexArray(tVAO);
	     glBindBuffer(GL_ARRAY_BUFFER, tVBO);

	     //Copy vertex data to buffer memory
	     glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

	     //Update OpenGL vertex interpreter
	     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	     glEnableVertexAttribArray(0);

	     //Unbind 
	     glBindBuffer(GL_ARRAY_BUFFER, 0);
	     glBindVertexArray(0);






	      //Generate Vertex and Element Objects
	     GLuint VBO, VAO, EBO;
	      glGenVertexArrays(1, &VAO);
	      glGenBuffers(1, &VBO);
	      glGenBuffers(1, &EBO);

	      //Bind VAO to Array Buffer
	      glBindVertexArray(VAO);

	      //Bind VBO to Array Buffer
	      glBindBuffer(GL_ARRAY_BUFFER, VBO);

	      //Copy vertex data to buffer memory
	      glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);

	      //Bind EBO to Array Buffer
	      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectIndices), rectIndices, GL_STATIC_DRAW);
	      
	      //Update OpenGL vertex interpreter
	      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	      glEnableVertexAttribArray(0); 

	      //Unbind 
	      glBindBuffer(GL_ARRAY_BUFFER, 0);
	      glBindVertexArray(0);

	      // Uncommenting this call will result in wireframe polygons.
	       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
	      //RENDER THE GOD DAMN TRIANGLE
	      testShader.Use(); // glUseProgram(simpleShaderProgram);
	      glBindVertexArray(VAO);
	      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	      glBindVertexArray(0);

	      glBindVertexArray(tVAO);
	      glDrawArrays(GL_TRIANGLES, 0, 3);
	      glBindVertexArray(0);
	    

	      //Update screen
	      SDL_GL_SwapWindow( window );

	      //Wait four seconds
	      SDL_Delay( 4000 );

	      	glDeleteVertexArrays(1, &VAO);
		glDeleteVertexArrays(1, &tVAO);
		glDeleteBuffers(1, &tVBO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	    }
	}

	//Destroy window
	SDL_DestroyWindow( window );



	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
