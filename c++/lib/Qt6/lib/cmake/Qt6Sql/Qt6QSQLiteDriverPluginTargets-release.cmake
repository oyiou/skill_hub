#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::QSQLiteDriverPlugin" for configuration "Release"
set_property(TARGET Qt6::QSQLiteDriverPlugin APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QSQLiteDriverPlugin PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C;CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/./plugins/sqldrivers/libqsqlite.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Qt6::QSQLiteDriverPlugin )
list(APPEND _IMPORT_CHECK_FILES_FOR_Qt6::QSQLiteDriverPlugin "${_IMPORT_PREFIX}/./plugins/sqldrivers/libqsqlite.a" )

# Import target "Qt6::QSQLiteDriverPlugin_init" for configuration "Release"
set_property(TARGET Qt6::QSQLiteDriverPlugin_init APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qt6::QSQLiteDriverPlugin_init PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_OBJECTS_RELEASE "${_IMPORT_PREFIX}/./plugins/sqldrivers/objects-Release/QSQLiteDriverPlugin_init/QSQLiteDriverPlugin_init.cpp.obj"
  )

list(APPEND _IMPORT_CHECK_TARGETS Qt6::QSQLiteDriverPlugin_init )
list(APPEND _IMPORT_CHECK_FILES_FOR_Qt6::QSQLiteDriverPlugin_init "${_IMPORT_PREFIX}/./plugins/sqldrivers/objects-Release/QSQLiteDriverPlugin_init/QSQLiteDriverPlugin_init.cpp.obj" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
