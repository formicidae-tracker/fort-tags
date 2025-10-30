#pragma once

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpedantic"
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif
#include <apriltag/apriltag.h>
#if defined(__clang__)
#pragma clang diagnostic pop
#else
#pragma GCC diagnostic pop
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum FortTagsFamily {
	FortTags_Tag36h11 = 0,
	FortTags_Tag36h10,
	FortTags_Tag36ARTag,
	FortTags_Tag16h5,
	FortTags_Tag25h9,
	FortTags_Circle21h7,
	FortTags_Circle49h12,
	FortTags_Custom48h12,
	FortTags_Standard41h12,
	FortTags_Standard52h13,
	FortTags_Undefined
} FortTagsFamily_e;

typedef apriltag_family_t *(*FortTagsFamilyConstructor)();
typedef void (*FortTagsFamilyDestructor)(apriltag_family_t *);

typedef struct FortTagsFamilyInterface {
	FortTagsFamilyConstructor Constructor;
	FortTagsFamilyDestructor  Destructor;
} FortTagsFamilyInterface_t;

FortTagsFamily_e FortTagsFindFamily(const char *familyName);

const char *FortTagsGetFamilyName(FortTagsFamily_e family);

int FortTagsGetFamily(
    FortTagsFamilyInterface_t *interface, FortTagsFamily_e family
);

int FortTagsGetFamilyFromName(
    FortTagsFamilyInterface_t *interface, const char *familyName
);

#ifdef __cplusplus
} // extern C
#endif
