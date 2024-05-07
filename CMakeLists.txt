cmake_minimum_required(VERSION 3.27)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

add_executable(CMakeSFMLProject ${SRC_FILES})
target_include_directories(CMakeSFMLProject PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics sfml-audio)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)

target_compile_definitions(CMakeSFMLProject PUBLIC "SOURCE_ROOT=${CMAKE_SOURCE_DIR}")

if(WIN32)
    add_custom_command(
        TARGET CMakeSFMLProject
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()

install(TARGETS CMakeSFMLProject)