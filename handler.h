#ifndef HANDLER_H_
#define HANDLER_H_

#include <string>

enum Method { Get , Post};

class Handler{
//  enum Method { Get , Post}; //може в глобальні?
  Method method;
  std::string path;
  int dest_socket;
  
   void doGet();
  void doPost();
  public:
  Handler(Method m , std::string p, int ds) ;
  
 
  
};
#endif