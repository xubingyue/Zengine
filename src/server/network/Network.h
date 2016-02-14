#include <SDL2/SDL_net.h>

class UDP_Network
{
	public:

		void Initialize();
		char* getMessage();
		void broadcastGameState(int* gameState);
		void Close();

	private:
        
        UDPsocket sd;       /* Socket descriptor */
        UDPpacket *p;       /* Pointer to packet memory */
};

