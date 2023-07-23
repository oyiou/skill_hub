#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::QMinimalIntegrationPlugin" for configuration "Release"
set_property(TARGET Qt6::QMinimalIntegrationPlugin APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QMinimalIntegrationPlugin PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/./plugins/platforms/libqminimal.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Qt6::QMinimalIntegrationPlugin )
list(APPEND _IMPORT_CHECK_FILES_FOR_Qt6::QMinimalIntegrationPlugin "${_IMPORT_PREFIX}/./plugins/platforms/libqminimal.a" )

# Import target "Qt6::QMinimalIntegrationPlugin_init" for configuration "Release"
set_property(TARGET Qt6::QMinimalIntegrationPlugin_init APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QMinimalIntegrationPlugin_init PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_OBJECTS_RELEASE "${_IMPORT_PREFIX}/./plugins/platforms/objects-Release/QMinimalIntegrationPlugin_init/QMinimalIntegrationPlugin_init.cpp.obj"
  )

list(APPEND _IMPORT_CHECK_TARGETS Qt6::QMinimalIntegrationPlugin_init )
list(APPEND _IMPORT_CHECK_FILES_FOR_Qt6::QMinimalIntegrationPlugin_init "${_IMPORT_PREFIX}/./plugins/platforms/objects-Release/QMinimalIntegrationPlugin_init/QMinimalIntegrationPlugin_init.cpp.obj" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
