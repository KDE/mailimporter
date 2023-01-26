########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5MailImporterAkonadi")
if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF5MailImporterAkonadi_QCH
        FILE KF5MailImporterAkonadiQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF5MailImporterAkonadiQchTargets.cmake\")")
endif()

add_library(KF5MailImporterAkonadi)
add_library(KF5::MailImporterAkonadi ALIAS KF5MailImporterAkonadi)
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
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/MailImporterAkonadi COMPONENT Devel
    )

target_sources(KF5MailImporterAkonadi PRIVATE
    filterimporterakonadi.cpp
    filterimporterakonadi.h
    filterimportertestutil.h
    )

ecm_qt_declare_logging_category(KF5MailImporterAkonadi HEADER mailimporterakonadi_debug.h IDENTIFIER MAILIMPORTERAKONADI_LOG CATEGORY_NAME org.kde.pim.mailimporterakonadi
        DESCRIPTION "mailimporterakonadi (mailimporter)"
        EXPORT MAILIMPORTER
    )



if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF5MailImporterAkonadi PROPERTIES UNITY_BUILD ON)
endif()

generate_export_header( KF5MailImporterAkonadi BASE_NAME mailimporterakonadi)

add_library(KF5::MailImporterAkonadi ALIAS KF5MailImporterAkonadi)

target_include_directories(KF5MailImporterAkonadi INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/MailImporterAkonadi/>")
target_include_directories(KF5MailImporterAkonadi PUBLIC "$<BUILD_INTERFACE:${MailImporter_SOURCE_DIR}/src;${MailImporter_BINARY_DIR}/src;>")


target_link_libraries(KF5MailImporterAkonadi
    PUBLIC
    KF5::MailImporter
    KF5::AkonadiCore
    PRIVATE
    KF5::Mime
    KF5::AkonadiMime
    KF${KF_MAJOR_VERSION}::I18n
    )

set_target_properties(KF5MailImporterAkonadi PROPERTIES
    VERSION ${MAILIMPORTER_VERSION}
    SOVERSION ${MAILIMPORTER_SOVERSION}
    EXPORT_NAME MailImporterAkonadi
    )

install(TARGETS
    KF5MailImporterAkonadi
    EXPORT KF5MailImporterAkonadiTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS}
    )


ecm_generate_headers(MailImporter_AkonadiCamelCase_HEADERS
    HEADER_NAMES
    FilterImporterAkonadi
    REQUIRED_HEADERS MailImporter_Akonadi_HEADERS
    PREFIX MailImporterAkonadi
    )


ecm_generate_pri_file(BASE_NAME MailImporterAkonadi
    LIB_NAME KF5MailImporterAkonadi
    DEPS "MailImporter AkonadiCore" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF}/MailImporterAkonadi
    )


install(FILES
    ${MailImporter_AkonadiCamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/MailImporterAkonadi/MailImporterAkonadi
    COMPONENT Devel
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/mailimporterakonadi_export.h
    ${MailImporter_Akonadi_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/MailImporterAkonadi/mailimporterakonadi
    COMPONENT Devel
    )
install(FILES
    ${PRI_FILENAME}
    DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

if (BUILD_TESTING)
   add_subdirectory(autotests)
endif()


if (BUILD_QCH)
    ecm_add_qch(
        KF5MailImporterAkonadi_QCH
        NAME KF5MailImporterAkonadi
        BASE_NAME KF5MailImporterAkonadi
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
            ${MailImporter_Akonadi_HEADERS}
        #MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        #IMAGE_DIRS "${CMAKE_SOURCE_DIR}/docs/pics"
        LINK_QCHS
            Qt${QT_MAJOR_VERSION}Core_QCH
            Qt${QT_MAJOR_VERSION}Gui_QCH
            Qt${QT_MAJOR_VERSION}Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            MAILIMPORTERAKONADI_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()
