########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5MailImporter")


if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF5MailImporter_QCH
        FILE KF5MailImporteQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF5MailImporterQchTargets.cmake\")")
endif()

add_library(KF5MailImporter)
add_library(KF5::MailImporter ALIAS KF5MailImporter)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KF5MailImporterConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5MailImporterConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )

ecm_setup_version(PROJECT VARIABLE_PREFIX MAILIMPORTER
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/mailimporter_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5MailImporterConfigVersion.cmake"
    SOVERSION 5
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF5MailImporterConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5MailImporterConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KF5MailImporterTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5MailImporterTargets.cmake NAMESPACE KF5::)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/mailimporter_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5} COMPONENT Devel
    )


target_sources(KF5MailImporter PRIVATE
    filters/filteroe.cpp
    filters/filterpmail.cpp
    filters/filterplain.cpp
    filters/filtermbox.cpp
    filters/filterevolution.cpp
    filters/filtermailapp.cpp
    filters/filterevolution_v2.cpp
    filters/filterevolution_v3.cpp
    filters/filteropera.cpp
    filters/filterthunderbird.cpp
    filters/filterkmail_maildir.cpp
    filters/filtersylpheed.cpp
    filters/filterclawsmail.cpp
    filters/filterthebat.cpp
    filters/filterlnotes.cpp
    filters/filterkmailarchive.cpp
    filters/filtermailmangzip.cpp
    filters/filtericedove.cpp
    filters/filterbalsa.cpp
    filters/filterseamonkey.cpp
    messagestatus.cpp
    importmailswidget.cpp
    filterinfogui.cpp
    filterinfo.cpp
    filters.cpp
    filterimporterbase.cpp
    othermailerutil.cpp
    selectthunderbirdprofilewidget.cpp
    )


ki18n_wrap_ui(KF5MailImporter ui/importmailswidget.ui ui/selectthunderbirdprofilewidget.ui)

ecm_qt_declare_logging_category(KF5MailImporter HEADER mailimporter_debug.h IDENTIFIER MAILIMPORTER_LOG CATEGORY_NAME org.kde.pim.mailimporter
        DESCRIPTION "mailimporter (mailimporter)"
        OLD_CATEGORY_NAMES log_mailimporter
        EXPORT MAILIMPORTER
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF5MailImporter PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header( KF5MailImporter BASE_NAME mailimporter)

target_include_directories(KF5MailImporter INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/MailImporter/;${KDE_INSTALL_INCLUDEDIR_KF5}/mailimporter>")
target_include_directories(KF5MailImporter PUBLIC "$<BUILD_INTERFACE:${MailImporter_SOURCE_DIR}/src;${MailImporter_BINARY_DIR}/src;>")


target_link_libraries(KF5MailImporter
    PUBLIC
    KF5::Archive
    PRIVATE
    KF5::PimCommon
    KF5::I18n
    KF5::ConfigCore
    Qt::Xml
    Qt::Widgets
    )

set_target_properties(KF5MailImporter PROPERTIES
    VERSION ${MAILIMPORTER_VERSION}
    SOVERSION ${MAILIMPORTER_SOVERSION}
    EXPORT_NAME MailImporter
    )

install(TARGETS
    KF5MailImporter
    EXPORT KF5MailImporterTargets ${KF5_INSTALL_TARGETS_DEFAULT_ARGS}
    )

ecm_generate_headers(MailImporter_CamelCase_HEADERS
    HEADER_NAMES
    FilterImporterBase
    FilterInfoGui
    OtherMailerUtil
    ImportMailsWidget
    MailImporter_Utils
    Filters
    FilterInfo
    MessageStatus
    REQUIRED_HEADERS MailImporter_HEADERS
    PREFIX MailImporter
    )

ecm_generate_headers(MailImporter_FiltersCamelCase_HEADERS
    HEADER_NAMES
    FilterClawsMail
    FilterBalsa
    FilterSylpheed
    FilterTheBat
    FilterEvolution
    FilterThunderbird
    FilterEvolution_v2
    FilterEvolution_v3
    FilterMailApp
    FilterMailmanGzip
    FilterPlain
    FilterPMail
    FilterMBox
    FilterOpera
    FilterLNotes
    FilterOE
    FilterKMail_maildir
    FilterKMailArchive
    FilterIcedove
    FilterSeaMonkey
    REQUIRED_HEADERS MailImporter_Filters_HEADERS
    PREFIX MailImporter
    RELATIVE filters
    )


ecm_generate_pri_file(BASE_NAME MailImporter
    LIB_NAME KF5MailImporter
    DEPS "KArchive" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF5}/MailImporter
    )


install(FILES
    ${MailImporter_CamelCase_HEADERS}
    ${MailImporter_FiltersCamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/MailImporter
    COMPONENT Devel
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/mailimporter_export.h
    ${MailImporter_HEADERS}
    ${MailImporter_Filters_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/mailimporter
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
        KF5MailImporter_QCH
        NAME KMailImporter
        BASE_NAME KF5MailImporter
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
            ${MailImporter_HEADERS}
            ${MailImporter_Filters_HEADERS}
        #MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        #IMAGE_DIRS "${CMAKE_SOURCE_DIR}/docs/pics"
        LINK_QCHS
            Qt5Core_QCH
            Qt5Gui_QCH
            Qt5Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            MAILIMPORTER_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()
