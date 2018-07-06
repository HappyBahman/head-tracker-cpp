cmake_minimum_required(VERSION 3.5)
PROJECT(something)

SET(OpenCV_DIR "E:/Programs/programming/opencv/build2")
FIND_PACKAGE( OpenCV REQUIRED )

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

SET(SOURCE_FILES main.cpp detector.cpp detector.h PointType.cpp PointType.h)

ADD_EXECUTABLE(something ${SOURCE_FILES} )

TARGET_LINK_LIBRARIES( something  ${OpenCV_LIBS})



