/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    liImageRegistrationConsoleBase.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef liIMAGEREGISTRATIONCONSOLEBASE
#define liIMAGEREGISTRATIONCONSOLEBASE

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkWriteMetaImage.h>
#include <itkResampleImageFilter.h>
#include <itkImageRegistrationMethod.h>

#include <itkMutualInformationImageToImageMetric.h>
#include <itkMeanSquaresImageToImageMetric.h>
#include <itkNormalizedCorrelationImageToImageMetric.h>
#include <itkPatternIntensityImageToImageMetric.h>

#include <itkGradientDescentOptimizer.h>
#include <itkRegularStepGradientDescentOptimizer.h>
#include <itkConjugateGradientOptimizer.h>


/**
 * \brief ImageRegistrationConsoleBase class that instantiate
 * the elements required for a registration method without GUI
 *
 */
class liImageRegistrationConsoleBase
{
public:


  typedef enum {
    mutualInformation,
    normalizedCorrelation,
    patternIntensity,
    meanSquares
  } MetricIdentifier;
  
 typedef enum {
    gradientDescent,
    regularStepGradientDescent,
    conjugateGradient
  } OptimizerIdentifier;

  /** Dimension of the images to be registered */ 
  enum { ImageDimension = 3 };

  /** Pixel type to be used internally during registration */
  typedef   unsigned char                         PixelType;
  
  /** Type of the Moving image */
  typedef   itk::Image<PixelType,ImageDimension>  MovingImageType;

  /** Type of the Fixed image */
  typedef   itk::Image<PixelType,ImageDimension>  FixedImageType;
 
  /**  Registration methods to use */
  typedef   itk::ImageRegistrationMethod< MovingImageType,
                                          FixedImageType > 
                                                  ImageRegistrationMethodType;

  typedef   itk::ImageFileReader< FixedImageType >    FixedImageReaderType;

  typedef   itk::ImageFileReader< MovingImageType >   MovingImageReaderType;

  typedef   itk::Transform< double,
                            ImageDimension,
                            ImageDimension >          TransformBaseType;

  typedef   TransformBaseType::ParametersType         TransformParametersType;


  typedef   itk::AffineTransform< double,
                                  ImageDimension >    AffineTransformType;


  typedef   itk::MutualInformationImageToImageMetric< 
                                  FixedImageType,
                                  MovingImageType 
                                         > MutualInformationMetricType;

  typedef   itk::MeanSquaresImageToImageMetric< 
                                  FixedImageType,
                                  MovingImageType 
                                         > MeanSquaresMetricType;

  typedef   itk::NormalizedCorrelationImageToImageMetric< 
                                  FixedImageType,
                                  MovingImageType 
                                         > NormalizedCorrelationImageMetricType;

  typedef   itk::PatternIntensityImageToImageMetric< 
                                  FixedImageType,
                                  MovingImageType 
                                         > PatternIntensityImageMetricType;

  typedef   itk::ResampleImageFilter< MovingImageType,
                                      MovingImageType,
                                      AffineTransformType 
                                                  >  ResampleFilterType;


public:
  liImageRegistrationConsoleBase();
  virtual ~liImageRegistrationConsoleBase();

  virtual void LoadFixedImage(void)=0;
  virtual void LoadFixedImage(const char * filename);
  virtual void LoadMovingImage(void)=0;
  virtual void LoadMovingImage(const char * filename);

  virtual void ShowProgress(float);
  virtual void ShowStatus(const char * text);

  virtual void Execute(void);
  virtual void Stop(void);

  virtual void GenerateMovingImage(void);
  virtual void GenerateMappedMovingImage(void);

  virtual void UpdateTransformParameters(void);

  virtual void SelectMetric( MetricIdentifier metricType );
  virtual void SelectOptimizer( OptimizerIdentifier optimizerType );

protected:

  FixedImageReaderType::Pointer           m_FixedImageReader;

  MovingImageReaderType::Pointer          m_MovingImageReader;

  ResampleFilterType::Pointer             m_ResampleInputMovingImageFilter;

  ResampleFilterType::Pointer             m_ResampleMovingImageFilter;

  ImageRegistrationMethodType::Pointer    m_ImageRegistrationMethod;
  
  AffineTransformType::Pointer            m_Transform;
  
  AffineTransformType::Pointer            m_InputTransform;

  bool                                    m_FixedImageIsLoaded;
  bool                                    m_MovingImageIsLoaded;

  MetricIdentifier                        m_SelectedMetric;

  OptimizerIdentifier                     m_SelectedOptimizer;

};



#endif
