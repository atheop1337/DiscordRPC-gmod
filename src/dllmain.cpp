#include "includes.h"

std::unordered_map<std::string, std::string> serverDict = {
    {"46.174.54.203", "riverton"},
    {"46.174.54.52", "minton"},
    {"37.230.228.180", "carlin"},
    {"62.122.213.48", "brooks"},
    {"37.230.162.208", "rockford"},
};

extern "C" __declspec(dllexport) std::string GetLargeImageKeyFromServer(const std::string& ipAddress) {
    auto it = serverDict.find(ipAddress);
    if (it != serverDict.end()) {
        return it->second;
    }
    return "wrp";
}

void WriteToLogFile(const std::string& message) {
    namespace fs = std::filesystem;

    fs::path logFilePath = "C:\\TFZO\\TFZO_LOGS.txt";
    fs::path logDir = logFilePath.parent_path();

    if (!fs::exists(logDir)) {
        if (!fs::create_directories(logDir)) {
            std::cerr << "Failed to create directories" << std::endl;
            return;
        }
    }

    std::ofstream logFile(logFilePath, std::ios_base::app);
    if (logFile.is_open()) {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);

        std::tm tm_now;
        localtime_s(&tm_now, &now_time);
        std::stringstream timeStream;
        timeStream << std::put_time(&tm_now, "[%Y-%m-%d %H:%M:%S] ");

        logFile << timeStream.str() << message << std::endl;
        logFile.close();
    }
    else {
        std::cerr << "Failed to open log file" << std::endl;
    }
}

DWORD GetProcessID(const std::wstring& processName) {
    DWORD processID = 0;
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32W entry;
        entry.dwSize = sizeof(entry);
        if (Process32FirstW(snap, &entry)) {
            do {
                if (!_wcsicmp(entry.szExeFile, processName.c_str())) {
                    processID = entry.th32ProcessID;
                    break;
                }
            } while (Process32NextW(snap, &entry));
        }
    }
    CloseHandle(snap);
    return processID;
}

DWORD GetModuleBaseAddress(DWORD pid, const wchar_t* moduleName) {
    DWORD baseAddress = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32W modEntry;
        modEntry.dwSize = sizeof(MODULEENTRY32W);
        if (Module32FirstW(hSnap, &modEntry)) {
            do {
                if (!_wcsicmp(modEntry.szModule, moduleName)) {
                    baseAddress = (DWORD)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32NextW(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return baseAddress;
}

std::string getStatus(DWORD ofs1) {
    DWORD pid = GetProcessID(L"hl2.exe");
    if (pid == 0) {
        WriteToLogFile("Process not found");
        return "";
    }

    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (processHandle == nullptr) {
        WriteToLogFile("Failed to open process");
        return "";
    }

    DWORD engineDllBaseAddr = GetModuleBaseAddress(pid, L"engine.dll");
    if (engineDllBaseAddr == 0) {
        WriteToLogFile("Failed to find engine.dll");
        CloseHandle(processHandle);
        return "";
    }

    std::stringstream ss;
    ss << "Engine DLL Base Address: " << std::hex << engineDllBaseAddr;
    WriteToLogFile(ss.str());

    uintptr_t targetAddress = engineDllBaseAddr + ofs1;
    if (targetAddress < engineDllBaseAddr) {
        WriteToLogFile("Address overflow detected!");
        CloseHandle(processHandle);
        return "";
    }

    char buffer[14] = { 0 };
    if (!ReadProcessMemory(processHandle, reinterpret_cast<LPCVOID>(targetAddress), buffer, sizeof(buffer), nullptr)) {
        WriteToLogFile("Failed to read memory");
        CloseHandle(processHandle);
        return "";
    }

    std::string data(buffer, sizeof(buffer));

    std::regex ipRegex(R"(\d+\.\d+\.\d+\.\d+)");
    std::smatch match;
    if (std::regex_search(data, match, ipRegex)) {
        std::string ip = match.str();
        WriteToLogFile("Found IP: " + ip + ":27015");
        CloseHandle(processHandle);
        return ip;
    }
    else {
        WriteToLogFile("IP not found in memory");
        CloseHandle(processHandle);
        return "wrp";
    }
}

DWORD WINAPI MainThread(LPVOID lpParam) {
    DWORD ofs1 = 0xA22A20; // no chromium

    Discord discord;
    discord.Initialize();

    while (true) {
        std::string ipAddress = getStatus(ofs1);
        if (!ipAddress.empty()) {
            discord.Update(ipAddress); 
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    discord.Destroy();
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        WriteToLogFile("Successfully attached!");
        CreateThread(nullptr, 0, MainThread, nullptr, 0, nullptr);
        break;
    case DLL_PROCESS_DETACH:
        WriteToLogFile("Successfully detached!");
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    }
    return TRUE;
}
