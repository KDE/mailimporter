cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(PIM_VERSION "5.240.40")

project(MailImporter VERSION ${PIM_VERSION})

set(KF_MIN_VERSION "5.240.0")
set(QT_REQUIRED_VERSION "6.4.0")

find_package(ECM ${KF_MIN_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

include(ECMGenerateExportHeader)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)

include(FeatureSummary)
include(KDEGitCommitHooks)
include(KDEClangFormat)
file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES *.cpp *.h *.c)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})

include(ECMQtDeclareLoggingCategory)
include(ECMDeprecationSettings)
include(ECMAddTests)

set(MAILIMPORTER_LIB ${PIM_VERSION})
include(ECMAddQch)


option(BUILD_QCH "Build API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)" OFF)
add_feature_info(QCH ${BUILD_QCH} "API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)")


set(AKONADIMIME_LIB_VERSION "5.240.40")
set(KMIME_LIB_VERSION "5.240.40")
set(AKONADI_VERSION "5.240.40")
set(PIMCOMMON_LIB_VERSION "5.240.40")

find_package(Qt6 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets Test Xml)

find_package(KF6KIO ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6Archive ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6Config ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6CoreAddons ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6I18n ${KF_MIN_VERSION} CONFIG REQUIRED)

find_package(KPim6Akonadi ${AKONADI_VERSION} CONFIG REQUIRED)
find_package(KPim6Mime ${KMIME_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6AkonadiMime ${AKONADIMIME_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6PimCommon ${PIMCOMMON_LIB_VERSION} CONFIG REQUIRED)
########### Targets ###########


ecm_set_disabled_deprecation_versions(QT 6.5  KF 5.240.0)


########### CMake Config Files ###########

add_definitions(-DTRANSLATION_DOMAIN=\"libmailimporter\")

if(BUILD_TESTING)
   add_definitions(-DBUILD_TESTING)
endif()

option(USE_UNITY_CMAKE_SUPPORT "Use UNITY cmake support (speedup compile time)" OFF)

set(COMPILE_WITH_UNITY_CMAKE_SUPPORT OFF)
if (USE_UNITY_CMAKE_SUPPORT)
    set(COMPILE_WITH_UNITY_CMAKE_SUPPORT ON)
endif()

add_subdirectory(src)

ecm_qt_install_logging_categories(
        EXPORT MAILIMPORTER
        FILE mailimporter.categories
        DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR}
        )

kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)

ki18n_install(po)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
