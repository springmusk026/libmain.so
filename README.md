# Unity JNI Loader

This project provides a C++ implementation for loading and unloading a Unity native library (libunity.so) dynamically using JNI (Java Native Interface).

## Purpose

The purpose of this project is to demonstrate how to load a native library dynamically in an Android environment using JNI. It specifically targets Unity native libraries but can be adapted for loading other native libraries as well.

## Prerequisites

- Android development environment set up.
- Basic understanding of JNI and C++ programming.
- Unity native library (libunity.so) to be loaded.

## Usage

1. Clone this repository to your local machine:

    ```
    git clone https://github.com/your-username/unity-jni-loader.git
    ```

2. Open the project in your preferred C++ IDE or text editor.

3. Replace `"com/unity3d/player/NativeLoader"` with your desired package and class name where the native methods will be called from.

4. Build the project using your Android NDK and toolchain.

5. Include the generated library in your Android project along with the Unity native library (`libunity.so`).

6. In your Java code, call the native methods `load()` and `unload()` to load and unload the Unity native library dynamically.

## Structure

- `main.cpp`: Contains the C++ implementation of the JNI native methods for loading and unloading the Unity native library.
- `CMakeLists.txt`: CMake configuration file for building the project.

## Contributing

Contributions are welcome! If you have any improvements or suggestions, feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

This project is inspired by the need to dynamically load Unity native libraries in Android applications.
