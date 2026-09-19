//
//  AvailabilityShim.c
//  Kayoko
//
//  Provides __isOSVersionAtLeast for toolchains that do not bundle
//  compiler-rt (clang's @available lowering calls it). Implemented with
//  kern.osproductversion, matching the compiler-rt semantics.
//

#include <sys/sysctl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static volatile int32_t availabilityShimInitialized = 0;
static int32_t availabilityShimMajor = 0;
static int32_t availabilityShimMinor = 0;
static int32_t availabilityShimPatch = 0;

static void availabilityShimLoadVersion(void) {
    char versionString[32] = {0};
    size_t size = sizeof(versionString) - 1;
    if (sysctlbyname("kern.osproductversion", versionString, &size, NULL, 0) != 0) {
        // Conservative fallback: iOS 14.
        availabilityShimMajor = 14;
        availabilityShimMinor = 0;
        availabilityShimPatch = 0;
        availabilityShimInitialized = 1;
        return;
    }

    char *end = NULL;
    long value = strtol(versionString, &end, 10);
    availabilityShimMajor = (int32_t)value;
    if (end && *end == '.') {
        value = strtol(end + 1, &end, 10);
        availabilityShimMinor = (int32_t)value;
        if (end && *end == '.') {
            value = strtol(end + 1, &end, 10);
            availabilityShimPatch = (int32_t)value;
        }
    }
    availabilityShimInitialized = 1;
}

int32_t __isOSVersionAtLeast(int32_t major, int32_t minor, int32_t patch) {
    if (!availabilityShimInitialized) {
        availabilityShimLoadVersion();
    }
    if (availabilityShimMajor != major) {
        return availabilityShimMajor > major;
    }
    if (availabilityShimMinor != minor) {
        return availabilityShimMinor > minor;
    }
    return availabilityShimPatch >= patch;
}
