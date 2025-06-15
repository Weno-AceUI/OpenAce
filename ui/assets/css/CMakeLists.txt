# CMakeLists.txt for common CSS assets

if(DEFINED UI_ASSETS_OUTPUT_DIR) # Check if the parent (ui/CMakeLists.txt or ui/assets/CMakeLists.txt) defined this
    set(CSS_OUTPUT_SUBDIR "css")
    add_custom_command(
        OUTPUT ${UI_ASSETS_OUTPUT_DIR}/${CSS_OUTPUT_SUBDIR}/openace_theme.css
        COMMAND ${CMAKE_COMMAND} -E make_directory ${UI_ASSETS_OUTPUT_DIR}/${CSS_OUTPUT_SUBDIR}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/openace_theme.css ${UI_ASSETS_OUTPUT_DIR}/${CSS_OUTPUT_SUBDIR}/openace_theme.css
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/openace_theme.css
        COMMENT "Copying openace_theme.css to UI assets"
    )
    add_custom_target(CopyOpenAceThemeCss ALL DEPENDS ${UI_ASSETS_OUTPUT_DIR}/${CSS_OUTPUT_SUBDIR}/openace_theme.css)

    add_custom_command(
        OUTPUT ${UI_ASSETS_OUTPUT_DIR}/${CSS_OUTPUT_SUBDIR}/acegui.css
        COMMAND ${CMAKE_COMMAND} -E make_directory ${UI_ASSETS_OUTPUT_DIR}/${CSS_OUTPUT_SUBDIR} # Directory might already exist
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/acegui.css ${UI_ASSETS_OUTPUT_DIR}/${CSS_OUTPUT_SUBDIR}/acegui.css
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/acegui.css
        COMMENT "Copying acegui.css to UI assets"
    )
    add_custom_target(CopyAceGUICss ALL DEPENDS ${UI_ASSETS_OUTPUT_DIR}/${CSS_OUTPUT_SUBDIR}/acegui.css)
endif()