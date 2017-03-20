macro(add_mailimporter_unittest _source _additionalSource)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_additionalSource}
        TEST_NAME ${_name}
        NAME_PREFIX "mailimporter-"
        LINK_LIBRARIES KF5::MailImporter Qt5::Test Qt5::Core Qt5::Gui Qt5::Widgets
    )
endmacro ()

add_mailimporter_unittest(filterthunderbirdtest.cpp "filterimportertest.cpp")
add_mailimporter_unittest(filtericedovetest.cpp "filterimportertest.cpp")
add_mailimporter_unittest(filterclawsmailtest.cpp "filterimportertest.cpp")
add_mailimporter_unittest(filtersylpheedtest.cpp "filterimportertest.cpp")

add_mailimporter_unittest(messagestatustest.cpp "")
add_mailimporter_unittest(selectthunderbirdprofiledialogtest.cpp "")

