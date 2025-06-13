# CMakeLists.txt for AceGUI SDK (Style Guide)

if(NOT UI_ASSETS_OUTPUT_DIR)
    # This variable should be set by the parent CMakeLists.txt (e.g., ui/CMakeLists.txt)
    # Defaulting here as a fallback, but it's better if the parent defines it.
    set(UI_ASSETS_OUTPUT_DIR ${CMAKE_BINARY_DIR}/ui_assets)
    message(WARNING "UI_ASSETS_OUTPUT_DIR not set by parent, defaulting to ${UI_ASSETS_OUTPUT_DIR} for AceGUI guide.")
endif()

# Copy the guide.html file to the UI assets directory
add_custom_command(
    OUTPUT ${UI_ASSETS_OUTPUT_DIR}/guide.html
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/guide.html
            ${UI_ASSETS_OUTPUT_DIR}/guide.html
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/guide.html
    COMMENT "Copying AceGUI guide.html to UI assets"
)
add_custom_target(CopyAceGUIGuide ALL DEPENDS ${UI_ASSETS_OUTPUT_DIR}/guide.html)