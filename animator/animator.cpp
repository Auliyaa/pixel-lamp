#include <iostream>
#include <set>
#include <filesystem>
#include <cstdlib>

#include <opencv2/opencv.hpp>

#define WIDTH 16
#define HEIGHT 8
#define BMP_HEADER_SZ 54

std::set<std::string> bmps;

int main(int argc, char** argv)
{
  if (argc < 3)
  {
    std::cerr << "usage: " << argv[0] << " <bmp-folder> <classname> [-r]" << std::endl;
    return 1;
  }

  bool rotate = (argc==4 && std::string(argv[3]).compare("-r") == 0);

  // list bmps
  for (const auto& file : std::filesystem::directory_iterator(argv[1]))
  {
    if (file.file_size() != WIDTH*HEIGHT*3 + BMP_HEADER_SZ)
    {
      std::cerr << "invalid file size for " << file.path().string() << std::endl;
      std::cerr << " actual size: " << file.file_size() << std::endl;
      std::cerr << " expected size: " << WIDTH*HEIGHT*3 << std::endl;
      return 1;
    }

    bmps.insert(file.path().string());
  }

  // parse bmps
  std::cout << "#pragma once" << std::endl
            << "" << std::endl
            << "#include <animations/bmp.h>" << std::endl
            << "" << std::endl
            << "struct " << argv[2] << "_t: public " << (rotate ? "animation_rotating_bmp_t<10>" : "animation_bmp_t") << std::endl
            << "{" << std::endl
            << "    virtual animation_step_t get(size_t idx) const" << std::endl
            << "    {" << std::endl
            << "        return _a[idx];" << std::endl
            << "    }" << std::endl
            << "    virtual size_t size() const" << std::endl
            << "    {" << std::endl
            << "      return " << bmps.size() << ";" << std::endl
            << "    }" << std::endl
            << "    animation_step_t _a[" << bmps.size() << "] = {" << std::endl;

  for (const auto& bmp : bmps)
  {
    std::cout << "      {10,{";
    cv::Mat3b mat = cv::imread(bmp);
    for(size_t c=0; c<mat.cols; ++c)
    {
      for(long long r=mat.rows-1; r>=0; --r)
      {
        auto bgr = mat(r,c);
        std::cout << static_cast<int>(bgr[2]) << "," << static_cast<int>(bgr[1]) << "," << static_cast<int>(bgr[0]) << ",";
      }
    }
    std::cout << "}}," << std::endl;
  }

  std::cout << "    };" << std::endl
            << "};" << std::endl;

  return 0;
}
