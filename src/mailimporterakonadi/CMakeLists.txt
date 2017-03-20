########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5MailImporterAkonadi")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KF5MailImporterAkonadiConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5MailImporterAkonadiConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )

ecm_setup_version(PROJECT VARIABLE_PREFIX MAILIMPORTER
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/mailimporterakonadi_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5MailImporterAkonadiConfigVersion.cmake"
    SOVERSION 5
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF5MailImporterAkonadiConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5MailImporterAkonadiConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KF5MailImporterAkonadiTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5MailImporterAkonadiTargets.cmake NAMESPACE KF5::)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/mailimporterakonadi_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5} COMPONENT Devel
    )

set(libmailimporterakonadi_SRCS
    filterimporterakonadi.cpp
    )

ecm_qt_declare_logging_category(libmailimporterakonadi_SRCS HEADER mailimporterakonadi_debug.h IDENTIFIER MAILIMPORTERAKONADI_LOG CATEGORY_NAME org.kde.pim.mailimporterakonadi)

add_library(KF5MailImporterAkonadi
    ${libmailimporterakonadi_SRCS}
    )

generate_export_header( KF5MailImporterAkonadi BASE_NAME mailimporterakonadi)

add_library(KF5::MailImporterAkonadi ALIAS KF5MailImporterAkonadi)

target_include_directories(KF5MailImporterAkonadi INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/MailImporterAkonadi/;${KDE_INSTALL_INCLUDEDIR_KF5}/mailimporterakonadi>")
target_include_directories(KF5MailImporterAkonadi PUBLIC "$<BUILD_INTERFACE:${MailImporter_SOURCE_DIR}/src;${MailImporter_BINARY_DIR}/src;>")


target_link_libraries(KF5MailImporterAkonadi
    PUBLIC
    KF5::MailImporter
    KF5::AkonadiCore
    PRIVATE
    KF5::AkonadiMime
    KF5::I18n
    )

set_target_properties(KF5MailImporterAkonadi PROPERTIES
    VERSION ${MAILIMPORTER_VERSION_STRING}
    SOVERSION ${MAILIMPORTER_SOVERSION}
    EXPORT_NAME MailImporterAkonadi
    )

install(TARGETS
    KF5MailImporterAkonadi
    EXPORT KF5MailImporterAkonadiTargets ${KF5_INSTALL_TARGETS_DEFAULT_ARGS} ${LIBRARY_NAMELINK}
    )


ecm_generate_headers(MailImporter_AkonadiCamelCase_HEADERS
    HEADER_NAMES
    FilterImporterAkonadi
    REQUIRED_HEADERS MailImporter_Akonadi_HEADERS
    PREFIX MailImporterAkonadi
    )


ecm_generate_pri_file(BASE_NAME MailImporterAkonadi
    LIB_NAME KF5MailImporterAkonadi
    DEPS "MailImporter AkonadiCore" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF5}/MailImporterAkonadi
    )


install(FILES
    ${MailImporter_AkonadiCamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/MailImporterAkonadi
    COMPONENT Devel
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/mailimporterakonadi_export.h
    ${MailImporter_Akonadi_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/mailimporterakonadi
    COMPONENT Devel
    )
install(FILES
    ${PRI_FILENAME}
    DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

if (BUILD_TESTING)
   add_subdirectory(autotests)
endif()

