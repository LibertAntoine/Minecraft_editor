# :hammer_and_wrench: MinecraftEditor

 ![MinecraftEditor](Doc/readme-img/MinecraftEditor.png?raw=true "MinecraftEditor")

## Table of Contents

- [**Building configuration**](#Building-configuration)
  * [**Clone repository**](#clone-repository)
  * [**Linux**](#linux)
    - [**Add dependencies**](#add-dependencies)
    - [**Build**](#build)
    - [**Execute**](#execute)
  * [**Windows**](#windows)
    
- [**Presentation**](#presentation)

- [**Main Features**](#main-features)

- [**Contributors**](#contributors)

- [**Dependencies**](#dependencies)


## Building configuration 
* **OS Supported :** Windows, Linux

### Clone repository 
In the local folder for the project
```bash
git clone https://github.com/LibertAntoine/Minecraft_editor.git
```

### Linux

#### Add dependencies 
```bash
sudo apt-get update
sudo apt-get install cmake libgl1-mesa-dev  libsdl2-dev libeigen3-dev libglew-dev.
```

#### Build
In the project folder
```bash
mkdir build
cd build
cmake ..
make
```

#### Execute
In the project folder
```bash
bin/Minecraft
```

### Windows
* Move SDL2.dll from WinDependencies\SDL2\{systemType} to the bin directory
* Move SDL2.dll from WinDependencies\glew-2.1.0\{configType}\{systemType} to the bin directory
* Open Visual studio project and generate the project.


## Presentation
<p>
Cubic-based 3D world editor, developed in C++ and the OpenGL 4 graphics API. This editor offers a very complete interface allowing you to create cubes by moving a selector or using the mouse. It is possible to change the colour or texture of the cubes, and to do multi-texturing on the same cube, by choosing a different texture per face. It is possible to place a directional or point light in the scene. Each cube is built by the geometry shader from a coordinate. The cubes are rendered in batch rendering technics.
</p>
<p>
This project is an initiative resulting from a lecture about image synthesis and applied mathematics at the IMAC engineering school.
</p>

Realized in December 2019.


[**More details... (FR)**](Doc/Minecraft_Editor_Rapport.pdf)

<p align="center">
<img src="Doc/readme-img//MinecraftEditor2.png?raw=true" width="45%" alt="Screenshot">
<img src="Doc/readme-img//MinecraftEditor3.png?raw=true" width="45%" alt="Screenshot">
</p>


## Main Features

* Graphics pipeline in OpenGL 4.
* Selection of cubes with the mouse.
* Multi-texturing of cubes.
* Interface with ImGui.
* Directional or point light.


## Contributors

* [Antoine Libert](https://github.com/LibertAntoine) - Graphic Renderer, GUI, multi-texturing, light.
* [Nicolas Liénart](https://github.com/nicolnt) - Selection, RBF.

## Dependencies

- [OpenGL4](http://docs.gl/) - Graphic API used
- [SDL2](https://wiki.libsdl.org/) - The library to create window.
- [ImGui](https://github.com/ocornut/imgui) - For interfaces.
- [StbImage](https://github.com/nothings/stb) - For loading images
- [Eigen3](https://eigen.tuxfamily.org/dox-devel/index.html) - For matrices.
- [GLM](https://glm.g-truc.net/0.9.9/index.html) - For transform.
- [Octree](https://nomis80.org/code/octree.html) - For 3D map location.

