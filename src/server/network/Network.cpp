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
	if (!(sd = SDLNet_UDP_Open(3000)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
	/* Make space for the packet */
	if (!(p = SDLNet_AllocPacket(512)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

}

char* UDP_Network::getMessage()
{
	if (SDLNet_UDP_Recv(this->sd, this->p))
	{
		printf("UDP Packet incoming\n");
		printf("\tChan:    %d\n", this->p->channel);
		printf("\tData:    %s\n", (char *)this->p->data);
		printf("\tLen:     %d\n", this->p->len);
		printf("\tMaxlen:  %d\n", this->p->maxlen);
		printf("\tStatus:  %d\n", this->p->status);
		printf("\tAddress: %x %x\n", this->p->address.host, this->p->address.port);
	}

	return (char *)this->p->data;
}

void UDP_Network::broadcastGameState(int* gamestate)
{
	/* Send gamestate to all current clients */
}

void UDP_Network::Close()
{
	/* Clean and exit */
	SDLNet_FreePacket(p);
	SDLNet_Quit();
}