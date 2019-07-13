cmake_minimum_required(VERSION 3.5)
set(PIM_VERSION "5.11.80")

project(MailImporter VERSION ${PIM_VERSION})

set(KF5_MIN_VERSION "5.60.0")

find_package(ECM ${KF5_MIN_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
set(LIBRARY_NAMELINK)
include(GenerateExportHeader)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)

include(ECMSetupVersion)
include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMQtDeclareLoggingCategory)
include(ECMAddTests)



set(MAILIMPORTER_LIB ${PIM_VERSION})


set(AKONADIMIME_LIB_VERSION "5.11.40")
set(KDEPIM_LIB_VERSION "5.11.40")
set(QT_REQUIRED_VERSION "5.11.0")
set(KMIME_LIB_VERSION "5.11.40")
set(AKONADI_VERSION "5.11.40")

find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets Test Xml)

find_package(KF5Archive ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Config ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5CoreAddons ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5I18n ${KF5_MIN_VERSION} CONFIG REQUIRED)

find_package(KF5Akonadi ${AKONADI_VERSION} CONFIG REQUIRED)
find_package(KF5Mime ${KMIME_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5AkonadiMime ${AKONADIMIME_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Libkdepim ${KDEPIM_LIB_VERSION} CONFIG REQUIRED)

########### Targets ###########


add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x060000)

########### CMake Config Files ###########

add_definitions(-DTRANSLATION_DOMAIN=\"libmailimporter\")

if(BUILD_TESTING)
   add_definitions(-DBUILD_TESTING)
endif()
add_definitions(-DQT_NO_FOREACH)

add_subdirectory(src)

install(FILES mailimporter.renamecategories mailimporter.categories  DESTINATION  ${KDE_INSTALL_LOGGINGCATEGORIESDIR})

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
