  #include <SDL2/SDL_net.h>

class UDP_ServerConnection
{
	public:

		void Initialize();
		void sendMessage(char *message);
		void getGameState();
		void Close();

	private:
        
        UDPsocket sd;       /* Socket descriptor */
        UDPpacket *p;       /* Pointer to packet memory */
        IPaddress srvadd;
};