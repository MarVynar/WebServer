#ifndef HANDLER__H_
#define HANDLER__H_

#include "request.h"
#include "response.h"

#include <string>
class Handler{
  std::string root_dir;
  
  public : 
    Handler (std::string root_dir_in);
  Response processRequest(const Request &req);

  
  Response doGet(const Request &req);
  //Response doPost(Request req);
  
};

#endif