project GLStudy
GLStudy {
	src/main.cpp
	src/glad.c
	src/ShaderProgram.cpp
	src/stb_image.c
	src/Texture2D.cpp
	src/Camera.cpp
	src/Light.cpp
}
GLStudy.path build/
compile cxx g++
compile c g++
compile cxxflags -std=c++14 -Wall -Wextra -I/mingw64/include -Iinclude -I/mingw64/include/mesa -L/mingw64/lib
compile cflags -std=c++14 -Wall -Wextra -I/mingw64/include -Iinclude -I/mingw64/include/mesa -L/mingw64/lib
compile cxxlibs glfw3 OSMesa
compile clibs glfw3 OSMesa
