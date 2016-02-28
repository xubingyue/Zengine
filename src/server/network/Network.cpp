#include <Network.h>


void UDP_Network::Initialize()
{
	/* Initialize SDL_net */
	if (SDLNet_Init() < 0)
	{
    	fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
    	exit(EXIT_FAILURE);
	}
 
	/* Open a socket */
	if (!(socket = SDLNet_UDP_Open(3000)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
	/* Make space for the packet */
	if (!(packet = SDLNet_AllocPacket(512)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

}

char* UDP_Network::getMessage() 
{
	if (SDLNet_UDP_Recv(this->socket, this->packet))
	{
		printf("UDP Packet incoming\n");
		printf("\tChan:    %d\n", this->packet->channel);
		printf("\tData:    %s\n", (char *)this->packet->data);
		printf("\tLen:     %d\n", this->packet->len);
		printf("\tMaxlen:  %d\n", this->packet->maxlen);
		printf("\tStatus:  %d\n", this->packet->status);
		printf("\tAddress: %x %x\n", this->packet->address.host, this->packet->address.port);
	}

	return (char *)this->packet->data;
}

void UDP_Network::broadcastGameState(int* gamestate)
{
	/* Send gamestate to all current clients */
}

void UDP_Network::Close()
{
	/* Clean and exit */
	SDLNet_FreePacket(packet);
	SDLNet_Quit();
}