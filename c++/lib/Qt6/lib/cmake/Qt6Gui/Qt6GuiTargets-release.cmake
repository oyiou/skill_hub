#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::Gui" for configuration "Release"
set_property(TARGET Qt6::Gui APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::Gui PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C;CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libQt6Gui.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Qt6::Gui )
list(APPEND _IMPORT_CHECK_FILES_FOR_Qt6::Gui "${_IMPORT_PREFIX}/lib/libQt6Gui.a" )

# Import target "Qt6::Gui_resources_1" for configuration "Release"
set_property(TARGET Qt6::Gui_resources_1 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::Gui_resources_1 PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_OBJECTS_RELEASE "${_IMPORT_PREFIX}/lib/objects-Release/Gui_resources_1/.rcc/qrc_qpdf.cpp.obj"
  )

list(APPEND _IMPORT_CHECK_TARGETS Qt6::Gui_resources_1 )
list(APPEND _IMPORT_CHECK_FILES_FOR_Qt6::Gui_resources_1 "${_IMPORT_PREFIX}/lib/objects-Release/Gui_resources_1/.rcc/qrc_qpdf.cpp.obj" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)