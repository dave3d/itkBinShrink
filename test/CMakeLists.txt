itk_module_test()

#${itk-module} will be the name of this module and will not need to be
#changed when this module is renamed.

set(ITK${itk-module}Tests
  itkBinShrinkExample.cxx
  itkBinShrinkImageFilterTest1.cxx
  itkBinShrinkImageFilterTest2.cxx
)

CreateTestDriver(${itk-module}  "${${itk-module}-Test_LIBRARIES}" "${ITK${itk-module}Tests}")

itk_add_test(NAME itkBinShrinkImageFilterTest1
  COMMAND ${itk-module}TestDriver  itkBinShrinkImageFilterTest1 )


itk_add_test(NAME itkBinShrinkImageFilter2Test1
  COMMAND ${itk-module}TestDriver  itkBinShrinkImageFilter2Test1 )

itk_add_test(NAME itkBinShrinkImageFilterTest2
  COMMAND ${itk-module}TestDriver  itkBinShrinkImageFilterTest2 )
