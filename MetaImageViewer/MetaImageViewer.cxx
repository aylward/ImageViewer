#include <iostream>

#include <itkImage.h>

#include <metaImage.h>
#include <metaITKUtils.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_file_chooser.H>
#include <GLSliceView.h>

#include "MetaImageViewerGUI.h"


Fl_Window *form;
itk::Image<float, 3>::Pointer imP;

int usage(void)
   {
   std::cout << "MetaImageViewer" << std::endl;
   std::cout << std::endl;
   std::cout << "MetaImageViewer <Filename>" << std::endl;
   std::cout << std::endl;

   return 1;
   }

int main(int argc, char **argv)
  {
  char *fName;

  if(argc > 2)
    {
    return usage();
    }
   else
    if(argc == 1)
      {
      fName = fl_file_chooser("Pick a MetaImage file", "*.mh*", ".");
      if(fName == NULL || strlen(fName)<1)
        {
        return 0;
        }
      }
    else
      if(argv[1][0] != '-')
        {
        fName = argv[argc-1];
        }
      else
        {
        return usage();
        }

  std::cout << "Loading File: " << fName << std::endl;
  imP = metaITKUtilLoadImage3D<float>(fName, MET_FLOAT);
  std::cout << "...Done Loading File" << std::endl;

  char mainName[255];
  sprintf(mainName, "metaView: %s", fName);

  std::cout << std::endl;
  std::cout << "For directions on interacting with the window," << std::endl;
  std::cout << "   type 'h' within the window" << std::endl;
  
  form = make_window();

  tkMain->label(mainName);
  
  tkWin->SetInputImage(imP);
  
  form->show();
  tkWin->show();
  tkWin->update();

  Fl::run();
  
  return 1;
  }
