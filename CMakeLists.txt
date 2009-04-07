project(kdelicious)
cmake_minimum_required(VERSION 2.6)
find_package(KDE4 REQUIRED)

include(KDE4Defaults)
include_directories(${KDE4_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${KDE4_KHTML_INCLUDES})
 
set(kdelicious_SRCS
  kdeliciousplugin.cpp
  createbookmarkdialog.cpp
  request.cpp
  browser.cpp
  bookmark.cpp
  bookmarkrequest.cpp
  postrequest.cpp)

set(kdelicious_UI
  newbookmarkwidget.ui)

kde4_add_ui_files(kdelicious_SRCS ${kdelicious_UI})
kde4_add_plugin(kdelicious ${kdelicious_SRCS})

target_link_libraries(kdelicious ${KDE4_KDECORE_LIBS} ${KDE4_KDEUI_LIBS} ${KDE4_KHTML_LIBS} ${KDE4_KPARTS_LIBS})
 
install(TARGETS kdelicious DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES plugin_kdelicious.rc plugin_kdelicious.desktop  DESTINATION  ${DATA_INSTALL_DIR}/khtml/kpartplugins)

