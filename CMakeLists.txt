cmake_minimum_required(VERSION 3.11)
project(project_terracotta)

include(FetchContent)

FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
        raygui
        GIT_REPOSITORY https://github.com/raysan5/raygui.git
        GIT_TAG 4.0
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(raygui)

add_executable(project_terracotta
        src/main.c
        src/Tile.c
        src/Tile.h
        src/utils.c
        src/utils.h
        src/Editor.c
        src/Editor.h
        src/TextureAtlas.c
        src/TextureAtlas.h
        src/Canvas.c
        src/Canvas.h
        src/Pallet.c
        src/Pallet.h
)

target_include_directories(project_terracotta PRIVATE ${raygui_SOURCE_DIR}/src)
target_link_libraries(project_terracotta PRIVATE raylib)
