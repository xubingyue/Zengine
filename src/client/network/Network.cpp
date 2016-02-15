 #include <Network.h>

void UDP_ServerConnection::Initialize()
{
	/* Initialize SDL_net */
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
    	exit(EXIT_FAILURE);
	}
 
	/* Open a socket on random port */
	if (!(sd = SDLNet_UDP_Open(0)))
	{
    	fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
    	exit(EXIT_FAILURE);
	}
	int port = 3000;
	/* Resolve server name  */
	if (SDLNet_ResolveHost(&srvadd, "localhost", port) == -1)
	{
    	fprintf(stderr, "SDLNet_ResolveHost(%s %d): %s\n", "localhost", port, SDLNet_GetError());
    	exit(EXIT_FAILURE);
	}
 
	/* Allocate memory for the packet */
	if (!(p = SDLNet_AllocPacket(512)))
	{
    	fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
    	exit(EXIT_FAILURE);
	}

}

void UDP_ServerConnection::sendMessage(char* message)
{
	strcpy((char *)p->data, message); /* Add message to packet */
	p->address.host = srvadd.host;  /* Set the destination host */
    p->address.port = srvadd.port;  /* And destination port */
 
    p->len = strlen((char *)p->data) + 1;
    SDLNet_UDP_Send(sd, -1, p); /* This sets the p->channel */
}

void UDP_ServerConnection::getGameState()
{

}

void UDP_ServerConnection::Close()
{
	SDLNet_FreePacket(p);
    SDLNet_Quit();
}