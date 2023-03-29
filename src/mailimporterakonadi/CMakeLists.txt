########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KPim${KF_MAJOR_VERSION}MailImporterAkonadi")

ecm_setup_version(PROJECT VARIABLE_PREFIX MAILIMPORTER
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/mailimporterakonadi_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}MailImporterAkonadiConfigVersion.cmake"
    SOVERSION 5
    )

add_library(KPim${KF_MAJOR_VERSION}MailImporterAkonadi)
add_library(KPim${KF_MAJOR_VERSION}::MailImporterAkonadi ALIAS KPim${KF_MAJOR_VERSION}MailImporterAkonadi)


target_sources(KPim${KF_MAJOR_VERSION}MailImporterAkonadi PRIVATE
    filterimporterakonadi.cpp
    filterimporterakonadi.h
    )

ecm_qt_declare_logging_category(KPim${KF_MAJOR_VERSION}MailImporterAkonadi HEADER mailimporterakonadi_debug.h IDENTIFIER MAILIMPORTERAKONADI_LOG CATEGORY_NAME org.kde.pim.mailimporterakonadi
        DESCRIPTION "mailimporterakonadi (mailimporter)"
        EXPORT MAILIMPORTER
    )



if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KPim${KF_MAJOR_VERSION}MailImporterAkonadi PROPERTIES UNITY_BUILD ON)
endif()

generate_export_header( KPim${KF_MAJOR_VERSION}MailImporterAkonadi BASE_NAME mailimporterakonadi)

target_include_directories(KPim${KF_MAJOR_VERSION}MailImporterAkonadi INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/MailImporterAkonadi/>")
target_include_directories(KPim${KF_MAJOR_VERSION}MailImporterAkonadi PUBLIC "$<BUILD_INTERFACE:${MailImporter_SOURCE_DIR}/src;${MailImporter_BINARY_DIR}/src;>")


target_link_libraries(KPim${KF_MAJOR_VERSION}MailImporterAkonadi
    PUBLIC
    KPim${KF_MAJOR_VERSION}::MailImporter
    KPim${KF_MAJOR_VERSION}::AkonadiCore
    PRIVATE
    KPim${KF_MAJOR_VERSION}::Mime
    KPim${KF_MAJOR_VERSION}::AkonadiMime
    KF${KF_MAJOR_VERSION}::I18n
    )

set_target_properties(KPim${KF_MAJOR_VERSION}MailImporterAkonadi PROPERTIES
    VERSION ${MAILIMPORTER_VERSION}
    SOVERSION ${MAILIMPORTER_SOVERSION}
    EXPORT_NAME MailImporterAkonadi
    )

install(TARGETS
    KPim${KF_MAJOR_VERSION}MailImporterAkonadi
    EXPORT KPim${KF_MAJOR_VERSION}MailImporterAkonadiTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    )


ecm_generate_headers(MailImporter_AkonadiCamelCase_HEADERS
    HEADER_NAMES
    FilterImporterAkonadi
    REQUIRED_HEADERS MailImporter_Akonadi_HEADERS
    PREFIX MailImporterAkonadi
    )


ecm_generate_pri_file(BASE_NAME MailImporterAkonadi
    LIB_NAME KPim${KF_MAJOR_VERSION}MailImporterAkonadi
    DEPS "MailImporter AkonadiCore" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/MailImporterAkonadi
    )


install(FILES
    ${MailImporter_AkonadiCamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/MailImporterAkonadi/MailImporterAkonadi
    COMPONENT Devel
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/mailimporterakonadi_export.h
    ${MailImporter_Akonadi_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/MailImporterAkonadi/mailimporterakonadi
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
        KPim${KF_MAJOR_VERSION}MailImporterAkonadi_QCH
        NAME KPim${KF_MAJOR_VERSION}MailImporterAkonadi
        BASE_NAME KPim${KF_MAJOR_VERSION}MailImporterAkonadi
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


if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KPim${KF_MAJOR_VERSION}MailImporterAkonadi_QCH
        FILE KPim${KF_MAJOR_VERSION}MailImporterAkonadiQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KPim${KF_MAJOR_VERSION}MailImporterAkonadiQchTargets.cmake\")")
endif()
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KPimMailImporterAkonadiConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}MailImporterAkonadiConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )



install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}MailImporterAkonadiConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}MailImporterAkonadiConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KPim${KF_MAJOR_VERSION}MailImporterAkonadiTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KPim${KF_MAJOR_VERSION}MailImporterAkonadiTargets.cmake NAMESPACE KPim${KF_MAJOR_VERSION}::)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/mailimporterakonadi_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/MailImporterAkonadi COMPONENT Devel
    )
