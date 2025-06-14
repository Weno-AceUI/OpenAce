# Camera Application (WebCpp-based)
add_executable(CameraApp Main.cpp)

# Add include directory for WebCpp
target_include_directories(CameraApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../WebCpp/include
)

# Link with WebCpp library
target_link_libraries(CameraApp PRIVATE webcpp_lib pthread)

target_compile_features(CameraApp PRIVATE cxx_std_17)

# Copy HTML file to the build directory next to the executable
add_custom_command(
    TARGET CameraApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/Camera.html
            $<TARGET_FILE_DIR:CameraApp>/Camera.html
    COMMENT "Copying Camera.html for CameraApp"
)