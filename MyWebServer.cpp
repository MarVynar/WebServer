#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <thread>

//#include <conio.h>

#define PORT 9999
#define MAXCONNECTS 100

using namespace std;

//#include "MyServer.h"
//////////////////////Replier
class Replier{
  int dest_socket;
  char* message;
 public: Replier(){}
  Replier(int ds): dest_socket(ds){cout<<"Destination "<<dest_socket<<endl;}
  ~Replier (){}
  
  void sendReply(string msg);
  
};


void Replier::sendReply(string msg){
   strcpy(message,msg.c_str());
    send(dest_socket, message, strlen(message), MSG_PEEK);
  
}

////////////////////////////REQUESTS////////
class Request{
 protected:
  char request_mes[7000];
  string replytext;
  Replier* rep;
  string request_info[20];
  
  public:
  Request(){}
  ~Request(){}
 
 virtual void doRequest(char[])=0; 
};

/////////----------GetRequest
class GetRequest : public Request{
  
  ifstream rfile;
  string ftxt;

  public:
  void doRequest(char rt[]);
  
  GetRequest(): Request (){}
  GetRequest(char c[7000], Replier r) 
    { rep=&r; doRequest(c);}
 ~ GetRequest() {}
  
  
};


void GetRequest::doRequest(char rt[]){
 //request_mes=rt;
  int k=0;
  for (int i=0; i<14; i++){
    while(rt[k]!='\n'){
      request_info[i]+=rt[k++];
      
      
    }  
    k++; /////Segmentation Fault
    cout<<"I"<<i<<" "<<request_info[i]<<endl;
  }
  
  

  string fileaddr;
  k=0;
  while( request_info[0][k]!='/') {k++;}
  k++;
  while( request_info[0][k]!=' ') { fileaddr+=request_info[0][k]; k++;}

  char* cfileaddr;
  strcpy(cfileaddr, fileaddr.c_str());
  cout<<"Address is "<<cfileaddr<<"ENDADDRESS"<<endl;
  rfile.open(  cfileaddr , ios::in);
 
  if(rfile){
  char temp;
  while(rfile){
    rfile.get(temp);
    ftxt+=temp;   
   }
    cout <<ftxt<<endl;
    replytext= "<HTML> <HEAD><TITLE>"+fileaddr+"</TITLE></HEAD><BODY>"+ftxt+"</BODY></HTML>";
  //  Replier newrep;
//    newrep.sendReply(replytext);
  //  rep->sendReply(replytext);
} //if
  else{ replytext= "Sorry, buddy, there is no such file " + fileaddr;
       cout<<replytext<<endl;
  //     rep->sendReply(replytext);
      }// else
}


//----------------PostRequest


class PostRequest : public Request{
  //char reqtext[6000];
  string reqtext;
  ofstream rfile;
  public:
  void doRequest(char rt[]);
   PostRequest(): Request (){}
    PostRequest(char c[7000], Replier r) 
  //  : Request(char c[])
    {rep= &r; doRequest(c);}
 ~ PostRequest(){}
   
};

void PostRequest::doRequest(char rt[]){
 //request_mes=rt;
  int k=0;
  for (int i=0; i<19; i++){
    while((rt[k]!='\n')&&(rt)){
      request_info[i]+=rt[k++];
      
      
    }  
    k++; /////Segmentation Fault
    cout<<"I"<<i<<" "<<request_info[i]<<endl;
  }
  
  reqtext=request_info[18];

  string fileaddr;

  
  k=0;
  while( request_info[0][k]!='/') {k++;}
  k++;
  while( request_info[0][k]!=' ') { fileaddr+=request_info[0][k]; k++;}

  char* cfileaddr;
  strcpy(cfileaddr, fileaddr.c_str());
  cout<<"Address is "<<cfileaddr<<"ENDADDRESS"<<endl;
  cout<<"Opening file"<<endl;
  rfile.open(  cfileaddr , ios::out);
 
 
  if(rfile){
  char* temp;
    strcpy(temp, reqtext.c_str());
   // rfile.put(temp);
    rfile.write(temp,sizeof(temp));

    cout<<"File Rewritten "<<temp<<endl;
        replytext= "<HTML> <HEAD><TITLE>"+fileaddr+"</TITLE></HEAD><BODY>File rewritten</BODY></HTML>";
    rep->sendReply(replytext);
} //if
  else{ replytext= "Sorry, buddy, there is no such file " + fileaddr;
       cout<<replytext<<endl;
       rep->sendReply(replytext);
      }// else
}

