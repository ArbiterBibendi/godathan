#include "godathan.h"
#include <string>


/** Replace substr1 with substr2 inside of string **/
std::string Godathan::replace_string(std::string string, std::string substr1, std::string substr2){
    std::string newStr = string;
       
    int pos = string.find(substr1, 0);
    newStr.replace(pos, substr1.length(), substr2);
        
    return newStr;
}

/**
 * Takes a string of space separated arguments
 * or arguments grouped by quotation marks
 * and places them into a vector
 */
std::vector<std::string> Godathan::arguments(std::string s){ 
    std::vector<std::string> args;
    std::string sub;
    int space = 0;
    int searchIndex = 0;
        
    int quotation1 = 0;
    int quotation2 = 0;
    while(space != std::string::npos){ 
        quotation1 = s.find("\"", searchIndex);
        quotation2 = s.find("\"", quotation1+1);
            
        if((quotation1 != std::string::npos) && (quotation2 != std::string::npos))
        {
            sub = s.substr(quotation1, quotation2-quotation1+1);
            searchIndex = quotation2+1;
            args.push_back(sub);
        }
        
        
        space = s.find(" ", searchIndex);
        sub = s.substr(searchIndex, space-searchIndex);
        searchIndex = space+1;
        args.push_back(sub);
    }
        
    return args;
}
/**
 * execve with an argument vector
 * 
 * Converts argument vector into a suitable char * array
 * and passes it to execve
 */
