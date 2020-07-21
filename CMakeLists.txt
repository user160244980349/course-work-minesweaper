cmake_minimum_required(VERSION 3.14)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_SOURCE_DIR}/cmake_modules/copy_resources.cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

if (WIN32)
    set(SDL2_PATH D:/Programs/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/x86_64-w64-mingw32)
    set(SDL2_TTF_PATH D:/Programs/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/x86_64-w64-mingw32)
    set(SDL2_IMAGE_PATH D:/Programs/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/x86_64-w64-mingw32)
endif (WIN32)

project(minesweaper)

file(GLOB_RECURSE INC ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp)

add_executable(${PROJECT_NAME}
        ${INC}
        ${SRC})

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${SDL2_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}
        ${SDL2_LIBRARY}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES})

copy_resources(${CMAKE_SOURCE_DIR}/resources)
