#include <SDL2/SDL_net.h>

class UDP_Connection
{
	public:

		void Initialize();
		char* getMessages();
		void handleMessages();
		void Close();

	private:
        
        UDPsocket sd;       /* Socket descriptor */
        UDPpacket *p;       /* Pointer to packet memory */
};

void UDP_Connection::Initialize()
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

char* UDP_Connection::getMessages()
{
	 //Wait a packet. UDP_Recv returns != 0 if a packet is coming 
    if (SDLNet_UDP_Recv(this->sd, this->p))
    {
      printf("UDP Packet incoming\n");
      printf("\tChan:    %d\n", this->p->channel);
      printf("\tData:    %s\n", (char *)this->p->data);
      printf("\tLen:     %d\n", this->p->len);
      printf("\tMaxlen:  %d\n", this->p->maxlen);
      printf("\tStatus:  %d\n", this->p->status);
      printf("\tAddress: %x %x\n", this->p->address.host, this->p->address.port);
      //superPrint();
  	}

      return (char *)this->p->data;
}

void UDP_Connection::Close()
{
	/* Clean and exit */
  SDLNet_FreePacket(p);
  SDLNet_Quit();
}