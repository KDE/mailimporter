add_definitions( -DMAILIMPORTER_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/samples/" )

macro(add_mailimporter_unittest _source _additionalSource)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_additionalSource} ${_name}.h
        TEST_NAME ${_name}
        NAME_PREFIX "mailimporter-"
        LINK_LIBRARIES KPim${KF_MAJOR_VERSION}::MailImporter Qt::Test Qt::Core Qt::Gui Qt::Widgets
    )
endmacro ()

add_mailimporter_unittest(filterthunderbirdtest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporter_unittest(filtericedovetest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporter_unittest(filterclawsmailtest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporter_unittest(filtersylpheedtest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporter_unittest(filterlnotestest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporter_unittest(filtermailapptest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporter_unittest(filterthebattest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporter_unittest(filtermboxtest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporter_unittest(filterbalsamailtest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporter_unittest(filterplaintest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporter_unittest(filtermailmangziptest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")

add_mailimporter_unittest(messagestatustest.cpp "")
add_mailimporter_unittest(selectthunderbirdprofiledialogtest.cpp "")

