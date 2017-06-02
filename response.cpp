#include <sstream>
#include "response.h"

Response:: Response(unsigned int status_in, std::string body_in): body(body_in) {
 if (possible_statuses.count(status_in)){
   status.first = status_in;
   status.second = possible_statuses[status_in];
 }
  
}

std::string Response::toString() {
  std::stringstream response;
  response << version << " ";
  response << status.first << " " << status.second << "\n";
  for(std::map <std::string, std::string>::iterator it = headers.begin(); it != headers.end(); ++it){
    response << (*it).first << ": " << (*it).second << "\n";
  }
  response << "\n";
  response << body;
  return response.str();
}
