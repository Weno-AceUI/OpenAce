# UI Components

# Lock Screen
add_executable(LockScreen lock/LockScreen.cpp)
target_link_libraries(LockScreen PRIVATE crow pthread)
target_compile_features(LockScreen PRIVATE cxx_std_17) 

find_package(Crow) # The package name might vary, check Crow's documentation

add_library(LockScreen lock/LockScreen.cpp)

if(Crow_FOUND)
    # If Crow provides an imported target (e.g., Crow::crow or Crow::headers)
    # target_link_libraries(LockScreen PUBLIC Crow::crow) 
    # This often handles include directories and linking automatically.

    # Or, if it sets variables like Crow_INCLUDE_DIRS:
    target_include_directories(LockScreen PUBLIC ${Crow_INCLUDE_DIRS})
    # If Crow also has libraries to link:
    # target_link_libraries(LockScreen PUBLIC ${Crow_LIBRARIES})
else()
    message(WARNING "Crow library not found by find_package. Ensure it's installed or provide path manually.")
    # Fallback to manual path or error out
    # target_include_directories(LockScreen PUBLIC /path/to/crow_parent_include_dir) # Manual fallback
endif()