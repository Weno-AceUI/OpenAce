# CMakeLists.txt for Notifications UI Component

# This component is primarily HTML/CSS/JS and might be loaded
# by a shell or another WebCpp application.
# This CMake file can be used to copy its assets if needed.

if(DEFINED UI_ASSETS_OUTPUT_DIR) # Check if the parent (ui/CMakeLists.txt) defined this
    add_custom_command(
        OUTPUT ${UI_ASSETS_OUTPUT_DIR}/notifications/notifications.html
        COMMAND ${CMAKE_COMMAND} -E make_directory ${UI_ASSETS_OUTPUT_DIR}/notifications
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/notifications.html ${UI_ASSETS_OUTPUT_DIR}/notifications/notifications.html
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/notifications.html
        COMMENT "Copying notifications.html to UI assets"
    )
    add_custom_target(CopyNotificationsComponent ALL DEPENDS ${UI_ASSETS_OUTPUT_DIR}/notifications/notifications.html)
endif()