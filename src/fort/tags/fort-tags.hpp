#pragma once

#include <string>
#include <functional>
#include "fort-tags.h"

namespace fort {
namespace tags {
enum class Family {
	Tag36h11=FortTags_Tag36h11,
	Tag36h10=FortTags_Tag36h10,
	Tag36ARTag=FortTags_Tag36ARTag,
	Tag16h5=FortTags_Tag16h5,
	Tag25h9=FortTags_Tag25h9,
	Circle21h7=FortTags_Circle21h7,
	Circle49h12=FortTags_Circle49h12,
	Custom48h12=FortTags_Custom48h12,
	Standard41h12=FortTags_Standard41h12,
	Standard52h13=FortTags_Standard52h13,
	Undefined=FortTags_Undefined
};

typedef std::function<apriltag_family_t*()>    FamilyConstructor;
typedef std::function<void(apriltag_family_t*)> FamilyDestructor;


Family FindFamily(const std::string & name);

const std::string & GetFamilyName(fort::tags::Family family);

std::pair<FamilyConstructor,FamilyDestructor> GetFamily(Family family);
std::pair<FamilyConstructor,FamilyDestructor> GetFamily(const std::string & familyName);

} // namespace tags
} // namespace fort
