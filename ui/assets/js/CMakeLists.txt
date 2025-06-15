# CMakeLists.txt for common JavaScript assets

if(DEFINED UI_ASSETS_OUTPUT_DIR) # Check if the parent (ui/CMakeLists.txt or ui/assets/CMakeLists.txt) defined this
    set(JS_OUTPUT_SUBDIR "js")
    add_custom_command(
        OUTPUT ${UI_ASSETS_OUTPUT_DIR}/${JS_OUTPUT_SUBDIR}/acegui.js
        COMMAND ${CMAKE_COMMAND} -E make_directory ${UI_ASSETS_OUTPUT_DIR}/${JS_OUTPUT_SUBDIR}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/acegui.js ${UI_ASSETS_OUTPUT_DIR}/${JS_OUTPUT_SUBDIR}/acegui.js
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/acegui.js
        COMMENT "Copying acegui.js to UI assets"
    )
    add_custom_target(CopyAceGUIJs ALL DEPENDS ${UI_ASSETS_OUTPUT_DIR}/${JS_OUTPUT_SUBDIR}/acegui.js)
endif()