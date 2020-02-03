#include <iostream>
#include <websocketpp_websocket.h>


class Godathan : public SleepyDiscord::DiscordClient{
    using SleepyDiscord::DiscordClient::DiscordClient;
    
    std::string replaceSub(std::string string, std::string substr1, std::string substr2){
        std::string newStr = string;
        
        int pos = string.find(substr1, 0);
        newStr.replace(pos, substr1.length(), substr2);
        
        return newStr;
    }
    
    void onMessage(SleepyDiscord::Message message) override{
        std::cout << "Message Recieved!" << std::endl;
        if(message.author.ID != 456655185901518848){ //If message isn't by godathan
            
            //Send Command: -send ChannelID Message
            if(message.startsWith("-send ")){
                try{
                    std::string args = replaceSub(message.content, "-send ", "");
                    
                    //Use a space to separate the channelID from the message to send
                    int channelIDLen = args.find(" ", 0);
                    std::string channelID = args.substr(0, channelIDLen);
                    std::string messageToSend = replaceSub(args, channelID + " ", "");
                    
                    sendMessage(channelID, messageToSend);
                }catch(...){}
            }
            
            
            
        }
    }
};


int main(){
    
	Godathan godathan("TOKEN_HIDDEN", 2);
    godathan.run();
	return 0;
}
