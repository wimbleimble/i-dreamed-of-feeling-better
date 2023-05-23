cmake_minimum_required(VERSION 3.7...3.18)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(godfeels VERSION 0.0.1
		DESCRIPTION "I Dreamed of Feeling Better"
		LANGUAGES C)

set(ecs
	src/ecs/ecs.c
	src/ecs/component.c
	src/ecs/entity.c
	src/ecs/event_bus.c)

set(renderer
	src/renderer/renderer.c
	src/renderer/shader.c
	src/renderer/texture.c)

set(resources
	src/resources/resources.c
	src/resources/stb_image.c)

set(systems
	src/systems/system_defs.c
	src/systems/system_render.c
	src/systems/system_animation.c
	src/systems/system_movement.c)

set(misc
	src/input.c)

set(game
	src/main.c
	src/component_defs.c)

set(src ${ecs} ${renderer} ${resources} ${game} ${systems} ${misc})

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_executable(${PROJECT_NAME}
	${src})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include/")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include/renderer")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include/resources")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include/ecs")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include/systems")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include/components")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/lib/stb")
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} m)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} OpenGL::OpenGL)
target_link_libraries(${PROJECT_NAME} GLU)
target_link_libraries(${PROJECT_NAME} GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} cglm)
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/cglm/")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E
	copy_directory "../assets" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

