#include "request.h"
#include <iostream>
#include <sstream>

//#include <vector>
//#include "handler.h"


using namespace std; 
Request::Request(const std::string &request){
 
  int i=0;
  int pos = request.find("\n");
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
  path = request.substr(space_pos+1, space_pos2-space_pos-1);
  std::cout<<" Path: "<<path<<std::endl;
  
   int end_pos = request.find("\n");
  version =  request.substr(space_pos2, end_pos-space_pos2);
   std::cout<<" Version: "<< version << std::endl;
  
  
   std::string line;
   std::string tmp, tmp1;

 std::string headers_str = request.substr(pos );
  std::istringstream hstream(headers_str);
  while (std::getline(hstream, line)){
    
 //  std :: cout << line <<endl;
    int pos_strt = line.find(":");
    int pos_end = line.find("\n");
    
    tmp1 = line.substr(0, pos_strt);
    tmp= line.substr(pos_strt+1, pos_end-1-pos_strt);
    
   // cout << "Tmp1 = " << tmp1 << endl;
    //cout << "Tmp = " << tmp << endl;
    
    headers.insert ( pair <std::string, std::string> ( tmp1, tmp));
        
  }
  int endln = line.rfind("\0");
  int nln= line.rfind("\n");

  body = line.substr(nln+1, endln-1-nln);
  cout << "body = " << body <<"\n";

  

  
}