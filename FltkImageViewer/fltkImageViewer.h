/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    fltkImageViewer.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __fltkImageViewer_h
#define __fltkImageViewer_h

#include "fltkImageViewerGUI.h"

namespace fltk {

template <class ImagePixelType, class OverlayPixelType>
class ImageViewer : public fltkImageViewerGUI
{
public:

   /**
   * Standard "Self" typedef.
   */
  typedef ImageViewer         Self;

  /** 
   * Smart pointer typedef support.
   */
  typedef SmartPointer<Self>        Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

 
  typedef itk::Image< ImagePixelType, 3 >   ImageType;
  typedef itk::Image< OverlayPixelType, 3 > OverlayType;
  typedef GLSliceView< ImagePixelType, OverlayPixelType > GLSliceViewType;
    
  ImageViewer();
  virtual ~ImageViewer();
  virtual void SetImage(ImageBase<3> * img);
  virtual void SetOverlay(ImageBase<3> * img);
  virtual void Show(void);
  virtual void Hide(void);
  virtual void Update(void);
  virtual void Synchronize(void);
  virtual void ImageMode(ImageModeType mode);
  virtual void SelectSlice(unsigned int num);
  virtual void SetIntensityWindowingMin(float val);
  virtual void SetIntensityWindowingMax(float val);
  virtual void CenterWindow(void);
  virtual void ZoomIn(void);
  virtual void ZoomOut(void);
  virtual void ShiftUp(void);
  virtual void ShiftDown(void);
  virtual void ShiftLeft(void);
  virtual void ShiftRight(void);
  virtual void SetOrientation(void);
  virtual void CreateGLSliceView( Fl_Group * g , Fl_Gl_Window * w );
  virtual void SetLabel( const char * );
  virtual void ShowClickedPointsWindow(void);
  virtual void UpdateClickedPoints(void);
  virtual void ClearClickedPoints(void);
  virtual void ClickSelectCallBack(
                void (*newClickSelectArgCallBack)(float, float,
                                                  float, float,
                                                  void *),
                     void * newClickSelectArg);

private:
  GLSliceViewType * glSliceView;
};


} // end namespace fltk

#ifndef ITK_MANUAL_INSTANTIATION
#include <fltkImageViewer.txx>
#endif




#endif
