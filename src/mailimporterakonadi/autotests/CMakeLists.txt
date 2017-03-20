macro(add_mailimporterakonadi_unittest _source _additionalSource)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_additionalSource}
        TEST_NAME ${_name}
        NAME_PREFIX "mailimporterakonadi-"
	LINK_LIBRARIES KF5::MailImporterAkonadi Qt5::Test Qt5::Core Qt5::Gui Qt5::Widgets
    )
endmacro ()

add_mailimporter_unittest(filterimporterakonaditest.cpp "")

