project GLStudy
GLStudy {
	src/main.cpp
	src/glad.c
	src/stb_image.c
	src/SNCGraphics/ShaderProgram.cpp
	src/SNCGraphics/Camera.cpp
	src/SNCGraphics/Lighting/Light.cpp
	src/SNCGraphics/Model/Texture2D.cpp
	src/SNCGraphics/Model/Model.cpp
	src/SNCGraphics/Model/Mesh.cpp
}
GLStudy.path build/
compile cxx g++
compile c g++
compile cxxflags -std=c++14 -Wall -Wextra -Isrc -Iinclude
compile cflags -std=c++14 -Wall -Wextra -Isrc -Iinclude
compile cxxlibs glfw3 OSMesa assimp
compile clibs glfw3 OSMesa assimp
