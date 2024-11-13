# DiscordRPC-gmod

**DiscordRPC-gmod** is a specialized Discord Rich Presence (RPC) integration for the WayZerRP server in Garry's Mod, developed in C++. This project allows real-time, customizable Discord Rich Presence displays, showing server and gameplay details on your Discord profile. You can use this code as a template for other games where Rich Presence modifications are allowed, and you may also adjust offsets and settings as needed.

## Features

- **Real-Time Discord Rich Presence**: Display dynamic, up-to-date server and gameplay information directly on your Discord profile.
- **Customizable Status Updates**: Automatically syncs with Garry's Mod to show server details and status in real-time.
- **Server Info Display**: Shows server IP and other relevant details on your Discord profile, enhancing visibility.
- **Detailed Logging**: Provides extensive logs of events and errors for easy debugging and monitoring.

## Compatibility

- **Supported**: Works with the standard version of Garry's Mod. If it doesn't work that's means that offset is outdated.
- **Not Supported**: Does **not** support the Chromium version of Garry's Mod.

## Installation

1. **Clone the Repository**:
   ```sh
   git clone https://github.com/atheop1337/DiscordRPC-gmod
   cd DiscordRPC-gmod
   ```

2. **Build the DLL**:
   - Ensure a compatible C++ compiler and dependencies are installed.
   - Use CMake or another build system to compile the project:
     ```sh
     mkdir build
     cd build
     cmake ..
     cmake --build .
     ```
   - Alternatively, download a precompiled DLL from the [Releases](https://github.com/atheop1337/DiscordRPC-gmod/releases/tag/Release) section if you prefer not to build the DLL yourself.

3. **Inject the DLL**:
   - Use a **DLL injector** tool to inject the compiled DLL into the Garry's Mod process.

## Configuration

- **Log Path**: Logs are written to `C:\RPC\RPC_LOGS.txt` by default. Adjust the path in the `WriteToLogFile` function if needed.
- **Server Dictionary**: Update `serverDict` in the code to match your server's IP-to-name mapping for accurate displays.

## Usage

1. **Start Garry's Mod**: Launch Garry's Mod and inject the DLL.
2. **Verify on Discord**: Confirm that your Discord profile displays the Rich Presence with server details.
3. **Review Logs**: Check `C:\RPC\RPC_LOGS.txt` for detailed logs on the application’s operation and error reporting.

## Code Overview

- **`GetLargeImageKeyFromServer`**: Retrieves the Discord image key associated with the server IP from `serverDict`.
- **`WriteToLogFile`**: Logs messages to a specified file, creating directories if they don’t exist.
- **`GetProcessID`**: Fetches the process ID of the target application.
- **`GetModuleBaseAddress`**: Retrieves the base address of a module within the target process.
- **`getStatus`**: Reads memory to identify the server IP and updates Discord Rich Presence accordingly.
- **`MainThread`**: Main loop that periodically refreshes the Discord Rich Presence with current server information.
- **`DllMain`**: Manages DLL events for attachment and detachment.

## Authors

- **atheop1337** - [GitHub Profile](https://github.com/atheop1337)

## Contributing

Contributions are encouraged! Feel free to open issues or submit pull requests to enhance EvaRPC-gmod.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

This version is more concise and polished, with improved section organization and clearer instructions. Let me know if you want any additional customization!
