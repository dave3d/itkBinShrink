
#include "itkTestingMacros.h"
#include "itkRGBPixel.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkBinShrinkImageFilter.h"

//
// This is an example which is intended to be useful to process images
// of a variety of types.

namespace
{


template<class  TInputImageType >
int itkBinShrinkExampleImp( const std::string &infname,
                                       const std::string &outfname,
                                       unsigned int shrink )
{
  typedef TInputImageType InputImageType;
  typedef TInputImageType OutputImageType;

  typedef typename TInputImageType::PixelType InputPixelType;

  typedef itk::ImageFileReader<InputImageType>  ReaderType;
  typedef itk::ImageFileWriter<OutputImageType> WriterType;

  typedef itk::BinShrinkImageFilter<InputImageType, OutputImageType> FilterType;

  typename ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( infname );

  typename FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );
  filter->SetShrinkFactors( shrink );

  typename WriterType::Pointer writer = WriterType::New();
  writer->SetInput( filter->GetOutput() );
  writer->SetFileName( outfname );
  writer->SetNumberOfStreamDivisions( 5 );
  writer->Update();

  // excersie some methods to improve coverage
  EXERCISE_BASIC_OBJECT_METHODS( filter, FilterType );

  std::cout << filter;

  return EXIT_SUCCESS;
}


template< class TComponent >
int itkBinShrinkExampleDispatch( const std::string &imageFileName,
                                 const std::string &outfname,
                                 unsigned int dimensions,
                                 itk::ImageIOBase::IOPixelType pixelType,
                                 unsigned int numberOfComponents,
                                 unsigned int shrink )
{
  if ( dimensions == 2 )
    {
    if ( pixelType == itk::ImageIOBase::RGB )
      {
      return itkBinShrinkExampleImp<itk::Image<itk::RGBPixel<TComponent>,2> >(imageFileName, outfname, shrink);
      }
    else  if (numberOfComponents > 1)
      {
      return itkBinShrinkExampleImp<itk::VectorImage<TComponent,2> >(imageFileName, outfname, shrink);
      }
    return itkBinShrinkExampleImp<itk::Image<TComponent,2> >(imageFileName, outfname, shrink);
    }
  else if (dimensions == 3 )
    {
    if ( pixelType == itk::ImageIOBase::RGB )
      {
      return itkBinShrinkExampleImp<itk::Image<itk::RGBPixel<TComponent>,2> >(imageFileName, outfname, shrink);
      }
    else if (numberOfComponents == 3)
       {
       return itkBinShrinkExampleImp<itk::Image<itk::Vector<TComponent>,3> >(imageFileName, outfname, shrink);
       }
     else if (numberOfComponents > 1)
      {
      return itkBinShrinkExampleImp<itk::VectorImage<TComponent,3> >(imageFileName, outfname, shrink);
      }
    return itkBinShrinkExampleImp<itk::Image<TComponent,3> >(imageFileName, outfname, shrink);
    }
  else
    {
    std::cerr << "Only 2D and 3D image supported." << std::endl;
    return 1;
    }
}


}

int itkBinShrinkExample( int argc, char *argv[] )
{

  if ( argc < 3 )
  {
    std::cerr << "Missing arguments" << std::endl;
    std::cerr << "Usage: " << argv[0] << " InputImage OutputImage shrinkFactor" << std::endl;
    return EXIT_FAILURE;
  }

  const std::string infname = argv[1];
  const std::string outfname = argv[2];
  const unsigned int shrink = atoi( argv[3] );

  itk::ImageIOBase::Pointer iobase =
    itk::ImageIOFactory::CreateImageIO( infname.c_str(), itk::ImageIOFactory::ReadMode);

  if ( iobase.IsNull() )
    {
    itkGenericExceptionMacro( "Unable to determine ImageIO reader for \"" << infname << "\"" );
    }
  iobase->SetFileName( infname );
  iobase->ReadImageInformation();


  std::cout << iobase << std::endl;

  const itk::ImageIOBase::IOComponentType componentType = iobase->GetComponentType();
  const itk::ImageIOBase::IOPixelType pixelType = iobase->GetPixelType();
  const unsigned int dimension = iobase->GetNumberOfDimensions();
  const unsigned int numComp = iobase->GetNumberOfComponents();


  switch(componentType)
    {

    case itk::ImageIOBase::CHAR:
      return itkBinShrinkExampleDispatch< char >( infname, outfname, dimension, pixelType, numComp, shrink );
    case itk::ImageIOBase::UCHAR:
      return itkBinShrinkExampleDispatch< unsigned char >( infname, outfname, dimension, pixelType, numComp, shrink );
    case itk::ImageIOBase::SHORT:
      return itkBinShrinkExampleDispatch< short >( infname, outfname, dimension, pixelType, numComp, shrink );
    case itk::ImageIOBase::USHORT:
      return itkBinShrinkExampleDispatch< unsigned short >( infname, outfname, dimension, pixelType, numComp, shrink );
    case itk::ImageIOBase::INT:
      return itkBinShrinkExampleDispatch< int >( infname, outfname, dimension, pixelType, numComp, shrink );
    case itk::ImageIOBase::UINT:
      return itkBinShrinkExampleDispatch< unsigned int >( infname, outfname, dimension, pixelType, numComp, shrink );
    case itk::ImageIOBase::ULONG:
      return itkBinShrinkExampleDispatch< unsigned long >( infname, outfname, dimension, pixelType, numComp, shrink );
    case itk::ImageIOBase::LONG:
      return itkBinShrinkExampleDispatch< long >( infname, outfname, dimension, pixelType, numComp, shrink );
    case itk::ImageIOBase::FLOAT:
      return itkBinShrinkExampleDispatch< float >( infname, outfname, dimension, pixelType, numComp, shrink );
    case itk::ImageIOBase::DOUBLE:
      return itkBinShrinkExampleDispatch< double >( infname, outfname, dimension, pixelType, numComp, shrink );
    case itk::ImageIOBase::UNKNOWNCOMPONENTTYPE:
    default:
      itkGenericExceptionMacro( "Input image is a real, long or a unknown component type" );
    }

  std::cerr << "Unexcpected program flow!" << std::endl;
  return EXIT_FAILURE;
}

