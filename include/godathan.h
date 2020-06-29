#pragma once
#include "sleepy_discord/websocketpp_websocket.h"
#include "voiceeventhandler.h"
#include <sys/wait.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <string>
#include <vector>



class Godathan : public SleepyDiscord::DiscordClient{

public:
    using SleepyDiscord::DiscordClient::DiscordClient;
    std::string replace_string(std::string string, std::string substr1, std::string substr2);
    std::vector<std::string> arguments(std::string s);
    int execvec(std::string pathToProcess, std::vector<std::string> argslist, std::string workingDir);
    static void handle_child(int);
    
    void onReady(SleepyDiscord::Ready readData) override;
    void onMessage(SleepyDiscord::Message message) override;
    
    VoiceEventHandler voiceEventHandler;
};



