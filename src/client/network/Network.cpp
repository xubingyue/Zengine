 #include <Network.h>

bool UDP_ServerConnection::Initialize()
{
	/* Initialize SDL_net */
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
    	return false;
	}
 
	/* Open a socket on random port */
	if (!(socket = SDLNet_UDP_Open(0)))
	{
    	fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
    	return false;
	}

	int port = 3000;
	/* Resolve server name  */
	if (SDLNet_ResolveHost(&serverAddress, "localhost", port) == -1)
	{
    	fprintf(stderr, "SDLNet_ResolveHost(%s %d): %s\n", "localhost", port, SDLNet_GetError());
    	return false;
	}
 
	/* Allocate memory for the packet */
	if (!(packet = SDLNet_AllocPacket(512)))
	{
    	fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
    	return false;
	}

	return true;
}

void UDP_ServerConnection::sendMessage(char* message)
{
	/* Add message to packet */
	strcpy((char *)packet->data, message);

	/* Set the destination host and destination port */
	packet->address.host = serverAddress.host;  
    packet->address.port = serverAddress.port; 
 
 	/* set message length, plus 1 for newline char */
    packet->len = strlen((char *)packet->data) + 1;

    /* Set packet->channel */
    SDLNet_UDP_Send(socket, -1, packet); 

}

void UDP_ServerConnection::getGameState()
{

}

void UDP_ServerConnection::Close()
{
	/* Free resources */
	SDLNet_FreePacket(packet);
    SDLNet_Quit();
}