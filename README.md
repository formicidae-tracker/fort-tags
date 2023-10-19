# FORmicidae Tracker (FORT) : Legacy Fiducial Marker Support

[![DOI](https://zenodo.org/badge/218741181.svg)](https://zenodo.org/doi/10.5281/zenodo.10019059)


The [FORmicidae Tracker (FORT)](https://formicidae-tracker.github.io) is an advanced online tracking system designed specifically for studying social insects, particularly ants and bees, FORT utilizes fiducial markers for extended individual tracking. Its key features include real-time online tracking and a modular design architecture that supports distributed processing. The project's current repositories encompass comprehensive hardware blueprints, technical documentation, and associated firmware and software for online tracking and offline data analysis.

This repository holds the custom tag families used by the FORT project.
It also points to the exact version of
[apriltag](https://github.com/AprilRobotics/apriltag) used in
throughout FORT. This is mainly desgned to be used by CMake targets.

## Getting Started

These instruction explains how to setup the repository for development
purpose. If you want to use it in your project please look for section

### Prerequisites

 * cmake >= 3.11

 On Ubuntu 18.04, you will need to install cmake from kitware apt repository :


```bash
wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | sudo apt-key add -
sudo apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main'
sudo apt update
sudo apt install cmake
```

### Compiling and testing

This project aims to be used externally by other project. There are no
need to install it globally.

```bash
mkdir -p build
cd build
cmake ../
make
```

## How to use it with other CMake Project

Simply add to you CMakeLists.txt:

``` cmake
include(FetchContent)
FetchContent_Declare(fort-tags
                     GIT_REPOSITORY https://github.com/formicidae-tracker/fort-tags.git
                     GIT_TAG        v1.0.0)
FetchContent_GetProperties(fort-tags)
if(NOT fort-tags_POPULATED)
	FetchContent_Populate(fort-tags)
	add_subdirectory(${fort-tags_SOURCE_DIR} ${fort-tags_BINARY_DIR})
endif(NOT fort-tags_POPULATED)

include_directories(${fort-tags_SOURCE_DIR}/include)

add_executable(my-exec)

target_link_libraries(my-exec fort-tags)
```

You can choose the exact version of `fort-tag` you want to use using a
git commit or tag (here v1.0.0 in this example). By default, this
snippet will add to the install targets the header and apriltag
libraries. You can pass the option `EXCLUDE_FROM_ALL` to the
`add_subdirectory` call to avoid this behavior, but note that your
target will need this library to be present on the system if you
install it.


## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags).

## Contributors

See the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

This list is not the copyright holders for this work.

## License

This project is licensed under the BSD 2 Clause License - see the [LICENSE.md](LICENSE.md) file for details
