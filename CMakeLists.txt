cmake_minimum_required(VERSION 3.25)
project(DataVisualization2 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

include_directories(src)
add_executable(DataVisualization2 src/Main.cpp src/Template/Application.cpp src/Template/SceneNode.cpp src/Template/State.cpp src/Template/StateStack.cpp src/States/MenuState.cpp src/States/MenuState.hpp src/States/States.hpp src/Template/Utility.cpp src/Template/Utility.hpp src/Template/Constants.hpp src/GUI/Component.cpp src/GUI/Component.hpp src/GUI/Container.cpp src/GUI/Container.hpp src/GUI/Button.cpp src/GUI/Button.hpp src/Template/ColorHolder.cpp src/Template/ColorHolder.hpp src/States/AboutState.cpp src/States/AboutState.hpp src/GUI/Sprite.cpp src/GUI/Sprite.hpp)

target_link_libraries(DataVisualization2 PRIVATE sfml-graphics)
target_compile_features(DataVisualization2 PRIVATE cxx_std_17)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET DataVisualization2 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:DataVisualization2> $<TARGET_FILE_DIR:DataVisualization2> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS DataVisualization2)