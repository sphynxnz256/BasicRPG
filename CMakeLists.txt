cmake_minimum_required(VERSION 3.20)
project(BasicRPG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The bundled SFML 2.6.0 binaries in external/SFML were built with MSVC (x64),
# so this project must be built with the MSVC compiler.
if(NOT MSVC)
    message(FATAL_ERROR "The bundled SFML libraries require the MSVC compiler.")
endif()

set(SFML_ROOT ${CMAKE_SOURCE_DIR}/external/SFML)

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
target_compile_options(BasicRPG PRIVATE /W3 /sdl)
target_include_directories(BasicRPG PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${SFML_ROOT}/include
)
target_link_directories(BasicRPG PRIVATE ${SFML_ROOT}/lib)

# Link the debug (-d) SFML libraries in Debug builds and the regular ones otherwise.
foreach(module graphics window system network audio)
    target_link_libraries(BasicRPG PRIVATE
        debug sfml-${module}-d
        optimized sfml-${module}
    )
endforeach()

# Copy the SFML DLLs and game assets next to the executable so it runs on its own.
file(GLOB SFML_DLLS ${SFML_ROOT}/bin/*.dll)
add_custom_command(TARGET BasicRPG POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SFML_DLLS} $<TARGET_FILE_DIR:BasicRPG>
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:BasicRPG>
)
