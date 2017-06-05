#include "request.h"
#include <iostream>
#include <sstream>

//#include <vector>
//#include "handler.h"


using namespace std; 
Request::Request(const std::string &request){
 
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
  path = request.substr(space_pos+1, space_pos2-space_pos-1);
  std::cout<<" Path: "<<path<<std::endl;
  
   int end_pos = request.find("\n");
  version =  request.substr(space_pos2, end_pos-space_pos2);
   std::cout<<" Version: "<< version << std::endl;
  
  
   std::string line;
  std::string tmp;

 std::string headers_str = request.substr(pos );
  std::istringstream hstream(headers_str);
  while (std::getline(hstream, line)){
   std :: cout << line <<endl;
    int pos_strt = line.find(":");
    int pos_end = line.find("\n");
   // tmp= line.substr(pos_strt, pos_end-pos_strt);
   // tmp= line.substr(pos_strt, 2);
   // cout << tmp << endl;
  }
 /*
  std::string line;
 std::string headers_str = request.substr(pos);
  std::istringstream hstream(headers_str);
  while (std::getline(hstream, line)){
    int pos = line.find(":");
    headers[line.substr(0, pos)] = line.substr(pos);
    std::cout << headers[line.substr(0, pos)] << "\n";
  } */
 /* std::string request_info;
    int k=0;
  for (int i=0; i<14; i++){
    while(request[k]!='\n'){
      request_info[i]+=request[k++];  
      
    }  
    k++; /////Segmentation Fault
    cout<<"I"<<i<<" "<<request_info[i]<<endl;
  }*/
  
/*  while (!request.eof()){
    int k=0;
    while(request[k]!='\n'){
      std::cout << request[k] <<"\n"; 
    }
     }*/
/*  std::string request_info;
  int req_pos= request.find( "\n\n");
//  int req_pos =end_pos;
 cout << request[req_pos] <<  request[req_pos+1] <<  request[req_pos+2]<<  request[req_pos+3] << endl;
  
  req_pos= request.rfind( "\n\n");
//  int req_pos =end_pos;
 cout << request[req_pos] <<  request[req_pos+1] <<  request[req_pos+2]<<  request[req_pos+3] << endl;
  
   req_pos= request.find( "\n \n");
//  int req_pos =end_pos;
 cout << request[req_pos] <<  request[req_pos+1] <<  request[req_pos+2]<<  request[req_pos+3] << endl;
  
  req_pos= request.rfind( "\n \n");
//  int req_pos =end_pos;
 cout << request[req_pos] <<  request[req_pos+1] <<  request[req_pos+2]<<  request[req_pos+3] << endl;
  */
/* 
std::string request_info;
  int req_pos= request.find( "\n\n");
//  int req_pos =end_pos;
// int req_pos =0;
  int req_end_pos = request.find("\n");
  //request_info= request.substr(req_pos, req_end_pos);
 // request_info= request.substr(req_pos, req_end_pos-req_pos);
 // request_info= request.substr(req_pos, 3);
  request_info=request[req_pos+1];
   request_info+= request[req_pos+2];
  request_info+= request[req_pos+3];
  request_info+= request[req_pos+4];
  cout << "Req Info =" << request_info << "\n";*/
  
 /* std::string request_info[20];
//  vector <string> request_info;
  
  int k=0;
  for (int i=0; i<20 ; i++){
    while( (request[k]!='\n') || ((request[k]!='\n')&&(request[k+1]!='\n')) ){
      request_info[i]+=request[k++];  
      
    } k++; /* request_info[i]+= "end"; x// request_info[i]+= "\0"; std::cout << "I "<<i << " = " << request_info [i] << "\n"; } */
  
}