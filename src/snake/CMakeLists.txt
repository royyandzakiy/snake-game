# src/snake/CMakeLists.txt
set(MY_PROJECT_NAME ${PROJECT_NAME})
add_executable(${MY_PROJECT_NAME})

file(GLOB SOURCES *.cpp)
target_sources(${MY_PROJECT_NAME} PRIVATE ${SOURCES})

target_include_directories(${MY_PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${MY_PROJECT_NAME}
    PRIVATE
        fmt::fmt
        raylib
)

get_target_property(EXEC_OUTPUT_DIR ${MY_PROJECT_NAME} RUNTIME_OUTPUT_DIRECTORY)

if(NOT EXEC_OUTPUT_DIR)
    set(EXEC_OUTPUT_DIR "$<TARGET_FILE_DIR:${MY_PROJECT_NAME}>")
endif()

# Copy the assets folder to the executable directory after a successful build
add_custom_command(
    TARGET ${MY_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/../../assets"   # Adjust this path to where your assets actually live
            "${EXEC_OUTPUT_DIR}/assets"
    COMMENT "Copying assets to build directory..."
)