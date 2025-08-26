# FrimWin

FrimWin is a small Windows tool written in C++ that lets you **rename the title of any application window**.  
It works by finding the process by name, locating its window(s), and applying a new title of your choice.  

This can be useful if you want to:
- Personalize the titles of your applications
- Hide or mask sensitive window names
- Organize your workspace by giving clearer titles

---

## ⚡ Features
- Find a process by its name (e.g. `notepad.exe`, `Procmon.exe`)
- Get its PID automatically
- Change the window title once

---

## 🛠️ Build
The project is in **C++** and uses the **Win32 API**.  
You can build it with Visual Studio or `g++` (MinGW).

Example with `g++`:
```sh
g++ -std=c++17 -o FrimWin.exe main.cpp -luser32 -lkernel32
```
🚀 Usage

Run the program from the terminal:

FrimWin.exe

Then:

    Enter the process name (e.g. notepad.exe)

    Enter the new title

    The window(s) of the process will be renamed

⚠️ Notes

    The tool must be run with the same privileges as the target app.
    (If the app is running as Administrator, run FrimWin as Administrator too.)

    Some applications (like Procmon) may reset their own title. In that case the rename will not persist.

📜 License

This project is released under the MIT License.
You are free to use, modify, and share it.
