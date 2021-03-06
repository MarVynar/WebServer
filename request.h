#ifndef REQUEST_H_
#define REQUEST_H_

#include <string>
#include <map>

class Request{
  public:
    enum Method { Get , Post};
    Method method;
    int cl_socket;
    std::string version;
    std::string path;
    std::string body;
    std::map<std::string, std::string> headers;
    Request(const std::string &request, int sock);  
};

#endif