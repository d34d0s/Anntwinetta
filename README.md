![banner3x](https://github.com/user-attachments/assets/fdc5a337-8fd8-4dbb-a4f6-b53edd92c81c)

[![GitHub Releases Downloads](https://img.shields.io/github/downloads/F4R4W4Y/Anntwinetta/total)](https://github.com/F4R4W4Y/Anntwinetta/releases)
[![GitHub Stars](https://img.shields.io/github/stars/F4R4W4Y/Anntwinetta?style=flat&label=stars)](https://github.com/F4R4W4Y/Anntwinetta/stargazers)
[![GitHub commits since tagged version](https://img.shields.io/github/commits-since/F4R4W4Y/Anntwinetta/Anntwinetta.1.0.2024)](https://github.com/F4R4W4Y/Anntwinetta/commits/master)
[![License](https://img.shields.io/badge/license-apache%2Flibpng-green.svg)](LICENSE)

#### Relevant Links
[ [ Official Atwin SDK ] ](https://github.com/d34d0s/AtwinSDK)

[  [Official Wiki](https://github.com/F4R4W4Y/Anntwinetta/wiki) | [API Documentation](https://github.com/F4R4W4Y/Anntwinetta/wiki/Anntwinetta-API-Docs) | [Anntwinetta Examples](https://github.com/F4R4W4Y/Anntwinetta/tree/refactor_01/examples) ]
  
[ [Official Discord](https://discord.gg/e43PDC45wu) | [Official Reddit](https://www.reddit.com/r/Anntwinetta/) | [Anntwinetta Discussions](https://github.com/F4R4W4Y/Anntwinetta/discussions) | [Anntwinetta FAQ](https://github.com/F4R4W4Y/Anntwinetta/wiki/Anntwinetta-FAQ) ]

</br>
</br>
</br>
</br>

## Building Engine Source
### Without AtwinSDK

If you don’t want to use the AtwinSDK, you can manually compile the engine by following these steps:

1. **Clone the repository**:
    ```bash
    git clone https://github.com/d34d0s/Anntwinetta.git
    cd Anntwinetta
    ```

2. **Compile the engine**:
    For Windows, you can use `gcc` to build the engine:
    ```bash
    gcc -c core/src/*.c -Ivendor -D_ATWIN_WINDOWS_ -o core/bin/Atwin.o
    gcc -shared core/bin/*.o -lSDL2 -lglfw3 -luser32 -lglew32 -lopengl32 -o core/bin/Atwin.dll
    ```

3. **Install compiled binaries**:
    Move the compiled binaries into your project's `lib` and `bin` directories:
    ```bash
    cp core/bin/*.dll your_project/bin/
    ```
    ```bash
    cp vendor/bin/*.dll your_project/bin/
    ```

## Building Projects/Mods
### Without AtwinSDK

1. Navigate to your mod's source directory.
2. Compile your mod:
    ```bash
    gcc -c mod_src/*.c -Icore/headers -o mod_bin/mod.o
    gcc -shared mod_bin/*.o -lAtwin -lSDL2 -o mod_bin/your_mod.dll
    ```

</br>

<h2> 🪷 Anntwinetta' Contributors 🪷 </h2>

<a href="https://github.com/F4R4W4Y/Anntwinetta/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=F4R4W4Y/Anntwinetta&max=500&columns=20&anon=1" />
</a>

</br>

<h2> 🪷 License 🪷 </h2>

Anntwinetta is licensed under the Apache 2.0 license.

