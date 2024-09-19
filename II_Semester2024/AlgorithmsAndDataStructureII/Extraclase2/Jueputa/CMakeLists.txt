cmake_minimum_required(VERSION 3.16)

# Definir el nombre del proyecto y su versión
project(ExtraclaseII VERSION 0.1 LANGUAGES CXX)

# Activar funcionalidades automáticas de Qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar paquetes de Qt necesarios
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts)

# Definir los archivos fuente
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    Sorters.h
    Sorters.cpp
    measuretime.h
    measuretime.cpp
)

# Definir el ejecutable según la versión de Qt
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ExtraclaseII
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(ExtraclaseII
        ${PROJECT_SOURCES}
    )
endif()

# Enlazar las bibliotecas de Qt necesarias
target_link_libraries(ExtraclaseII PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)

# Configuración adicional para macOS o Windows si es necesario
set_target_properties(ExtraclaseII PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Incluir la configuración de instalación
include(GNUInstallDirs)
install(TARGETS ExtraclaseII
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalizar el ejecutable en Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ExtraclaseII)
endif()
