cmake_minimum_required(VERSION 3.12)
project(road_detect)

set(CMAKE_CXX_STANDARD 14)

#打开Qt的MOC功能和UI文件处理功能
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(OpenCV_DIR /usr/lib/cmake/opencv4)
set(OpenCV2_DIR /usr/include/opencv4/opencv2)

# 有GUI界面的代码
add_executable(road_detect AutoAdjust.h GUI/main.cpp GUI/mainwindow.cpp GUI/mainwindow.h SignDetect.cpp SignDetect.h GUI/ui_mainwindow.h LaneDetect.cpp LaneDetect.h)

## 没有GUI的demo
#add_executable(road_detect LaneDetect.cpp LaneDetect.h main.cpp SignDetect.cpp SignDetect.h AutoAdjust.h)


#查找Qt的库
find_package(Qt5Widgets)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(road_detect ${OpenCV_LIBS}  Qt5::Widgets)



