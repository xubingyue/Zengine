#include <SDL2/SDL_net.h>

class UDP_Network
{
	public:

		void Initialize();
		char* getMessage();
		void broadcastGameState(int* gameState);
		void Close();

	private:
        
        UDPsocket socket;       /* Socket descriptor */
        UDPpacket *packet;      /* Pointer to packet memory */
};

