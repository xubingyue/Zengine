#include <SDL2/SDL_net.h>

class UDP_Connection
{
	public:

		bool Initialize();
		char* getMessage();
		bool Exit();

	private:
        
        UDPsocket sd;       /* Socket descriptor */
        UDPpacket *p;       /* Pointer to packet memory */
};