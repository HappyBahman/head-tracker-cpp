cmake_minimum_required(VERSION 3.5)
PROJECT(something)

SET(OpenCV_DIR "E:/Programs/programming/opencv/build2")
FIND_PACKAGE( OpenCV REQUIRED )
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR}  ${GLUT_INCLUDE_DIRS})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

SET(SOURCE_FILES main.cpp detector.cpp detector.h PointType.cpp PointType.h)

set(GLUT_INCLUDE_DIRS )

ADD_EXECUTABLE(something ${SOURCE_FILES} )

TARGET_LINK_LIBRARIES( something  ${OpenCV_LIBS} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} libopengl32.a libglu32.a libfreeglut.a)


