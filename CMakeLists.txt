cmake_minimum_required( VERSION 3.16 )

project( OpenGL_Tutorial )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set( OpenGL_GL_PREFERENCE GLVND )
find_package( OpenGL REQUIRED )

include_directories( ${OPENGL_INCLUDE_DIRS} )

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_USE_WAYLAND ON CACHE BOOL "GLFW use wayland")

add_subdirectory( glfw )
add_subdirectory( glm )

if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

set( ${PROJECT_NAME}-SRC
     src/Application.cpp
     src/Renderer.cpp
     src/IndexBuffer.cpp
     src/VertexBuffer.cpp
     src/VertexArray.cpp
     src/Shader.cpp
     src/Texture.cpp
     src/vendor/stb_image/stb_image.cpp
     src/vendor/imgui/imgui.cpp
     src/vendor/imgui/imgui_demo.cpp
     src/vendor/imgui/imgui_draw.cpp
     src/vendor/imgui/imgui_tables.cpp
     src/vendor/imgui/imgui_widgets.cpp
     src/vendor/imgui/imgui_impl_glfw.cpp
     src/vendor/imgui/imgui_impl_opengl3.cpp
     src/tests/TestClearColor.cpp
     )
     
add_executable( ${PROJECT_NAME} WIN32 ${${PROJECT_NAME}-SRC} )
target_link_libraries( ${PROJECT_NAME} ${OPENGL_LIBRARIES} glm glfw GLEW )
target_include_directories( ${PROJECT_NAME} PRIVATE src/vendor )
target_include_directories( ${PROJECT_NAME} PRIVATE src/tests )
target_include_directories( ${PROJECT_NAME} PRIVATE src )


if( MSVC )
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0") 
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'GLFW-CMake-starter' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME} )
    endif()
endif()
