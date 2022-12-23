set (SOURCE_FILES
    demo/api/Helper.cpp
    demo/api/TableAPI.cpp
)

add_library(demo_sources ${SOURCE_FILES})
target_include_directories(demo_sources PUBLIC ${CONAN_INCLUDE_DIRS})

target_link_libraries(demo_sources ${CONAN_LIBS})

add_executable(demo demo/Main.cpp)
target_link_libraries(demo demo_sources)

add_custom_target(luascripts
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/lua
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/lua ${CMAKE_BINARY_DIR}/lua
    COMMENT "Copying ${CMAKE_SOURCE_DIR}/lua to ${CMAKE_BINARY_DIR}/lua"
)

add_dependencies(demo luascripts)

# vim:ft=cmake
