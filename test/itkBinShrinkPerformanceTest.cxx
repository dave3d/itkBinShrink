/*=========================================================================
 *
 *  Copyright Bradley Lowekamp
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "itkBinShrinkImageFilter.h"
#include "itkBinShrinkImageFilter2.h"

#include "itkImageFileReader.h"

#include "itkTimeProbe.h"

int itkBinShrinkPerformanceTest( int argc, char *argv[] )
{

const unsigned int shrinkFactor = 4;

const unsigned int ImageDimension = 3;
typedef int               PixelType;
typedef itk::Image<PixelType, ImageDimension> ImageType;


typedef itk::ImageFileReader<ImageType> ReaderType;
ReaderType::Pointer reader = ReaderType::New();

reader->SetFileName( argv[1] );
reader->UpdateLargestPossibleRegion();

ImageType::Pointer image = reader->GetOutput();
image->DisconnectPipeline();


itk::TimeProbe t0;

typedef itk::ShrinkImageFilter<ImageType, ImageType> Filter0Type;
Filter0Type::Pointer filter0 =  Filter0Type::New();
filter0->SetShrinkFactors( shrinkFactor );
filter0->SetInput( image );

for( unsigned int i = 0; i < 5; ++i )
  {
t0.Start();
filter0->Modified();
filter0->UpdateLargestPossibleRegion();
t0.Stop();
}

std::cout << "Average time of " << filter0->GetNameOfClass() <<  ": " << t0.GetMean() << std::endl;

itk::TimeProbe t1;

typedef itk::BinShrinkImageFilter<ImageType, ImageType> Filter1Type;
Filter1Type::Pointer filter1 =  Filter1Type::New();
filter1->SetShrinkFactors( shrinkFactor );
filter1->SetInput( image );

for( unsigned int i = 0; i < 5; ++i )
  {
t1.Start();
filter1->Modified();
filter1->UpdateLargestPossibleRegion();
t1.Stop();
}

std::cout << "Average time of " << filter1->GetNameOfClass() <<  ": " << t1.GetMean() << std::endl;

itk::TimeProbe t2;

typedef itk::BinShrinkImageFilter2<ImageType, ImageType> Filter2Type;
Filter2Type::Pointer filter2 =  Filter2Type::New();
filter2->SetShrinkFactors( shrinkFactor );
filter2->SetInput( image );


for( unsigned int i = 0; i < 2; ++i )
  {
t2.Start();

filter2->Modified();
filter2->UpdateLargestPossibleRegion();

t2.Stop();
}

std::cout << "Average time of " << filter2->GetNameOfClass() <<  ": " << t2.GetMean() << std::endl;



return EXIT_SUCCESS;


}
