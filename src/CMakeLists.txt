include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(kdelicious_SRCS kdelicious.cpp main.cpp)
qt4_automoc(${kdelicious_SRCS})
add_executable(kdelicious ${kdelicious_SRCS})
target_link_libraries(kdelicious ${QT_QTCORE_LIBRARY})
