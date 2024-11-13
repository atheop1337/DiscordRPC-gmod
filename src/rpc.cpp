#include "rpc.h"

#include <ctime>
#include <string>

extern "C" __declspec(dllimport) std::string GetLargeImageKeyFromServer(const std::string& ipAddress);

const char* applicationID = "1237037992368148490";

void Discord::Initialize()
{
    DiscordEventHandlers Handle;
    memset(&Handle, 0, sizeof(Handle));
    Discord_Initialize(applicationID, &Handle, 1, NULL);
}

void Discord::Update(const std::string& ipAddress)
{
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    static auto elapsed = std::time(nullptr);

    std::string serverKey = GetLargeImageKeyFromServer(ipAddress);

    const char* state = reinterpret_cast<const char*>(u8"Creator - github/atheop1337");
    const char* details = reinterpret_cast<const char*>(u8"Idling in menu");

    if (serverKey == "riverton") {
        details = reinterpret_cast<const char*>(u8"Playing on Riverton");
    }
    else if (serverKey == "minton") {
        details = reinterpret_cast<const char*>(u8"Playing on Minton");
    }
    else if (serverKey == "carlin") {
        details = reinterpret_cast<const char*>(u8"Playing on Carlin");
    }
    else if (serverKey == "brooks") {
        details = reinterpret_cast<const char*>(u8"Playing on Brooks");
    }
    else if (serverKey == "rockford") {
        details = reinterpret_cast<const char*>(u8"Playing on Rockford");
    }
    else if (serverKey == "wrp") {
        serverKey = "wrp";
        details = reinterpret_cast<const char*>(u8"Idling in menu");
    }

    discordPresence.details = details;
    discordPresence.state = state;
    discordPresence.largeImageText = serverKey.c_str();
    discordPresence.largeImageKey = serverKey.c_str();
    discordPresence.startTimestamp = elapsed;

    Discord_UpdatePresence(&discordPresence);
}



void Discord::Destroy() {
    Discord_Shutdown();
}
