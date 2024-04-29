# Unity JNI Loader

This project provides a C++ implementation for dynamically recompiling the Unity native library (`libmain.so`) within Unity games. This functionality aids in debugging games and can be utilized to enhance anti-cheat measures.

## Purpose

The primary purpose of this project is to demonstrate how to dynamically recompile a Unity native library within Unity games using JNI (Java Native Interface). By reloading the native library during runtime, developers can debug game issues more effectively and implement stronger anti-cheat mechanisms.

**Please note:** This project is intended for educational purposes only and should not be used for unethical or malicious purposes.

## Prerequisites

- Android development environment set up.
- Basic understanding of JNI and C++ programming.
- Unity game for testing.

## Usage

1. Clone this repository to your local machine:

    ```
    git clone https://github.com/springmusk026/libmain.so.git
    ```

2. Open the project in your preferred C++ IDE or text editor.

3. Replace `"com/unity3d/player/NativeLoader"` with your desired package and class name where the native methods will be called from.

4. Build the project using your Android NDK and toolchain.

5. Include the generated library (`libmain.so`) in your Unity game project.

6. Integrate the JNI loader into your Unity game to dynamically reload the native library during runtime.

## Structure

- `main.cpp`: Contains the C++ implementation of the JNI native methods for recompiling the Unity native library.
- `CMakeLists.txt`: CMake configuration file for building the project.

## Contributing

Contributions are welcome! If you have any improvements or suggestions, feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

This project is inspired by the need to dynamically recompile Unity native libraries in Android applications for debugging and anti-cheat purposes. It is intended for educational use only.
