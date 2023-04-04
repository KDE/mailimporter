macro(add_mailimporterakonadi_unittest _source _additionalSource)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_additionalSource} ${_name}.h
        TEST_NAME ${_name}-akonadi
        NAME_PREFIX "mailimporterakonadi-"
        LINK_LIBRARIES KPim6::MailImporterAkonadi Qt::Test Qt::Core Qt::Gui Qt::Widgets
    )
endmacro ()

add_mailimporterakonadi_unittest(filterimporterakonaditest.cpp "")
add_mailimporterakonadi_unittest(filterthunderbirdtest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporterakonadi_unittest(filtericedovetest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporterakonadi_unittest(filterclawsmailtest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporterakonadi_unittest(filtersylpheedtest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporterakonadi_unittest(filterlnotestest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporterakonadi_unittest(filtermailapptest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporterakonadi_unittest(filterthebattest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporterakonadi_unittest(filtermboxtest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporterakonadi_unittest(filterbalsamailtest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporterakonadi_unittest(filterplaintest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")
add_mailimporterakonadi_unittest(filtermailmangziptest.cpp "filterimportertest.cpp;filterimportertestutil.cpp")

