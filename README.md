# Projeto Integrador Pe01 — Marine Environment Simulation
 
A marine ecosystem simulation built with Unreal Engine 5.7, featuring AI-driven organisms including fish, sharks, and plants interacting in a procedurally populated ocean environment.
 
---
 
## 1. Required Software
 
### Unreal Engine 5.7
- Download and install the **Epic Games Launcher** from [unrealengine.com](https://www.unrealengine.com/download)
- After installing, open the launcher and go to **Unreal Engine → Library**
- Click **+** to add a new engine version and select the latest version of **5.7**
- Click **Install** and wait for it to finish
### Visual Studio 2022
 
- If not installed, download **Visual Studio** from [visualstudio.microsoft.com](https://visualstudio.microsoft.com/downloads) — select the **Community** version (free)
- After running the installer, a window will appear with installation options. Select the following:
  - On the **Workloads** tab:
    - Desktop development with C++
    - Game development with C++
    - Desktop development with .NET
    
  - On the **Individual Components** tab:
    - .NET Framework 4.8.1 SDK
    - .NET Framework 4.8.1 targeting pack
    - MSVC Build Tools for x64/x86 (Latest)
    - MSVC v143 - VS 2022 C++ x64/x86 build tools
- If Visual Studio is already installed, open **Visual Studio Installer**, click **Modify** on your existing installation, and verify all the options above are selected
### Git
 
- If not installed, download from [git-scm.com](https://git-scm.com/)
- Install with default settings
- Used to clone the project repository to your machine
---
 
## 2. Development
 
### Cloning the Project
 
Open a terminal (Command Prompt or Git Bash) and run:
 
```bash
git clone https://gitlab.up.pt/l.eic/projeto-integrador-pe01-unrealengine-2026.git
cd projeto-integrador-pe01-unrealengine-2026
```
 
### Running the Project
 
After cloning, open **Visual Studio** and select **Open Project or Solution**, then select the **.sln** file from the project folder.
 
To compile and launch the project, click the **green play button** on the top bar. This will automatically open an **Unreal Engine** window with the project loaded.
 
Inside **Unreal Engine**, go to **File → Open Level**, and select `Content/Map/OceanLevel`.
 
To run the simulation, click the **green play button** or press **Alt+P**.
 
### Modifying the Code
 
To open and edit C++ source files, go to **Tools → Open Visual Studio** inside Unreal Engine, or open Visual Studio directly and navigate to the `Source/MarineEnv/` folder.
 
After making changes in Visual Studio, you can rebuild without closing Unreal Engine using **Live Coding** — click the **Compile** button in the bottom right bar of the Unreal Engine window.
 
For larger changes or if Live Coding fails:
1. Close Unreal Engine
2. In Visual Studio, go to **Build → Build Solution** (`Ctrl+Shift+B`)
3. Once the build succeeds, reopen the project by double clicking **MarineEnv.uproject**

### Exporting
 
To export the simulation as a standalone Windows executable:
 
1. In Unreal Engine go to **Platforms → Windows → Package Project**
2. Select an output folder outside the project directory
3. Wait for packaging to complete — this can take **1–2 hours** on the first run due to shader compilation
4. After packaging, the output folder contains all the files required to run the executable in the folder. No Unreal Engine installation is required to run the program on the target machine.