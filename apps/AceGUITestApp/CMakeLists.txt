# AceGUI Test Application (WebCpp-based)
add_executable(AceGUITestApp Main.cpp)

# Add include directory for WebCpp
target_include_directories(AceGUITestApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../WebCpp/include
)

# Link with WebCpp library
target_link_libraries(AceGUITestApp PRIVATE webcpp_lib pthread)

target_compile_features(AceGUITestApp PRIVATE cxx_std_17)

# Copy HTML file to the build directory next to the executable
add_custom_command(
    TARGET AceGUITestApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/AceGUITestApp.html
            $<TARGET_FILE_DIR:AceGUITestApp>/AceGUITestApp.html
    COMMENT "Copying AceGUITestApp.html for AceGUITestApp"
)