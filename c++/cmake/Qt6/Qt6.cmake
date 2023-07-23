
set(Qt6_CMAKE_DIRS      ${CPP_DIR}/lib/Qt6/lib/cmake/)

set(Qt6_DIR "${Qt6_CMAKE_DIRS}/Qt6")
set(Qt6Gui_DIR "${Qt6_CMAKE_DIRS}/Qt6Gui")
set(Qt6Core_DIR "${Qt6_CMAKE_DIRS}/Qt6Core")
set(Qt6Widgets_DIR "${Qt6_CMAKE_DIRS}/Qt6Widgets")
set(Qt6GuiTools_DIR "${Qt6_CMAKE_DIRS}/Qt6GuiTools")
set(Qt6CoreTools_DIR "${Qt6_CMAKE_DIRS}/Qt6CoreTools")
set(Qt6WidgetsTools_DIR "${Qt6_CMAKE_DIRS}/Qt6WidgetsTools")
set(Qt6BundledPcre2_DIR "${Qt6_CMAKE_DIRS}/Qt6BundledPcre2")
set(Qt6BundledHarfbuzz_DIR "${Qt6_CMAKE_DIRS}/Qt6BundledHarfbuzz")

find_package(Qt6
        COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
        PrintSupport
        #        Svg
        Network
        )

link_libraries(
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::PrintSupport
        #            Qt6::Svg
        Qt6::Network
)