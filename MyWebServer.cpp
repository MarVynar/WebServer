#include "MyWebServer.h"

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

using namespace std;

WebServer::WebServer(int port){
  server_socket = socket(AF_INET,SOCK_STREAM, 0);

  sockaddr_in local_addr;
  local_addr.sin_family = AF_INET;
  local_addr.sin_addr.s_addr = INADDR_ANY;
  local_addr.sin_port = htons(port);

  //sockaddr_in client_addr;
  //int client_addr_size  = sizeof(client_addr);
  cout << "Binding: " << bind(server_socket, (sockaddr *) &local_addr, sizeof(local_addr)) << endl;
}

void WebServer::serve(){
  cout << "Listening: " << listen(server_socket, 100) << endl;
  while(true){
    int client_socket = accept(server_socket, NULL, NULL);
    if (!client_socket){
      std::cout << "Accept error:\n";
      continue;
    }
  }
}






