set(QWindowsIntegrationPlugin_FOUND FALSE)

# note: _third_party_deps example: "ICU\\;FALSE\\;1.0\\;i18n uc data;ZLIB\\;FALSE\\;\\;"
set(__qt_QWindowsIntegrationPlugin_third_party_deps "")

foreach(__qt_QWindowsIntegrationPlugin_target_dep ${__qt_QWindowsIntegrationPlugin_third_party_deps})
    list(GET __qt_QWindowsIntegrationPlugin_target_dep 0 __qt_QWindowsIntegrationPlugin_pkg)
    list(GET __qt_QWindowsIntegrationPlugin_target_dep 1 __qt_QWindowsIntegrationPlugin_is_optional)
    list(GET __qt_QWindowsIntegrationPlugin_target_dep 2 __qt_QWindowsIntegrationPlugin_version)
    list(GET __qt_QWindowsIntegrationPlugin_target_dep 3 __qt_QWindowsIntegrationPlugin_components)
    list(GET __qt_QWindowsIntegrationPlugin_target_dep 4 __qt_QWindowsIntegrationPlugin_optional_components)
    set(__qt_QWindowsIntegrationPlugin_find_package_args "${__qt_QWindowsIntegrationPlugin_pkg}")
    if(__qt_QWindowsIntegrationPlugin_version)
        list(APPEND __qt_QWindowsIntegrationPlugin_find_package_args "${__qt_QWindowsIntegrationPlugin_version}")
    endif()
    if(__qt_QWindowsIntegrationPlugin_components)
        string(REPLACE " " ";" __qt_QWindowsIntegrationPlugin_components "${__qt_QWindowsIntegrationPlugin_components}")
        list(APPEND __qt_QWindowsIntegrationPlugin_find_package_args COMPONENTS ${__qt_QWindowsIntegrationPlugin_components})
    endif()
    if(__qt_QWindowsIntegrationPlugin_optional_components)
        string(REPLACE " " ";" __qt_QWindowsIntegrationPlugin_optional_components "${__qt_QWindowsIntegrationPlugin_optional_components}")
        list(APPEND __qt_QWindowsIntegrationPlugin_find_package_args OPTIONAL_COMPONENTS ${__qt_QWindowsIntegrationPlugin_optional_components})
    endif()

    if(__qt_QWindowsIntegrationPlugin_is_optional)
        if(${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY)
            list(APPEND __qt_QWindowsIntegrationPlugin_find_package_args QUIET)
        endif()
        find_package(${__qt_QWindowsIntegrationPlugin_find_package_args})
    else()
        find_dependency(${__qt_QWindowsIntegrationPlugin_find_package_args})
    endif()
endforeach()

set(__qt_use_no_default_path_for_qt_packages "NO_DEFAULT_PATH")
if(QT_DISABLE_NO_DEFAULT_PATH_IN_QT_PACKAGES)
    set(__qt_use_no_default_path_for_qt_packages "")
endif()

# note: target_deps example: "Qt6Core\;5.12.0;Qt6Gui\;5.12.0"
set(__qt_QWindowsIntegrationPlugin_target_deps "Qt6CorePrivate\;6.2.4;Qt6GuiPrivate\;6.2.4;Qt6Core\;6.2.4;Qt6Gui\;6.2.4;Qt6OpenGLPrivate\;6.2.4")
set(__qt_QWindowsIntegrationPlugin_find_dependency_paths "${CMAKE_CURRENT_LIST_DIR}/..;${_qt_cmake_dir}")
_qt_internal_find_dependencies(__qt_QWindowsIntegrationPlugin_target_deps __qt_QWindowsIntegrationPlugin_find_dependency_paths)

set(QWindowsIntegrationPlugin_FOUND TRUE)
