#include "color/color.h"
#include "ray/ray.h"
#include "vector/vector.h"
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

const char *imageName = "image.ppm";

Color rayColor(const Ray &ray) {
    Vector unitDirection = unitVector(ray.direction());
    double a             = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main() {
    // image
    double aspectRatio = 16.0 / 9.0;
    int    imageWidth  = 256;

    int imageHeight = int(imageWidth / aspectRatio);
    if (imageHeight < 1)
        imageHeight = 1; // ensure that the image height is atleast 1 pixel

    // viewport
    double viewportHeight = 2.0;
    // in order for our viewport proportions to exactly match our image proportions, we use the
    // calculated image aspect ratio to determine our final viewport width
    double viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);

    // camera (C)
    // the line from the camera to the centre of the viewport (say L) is orthagonal to the viewport
    // (say at point M)
    double focalLength = 1.0;     // the length CM
    Point  cameraCentre(0, 0, 0); // we set the origin to be the camera

    // viewport vectors
    Vector viewport_u(viewportWidth, 0,
                      0); // horizontal vector along the viewport width from left to right
    Vector viewport_v(-viewportHeight, 0,
                      0); // vertical vector along the viewport height from top to bottom

    // delta vectors from pixel to pixel
    Vector pixelDelta_u = viewport_u / imageWidth;
    Vector pixelDelta_v = viewport_v / imageHeight;

    Vector orthagonalOnViewPort(0, 0, -focalLength);
    Vector viewportUpperLeft =
        cameraCentre + orthagonalOnViewPort - pixelDelta_v / 2 - pixelDelta_u / 2;
    Point pixel00 = viewportUpperLeft + pixelDelta_u / 2 + pixelDelta_v / 2;

    ofstream image(imageName); // will create the file if it doesn't exist
    if (!image) {
        cerr << "ERROR -> couldn't open/create the file " << imageName << "\n";
        return EXIT_FAILURE;
    }

    // PPM format headers
    image << "P3\n";
    image << imageWidth << " " << imageHeight << "\n";
    image << "255\n";

    // image pixel data
    cout << "Rendering Progress -> 0.00%" << flush;
    for (int row = 0; row < imageHeight; row++) {
        if (!(row % 5)) {
            double progress = ((double) (row + 1) / imageHeight) * 100.0;
            cout << "\rRendering Progress -> " << fixed << setprecision(2) << progress << "%"
                 << flush;
        }
        for (int col = 0; col < imageWidth; col++) {
            Point  pixelCentre = pixel00 + row * pixelDelta_u + col * pixelDelta_v;
            Vector rayDirection =
                pixelCentre -
                cameraCentre; // ray is started from camera, and passes through the viewport
                              // (through the corresponding pixel point) onto the scene
            Ray directedRay(cameraCentre, rayDirection);

            Color pixel = rayColor(directedRay);
            writePixelToFile(image, pixel);
        }
    }
    cout << "\rRendering Progress -> 100.00%" << endl;
    return EXIT_SUCCESS;
}