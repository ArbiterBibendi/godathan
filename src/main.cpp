#include <iostream>
#include <websocketpp_websocket.h>


class Godathan : public SleepyDiscord::DiscordClient{
    using SleepyDiscord::DiscordClient::DiscordClient;
    
    void onMessage(SleepyDiscord::Message message) override{
        std::cout << "Message recieved!" << std::endl;
    }
};


int main(){
    
	Godathan godathan("TOKEN_HIDDEN", 2);
    godathan.run();
	return 0;
}
