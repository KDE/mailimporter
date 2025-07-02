########### CMake Config Files ###########

ecm_setup_version(PROJECT VARIABLE_PREFIX MAILIMPORTER
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/mailimporter_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KPim6MailImporterConfigVersion.cmake"
    SOVERSION 6
)

add_library(KPim6MailImporter)
add_library(KPim6::MailImporter ALIAS KPim6MailImporter)

target_sources(
    KPim6MailImporter
    PRIVATE
        importmailswidget.cpp
        filterinfogui.cpp
        importmailswidget.h
        filterinfogui.h
)

target_sources(
    KPim6MailImporter
    PRIVATE
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
        filterinfo.cpp
        filters.cpp
        filterimporterbase.cpp
        othermailerutil.cpp
        selectthunderbirdprofilewidget.cpp
        messagestatus.h
        selectthunderbirdprofilewidget.h
        filters/filterclawsmail.h
        filters/filterseamonkey.h
        filters/filterevolution_v3.h
        filters/filteroe.h
        filters/filtermailapp.h
        filters/filterkmail_maildir.h
        filters/filtericedove.h
        filters/filtermailmangzip.h
        filters/filterpmail.h
        filters/filterthunderbird.h
        filters/filterlnotes.h
        filters/filterevolution_v2.h
        filters/filterkmailarchive.h
        filters/filteropera.h
        filters/filtersylpheed.h
        filters/filterthebat.h
        filters/filterbalsa.h
        filters/filterevolution.h
        filters/filtermbox.h
        filters/filterplain.h
        othermailerutil.h
        mailimporter_utils.h
        filterimporterbase.h
        filters.h
        mailimporter_private_export.h
        filterinfo.h
)

ki18n_wrap_ui(KPim6MailImporter ui/importmailswidget.ui ui/selectthunderbirdprofilewidget.ui)

ecm_qt_declare_logging_category(KPim6MailImporter HEADER mailimporter_debug.h IDENTIFIER MAILIMPORTER_LOG CATEGORY_NAME org.kde.pim.mailimporter
        DESCRIPTION "mailimporter (mailimporter)"
        OLD_CATEGORY_NAMES log_mailimporter
        EXPORT MAILIMPORTER
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        KPim6MailImporter
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
ecm_generate_export_header(KPim6MailImporter
    BASE_NAME mailimporter
    VERSION ${MAILIMPORTER_VERSION}
    DEPRECATED_BASE_VERSION 0
    USE_VERSION_HEADER
)
target_include_directories(
    KPim6MailImporter
    INTERFACE
        "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/KPim6/MailImporter/>"
)
target_include_directories(
    KPim6MailImporter
    PUBLIC
        "$<BUILD_INTERFACE:${MailImporter_SOURCE_DIR}/src;${MailImporter_BINARY_DIR}/src;>"
)

target_link_libraries(
    KPim6MailImporter
    PUBLIC
        KF6::Archive
    PRIVATE
        KPim6::PimCommon
        KF6::I18n
        KF6::ConfigCore
        Qt::Xml
        Qt::Widgets
)

set_target_properties(
    KPim6MailImporter
    PROPERTIES
        VERSION
            ${MAILIMPORTER_VERSION}
        SOVERSION
            ${MAILIMPORTER_SOVERSION}
        EXPORT_NAME
            MailImporter
)

install(TARGETS KPim6MailImporter EXPORT KPim6MailImporterTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

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

install(
    FILES
        ${MailImporter_CamelCase_HEADERS}
        ${MailImporter_FiltersCamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/MailImporter/MailImporter
    COMPONENT Devel
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/mailimporter_export.h
        ${MailImporter_HEADERS}
        ${MailImporter_Filters_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/MailImporter/mailimporter
    COMPONENT Devel
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

if(BUILD_QCH)
    ecm_add_qch(
        KPim6MailImporter_QCH
        NAME KMailImporter
        BASE_NAME KPim6MailImporter
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
            ${MailImporter_HEADERS}
            ${MailImporter_Filters_HEADERS}
        #MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        #IMAGE_DIRS "${CMAKE_SOURCE_DIR}/docs/pics"
        LINK_QCHS
            Qt6Core_QCH
            Qt6Gui_QCH
            Qt6Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            MAILIMPORTER_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KPim6MailImporter")

if(BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KPim6MailImporter_QCH
        FILE KPim6MailImporterQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KPim6MailImporterQchTargets.cmake\")")
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KPimMailImporterConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6MailImporterConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/KPim6MailImporterConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/KPim6MailImporterConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(
    EXPORT KPim6MailImporterTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KPim6MailImporterTargets.cmake
    NAMESPACE KPim6::
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/mailimporter_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/MailImporter
    COMPONENT Devel
)
