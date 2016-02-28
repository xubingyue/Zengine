#include <SDL2/SDL.h>

class Window 
{
	public:
		bool Initialize();

		char* handleEvents();

		void updateScreen();

		SDL_Window* getWindow();

		char* getMessage();

		void Close();

	private:
		SDL_Window* window;
		SDL_Event* Event;

        char message[256];
        char buffer[256];
        char *composition;
        Sint32 cursor;
        Sint32 selection_len;
        int SCREEN_WIDTH;// = 640;
		int SCREEN_HEIGHT;// = 480;
};