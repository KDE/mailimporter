########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KPim${KF_MAJOR_VERSION}MailImporter")
set(MAILIMPORTER_KF5_COMPAT FALSE)

if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KPim${KF_MAJOR_VERSION}MailImporter_QCH
        FILE KPim${KF_MAJOR_VERSION}MailImporteQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KPim${KF_MAJOR_VERSION}MailImporterQchTargets.cmake\")")
endif()

add_library(KPim${KF_MAJOR_VERSION}MailImporter)
add_library(KPim${KF_MAJOR_VERSION}::MailImporter ALIAS KPim${KF_MAJOR_VERSION}MailImporter)
add_library(KF5::MailImporter ALIAS KPim${KF_MAJOR_VERSION}MailImporter)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KPimMailImporterConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}MailImporterConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )

ecm_setup_version(PROJECT VARIABLE_PREFIX MAILIMPORTER
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/mailimporter_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}MailImporterConfigVersion.cmake"
    SOVERSION 5
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}MailImporterConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}MailImporterConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KPim${KF_MAJOR_VERSION}MailImporterTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KPim${KF_MAJOR_VERSION}MailImporterTargets.cmake NAMESPACE KPim${KF_MAJOR_VERSION}::)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/mailimporter_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/MailImporter COMPONENT Devel
    )


target_sources(KPim${KF_MAJOR_VERSION}MailImporter PRIVATE
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
    filterinfogui.h
    othermailerutil.h
    mailimporter_utils.h
    importmailswidget.h
    filterimporterbase.h
    filters.h
    mailimporter_private_export.h
    filterinfo.h
    )


ki18n_wrap_ui(KPim${KF_MAJOR_VERSION}MailImporter ui/importmailswidget.ui ui/selectthunderbirdprofilewidget.ui)

ecm_qt_declare_logging_category(KPim${KF_MAJOR_VERSION}MailImporter HEADER mailimporter_debug.h IDENTIFIER MAILIMPORTER_LOG CATEGORY_NAME org.kde.pim.mailimporter
        DESCRIPTION "mailimporter (mailimporter)"
        OLD_CATEGORY_NAMES log_mailimporter
        EXPORT MAILIMPORTER
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KPim${KF_MAJOR_VERSION}MailImporter PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header( KPim${KF_MAJOR_VERSION}MailImporter BASE_NAME mailimporter)

target_include_directories(KPim${KF_MAJOR_VERSION}MailImporter INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/MailImporter/>")
target_include_directories(KPim${KF_MAJOR_VERSION}MailImporter PUBLIC "$<BUILD_INTERFACE:${MailImporter_SOURCE_DIR}/src;${MailImporter_BINARY_DIR}/src;>")


target_link_libraries(KPim${KF_MAJOR_VERSION}MailImporter
    PUBLIC
    KF${KF_MAJOR_VERSION}::Archive
    PRIVATE
    KF5::PimCommon
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::ConfigCore
    Qt::Xml
    Qt::Widgets
    )

set_target_properties(KPim${KF_MAJOR_VERSION}MailImporter PROPERTIES
    VERSION ${MAILIMPORTER_VERSION}
    SOVERSION ${MAILIMPORTER_SOVERSION}
    EXPORT_NAME MailImporter
    )

install(TARGETS
    KPim${KF_MAJOR_VERSION}MailImporter
    EXPORT KPim${KF_MAJOR_VERSION}MailImporterTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
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
    LIB_NAME KPim${KF_MAJOR_VERSION}MailImporter
    DEPS "KArchive" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/MailImporter
    )


install(FILES
    ${MailImporter_CamelCase_HEADERS}
    ${MailImporter_FiltersCamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/MailImporter/MailImporter
    COMPONENT Devel
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/mailimporter_export.h
    ${MailImporter_HEADERS}
    ${MailImporter_Filters_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/MailImporter/mailimporter
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
        KPim${KF_MAJOR_VERSION}MailImporter_QCH
        NAME KMailImporter
        BASE_NAME KPim${KF_MAJOR_VERSION}MailImporter
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
            ${MailImporter_HEADERS}
            ${MailImporter_Filters_HEADERS}
        #MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        #IMAGE_DIRS "${CMAKE_SOURCE_DIR}/docs/pics"
        LINK_QCHS
            Qt${QT_MAJOR_VERSION}Core_QCH
            Qt${QT_MAJOR_VERSION}Gui_QCH
            Qt${QT_MAJOR_VERSION}Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            MAILIMPORTER_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()

if (QT_MAJOR_VERSION STREQUAL "5")
##
# TODO: Backwards compatiblity. Remove in next major version
##
set(CMAKECONFIG_INSTALL_DIR_KF5 "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5MailImporter")
set(MAILIMPORTER_KF5_COMPAT TRUE)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KPimMailImporterConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5MailImporterConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR_KF5}
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF5MailImporterConfig.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR_KF5}"
    COMPONENT Devel
)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}MailImporterConfigVersion.cmake"
    RENAME "KF5MailImporterConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR_KF5}"
    COMPONENT Devel
)
if (0)
install(EXPORT KPim${KF_MAJOR_VERSION}MailImporterTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR_KF5}"
    FILE KPim${KF_MAJOR_VERSION}MailImporterTargets.cmake
    NAMESPACE KF5::
)
endif()
endif()
