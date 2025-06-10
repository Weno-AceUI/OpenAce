# UI components
add_subdirectory(components)

add_subdirectory(../sdk/AceGUI) # Assuming framework is a direct subdirectory of ui

# Define a common output directory for UI assets
set(UI_ASSETS_OUTPUT_DIR ${CMAKE_BINARY_DIR}/ui_assets)

# Ensure the asset directory exists
file(MAKE_DIRECTORY ${UI_ASSETS_OUTPUT_DIR})

# Copy common framework assets
# Note: This assumes acepaper.png is in ui/home. Adjust path if different.
# Changed to source acepaper.png from ui/components/home/
set(ACEPAPER_SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/components/home/acepaper.png)

if(EXISTS ${ACEPAPER_SOURCE_PATH})
    add_custom_command(
        OUTPUT ${UI_ASSETS_OUTPUT_DIR}/acepaper.png
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${ACEPAPER_SOURCE_PATH}
                ${UI_ASSETS_OUTPUT_DIR}/acepaper.png
        DEPENDS ${ACEPAPER_SOURCE_PATH}
        COMMENT "Copying acepaper.png to UI assets"
    )
    add_custom_target(CopyFrameworkAssets ALL DEPENDS ${UI_ASSETS_OUTPUT_DIR}/acepaper.png)
endif()