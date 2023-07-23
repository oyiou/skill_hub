#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::QWindowsVistaStylePlugin" for configuration "Release"
set_property(TARGET Qt6::QWindowsVistaStylePlugin APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QWindowsVistaStylePlugin PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/./plugins/styles/libqwindowsvistastyle.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Qt6::QWindowsVistaStylePlugin )
list(APPEND _IMPORT_CHECK_FILES_FOR_Qt6::QWindowsVistaStylePlugin "${_IMPORT_PREFIX}/./plugins/styles/libqwindowsvistastyle.a" )

# Import target "Qt6::QWindowsVistaStylePlugin_init" for configuration "Release"
set_property(TARGET Qt6::QWindowsVistaStylePlugin_init APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QWindowsVistaStylePlugin_init PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_OBJECTS_RELEASE "${_IMPORT_PREFIX}/./plugins/styles/objects-Release/QWindowsVistaStylePlugin_init/QWindowsVistaStylePlugin_init.cpp.obj"
  )

list(APPEND _IMPORT_CHECK_TARGETS Qt6::QWindowsVistaStylePlugin_init )
list(APPEND _IMPORT_CHECK_FILES_FOR_Qt6::QWindowsVistaStylePlugin_init "${_IMPORT_PREFIX}/./plugins/styles/objects-Release/QWindowsVistaStylePlugin_init/QWindowsVistaStylePlugin_init.cpp.obj" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
