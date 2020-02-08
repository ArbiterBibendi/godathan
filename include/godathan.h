#pragma once

#include <websocketpp_websocket.h>
#include <sys/wait.h>
#include <sys/wait.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <string>
#include <vector>

class Godathan : public SleepyDiscord::DiscordClient{
    using SleepyDiscord::DiscordClient::DiscordClient;
    
    

public:
    
    std::string replace_string(std::string string, std::string substr1, std::string substr2);
    std::vector<std::string> arguments(std::string s);
    static void handle_child(int);
    
    void onMessage(SleepyDiscord::Message message) override;
};


