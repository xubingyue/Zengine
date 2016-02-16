  #include <SDL2/SDL_net.h>

class UDP_ServerConnection
{
	public:

		bool Initialize();
		void sendMessage(char *message);
		void getGameState();
		void Close();

	private:
        
        UDPsocket socket;        		 /* Socket descriptor */
        UDPpacket *packet;      		 /* Pointer to packet memory */
        IPaddress serverAddress;		 /* Address of server */
};