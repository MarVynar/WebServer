#include "request.h"
#include <iostream>
#include <sstream>
//#include "handler.h"


using namespace std; 
Request::Request(const std::string &request , int sock){
  cl_socket=sock;
  int i=0;
 //while ((request[i]!= '\n')||(request[i]!= '\0'))
  int pos = request.find("\n");
 // std::string first_line = request.substr(0, pos);
  int space_pos = request.find(" ");
  std::string temp = request.substr(0, space_pos);
  if(temp == "GET"){
    cout<< temp <<endl;
    method = Method::Get;
  }else if (temp == "POST"){
    method = Method::Post;
    cout<< temp <<endl;
  } else {std::cerr << "Unknow Method:" << method << "Temp" << temp << std::endl; }
  
  int space_pos2= request.find(" ", (space_pos+1) );
  path = request.substr(space_pos+2, space_pos2-space_pos-2);
  std::cout<<" Path: "<<path<<std::endl;
  
   int end_pos = request.find("\n");
  version =  request.substr(space_pos2, end_pos-space_pos2);
   std::cout<<" Version: "<< version << std::endl;
  
  /*
  std::string line;
 std::string headers_str = request.substr(pos);
  std::istringstream hstream(headers_str);
  while (std::getline(hstream, line)){
    int pos = line.find(":");
    headers[line.substr(0, pos)] = line.substr(pos);
  }*/

  
  Handler handler (method , path, cl_socket );
  
}