////////////////////////////HANDLER////////////////////////

class Handler
{
  
  char req[4];
  public:
  Handler() {}
  ~Handler(){}
  void checkRequest(char[], Replier repl);
  
};


void Handler::checkRequest(char r[], Replier repl){
  req[0]=r[0];
  req[1]=r[1];
  req[2]=r[2];
  req[3]=r[3];
  cout<<req<<endl;
  
  //if (req=="GET\n")
  if ((req[0]=='G')&&(req[1]=='E')&&(req[2]=='T'))
  { cout<<"Getting"<<endl; GetRequest get_request(r,repl);}
  
  
 // else if (req=="POST")
  else if ((req[0]=='P')&&((req[1]='O'))&&((req[2]=='S'))&&((req[3]=='T')))
  { cout<<"Posting"<<endl; PostRequest post_request(r,repl);}
  
  else cout << "Unknown request, we are too young for this..."<<endl;
  
}

////////////////SERVER////////////////////////
class MyServer
{

  char buff[1024];
  char exit='a';
  char mes[7000];
 // vector<Handler> handler;
  Handler handler;
  
  
  int mysocket;
  sockaddr_in local_addr;
    
    
  
  
  int client_socket;
  sockaddr_in client_addr;
   int client_addr_size ;
 
  int number_of_connections, number_of_connectionsnew;
  thread Thread[MAXCONNECTS];
  public:
  MyServer(){
    mysocket = socket(AF_INET,SOCK_STREAM,0);
    
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = INADDR_ANY;
    local_addr.sin_port = htons(PORT);
  
   client_addr_size = sizeof(client_addr);
    number_of_connections=0;
    number_of_connectionsnew=1;
  }
  ~MyServer() {}
  
  void serverInit();
  void serverRun();
 bool serverCheck();
 
    
};

bool MyServer::serverCheck(){
  // if(number_of_connections!=number_of_connectionsnew){
  return (number_of_connections!=number_of_connectionsnew);
   number_of_connections=number_of_connectionsnew;
   Thread[number_of_connections]=thread(serverCheck());
  serverRun();
  Thread[number_of_connections].join();
  
}

void MyServer::serverInit(){
   cout<<"Server Start"<<endl;      
   cout<<"Server Socket "<<mysocket<<endl;
   cout<<"Binding"<<bind(mysocket, (sockaddr *) &local_addr, sizeof(local_addr))<<endl;
//thread Thread[MAXCONNECTS];
 // int number_of_connections=0;
  
  while(exit!='e'){
    Thread[number_of_connections]=thread(serverCheck());
  Thread[number_of_connections].join();
 }
    
  }
  
     }

void MyServer::serverRun(){
 //if (number_of_connections!=number_of_connectionsnew){ number_of_connections=number_of_connectionsnew;
 
  
    cout<<"Listening"<<listen(mysocket,MAXCONNECTS)<<endl;
    cout<<"local_addr =  "<<local_addr.sin_addr.s_addr/* IP */<<", Port "<<ntohs(local_addr.sin_port)<<" "<<endl;
    cout<<"Waiting for connects..."<<endl;

  

  if (client_socket = accept(mysocket, NULL, NULL))
        cout<<"ACCEPT TO CONNECT"<<endl;

    else
        cout<<"NOT ACCEPT TO CONNECT"<<endl;
        

   number_of_connectionsnew++;
  recv(client_socket, (char*)mes, sizeof(mes), MSG_PEEK);
    cout<<"Message received: "<<mes<<endl;
  
  //  close(client_socket);
    //close(mysocket);
//  cout<<"Client "<<client_socket<<endl;
  Replier replier(client_socket);
 handler.checkRequest(mes, replier);
  
  //  cin>>exit;
 // }
  
  
  
}



/////////////////////////////////////////////////////////////



int main()
{

   MyServer my_server;
  my_server.serverInit();
 // my_server.serverRun();

    return 0;
}