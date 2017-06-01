#include "handler.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

Handler::Handler(Method m , std::string p, int ds) : method(m), path(p) , dest_socket(ds) {
   if (method==Get) {doGet();} 
   else if (method==Post) { cout<< "doPosting" <<endl; doPost();} 
  }

void Handler::doGet(){
  ifstream rfile;
  std::string ftxt;
  std::string replytext;
   char* cpath;
  
  strcpy(cpath, path.c_str());
 std:: cout<< "Getting! \n Address is " << cpath <<endl;
  rfile.open(  cpath , ios::in);
 
  if(rfile){
  char temp;
  while(rfile){
    rfile.get(temp);
    ftxt+=temp;   
   }
   std:: cout << ftxt <<endl;
  //  replytext = "<HTML> <HEAD><TITLE>"+path+"</TITLE></HEAD><BODY>"+ftxt+"</BODY></HTML>";
    replytext= "Bo";
    //replytext = "<HTML> <HEAD><TITLE>"+path+"</TITLE></HEAD><BODY> Yo , man </BODY></HTML>";
  //char* msg;
 //   msg="Bo";
      // strcpy(msg, replytext.c_str());
    //cout<< "StrCpied\n";
      // send(dest_socket, msg, sizeof(msg), MSG_PEEK);
} //if
  else{ replytext= "Sorry, buddy, there is no such file " + path;
     std:: cout << replytext << endl;
      // char* msg;
    //   strcpy(msg, replytext.c_str());
     //  send(dest_socket, msg, strlen(msg), MSG_PEEK);
 
      }// else
  
  
}

void Handler::doPost(){
   cout<< "Creating Variables" <<endl;
  string reqtext;
  ofstream wfile;
  std::string replytext;
  cout<< "Variables Created" <<endl;
  // char* cpath;
  const char* cpath= path.c_str();
  cout << " Cpath created" <<endl;
//  strcpy(cpath, path.c_str());
  cout <<"Cpath : " << cpath <<endl;
  cout << "Posting! \n Address is " << cpath <<endl;
 // char* temppath=cpath;
  cout<<"Opening file"<<endl;
  //wfile.open(  cpath , ios::out);
 // wfile.open(  cpath );
  wfile.open(  path.c_str() );
//  wfile.open(  temppath , ios::out);
  
 reqtext= "Test test test";
  if(wfile){
  char* temp;
    strcpy(temp, reqtext.c_str());
   // rfile.put(temp);
    wfile.write(temp,sizeof(temp));

    cout<<"File Rewritten "<<temp<<endl;
        replytext= "<HTML> <HEAD><TITLE>" +path+ "</TITLE></HEAD><BODY>File rewritten</BODY></HTML>" ;
   // char* msg;
    //   strcpy(msg, replytext.c_str());
     //  send(dest_socket, msg, sizeof(msg), MSG_PEEK);
} //if
  else{ replytext= "Sorry, buddy, there is no such file " + path;
       cout << replytext << endl;
       // char* msg;
    //   strcpy(msg, replytext.c_str());
     //  send(dest_socket, msg, sizeof(msg), MSG_PEEK);
      }// else
  
  
}
