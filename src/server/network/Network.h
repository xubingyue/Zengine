#pragma once
#include <SDL2/SDL_net.h>
#include <string>

class UDP_Network
{
	public:

		void Initialize();
		std::string getMessage();
		void broadcastGameState(int* gameState);
		void Close();

	private:
        
        UDPsocket socket;       /* Socket descriptor */
        UDPpacket *packet;      /* Pointer to packet memory */
        std::string message;
};

