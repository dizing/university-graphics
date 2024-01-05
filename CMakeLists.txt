cmake_minimum_required(VERSION 3.16)
project(oop_sibsutis LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)

#DEPENDENCIES
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

#SOURCE FILES
add_subdirectory(my_graph_lib)
add_subdirectory(drawing_figures)

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} PRIVATE drawing_figures)

#RESOURCES
set (${PROJECT_NAME}_RESOURCE_DIRECTORY ${CMAKE_BINARY_DIR}/resources)
target_compile_definitions(${PROJECT_NAME} PRIVATE -D${PROJECT_NAME}_RESOURCE_DIRECTORY="${${PROJECT_NAME}_RESOURCE_DIRECTORY}")

add_custom_command(TARGET ${PROJECT_NAME}
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/font.otf                   
        ${${PROJECT_NAME}_RESOURCE_DIRECTORY}/font.otf
)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()

install(TARGETS ${PROJECT_NAME})
