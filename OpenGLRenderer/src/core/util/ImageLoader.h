#pragma once

class ImageLoader {
public:
   static unsigned char* loadImage(std::string src, int* w, int* h, int* n);
   void static Clear(unsigned char* d);
private:
};

