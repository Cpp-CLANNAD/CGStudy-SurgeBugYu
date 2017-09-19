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
}
GLStudy.path build/
compile cxx g++
compile c g++
compile cxxflags -std=c++14 -Wall -Wextra -I/mingw64/include -Iinclude -I/mingw64/include/mesa -L/mingw64/lib
compile cflags -std=c++14 -Wall -Wextra -I/mingw64/include -Iinclude -I/mingw64/include/mesa -L/mingw64/lib
compile cxxlibs glfw3 OSMesa assimp
compile clibs glfw3 OSMesa assimp
