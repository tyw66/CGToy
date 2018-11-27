TEMPLATE = app
TARGET = GLDemo
INCLUDEPATH += .

#config opengl
LIBS += -lopengl32 -lglfw3
#LIBS += -lgdi32 -lwinmm -lkernel32 -luser32 -lwinspool -lcomdlg32 -ladvapi32 -lshell32 -lole32 -loleaut32 -luuid -lodbc32 -lodbccp32


#config glfw
INCLUDEPATH += E:\opengl\glfw-3.2.1.bin.WIN32\include
DEPENDPATH += E:/opengl/glfw-3.2.1.bin.WIN32/lib-mingw
unix|win32: LIBS += -LE:/opengl/glfw-3.2.1.bin.WIN32/lib-mingw/ -lglfw3


#config glew
#INCLUDEPATH += E:\opengl\glew-2.1.0-win32\glew-2.1.0\include


SOURCES += helloGL.cpp
