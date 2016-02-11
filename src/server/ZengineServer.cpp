 /*
   Include Files
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <SDL2/SDL_net.h>


/*
  Class Declaration
*/

class ZengineServer {
    private:
        bool    Running;
 
    public:
        ZengineServer();
 
        int Run();
 
    public:
 
        bool Initialize();
 
        //Get>Execute>Tell players' results
        void OnEvent(); 
 
        //Simulate world and broadcast to all players
        void Loop();
 
        //Note, no Render loop, rendering is handled by the client.

        void Exit();

    private:
        
        int sockfd, newsockfd, portno;
        socklen_t clilen;
        char buffer[256];
        struct sockaddr_in serv_addr, cli_addr;




        UDPsocket sd;       /* Socket descriptor */
        UDPpacket *p;       /* Pointer to packet memory */
        

};


/*
  Function Implementation
*/





bool ZengineServer::Initialize()
{
  // sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  // if(sockfd < 0 )
  //   perror("ERROR opening socket");
  // bzero((char *) &serv_addr, sizeof(serv_addr));
  // portno = 5050;
  // serv_addr.sin_family = AF_INET;
  // serv_addr.sin_addr.s_addr = INADDR_ANY;
  // serv_addr.sin_port= htons(portno);
  // if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  //   perror("ERROR on binding");
  // clilen= sizeof(struct sockaddr_in); 
    


  //UDP Connection stuff
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


  return true;
}

void ZengineServer::OnEvent()
{

  // bzero(buffer, 256);
  // if((recvfrom(sockfd, buffer, 255, 0,(struct sockaddr *)&cli_addr, &clilen)) < 0 )
  //   perror("ERROR reading from socket, recvfrom()");
  // printf("Here is the message: %s\n", buffer);
  // if(strcmp(buffer, "quit\n") == 0)
  //   Running = false;
  
}

void ZengineServer::Loop()
{
  // if((sendto(sockfd, "Message Received", 18, 0, (struct sockaddr *)&cli_addr, clilen)) < 0 ) //18 is the number of bits in message
  //   perror("ERROR writing to socket, sendto()");


// UDP stuff
  /* Wait a packet. UDP_Recv returns != 0 if a packet is coming */
    if (SDLNet_UDP_Recv(sd, p))
    {
      printf("UDP Packet incoming\n");
      printf("\tChan:    %d\n", p->channel);
      printf("\tData:    %s\n", (char *)p->data);
      printf("\tLen:     %d\n", p->len);
      printf("\tMaxlen:  %d\n", p->maxlen);
      printf("\tStatus:  %d\n", p->status);
      printf("\tAddress: %x %x\n", p->address.host, p->address.port);
 
      /* Quit if packet contains "quit" */
      if (strcmp((char *)p->data, "quit") == 0)
        Running = false;
    }


}

void ZengineServer::Exit()
{
  close(newsockfd);
  close(sockfd);


   /* Clean and exit */
  SDLNet_FreePacket(p);
  SDLNet_Quit();
}

ZengineServer::ZengineServer()
{
  Running = true;
}



int ZengineServer::Run()
{
  if(Initialize() == false)
    {
      return -1;
    }

  while(Running)
    {
      //while(true) //Infinite atm, need to loop through players vector
      //{
	  OnEvent();
      //}

      Loop();

    }

  Exit();
  
  return 0;
}

int main ( int argc, char* argv [] )
{
  ZengineServer TestServer;

  TestServer.Run();

  return 0;
}
