#include "handler.h"
#include <fstream>
#include <iostream>

Handler::Handler (std::string root_dir_in): root_dir(root_dir_in) {
  
}
Response Handler::processRequest(const Request &req){
  if (req.method == Request::Method::Get){
    return doGet(req);
  }
}
Response Handler::doGet(const Request &req){
  
  std::cout << "Opening file: '" << root_dir+req.path << "'\n";
  std::ifstream ifile (root_dir+req.path);
  if(ifile.good()){
    return Response(200, "dsfdsgfdgfdgdfgbsfdkgsdkgsdkfjgk"); 
  }else{
   return Response(404, "Not Found"); 
  }
}