int Godathan::execvec(std::string pathToProcess, std::vector<std::string> argslist, std::string workingDir){
    int argsSize = argslist.size();
    /** 
     * argv1 is the argument array before it is casted into a const char *const *
     * Extra space added for program name and null byte
     */
    const char* argv1[argsSize+2]; 
             
    /** Covert arguments vector into a char * array with the first element empty **/
    for (int i = 0; i < argsSize; i++){ 
        argv1[i+1] = argslist[i].c_str();
    }
    argv1[argsSize+1] = NULL;
    const char *const * argv = argv1; /** Cast argv1 array into const char *const * to pass to execv **/
    try{
        int pid = fork();  /**fork to provide new memory space for program-dl to run in **/
        if(pid == 0){ /** If we are inside the forked process **/
            chdir(workingDir.c_str());
            execv(pathToProcess.c_str(), (char**)argv); /** Replace process image with the child process **/
        }
        wait(NULL); /** Halt execution until child process finishes **/
    } catch(...){
        return 1;
    }  
    return 0;
}
SleepyDiscord::VoiceState Godathan::getVoiceState(SleepyDiscord::Snowflake<SleepyDiscord::User> userID){
    SleepyDiscord::VoiceState voiceState;
    for(int i = 0; i < voiceStates.size(); i++){
        if(voiceStates[i].userID == userID){
            voiceState = voiceStates[i];
        }
        std::cout << "getVoiceState User " << (std::string)voiceStates[i].userID << "connected on " << (std::string)voiceStates[i].channelID << std::endl;
    }
    return voiceState;
}
void Godathan::onReady(SleepyDiscord::Ready readyData){
    std::cout << "Godathan Ready" << std::endl;
}
void Godathan::onServer(SleepyDiscord::Server server){
    servers.push_back(server);
    
    if (!server.voiceStates.empty()){
        for(SleepyDiscord::VoiceState& i : server.voiceStates){
            std::string userID = i.userID;
            SleepyDiscord::User user = getUser(userID);
            std::cout << "onServer User " << user.username << "connected on " << (std::string)i.channelID << std::endl;
            
            voiceStates.push_back(i);
        }
    }
}
void Godathan::onEditVoiceState(SleepyDiscord::VoiceState& voiceState){
    
    std::string userID = voiceState.userID;
    SleepyDiscord::User user = getUser(userID);
    bool foundUser = false;
    
    std::cout << "onEditVoiceState User " << user.username << "connected on " << (std::string)voiceState.channelID << std::endl;
    
    for(int i = 0; i <= voiceStates.size(); i++){
        if(voiceStates.size() == 0){ 
            voiceStates.push_back(voiceState);
        } else if (userID == (std::string)voiceStates[i].userID){
            voiceStates[i] = voiceState;
            foundUser = true;
            break;
        } else{
            foundUser = false;
        }
    }
    if(!foundUser){
        voiceStates.push_back(voiceState);
    }
}
void Godathan::onMessage(SleepyDiscord::Message message){
    std::string authorID = message.author.ID;
    std::string serverID = message.serverID;
    
    if(authorID != "456655185901518848"){ //If message isn't by godathan 
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
            } catch(...){}
        }
        
        /* -yt
         * Uploads a specified youtube video or audio to the channel
         * Usage: -yt [format] [video name]
         * 
         * Supported formats are mp3 and mp4
         * 
         * The video url can be passed as well as the title
         */
        if(message.startsWith("-yt")){
            std::string args = replace_string(message.content, "-yt ", "");
            std::string url;
            std::vector<std::string> argslist;
            
            if (args.find("mp3 ") == 0){
                sendMessage(message.channelID, "Downloading MP3");
                
                args = replace_string(args, "mp3 ", "");
                url = args;
                argslist.push_back("-x");
                argslist.push_back("--audio-format");
                argslist.push_back("mp3");
            } else if(args.find("mp4 ") == 0){ //if option mp4 is specified extract url and specify mp4 format
                sendMessage(message.channelID, "Downloading MP4");
                    
                args = replace_string(args, "mp4 ", "");
                url = args;
                argslist.push_back("-f");
                argslist.push_back("mp4");
            } else{
                sendMessage(message.channelID, "You didn't specify a format. Defaulting to MP4.");
                
                url = args;
                argslist.push_back("-f");
                argslist.push_back("mp4");
            }
            /** Discord max filesize is 8MB **/
            argslist.push_back("--max-filesize");
            argslist.push_back("8m");
            argslist.push_back("ytsearch:" + url);
            execvec("../youtube-dl", argslist, "../externals/youtube-dl/temp");
                
            /** Scan directory for mp4 and mp3 files and delete them **/
            DIR * dir = opendir("../externals/youtube-dl/temp");
            struct dirent *entry;
                
            std::string filename;
            bool found = false;
            /** While we haven't reached the end of the directory **/
            while(((entry = readdir(dir)) != NULL) || found){ 
                filename = entry->d_name;
                if (filename.find("mp", 0) != std::string::npos){
                    filename = "../externals/youtube-dl/temp/" + filename;
                    found = true;
                    break;
                } else{
                    filename = ""; /** Clear filename to avoid deleting the wrong file if the download fails **/
                }
            }
            try{ 
                uploadFile(message.channelID, filename, ""); 
            } catch(SleepyDiscord::ErrorCode err){
                std::cout << "Couldn't upload file: " << err << std::endl;
                sendMessage(message.channelID, "Something went wrong. The file is probably too large"); /** Discord max filesize is 8MB **/
            }
            
            remove(filename.c_str());
        }
        
        /**  
         * -say
         * DECtalk text to speech
         * Usage: -say [message]
         */
        if(message.startsWith("-say ")){
            try{
                SleepyDiscord::VoiceState voiceState = getVoiceState(authorID);
                std::string channelID = voiceState.channelID;
                if(channelID != ""){ 
                    /** Join the same channel as the author **/
                    SleepyDiscord::VoiceContext& context = connectToVoiceChannel(serverID, channelID);
                    context.setVoiceHandler(&voiceEventHandler);
                    
                    /**
                    * DECTalk is a windows application so we need to use wineconsole
                    * to execute it
                    * 
                    * This section is setting up an argument vector for wineconsole
                    */
                    std::string text = replace_string(message.content, "-say ", "");
                    std::vector<std::string> argslist;
                    argslist.push_back("--backend=curses"); 
                    argslist.push_back("say.exe");
                    argslist.push_back("-w");
                    argslist.push_back("outfile.wav");
                    argslist.push_back(text);
            
            
                    try{
                        execvec("/usr/bin/wineconsole", argslist, "../externals/dectalk");
                        usleep(1000); //make sure the file is written to before sending, this is a caveman method so fix this later
                    } catch(...){
                        std::cout << "Couln't exec wineconsole" << std::endl;
                    }
                } else{
                    std::cout << "User not in a voice channel" << std::endl;
                }
            } catch(SleepyDiscord::ErrorCode err){
                std::cout << "Something went wrong" << err << std::endl;
            }
        }
    }
}
