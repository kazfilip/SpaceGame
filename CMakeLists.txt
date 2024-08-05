cmake_minimum_required(VERSION 3.25)
project(PROJECT_2024)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)
FetchContent_MakeAvailable(SFML)

add_executable(PROJECT_2024 main.cpp
        Bullet.cpp
        Bullet.h
        Player.h
        Player.h
        Enemy.cpp
        Enemy.h
        Enemy.h
        Player.cpp
        Player.cpp
        Experience.h
        Experience.h
        Collider.cpp
        Collider.h
        Collider.h)
target_link_libraries(PROJECT_2024
        sfml-graphics
        sfml-window
        sfml-system
        )