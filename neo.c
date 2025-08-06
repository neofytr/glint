#include "buildsysdep/neobuild.h"
#include <stdio.h>
#include <string.h>

#define BIN "bin/"
#define SRC "source/"
#define RAY "ray/"
#define COLOR "color/"
#define VECTOR "vector/"
#define HITTABLE "hittable/"

#define INC                                                                                                                                                                                            \
    "-I" RAY " "                                                                                                                                                                                       \
    "-I" COLOR " "                                                                                                                                                                                     \
    "-I" VECTOR " "                                                                                                                                                                                    \
    "-I" HITTABLE

#define MAX_BUFLEN (2048 + 1)

#define CXXFLAGS "-O2 -Wall -Wextra -std=c++17 " INC
#define LFLAGS ""
int main(int argc, char **argv) {
    neocmd_t *cmd, *tmp;
    char      buf[MAX_BUFLEN];
    neorebuild("neo.c", argv, &argc);

    if (argc > 1 && !strcmp(argv[1], "clean")) {
        cmd = neocmd_create(BASH);
        neocmd_append(cmd, "rm -f " BIN "*.o " BIN "main");
        neocmd_run_sync(cmd, NULL, NULL, false);
        neocmd_delete(cmd);
        return EXIT_SUCCESS;
    }

    if (argc > 1 && !strcmp(argv[1], "push")) {
        if (argc < 3) {
            printf("Usage: %s push \"commit message\"\n", argv[0]);
            return EXIT_FAILURE;
        }

        snprintf(buf, MAX_BUFLEN - 1, "git commit -m \"%s\" &&", argv[2]);
        buf[MAX_BUFLEN - 1] = 0;

        cmd = neocmd_create(BASH);
        neocmd_append(cmd, "./neo clean");
        neocmd_run_sync(cmd, NULL, NULL, false);

        tmp = neocmd_create(BASH);
        neocmd_append(tmp, "git add . &&");
        neocmd_append(tmp, buf);
        neocmd_append(tmp, "git push -u origin main");

        neocmd_run_sync(tmp, NULL, NULL, false);
        neocmd_delete(cmd);
        neocmd_delete(tmp);
        return EXIT_SUCCESS;
    }

    neo_compile_to_object_file(GPP, VECTOR "vector.cpp", BIN "vector.o", CXXFLAGS, false);
    neo_compile_to_object_file(GPP, RAY "ray.cpp", BIN "ray.o", CXXFLAGS, false);
    neo_compile_to_object_file(GPP, COLOR "color.cpp", BIN "color.o", CXXFLAGS, false);
    neo_compile_to_object_file(GPP, "main.cpp", BIN "main.o", CXXFLAGS, false);

    neo_link(GPP, BIN "main", LFLAGS, false, BIN "main.o", BIN "vector.o", BIN "ray.o", BIN "color.o");

    if (argc > 1 && !strcmp(argv[1], "dis")) {
        tmp = neocmd_create(BASH);
        neocmd_append(tmp, "objdump -d -M intel", BIN "main");
        neocmd_run_sync(tmp, NULL, NULL, false);
        neocmd_delete(tmp);
    }

    if (argc > 1 && !strcmp(argv[1], "run")) {
        tmp = neocmd_create(BASH);
        neocmd_append(tmp, "./" BIN "main");
        neocmd_run_sync(tmp, NULL, NULL, false);
        neocmd_delete(tmp);
    }

    return EXIT_SUCCESS;
}
