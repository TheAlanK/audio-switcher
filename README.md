# audio-switcher
Program that switches between two audio devices

## Description
Audio Switcher is a utility designed to easily switch between different audio devices. It's particularly useful for users who regularly switch output devices such as speakers and headphones.

## Technologies Used
- **C++**: For the core functionality to switch between audio devices using PolicyConfig.
- **Python**: To create a system tray executable for easy access and control.
- **PyInstaller**: Used for generating a standalone Windows executable from the Python script.

## Features
- **Hotkey Activation**: Users can switch between devices using a predefined hotkey (`Ctrl+Alt+A`).
- **System Tray Integration**: The application resides in the system tray for easy access.
- **Logging**: Keeps a log of actions and errors for troubleshooting.

## Python Script
The Python script facilitates system tray integration and hotkey management. It utilizes `pystray` for the system tray icon and `keyboard` for hotkey functionality.

### Key Components of the Python Script
- System Tray Icon Creation
- Hotkey Registration
- Executable Runner for Device Switching
- Exit Functionality

## C++ Application
The C++ application is responsible for the direct interaction with the audio devices. It uses PolicyConfig to switch between audio endpoints. This section of the application handles device enumeration, default device switching, and error handling with detailed logs for any issues that may arise during the switch.

### Key Components of the C++ Application
- COM Initialization and Cleanup
- Device Enumeration
- Switching the Default Audio Device
- Comprehensive Error Handling and Logging

## Building the Application
1. **Compile the C++ Code**: Use your preferred C++ compiler to build the application that handles the device switching.
2. **Prepare the Python Environment**: Install the necessary Python packages (`pystray`, `PIL`, `keyboard`, etc.).
3. **Create the Executable**: Use PyInstaller to generate a standalone executable for Windows. The command for this can be something like `pyinstaller --add-data "./dependencies/audio-switcher.exe;dependencies" --noconsole AudioSwitcher.py`.

## Installation
- Clone the repository.
- Follow the build instructions to create the executables.
- Place the compiled C++ executable and the generated Python executable in the desired location.

## Usage
- Run the Python executable to start the system tray application.
- Use the hotkey (`Ctrl+Alt+A`) to switch between the predefined audio devices.

## Logging
The application generates logs for monitoring and debugging purposes, found in `AudioSwitcher.log`.

## Future Enhancements
- UI for selecting preferred devices.
- Support for more hotkey configurations.
- Cross-platform compatibility.

## License
MIT

## Contributions
Contributions are welcome. Please feel free to fork, improve, and make pull requests.

## Acknowledgments
- Special thanks to [EreTIk](https://github.com/EreTIk) for the PolicyConfig header.

