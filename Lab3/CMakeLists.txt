cmake_minimum_required(VERSION 3.23)
project(Lab3)

set(CMAKE_CXX_STANDARD 14)
include_directories(С:/SFML/include)

set(SFML_ROOT "C:/SFML")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(SFML 2 REQUIRED system window graphics)

add_executable(Lab3 main.cpp Functions.h Functions.cpp Vector.cpp Vector.h Delone.cpp Delone.h BrownianMotion.cpp BrownianMotion.h)


if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()