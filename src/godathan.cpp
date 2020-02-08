#include "godathan.h"


    
std::string Godathan::replace_string(std::string string, std::string substr1, std::string substr2){
    std::string newStr = string;
       
    int pos = string.find(substr1, 0);
    newStr.replace(pos, substr1.length(), substr2);
        
    return newStr;
}
std::vector<std::string> Godathan::arguments(std::string s){ //Places command line arguments into vector
    std::vector<std::string> args;
    std::string sub;
    int i = 0;
    int li = 0;
        
    int q1 = 0;
    int q2 = 0;
    while(i != std::string::npos){ 
        q1 = s.find("\"", li);
        q2 = s.find("\"", q1+1);
            
        if((q1 != std::string::npos) && (q2 != std::string::npos))
        {
            sub = s.substr(q1, q2-q1+1);
            li = q2+1;
            args.push_back(sub);
        }
        
           
        i = s.find(" ", li);
        sub = s.substr(li, i-li);
        li = i+1;
        args.push_back(sub);
    }
        
    return args;
}

void Godathan::handle_child(int){
    wait(NULL);
}

void Godathan::onMessage(SleepyDiscord::Message message){
    std::cout << "Message Recieved!" << std::endl;
    if(message.author.ID != 456655185901518848){ //If message isn't by godathan
        
        if(message.startsWith("-exit")){
            exit(0);
        }
        /* 
         * -send
         *  Sends a message to a specified channel
         * Usage: -send channelID message
         */
        if(message.startsWith("-send ")){
            try{
                std::string argString = replace_string(message.content, "-send ", "");
                std::vector<std::string> args = arguments(argString);

                std::string channelID = args[0];
                std::string messageToSend = replace_string(argString, channelID, "");
                
                sendMessage(channelID, messageToSend);
            }catch(...){}
        }
        
        /* -yt
         * Uploads a specified youtube video or audio to the channel
         * Usage: -yt format video
         * 
         * Supported formats are mp3 and mp4
         * 
         * The video url can be passed as well as the title
         */
        if(message.startsWith("-yt")){
            
            std::string args = replace_string(message.content, "-yt ", "");
            std::string url;
            if (args.find("mp3 ") == 0){ //if option mp3 is specified extract url and specify mp3 format
               sendMessage(message.channelID, "Downloading MP3");
                
                args.erase(0,4);
                url = args;
                args = "-x --audio-format mp3";
            }
            else if(args.find("mp4 ") == 0){ //if option mp4 is specified extract url and specify mp4 format
                sendMessage(message.channelID, "Downloading MP4");
                    
                args.erase(0,4);
                url = args;
                args = "-f mp4";
            }
            else{ //if no format is specified, default to mp4
                sendMessage(message.channelID, "You didn't specify a format. Defaulting to MP4.");
                    
                url = args;
                    args = "-f mp4";
            }
            args += " --max-filesize 8m"; //max discord file upload size is 8 megabytes

            
            std::vector<std::string> argslist = arguments(args); //pass argument list to a basic parser
            argslist.push_back("ytsearch:" + url); //append ytsearch argument to argslist vector
                
                
                
                
                
            int argsSize = argslist.size();
            const char* argv1[argsSize+2]; //extra space added for program name and sentinel
                
             
            //Covert arguments vector into a char * array to pass to execv
            for (int i = 0; i < argsSize; i++){ 
                argv1[i+1] = argslist[i].c_str();
                std::cout << argslist[i].c_str() <<  std::endl;
            }
            argv1[argsSize+1] = NULL;
            const char *const * argv = argv1; //transfer argv1 array into const char *const * to pass to execv
                
                
                
            //call youtube-dl
            int pid = fork();  //fork to provide new memory space for youtube-dl to run in
            if(pid == 0){ //child process code
                execv("../externals/youtube-dl", (char**)argv); //replace child process image with youtube-dl
                wait(NULL);
            }
            //wait until youtube-dl exits and find file containing "mp(3/4)"
            wait(NULL);
                
                
            //code below iterates through directory and find file with "mp" in it's name'
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
                uploadFile(message.channelID, filename, "");
                    
            }
            catch(...){
                sendMessage(message.channelID, "Something went wrong. The file is probably too large");
            }
                
            //delete youtube file
            remove(filename.c_str());
        }
            
    }
}
