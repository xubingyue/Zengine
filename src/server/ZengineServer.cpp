 /*
   Include Files
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>



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
        

};


/*
  Function Implementation
*/
bool ZengineServer::Initialize()
{
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd < 0 )
    perror("ERROR opening socket");
  bzero((char *) &serv_addr, sizeof(serv_addr));
  portno = 5050;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port= htons(portno);
  if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    perror("ERROR on binding");
  clilen= sizeof(struct sockaddr_in); 
    

  return true;
}

void ZengineServer::OnEvent()
{

  bzero(buffer, 256);
  if((recvfrom(sockfd, buffer, 255, 0,(struct sockaddr *)&cli_addr, &clilen)) < 0 )
    perror("ERROR reading from socket, recvfrom()");
  printf("Here is the message: %s\n", buffer);
  if(strcmp(buffer, "quit\n") == 0)
    Running = false;
  
}

void ZengineServer::Loop()
{
  if((sendto(sockfd, "Message Received", 18, 0, (struct sockaddr *)&cli_addr, clilen)) < 0 ) //18 is the number of bits in message
    perror("ERROR writing to socket, sendto()");
}

void ZengineServer::Exit()
{
  close(newsockfd);
  close(sockfd);
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
