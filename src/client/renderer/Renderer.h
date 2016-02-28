#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <Shader.h>

class Renderer
{
	public:

		bool Initialize(SDL_Window* SDLwindow);

		void Render();

		void Close();

	private:

		SDL_GLContext sdlGlContext;

		GLenum error;
};