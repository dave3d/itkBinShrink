#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "itkBinShrinkImageFilter.h"
#include "itkBinShrinkImageFilter2.h"

#define itkBinShrinkImageFilterTest1 itkBinShrinkImageFilter2Test1
#define BinShrinkImageFilter BinShrinkImageFilter2

#include "itkBinShrinkImageFilterTest1.cxx"
#if 0
int itkBinShrinkImageFilterTest1( int , char *[] )
{

   // typedefs to simplify the syntax
  typedef itk::Image<int, 2>   ImageType;
  ImageType::Pointer sourceImage = ImageType::New();


  typedef itk::PipelineMonitorImageFilter<ImageType> MonitorFilter;

  // fill in an image
  ImageType::IndexType  index = {{100, 100}};
  ImageType::SizeType   size = {{12, 20}};
  ImageType::RegionType region;
  region.SetSize( size );
  region.SetIndex( index );
  sourceImage->SetRegions( region );
  sourceImage->Allocate();


  itk::ImageRegionIteratorWithIndex<ImageType> outIt(sourceImage, region);
  for ( outIt.GoToBegin(); !outIt.IsAtEnd(); ++outIt )
    {
    // we multiply by ten so for more precision
    outIt.Set( outIt.GetIndex()[0]*10 );
    }



  // assemple pipeline
  MonitorFilter::Pointer monitor1 = MonitorFilter::New();
  monitor1->SetInput( sourceImage );

  itk::BinShrinkImageFilter< ImageType, ImageType >::Pointer bin;
  bin = itk::BinShrinkImageFilter< ImageType, ImageType >::New();
  bin->SetInput( monitor1->GetOutput() );


  MonitorFilter::Pointer monitor2 = MonitorFilter::New();
  monitor2->SetInput(bin->GetOutput());

  bool failed = false;


  try
    {
    // update with 1,1 shrink factor
    unsigned int factors[2] = { 1, 1 };
    std::cout << "== Testing with shrink factors " << factors[0] << " " << factors[1] << " == " << std::endl;
    bin->SetShrinkFactors(factors);
    monitor2->Update();

    // check values
    itk::ImageRegionConstIteratorWithIndex<ImageType> inIt( monitor2->GetOutput(), monitor2->GetOutput()->GetLargestPossibleRegion() );
    for (inIt.GoToBegin(); !inIt.IsAtEnd(); ++inIt)
      {
      if (inIt.Get() != inIt.GetIndex()[0]*10)
        {
        std::cout << "Wrong pixel value at " << inIt.GetIndex() << " of " << inIt.Get() << std::endl;
        failed = true;
        }
      }
    }
  catch (itk::ExceptionObject &e)
    {
    std::cout << "Excpetion: " << e << std::endl;
    failed = true;
    }

  try
    {
    // update with 2,1 shrink factor
    unsigned int factors[2] = { 2, 1 };
    std::cout << "== Testing with shrink factors " << factors[0] << " " << factors[1] << " == " << std::endl;
    bin->SetShrinkFactors(factors);
    monitor2->UpdateLargestPossibleRegion();

    // check values
    itk::ImageRegionConstIteratorWithIndex<ImageType> inIt( monitor2->GetOutput(), monitor2->GetOutput()->GetLargestPossibleRegion() );
    for (inIt.GoToBegin(); !inIt.IsAtEnd(); ++inIt)
      {
      if (inIt.Get() != (inIt.GetIndex()[0]*factors[0] )*10 + 5 )
        {
        std::cout << "Wrong pixel value at " << inIt.GetIndex() << " of " << inIt.Get() << std::endl;
        failed = true;
        }
      }
    }
  catch (itk::ExceptionObject &e)
    {
    std::cout << "Excpetion: " << e << std::endl;
    failed = true;
    }

  try
    {
    // update with 2,2 shrink factor
    unsigned int factors[2] = { 2, 2 };
    std::cout << "== Testing with shrink factors " << factors[0] << " " << factors[1] << " == " << std::endl;
    bin->SetShrinkFactors(factors);
    monitor2->UpdateLargestPossibleRegion();

    // check values
    itk::ImageRegionConstIteratorWithIndex<ImageType> inIt( monitor2->GetOutput(), monitor2->GetOutput()->GetLargestPossibleRegion() );
    for (inIt.GoToBegin(); !inIt.IsAtEnd(); ++inIt)
      {
      if (inIt.Get() != (inIt.GetIndex()[0]*factors[0] )*10 + 5 )
        {
        std::cout << "Wrong pixel value at " << inIt.GetIndex() << " of " << inIt.Get() << std::endl;
        failed = true;
        }
      }
    }
  catch (itk::ExceptionObject &e)
    {
    std::cout << "Excpetion: " << e << std::endl;
    failed = true;
    }



  try
    {
    // update with 5,2 shrink factor
    unsigned int factors[2] = { 5, 2 };
    std::cout << "== Testing with shrink factors " << factors[0] << " " << factors[1] << " == " << std::endl;
    bin->SetShrinkFactors(factors);
    monitor2->UpdateLargestPossibleRegion();

    // check values
    itk::ImageRegionConstIteratorWithIndex<ImageType> inIt( monitor2->GetOutput(), monitor2->GetOutput()->GetLargestPossibleRegion() );
    for (inIt.GoToBegin(); !inIt.IsAtEnd(); ++inIt)
      {
      if (inIt.Get() != (inIt.GetIndex()[0]*factors[0]+2)*10)
        {
        std::cout << "Wrong pixel value at " << inIt.GetIndex() << " of " << inIt.Get() << std::endl;
        failed = true;
        }
      }
    }
  catch (itk::ExceptionObject &e)
    {
    std::cout << "Excpetion: " << e << std::endl;
    failed = true;
    }

  std::cout << "-- Changing starting index to odd numer --" << std::endl;

  // set to odd index then reallocate and set values
  index[0] = 101;
  region.SetIndex( index );
  sourceImage->SetRegions( region );
  sourceImage->Allocate();

  outIt =  itk::ImageRegionIteratorWithIndex<ImageType>(sourceImage, region);
  for ( outIt.GoToBegin(); !outIt.IsAtEnd(); ++outIt )
    {
    // we multiply by ten for more precision
    outIt.Set( outIt.GetIndex()[0]*10 );
    }
  monitor1->SetInput( sourceImage );

  try
    {
    // update with 2,1 shrink factor
    unsigned int factors[2] = { 2, 1 };
    std::cout << "== Testing with shrink factors " << factors[0] << " " << factors[1] << " == " << std::endl;
    bin->SetShrinkFactors(factors);
    monitor2->UpdateLargestPossibleRegion();

    // check values
    itk::ImageRegionConstIteratorWithIndex<ImageType> inIt( monitor2->GetOutput(), monitor2->GetOutput()->GetLargestPossibleRegion() );
    for (inIt.GoToBegin(); !inIt.IsAtEnd(); ++inIt)
      {
      if (inIt.Get() != (inIt.GetIndex()[0]*factors[0] )*10 + 5 )
        {
        std::cout << "Wrong pixel value at " << inIt.GetIndex() << " of " << inIt.Get() << std::endl;
        failed = true;
        }
      }
    }
  catch (itk::ExceptionObject &e)
    {
    std::cout << "Excpetion: " << e << std::endl;
    failed = true;
    }

  try
    {
    // update with 3,1 shrink factor
    unsigned int factors[2] = { 3, 1 };
    std::cout << "== Testing with shrink factors " << factors[0] << " " << factors[1] << " == " << std::endl;
    bin->SetShrinkFactors(factors);
    monitor2->UpdateLargestPossibleRegion();

    // check values
    itk::ImageRegionConstIteratorWithIndex<ImageType> inIt( monitor2->GetOutput(), monitor2->GetOutput()->GetLargestPossibleRegion() );
    for (inIt.GoToBegin(); !inIt.IsAtEnd(); ++inIt)
      {
      if (inIt.Get() != (inIt.GetIndex()[0]*factors[0]+1 )*10 )
        {
        std::cout << "Wrong pixel value at " << inIt.GetIndex() << " of " << inIt.Get() << std::endl;
        failed = true;
        }
      }
    }
  catch (itk::ExceptionObject &e)
    {
    std::cout << "Excpetion: " << e << std::endl;
    failed = true;
    }

  index[0] = 0;
  index[1] = 3;
  region.SetIndex( index );

  for (unsigned int shrink = 1; shrink < 12; ++shrink)
    {
     // update with 3,1 shrink factor
    unsigned int factors[2] = { 1, shrink };
    std::cout << "== Testing with shrink factors " << factors[0] << " " << factors[1] << " == " << std::endl;

    for (unsigned int x = 1; x < 10; ++x )
      for (unsigned int y = 2*shrink; y < 20; ++y )
        {
        // fill in an image
        size[0] = x;
        size[1] = y;
        region.SetSize( size );
        sourceImage->SetRegions( region );
        sourceImage->Allocate();

        std::cout << "--Resolution " << x << " " << y << "--" << std::endl;

        itk::ImageRegionIteratorWithIndex<ImageType> outIt(sourceImage, region);
        for ( outIt.GoToBegin(); !outIt.IsAtEnd(); ++outIt )
          {
          // we multiply by ten so for more precision
          outIt.Set( outIt.GetIndex()[0]*10 );
          }

        try
          {
          bin->SetShrinkFactors(factors);
          monitor2->UpdateLargestPossibleRegion();
          // check values
          itk::ImageRegionConstIteratorWithIndex<ImageType> inIt( monitor2->GetOutput(), monitor2->GetOutput()->GetLargestPossibleRegion() );
          bool lfailed = false;
          for (inIt.GoToBegin(); !inIt.IsAtEnd(); ++inIt)
            {
            int expectedValue = inIt.GetIndex()[0]*10;
            if (inIt.Get() != expectedValue )
              {
              if (!lfailed)
                {
                std::cout << "--Resolution " << x << " " << y << "--" << std::endl;
                }
              std::cout << "Wrong pixel value at " << inIt.GetIndex() << " of " << inIt.Get() << ", expected: " << expectedValue << std::endl;
              lfailed = failed = true;
              }
            }
          if (lfailed)
            {
            monitor2->GetOutput()->Print(std::cout);
            exit(1);
            }
          }
        catch (itk::ExceptionObject &e)
          {
          std::cout << "Excpetion: " << e << std::endl;
          failed = true;
          }

        }
    }

  if ( failed )
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
#endif 
