


#include <godathan.h>
#include <string>
#include <fstream>




int main(){
    
    std::string APITOKEN;
    std::ifstream tokenFile;
    
    tokenFile.open("../APITOKEN");
    if(!tokenFile.is_open()){
        std::cout << "Could not open the APITOKEN file. Please make sure that the APITOKEN file is in" << std::endl;
        return 1;
    }
    else{
        std::getline(tokenFile, APITOKEN);
        tokenFile.close();
        Godathan godathan(APITOKEN, 2);
        godathan.run();
        return 0;
    }
}
