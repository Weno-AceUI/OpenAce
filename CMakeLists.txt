cmake_minimum_required(VERSION 4.0)

include_directories(/../base/frameworks/WebCpp/include)

add_executable(WebCppApp base/frameworks/WebCpp/WebCppApp.cpp)

target_link_libraries(WebCppApp
    /Users/dylando/libs/ultralight/libUltralightCore.a
    /Users/dylando/libs/ultralight/libUltralight.a
    # Add any other required Ultralight libraries here
)