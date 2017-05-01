cmake_minimum_required(VERSION 3.0)
set(PIM_VERSION "5.5.1")

project(MailImporter VERSION ${PIM_VERSION})

set(KF5_VERSION "5.32.0")
find_package(ECM ${KF5_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
set(LIBRARY_NAMELINK)
include(GenerateExportHeader)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)
include(CMakePackageConfigHelpers)
include(ECMSetupVersion)
include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMQtDeclareLoggingCategory)
include(ECMAddTests)
include(ECMCoverageOption)


set(MAILIMPORTER_LIB ${PIM_VERSION})


set(AKONADIMIME_LIB_VERSION "5.5.1")
set(KDEPIM_LIB_VERSION "5.5.1")
set(QT_REQUIRED_VERSION "5.6.0")
set(KMIME_LIB_VERSION "5.5.1")
set(AKONADI_VERSION "5.5.1")

find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets Test Xml)

find_package(KF5Archive ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5Config ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5CoreAddons ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5I18n ${KF5_VERSION} CONFIG REQUIRED)

find_package(KF5Akonadi ${AKONADI_VERSION} CONFIG REQUIRED)
find_package(KF5Mime ${KMIME_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5AkonadiMime ${AKONADIMIME_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Libkdepim ${KDEPIM_LIB_VERSION} CONFIG REQUIRED)

########### Targets ###########

add_definitions("-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII")
remove_definitions( -DQT_NO_CAST_FROM_BYTEARRAY )
########### CMake Config Files ###########

add_definitions(-DTRANSLATION_DOMAIN=\"libmailimporter\")

if(BUILD_TESTING)
   add_definitions(-DBUILD_TESTING)
endif(BUILD_TESTING)

add_subdirectory(src)

install( FILES mailimporter.renamecategories mailimporter.categories DESTINATION ${KDE_INSTALL_CONFDIR} )

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
