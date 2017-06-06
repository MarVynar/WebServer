#include "handler.h"
#include <fstream>
#include <iostream>


Handler::Handler (std::string root_dir_in): root_dir(root_dir_in) {
  
}
Response Handler::processRequest(const Request &req){
  if (req.method == Request::Method::Get){
    return doGet(req);
  }
  else if (req.method == Request::Method::Post){
    return doPost(req);
  }
  else std::cout<<"Unknown request, we are too young for this\n"; 
}
Response Handler::doGet(const Request &req){
  
  std::cout << "Opening file: '" << root_dir+req.path << "'\n";
  std::ifstream ifile (root_dir+req.path);
  if(ifile.good()){
    std::string file_body;
    std::string temp;
   // ifile.read(file_body, sizeof(file_body));
    while(ifile) {ifile>>temp; file_body+=temp;}
    return Response(200, file_body); 
  }else{
   return Response(404, "Not Found"); 
  }
}

Response Handler::doPost(const Request &req){
  
  std::cout << "Opening file: '" << root_dir+req.path << "'\n";
  std::ofstream ofile (root_dir+req.path);
  if(ofile.good()){
    
    ofile << req.body;    
    return Response(200, "File is written"); 
    
  }else{
   return Response(404, "Not Found"); 
  }
}