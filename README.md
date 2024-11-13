# EvaRPC-gmod

**EvaRPC-gmod** is a specialized Discord Rich Presence (RPC) integration for WayZerRP, developed in C++. This project enables customized and dynamic Discord Rich Presence for Garry's Mod, displaying information about the server and other relevant details directly on your Discord profile.

## Features

- **Discord Rich Presence Integration**: Displays real-time server information on your Discord profile.
- **Dynamic Status Updates**: Automatically updates the Discord Rich Presence with information from Garry's Mod.
- **Server Information Retrieval**: Extracts and displays the server IP address and other details in Discord.
- **Logging**: Provides detailed logging of key events and errors for easier debugging and monitoring.

## Compatibility

- **Supported Version**: This program supports only the standard version of Garry's Mod.
- **Unsupported Version**: The program does **not** support the Chromium version of Garry's Mod.

## Installation

1. **Clone the Repository**:
   ```sh
   git clone https://github.com/yourusername/EvaRPC-gmod.git
   cd EvaRPC-gmod
   ```

2. **Build the DLL**:
   - Ensure you have a C++ compiler and necessary dependencies installed.
   - Use CMake or your preferred build system to compile the project. For example, you can use the following commands if you are using CMake:
     ```sh
     mkdir build
     cd build
     cmake ..
     cmake --build .
     ```

   **Note**: If you prefer not to build the DLL yourself or are unfamiliar with the process, you can download a precompiled DLL from the [RELEASE](https://github.com/TFZO/EvaRPC-gmod/releases/tag/Release) section of this repository.

3. **Inject the DLL**:
   - Inject the compiled DLL into the Garry's Mod process. You can use tools like **DLL injectors** to achieve this.

## Configuration

- **Log File Path**: By default, the logs are written to `C:\\TFZO\\TFZO_LOGS.txt`. If necessary, adjust this path in the `WriteToLogFile` function to suit your environment.

- **Server Dictionary**: Modify the `serverDict` in the code to update the server IP-to-name mapping as needed.

## Usage

1. **Run Garry's Mod**: Ensure that Garry's Mod is running and the DLL has been successfully injected.

2. **Check Discord**: Your Discord profile should now display updated Rich Presence information, including server details.

3. **Monitor Logs**: Check `C:\\TFZO\\TFZO_LOGS.txt` for detailed logs on the application's operation and any errors that may occur.

## Code Overview

- **`GetLargeImageKeyFromServer`**: Returns the image key associated with a server IP from the `serverDict`.

- **`WriteToLogFile`**: Writes log messages to a specified log file, creating necessary directories if they don't exist.

- **`GetProcessID`**: Retrieves the process ID of a specified process.

- **`GetModuleBaseAddress`**: Retrieves the base address of a specified module within a process.

- **`getStatus`**: Reads memory from the Garry's Mod process to extract the server IP address and updates the Discord Rich Presence.

- **`MainThread`**: The main thread function that periodically updates the Discord Rich Presence with the current server status.

- **`DllMain`**: Handles DLL attachment and detachment events.

## Authors

- **Author**: atheop1337 - [GitHub Profile](https://github.com/atheop1337)

## Contributing

Contributions to EvaRPC-gmod are welcome! If you have suggestions or improvements, please open an issue or submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
