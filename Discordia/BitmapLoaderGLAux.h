#include <windows.h>

class AUX_RGBImageRec 
{
 public:
   unsigned char *data;
   DWORD sizeX;
   DWORD sizeY;
   bool NoErrors;
   AUX_RGBImageRec(): NoErrors(false), data(NULL) {};
   AUX_RGBImageRec(const char *FileName);
   ~AUX_RGBImageRec();
   bool loadFile(const char *FileName);

   friend AUX_RGBImageRec *auxDIBImageLoad(const char *FileName);

private:
   void convertBGRtoRGB();
};