cmake_minimum_required(VERSION 3.20)
project(BasicRPG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download and build SFML from source on the first configure.
# It's built as static libraries so the game doesn't need the SFML DLLs.
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SFML)

add_executable(BasicRPG
    src/main.cpp
    src/core/Game.cpp
    src/core/Level.cpp
    src/core/RNG.cpp
    src/entities/Boss.cpp
    src/entities/Coin.cpp
    src/entities/Enemy.cpp
    src/entities/Player.cpp
    src/graphics/Animator.cpp
    src/ui/Button.cpp
    src/ui/UI.cpp
)

target_precompile_headers(BasicRPG PRIVATE src/stdafx.h)
if(MSVC)
    target_compile_options(BasicRPG PRIVATE /W3 /sdl)
endif()
target_include_directories(BasicRPG PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(BasicRPG PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-network
    sfml-audio
)

# Copy the game assets next to the executable so it runs on its own.
add_custom_command(TARGET BasicRPG POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:BasicRPG>
)

# SFML 2's audio module loads OpenAL from a DLL at runtime, even in a static build.
if(WIN32)
    add_custom_command(TARGET BasicRPG POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${sfml_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
            $<TARGET_FILE_DIR:BasicRPG>
    )
endif()
