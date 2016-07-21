#ifndef SMOOTHING_FILTER_H
#define SMOOTHING_FILTER_H

#include "../../ITK/Modules/Core/Common/include/itkImage.h"
#include "../../ITK/Modules/Core/Common/include/itkImageToImageFilter.h"
#include "../../ITK/Modules/Core/Common/include/itkImageRegionConstIterator.h"
#include "../../ITK/Modules/Core/Common/include/itkImageRegionIterator.h"
#include "../../ITK/Modules/IO/ImageBase/include/itkImageFileReader.h"
#include "../../ITK/Modules/IO/ImageBase/include/itkImageFileWriter.h"
#include "../../ITK/Modules/Bridge/VtkGlue/include/QuickView.h"
#include "itkRGBPixel.h"


template< typename TImage>
class SmoothingFilter: public itk::ImageToImageFilter< TImage, TImage >
{

public:

    /** Standard class typedefs. */
    typedef SmoothingFilter                                 Self;
    typedef itk::ImageToImageFilter< TImage, TImage >       SuperClass;
    typedef itk::SmartPointer<Self>                         Pointer;
    typedef itk::SmartPointer<const Self>                   ConstPointer;
    typedef itk::ImageRegionIterator<TImage>                Iterator;
    typedef itk::ImageRegionConstIterator<TImage>           ConstIterator;

    typedef typename TImage::PixelType                      TPixel;
    typedef typename TImage::IndexType                      TIndex;
    typedef typename TImage::ConstPointer                   ImageConstPointer;
    typedef typename TImage::Pointer                        ImagePointer;
    typedef typename TImage::SizeType                       SizeType;


    /** Method for creation through the object factory  */
    itkNewMacro(Self)

    /** Run-time type information (and related methods) */
    itkTypeMacro(SmoothingFilter, ImageToImageFilter)

    /** Number of Neighbours */
    int NbNeighbours;



protected:

    SmoothingFilter();

    /** Does the real work */
    virtual void GenerateData();

private:

    bool IsInBundarie(TIndex PixelIndex, ImageConstPointer input, TIndex limit);

    TPixel Neighbours_4(ImageConstPointer input, ConstIterator inputIterator);
    TPixel Neighbours_8(ImageConstPointer input, ConstIterator inputIterator);


};



/** Find extension */
std::string SetExten(std::string file)
{
    int pos = file.find('.',0);
    std::string filename = file.substr(0,pos);
    std::string exten = file.substr(pos,file.size());
    return exten;

}



/** Set output filename */
std::string SetOutputName(std::string exten, std::string name, std::string path){
    std::string outputname = path + '/' + name + exten;
    return outputname;
}







/** launch filter */
template<typename ImageType>
void Filter(std::string InputFile, int neighbours, std::string OutputName, std::string Outputpath)
{
    /** Get Dimension & extension */

    //Extension
    std::string exten = SetExten(InputFile);

    //Set output filename
    std::string OutputFile = SetOutputName(exten, OutputName, Outputpath);


    typedef itk::ImageFileReader<ImageType>         ReaderType;
    typedef itk::ImageFileWriter<ImageType>         WriterType;
    typedef SmoothingFilter<ImageType>              FilterType;

    typename ReaderType::Pointer reader = ReaderType::New();
    typename WriterType::Pointer writer = WriterType::New();
    typename FilterType::Pointer filter = FilterType::New();


    filter->NbNeighbours = neighbours;

    /** Read **/
    reader->SetFileName(InputFile);
    reader->Update();


    /** Filter **/
    filter->SetInput(reader->GetOutput());
    filter->Update();

    /** Writer **/
    writer->SetInput(filter->GetOutput());
    writer->SetFileName(OutputFile);
    writer->Update();


    return;

}



/** Determine the image type */
void TypeImageFilterDefine(int dim, std::string InputFile, int neighbours, std::string OutputName, std::string Outputpath)
{
    if(dim ==2)
    {
        typedef itk::RGBPixel<unsigned char> PixelType;
        const unsigned int Dimension = 2;
        typedef itk::Image<PixelType,Dimension> TImage;
        Filter<TImage>(InputFile, neighbours, OutputName, Outputpath);
    }
    else
    {
        typedef itk::RGBPixel<float> PixelType;
        const unsigned int Dimension = 3;
        typedef itk::Image<PixelType,Dimension> TImage;
        Filter<TImage>(InputFile, neighbours, OutputName, Outputpath);
    }
}



#endif
