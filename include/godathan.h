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
#include <condition_variable>


class Godathan : public SleepyDiscord::DiscordClient{

public:
    using SleepyDiscord::DiscordClient::DiscordClient;
    std::string              replace_string (std::string string, std::string substr1, std::string substr2);
    int                      execvec        (std::string pathToProcess, std::vector<std::string> argslist, std::string workingDir);
    std::vector<std::string> arguments      (std::string s);
    
    void onServer         (SleepyDiscord::Server      server    ) override;
    void onReady          (SleepyDiscord::Ready       readData  ) override;
    void onMessage        (SleepyDiscord::Message     message   ) override;
    void onEditVoiceState (SleepyDiscord::VoiceState& voiceState) override;
    
    SleepyDiscord::VoiceState getVoiceState(SleepyDiscord::Snowflake<SleepyDiscord::User> userID);
    
    VoiceEventHandler* voiceEventHandler;
    std::vector<SleepyDiscord::Server> servers;
    std::vector<SleepyDiscord::VoiceState> voiceStates;
};



