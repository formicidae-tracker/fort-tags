#pragma once

#include <apriltag/apriltag.h>
#include <apriltag/tag16h5.h>
#include <apriltag/tag25h9.h>
#include <apriltag/tag36h11.h>
#include <apriltag/tagCircle21h7.h>
#include <apriltag/tagCircle49h12.h>
#include <apriltag/tagCustom48h12.h>
#include <apriltag/tagStandard41h12.h>
#include <apriltag/tagStandard52h13.h>
#include <fort-tags/tag36ARTag.h>
#include <fort-tags/tag36h10.h>

#ifdef __cplusplus
namespace fort {
namespace tags {
enum class Family {

#else //__cplusplus
typedef enum FortTagFamily {
#endif //__cplusplus
 Tag36h11=0,
 Tag36h10,
 Tag36ARTag,
 Tag16h5,
 Tag25h9,
 Circle21h7,
 Circle49h12,
 Custom48h12,
 Standard41h12,
 Standard52h13,
 Undefined

#ifdef __cplusplus
};
} // namespace tags
} // namespace fort
#else //__cplusplus
} FortTagFamily_e;
#endif //__cplusplus
