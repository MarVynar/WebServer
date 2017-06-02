#ifndef MYWEBSERVER_H_
#define MYWEBSERVER_H_

class WebServer {
  public:
    WebServer(int port);
    void serve();

  private:
    void serveClient(int client_socket);
    int server_socket;
};

#endif // MYWEBSERVER_H_