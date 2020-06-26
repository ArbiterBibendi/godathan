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
int Godathan::execvec(std::string pathToProcess, std::vector<std::string> argslist, std::string workingDir){
    int argsSize = argslist.size();
    const char* argv1[argsSize+2]; //extra space added for program name and terminator
    //memset(argv1, 0, sizeof(argv1));
             
    //Covert arguments vector into a char * array to pass to execv
    for (int i = 0; i < argsSize; i++){ 
        argv1[i+1] = argslist[i].c_str();
        std::cout << argslist[i].c_str() <<  std::endl;
    }
    argv1[argsSize+1] = NULL;
    const char *const * argv = argv1; //transfer argv1 array into const char *const * to pass to execv
                
                
    try{
        //call program
        int pid = fork();  //fork to provide new memory space for program-dl to run in
        if(pid == 0){ //child process code
            chdir(workingDir.c_str());
            execv(pathToProcess.c_str(), (char**)argv); //replace child process image with program
        }
        wait(NULL);
    }catch(...){
        return 1;
    }
    
            
    return 0;
}

void Godathan::handle_child(int){
    wait(NULL);
}

void Godathan::onMessage(SleepyDiscord::Message message){
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
                std::string args = replace_string(message.content, "-send ", "");
                std::vector<std::string> argslist = arguments(args);

                std::string channelID = argslist[0];
                std::string messageToSend = replace_string(args, channelID, "");
                
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
                
                
            execvec("../youtube-dl", argslist, "../externals/youtube-dl/temp");
                
                
            //code below iterates through directory and find file with "mp" in it's name'
            DIR * dir = opendir("../externals/youtube-dl/temp");
            struct dirent *entry;
                
            std::string filename;
            bool found = false;
            while(((entry = readdir(dir)) != NULL) || found){
                filename = entry->d_name;
                std::cout << filename << std::endl;
                if(filename.find("mp", 0) != std::string::npos){
                    filename = "../externals/youtube-dl/temp/" + filename;
                    found = true;
                    break;
                }
                else{
                    filename = "";
                }
            }
                
                
            try{
                uploadFile(message.channelID, filename, "");
                    
            }
            catch(SleepyDiscord::ErrorCode err){
                std::cout << "Couldn't upload file: " << err << std::endl;
                sendMessage(message.channelID, "Something went wrong. The file is probably too large");
            }
                
            //delete youtube file
            remove(filename.c_str());
            //end of youtube-dl
        }
        if(message.startsWith("-say ")){
            std::string text = replace_string(message.content, "-say ", "");
            std::vector<std::string> argslist;
            
            argslist.push_back("--backend=user");
            argslist.push_back("say.exe");
            argslist.push_back("-w");
            argslist.push_back("outfile.wav");
            argslist.push_back(text);
            
            
            try{
                execvec("/usr/bin/wineconsole", argslist, "../externals/dectalk");
            }catch(...){
                std::cout << "Couln't exec wineconsole" << std::endl;
            }
            try{
                usleep(1000); //make sure the file is written to before sending
                uploadFile(message.channelID, "../externals/dectalk/outfile.wav", "");
            }catch(SleepyDiscord::ErrorCode err){
                std::cout << "Couldn't upload file: " << err << std::endl;
            }
            
            
        }
            
    }
}
