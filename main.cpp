#include "color/color.h"
#include "ray/ray.h"
#include "vector/vector.h"
#include <cerrno>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

const char *imageName = "image.ppm";

double hitSphere(Point &sphereCentre, double radius, Ray &ray) {
    Vector oc           = ray.origin() - sphereCentre;
    double a            = dot(ray.direction(), ray.direction());
    double b            = -2.0 * dot(oc, ray.direction());
    double c            = dot(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return ((b - sqrt(discriminant)) / (2.0 * a)); // consider according to the facing surface
    }
}

Color getRayColor(Ray &ray) {
    Point  sphereCentre(0, 0, -1);
    double radius = 0.5;
    double t      = hitSphere(sphereCentre, radius, ray);
    if (t >= 0) { // so that the sphere is displayed only when it's in front of the camera
        Vector normal = unitVector(ray.at(t) - sphereCentre);
        // normals have components between [-1, 1];
        // since we need color components from 0 to 1
        // we map like this -> color = 1/2 * (normal + (1, 1, 1));
        return 0.5 * Color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
    }
    return Color(0, 0, 0);
}

int main() {
    // image
    double aspectRatio = 16.0 / 9.0;
    int    imageWidth  = 256;
    int    imageHeight = int(imageWidth / aspectRatio);

    // viewport
    double viewportHeight = 2.0;
    double viewportWidth  = viewportHeight * ((double) imageWidth / imageHeight);

    // camera (0, 0, 0)
    // the line from the camera to the viewport centre (say M) is perpendicular to the viewport
    double focalLength = 1.0; // the distance CM
    Point  camera(0, 0, 0);   // camera is at the origin

    // viewport edge vectors
    Vector viewportU(viewportWidth, 0, 0);
    Vector viewportV(0, -viewportHeight, 0);

    // delta vectors
    Vector deltaU = viewportU / imageWidth;
    Vector deltaV = viewportV / imageHeight;

    // viewport top left
    Vector perpendicularCM(0, 0, -focalLength);
    Vector viewportTopLeft = camera + perpendicularCM - viewportU / 2 - viewportV / 2;

    // pixel(0, 0) on the viewport
    Vector pixel00 = viewportTopLeft + deltaU / 2 + deltaV / 2;

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
            Vector pixelrc = pixel00 + row * deltaV + col * deltaU;
            Ray    rayThroughPixelRC(camera, (pixelrc - camera));
            Color  pixelColor = getRayColor(rayThroughPixelRC);
            writePixelToFile(image, pixelColor);
        }
    }
    cout << "\rRendering Progress -> 100.00%" << endl;
    return EXIT_SUCCESS;
}