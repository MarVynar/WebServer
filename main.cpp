#include "MyWebServer.h"

int main()
{
  WebServer server(9999);
  server.serve();
  return 0;
}