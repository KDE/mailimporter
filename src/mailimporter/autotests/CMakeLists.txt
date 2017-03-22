add_definitions( -DMAILIMPORTER_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/samples/" )

macro(add_mailimporter_unittest _source _additionalSource)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_additionalSource}
        TEST_NAME ${_name}
        NAME_PREFIX "mailimporter-"
        LINK_LIBRARIES KF5::MailImporter Qt5::Test Qt5::Core Qt5::Gui Qt5::Widgets
    )
endmacro ()

add_mailimporter_unittest(filterthunderbirdtest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporter_unittest(filtericedovetest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporter_unittest(filterclawsmailtest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporter_unittest(filtersylpheedtest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporter_unittest(filterlnotestest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporter_unittest(filtermailapptest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")

add_mailimporter_unittest(messagestatustest.cpp "")
add_mailimporter_unittest(selectthunderbirdprofiledialogtest.cpp "")

