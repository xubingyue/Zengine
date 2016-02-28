#include <SDL2/SDL.h>
#include <string>
#include <vector>

using namespace std;

class Window
{
	public:

		bool Initialize();
		void handleEvents();
		void updateWindow();
		void Close();

		vector<string> getMessageList();
		SDL_Window* getWindow();
		void clearMessageList();

	private:
		SDL_Window* sdlWindow;
		SDL_Event sdlEvent;

		vector<string> messageList;
		string message;

		//Screen dimension constants
		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;

        char *composition;
        Sint32 cursor;
        Sint32 selection_len;
};