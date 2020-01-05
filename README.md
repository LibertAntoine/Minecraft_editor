# IMAC 3D voxel editor project

![3D editor in action](Doc/Screenshots/Screenshot_20200105_210133.png?raw=true "3D editing made easy")

## Instructions
Please follow these steps to make compile the project and start using the 3D editor:
### Downloading
First you may first clone this Git repository
If you are using a terminal simply execute the following command :
```bash
git clone --depth=1 https://github.com/LibertAntoine/Minecraft_editor.git
```
Notice: the `--depth` option will perform a shallow clone with only 1 commit history, this will reduce the amount off downloaded content :upside_down_face:
Then move into `Minecraft_editor` directory or whatever name you've used when cloning and create a new directory at the root called `bin` for instance. It will contain your future executable.
### Compiling
Now we can compile the project using...
```bash
cmake ..
```
... or ...
```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
```
... if you when to keep debug data and make the compile verbose for warnings.
Then compile using the automatically generated `Makefile` with :
```bash
make
```
### Running
To use the 3D editor you have to execute it from a specific directory which is located in `Minecraft_editor/Minecraft`
Then hit this command from your terminal :
```bash
../bin/Minecraft/src/Minecraft
```
And there you go :smile: enjoy!
