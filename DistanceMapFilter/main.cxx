
#include "itkExceptionObject.h"
#include "DistanceMapFilter.h"


int main()
{

  DistanceMapFilter::Pointer example = 
                          DistanceMapFilter::New();

  example->Show();
  example->ShowDisplay();
  
  try 
    {
    Fl::run();
    }
  catch( itk::ExceptionObject & exception )
    {
    std::cout << "Exception caught !" << std::endl;
    std::cout << "Description : " << exception.GetDescription() << std::endl;
    std::cout << "Location    : " << exception.GetLocation()    << std::endl;
    }

  return 0;

}



