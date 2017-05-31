#include "MyWebServer.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <thread>

using namespace std;

WebServer::WebServer(int port){
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in local_addr;
  local_addr.sin_family = AF_INET;
  local_addr.sin_addr.s_addr = INADDR_ANY;
  local_addr.sin_port = htons(port);

  //sockaddr_in client_addr;
  //int client_addr_size  = sizeof(client_addr);
  cout << "Binding: " << bind(server_socket, (sockaddr *) &local_addr, sizeof(local_addr)) << endl;
}

void WebServer::serveClient(int client_socket){
  std::string request;
  char buffer[256];
  timeval tv;
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  fd_set rfds;
  FD_ZERO(&rfds);
  FD_SET(client_socket, &rfds);

  while(select(client_socket+1, &rfds, NULL, NULL, &tv ) > 0 ) {
    int recieved  = recv(client_socket, (char*)buffer, 255, 0 );
    if(recieved <= 0){
      std::cout << "Recieving error \n";
      break;
    }
    buffer[recieved] = '\0';
    std::cout << " size: " << recieved << "\n";
    request += buffer;
  }
}

void WebServer::serve(){
  cout << "Listening: " << listen(server_socket, 100) << endl;
  while(true){
    int client_socket = accept(server_socket, NULL, NULL);
    if (!client_socket){
      std::cout << "Accept error:\n";
      continue;
    }
    std::cout << "New client\n";
    serveClient(client_socket);
  }
}






