project(kdeliciousplugin)

find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include_directories(${KDE4_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(kdeliciousplugin_SRCS
	kdeliciousplugin.cpp)

kde4_add_plugin(kdeliciousplugin ${kdeliciousplugin_SRCS})
target_link_libraries(kdeliciousplugin ${KDE4_KDECORE_LIBS} ${KDE4_KDEUI_LIBS} ${KDE4_KHML_LIBS} ${KDE4_KPARTS_LIBS})

install(TARGETS kdeliciousplugin DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES kdeliciousplugin.rc kdeliciousplugin.desktop  DESTINATION  ${DATA_INSTALL_DIR}/khtml/kpartplugins)

