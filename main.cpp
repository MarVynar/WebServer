#include "MyWebServer.h"
#include "handler.h"

int main()
{
  Handler handler(".");

  
 WebServer server(9999, handler);
 server.serve();
  return 0;
}