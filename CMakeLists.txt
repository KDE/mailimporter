
cmake_minimum_required(VERSION 2.8.12)

project(MailImporter)

set(KF5_VERSION "5.23.0")
find_package(ECM ${KF5_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
set(LIBRARY_NAMELINK)
include(GenerateExportHeader)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)
include(ECMPackageConfigHelpers)
include(ECMSetupVersion)
include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMQtDeclareLoggingCategory)
include(ECMAddTests)

set(PIM_VERSION "5.3.1")
set(MAILIMPORTER_LIB ${PIM_VERSION})


set(AKONADIMIME_LIB_VERSION "5.3.0")
set(KDEPIM_LIB_VERSION "5.3.0")
set(QT_REQUIRED_VERSION "5.5.0")
set(KMIME_LIB_VERSION "5.3.0")
set(AKONADI_VERSION "5.3.0")

find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets Test Xml)

find_package(KF5Archive ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5Config ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5CoreAddons ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5I18n ${KF5_VERSION} CONFIG REQUIRED)

find_package(KF5Akonadi ${AKONADI_VERSION} CONFIG REQUIRED)
find_package(KF5Mime ${KMIME_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5AkonadiMime ${AKONADIMIME_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Libkdepim ${KDEPIM_LIB_VERSION} CONFIG REQUIRED)

ecm_setup_version(${MAILIMPORTER_LIB} VARIABLE_PREFIX MAILIMPORTER
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/mailimporter_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5MailImporterConfigVersion.cmake"
                        SOVERSION 5
)

########### Targets ###########

add_definitions("-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII")
remove_definitions( -DQT_NO_CAST_FROM_BYTEARRAY )
########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5MailImporter")

ecm_configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KF5MailImporterConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5MailImporterConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
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


add_definitions(-DTRANSLATION_DOMAIN=\"libmailimporter\")
add_subdirectory(src)
if (BUILD_TESTING)
   add_subdirectory(autotests)
endif()

install( FILES mailimporter.categories DESTINATION ${KDE_INSTALL_CONFDIR} )

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
