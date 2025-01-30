#ifndef TEXTURE
#define TEXTURE

#include "lodepng.h"
#include "raylib.h"

#include <cassert>
#include <format>
#include <iostream>
#include <ostream>
#include <vector>

static void loadTexture(const char *filename, std::vector<unsigned char> &image,
                        unsigned &width, unsigned &height);
//
struct Textures {
  std::vector<std::vector<Color>> textures{};

  // initializes an array of texture filepaths
  void initialize(const char **filenames, size_t numfiles) {
    textures.resize(numfiles);

    for (size_t i{}; i < numfiles; ++i) { // for every file
      std::vector<unsigned char> image{};
      unsigned width{};
      unsigned height{};
      loadTexture(filenames[i], image, width, height);

      textures[i].resize(width * height);

      for (size_t b{}; b < (width * height * 4); b += 4) {
        textures[i][b/4] = Color((int)image[b], (int)image[b + 1],
                               (int)image[b + 2], (int)image[b + 3]);
      }
    }
  }
};

// Decode from disk to raw pixels with a single function call
static void loadTexture(const char *filename, std::vector<unsigned char> &image,
                        unsigned &width, unsigned &height) {

  // decode
  unsigned error = lodepng::decode(image, width, height, filename);

  // if there's an error, display it
  if (error)
    std::cout << "decoder error " << error << ": " << lodepng_error_text(error)
              << std::endl;
  // the pixels are now in the vector "image", 4 bytes per pixel, ordered
  // RGBARGBA..., use it as texture, draw it,
}

#endif
