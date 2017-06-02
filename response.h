#ifndef RESPONSE_H_
#define RESPONSE_H_

#include <string>
#include <utility>
#include <map>


class Response{

  
  public:
    typedef std::pair <unsigned int, std::string> Status;
    Response(unsigned int status_in, std::string body_in);
    std::string toString();
  
  private:
    const std::string version = "HTTP/1.1 ";
    std::map <std::string, std::string> headers = {{"Connection","close"}};
    std::string body;
    Status status;
    std::map <unsigned int, std::string> possible_statuses = {{200, "OK"}, {404, "Not Found"} , {503, "Internal Server Error"}}; 
};




#endif