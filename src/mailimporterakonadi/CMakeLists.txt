########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR
    "${KDE_INSTALL_CMAKEPACKAGEDIR}/KPim6MailImporterAkonadi"
)

ecm_setup_version(PROJECT VARIABLE_PREFIX MAILIMPORTERAKONADI
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/mailimporterakonadi_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KPim6MailImporterAkonadiConfigVersion.cmake"
    SOVERSION 6
)

add_library(KPim6MailImporterAkonadi)
add_library(KPim6::MailImporterAkonadi ALIAS KPim6MailImporterAkonadi)

target_sources(
    KPim6MailImporterAkonadi
    PRIVATE filterimporterakonadi.cpp filterimporterakonadi.h
)

ecm_qt_declare_logging_category(KPim6MailImporterAkonadi HEADER mailimporterakonadi_debug.h IDENTIFIER MAILIMPORTERAKONADI_LOG CATEGORY_NAME org.kde.pim.mailimporterakonadi
        DESCRIPTION "mailimporterakonadi (mailimporter)"
        EXPORT MAILIMPORTER
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KPim6MailImporterAkonadi PROPERTIES UNITY_BUILD ON)
endif()

ecm_generate_export_header(KPim6MailImporterAkonadi
    BASE_NAME mailimporterakonadi
    VERSION ${MAILIMPORTERAKONADI_VERSION}
    DEPRECATED_BASE_VERSION 0
    USE_VERSION_HEADER
)

target_include_directories(
    KPim6MailImporterAkonadi
    INTERFACE
        "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/KPim6/MailImporterAkonadi/>"
)
target_include_directories(
    KPim6MailImporterAkonadi
    PUBLIC
        "$<BUILD_INTERFACE:${MailImporter_SOURCE_DIR}/src;${MailImporter_BINARY_DIR}/src;>"
)

target_link_libraries(
    KPim6MailImporterAkonadi
    PUBLIC KPim6::MailImporter KPim6::AkonadiCore
    PRIVATE KPim6::Mime KPim6::AkonadiMime KF6::I18n
)

set_target_properties(
    KPim6MailImporterAkonadi
    PROPERTIES
        VERSION ${MAILIMPORTERAKONADI_VERSION}
        SOVERSION ${MAILIMPORTERAKONADI_SOVERSION}
        EXPORT_NAME MailImporterAkonadi
)

install(
    TARGETS KPim6MailImporterAkonadi
    EXPORT KPim6MailImporterAkonadiTargets
    ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
)

ecm_generate_headers(MailImporter_AkonadiCamelCase_HEADERS
    HEADER_NAMES
    FilterImporterAkonadi
    REQUIRED_HEADERS MailImporter_Akonadi_HEADERS
    PREFIX MailImporterAkonadi
)

install(
    FILES ${MailImporter_AkonadiCamelCase_HEADERS}
    DESTINATION
        ${KDE_INSTALL_INCLUDEDIR}/KPim6/MailImporterAkonadi/MailImporterAkonadi
    COMPONENT Devel
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/mailimporterakonadi_export.h
        ${MailImporter_Akonadi_HEADERS}
    DESTINATION
        ${KDE_INSTALL_INCLUDEDIR}/KPim6/MailImporterAkonadi/mailimporterakonadi
    COMPONENT Devel
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

if(BUILD_QCH)
    ecm_add_qch(
        KPim6MailImporterAkonadi_QCH
        NAME KPim6MailImporterAkonadi
        BASE_NAME KPim6MailImporterAkonadi
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
            ${MailImporter_Akonadi_HEADERS}
        #MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        #IMAGE_DIRS "${CMAKE_SOURCE_DIR}/docs/pics"
        LINK_QCHS
            Qt6Core_QCH
            Qt6Gui_QCH
            Qt6Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            MAILIMPORTERAKONADI_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()

if(BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KPim6MailImporterAkonadi_QCH
        FILE KPim6MailImporterAkonadiQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS
        "include(\"\${CMAKE_CURRENT_LIST_DIR}/KPim6MailImporterAkonadiQchTargets.cmake\")"
    )
endif()
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KPimMailImporterAkonadiConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6MailImporterAkonadiConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/KPim6MailImporterAkonadiConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/KPim6MailImporterAkonadiConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(
    EXPORT KPim6MailImporterAkonadiTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KPim6MailImporterAkonadiTargets.cmake
    NAMESPACE KPim6::
)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/mailimporterakonadi_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/MailImporterAkonadi
    COMPONENT Devel
)
