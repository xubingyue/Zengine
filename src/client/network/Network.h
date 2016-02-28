#include <SDL2/SDL_net.h>

#include <string>

using namespace std;

class UDP_ServerConnection
{
	public:

		bool Initialize();
		void sendMessage(string message);
		void getGameState();
		void Close();

	private:
        
        UDPsocket socket;        		 /* Socket descriptor */
        UDPpacket *packet;      		 /* Pointer to packet memory */
        IPaddress serverAddress;		 /* Address of server */
        
};