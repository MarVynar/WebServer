#ifndef MYWEBSERVER_H_
#define MYWEBSERVER_H_
#include "handler.h"

class WebServer {
  public:
    WebServer(int port, const Handler &handler_in);
    void serve();

  private:
    void serveClient(int client_socket);
    int server_socket;
    Handler handler;
};

#endif // MYWEBSERVER_H_