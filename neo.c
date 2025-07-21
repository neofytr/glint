#include "buildsysdep/neobuild.h"

#define BIN "bin/"
#define VECTOR "vector/"
#define RAY "ray/"
#define COLOR "color/"

#define COMPILER_FLAGS NULL
#define LINKER_FLAGS NULL

int main(int argc, char **argv)
{
    neorebuild("neo.c", argv, &argc);

    neo_compile_to_object_file(GPP, VECTOR "vector.cpp", BIN "vector.o", COMPILER_FLAGS, false); 
    neo_compile_to_object_file(GPP, RAY "ray.cpp", BIN "ray.o", COMPILER_FLAGS, false);
    neo_compile_to_object_file(GPP, COLOR "color.cpp", BIN "color.o", COMPILER_FLAGS, false);
    neo_compile_to_object_file(GPP, "main.cpp", BIN "main.o", COMPILER_FLAGS, false);

    neo_link(GPP, "main", LINKER_FLAGS, false, BIN "main.o", BIN "vector.o", BIN "ray.o", BIN "color.o");

    return EXIT_SUCCESS;
}
