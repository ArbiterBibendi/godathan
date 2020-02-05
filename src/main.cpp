#include <iostream>
#include <string>
#include <vector>

#include <unistd.h>
#include <signal.h>
#include <websocketpp_websocket.h>
#include <sys/wait.h>
#include <dirent.h>
#include <stdio.h>




class Godathan : public SleepyDiscord::DiscordClient{
    using SleepyDiscord::DiscordClient::DiscordClient;
    
    std::string replace_string(std::string string, std::string substr1, std::string substr2){ //Replace string with another string
        std::string newStr = string;
        
        int pos = string.find(substr1, 0);
        newStr.replace(pos, substr1.length(), substr2);
        
        return newStr;
    }
    std::vector<std::string> arguments(std::string s){ //Places command line arguments into vector
        std::vector<std::string> args;
        std::string sub;
        int i = 0;
        int li = 0;
        
        while(i != std::string::npos){ //
            i = s.find(" ", li);
            sub = s.substr(li, i-li);
            li = i+1;
            args.push_back(sub);
        }
        
        return args;
    }

    static void handle_child(int){
        wait(NULL);
    }
    void onMessage(SleepyDiscord::Message message) override{
        std::cout << "Message Recieved!" << std::endl;
        if(message.author.ID != 456655185901518848){ //If message isn't by godathan
            
            //Send Command: -send ChannelID Message
            if(message.startsWith("-send ")){
                try{
                    std::string args = replace_string(message.content, "-send ", "");
                    
                    //Use a space to separate the channelID from the message to send
                    int channelIDLen = args.find(" ", 0);
                    std::string channelID = args.substr(0, channelIDLen);
                    std::string messageToSend = replace_string(args, channelID + " ", "");
                    
                    sendMessage(channelID, messageToSend);
                }catch(...){}
            }
            
            if(message.startsWith("-yt"))
            {
                
                std::string args = replace_string(message.content, "-yt ", "");
                if (args.find("mp3 ") == 0){
                    args.erase(0,4);
                    args += " -x --audio-format mp3";
                }
                else{
                    args += " -f mp4";
                }
                std::vector<std::string> argslist = arguments(args);
                //Places arguments into a vector buffer and transfers them into an array
                //If mp3 option is specified then pass mp3 audio arguments to youtube-dl, otherwise 
                //specify mp4 as format
                
                
                
                
                
                int argsSize = argslist.size();
                const char* argv1[argsSize+2]; //extra space added for program name and sentinel
                
             
                //Covert arguments vector into a char * array to pass to execv
                for (int i = 0; i < argsSize; i++){ 
                    argv1[i+1] = argslist[i].c_str();
                    std::cout << argslist[i] << "s" << std::endl;
                }
                argv1[argsSize+1] = NULL;
                const char *const * argv = argv1;
                
                
                
                //call youtube-dl
                int pid = fork();
                if(pid == 0){
                    execv("../externals/youtube-dl", (char**)argv);
                }
                //wait until youtube-dl exits and find file containing "mp(3/4)"
                wait(NULL);
                DIR * dir = opendir("./");
                struct dirent *entry;
                
                std::string filename;
                while((entry = readdir(dir)) != NULL){
                    filename = entry->d_name;
                    if(filename.find("mp", 0) != std::string::npos){
                        break;
                    }
                    else{
                        filename = "";
                    }
                }
                
                
                try{
                    uploadFile(message.channelID, filename, "Brap");
                    
                }
                catch(...){
                    sendMessage(message.channelID, "Something went wrong. The file is probably too large");
                }
                
                //delete youtube file
                remove(filename.c_str());
                
            }
        }
    }
};


int main(){
    
	Godathan godathan("TOKEN_HIDDEN", 2);
    godathan.run();
	return 0;
}
