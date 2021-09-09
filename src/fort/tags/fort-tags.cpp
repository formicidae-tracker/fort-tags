#include "fort-tags.hpp"

#include <map>
#include <stdexcept>

#include <apriltag/tag16h5.h>
#include <apriltag/tag25h9.h>
#include <apriltag/tag36h11.h>
#include <apriltag/tagCircle21h7.h>
#include <apriltag/tagCircle49h12.h>
#include <apriltag/tagCustom48h12.h>
#include <apriltag/tagStandard41h12.h>
#include <apriltag/tagStandard52h13.h>

#include "tag36h10.h"
#include "tag36ARTag.h"


namespace fort {
namespace tags {

Family FindFamily(const std::string & name) {
	static std::map<std::string,Family> families
		= {
		   {"",Family::Undefined},
		   {"undefined",Family::Undefined},
		   {"16h5",Family::Tag16h5},
		   {"25h9",Family::Tag25h9},
		   {"36h10",Family::Tag36h10},
		   {"36h11",Family::Tag36h11},
		   {"36ARTag",Family::Tag36ARTag},
		   {"Circle21h7",Family::Circle21h7},
		   {"Circle49h12",Family::Circle49h12},
		   {"Custom48h12",Family::Custom48h12},
		   {"Standard41h12",Family::Standard41h12},
		   {"Standard52h13",Family::Standard52h13},
	};

	auto fi = families.find(name);
	if ( fi == families.end() ) {
		throw std::out_of_range("Umknown family '" + name + "'");
	}
	return fi->second;
}

const std::string & GetFamilyName(fort::tags::Family family) {
	static std::map<Family,std::string> familyNames
		= {
		   {Family::Undefined,"undefined"},
		   {Family::Tag16h5,"16h5"},
		   {Family::Tag25h9,"25h9"},
		   {Family::Tag36h10,"36h10"},
		   {Family::Tag36h11,"36h11"},
		   {Family::Tag36ARTag,"36ARTag"},
		   {Family::Circle21h7,"Circle21h7"},
		   {Family::Circle49h12,"Circle49h12"},
		   {Family::Custom48h12,"Custom48h12"},
		   {Family::Standard41h12,"Standard41h12"},
		   {Family::Standard52h13,"Standard52h13"},
	};

	auto fi = familyNames.find(family);
	if ( fi == familyNames.cend() ) {
		throw std::out_of_range("Unknown family value " + std::to_string(int(family)));
	}
	return fi->second;
}

std::pair<::FortTagsFamilyConstructor,::FortTagsFamilyDestructor> getFamily(Family family) {
	if ( family == Family::Undefined ) {
		throw std::invalid_argument("Not possible to construct a 'fort::tags::Family::Undefined'");
	}

	static std::map<tags::Family,std::pair<::FortTagsFamilyConstructor,::FortTagsFamilyDestructor> >  familyFactory = {
		 {fort::tags::Family::Tag16h5,{&tag16h5_create, &tag16h5_destroy}},
		 {fort::tags::Family::Tag25h9,{&tag25h9_create, &tag25h9_destroy}},
		 {fort::tags::Family::Tag36h10,{&tag36h10_create, &tag36h10_destroy}},
		 {fort::tags::Family::Tag36h11,{&tag36h11_create, &tag36h11_destroy}},
		 {fort::tags::Family::Tag36ARTag,{&tag36ARTag_create, &tag36ARTag_destroy}},
		 {fort::tags::Family::Circle21h7,{&tagCircle21h7_create, &tagCircle21h7_destroy}},
		 {fort::tags::Family::Circle49h12,{&tagCircle49h12_create, &tagCircle49h12_destroy}},
		 {fort::tags::Family::Custom48h12,{&tagCustom48h12_create, &tagCustom48h12_destroy}},
		 {fort::tags::Family::Standard41h12,{&tagStandard41h12_create, &tagStandard41h12_destroy}},
		 {fort::tags::Family::Standard52h13,{&tagStandard52h13_create, &tagStandard52h13_destroy}},
	};
	auto fi =  familyFactory.find(family);
	if ( fi == familyFactory.cend() ) {
		throw std::out_of_range("Unsupported family value " + std::to_string(int(family)) );
	}
	return fi->second;
}

std::pair<FamilyConstructor,FamilyDestructor> GetFamily(Family family) {
	return getFamily(family);
}

std::pair<FamilyConstructor,FamilyDestructor> GetFamily(const std::string & familyName) {
	try {
		return GetFamily(FindFamily(familyName));
	} catch ( const std::out_of_range & ) {
		throw std::out_of_range("Unsupported family '" + familyName + "'");
	}
}

} // namespace tags
} // namespace fort

extern "C" {


FortTagsFamily_e FortTagsFindFamily(const char * familyName) {
	try {
		return FortTagsFamily_e(fort::tags::FindFamily(familyName));
	} catch ( const std::exception & e) {
		return FortTagsFamily_e(-1);
	}
}

const char * FortTagsGetFamilyName(FortTagsFamily_e family) {
	try {
		return fort::tags::GetFamilyName(fort::tags::Family(family)).c_str();
	} catch ( const std::exception & e ) {
		return NULL;
	}
}

int FortTagsGetFamily(FortTagsFamilyInterface_t * interface,FortTagsFamily_e family) {
	try {
		const auto & [constructor,destructor] = fort::tags::getFamily(fort::tags::Family(family));
		interface->Constructor = constructor;
		interface->Destructor = destructor;
		return 0;
	} catch ( const std::exception & e) {
		return -1;
	}
}

int FortTagsGetFamilyFromName(FortTagsFamilyInterface_t * interface,const char * familyName) {
	try {
		auto family = fort::tags::FindFamily(familyName);
		const auto & [constructor,destructor] = fort::tags::getFamily(family);
		interface->Constructor = constructor;
		interface->Destructor = destructor;
		return 0;
	} catch ( const std::exception & e) {
		return -1;
	}
}


} // extern "C"
