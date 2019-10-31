# Apriltag fiducial tag for the FORmicidae Tracker project

This repository holds the custom tag families used by the FORmicidae
Tracker project. It also points to the exact version of
[apriltag](https://github.com/AprilRobotics/apriltag) used in
throughout the project. This is mainly to be used by CMake targets.

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



## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags).

## Authors

* **Alexandre Tuleu** - *Initial work* - [atuleu](https://github.com/atuleu)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the LGPL License version 3 or later - see the [COPYING.LESSER](COPYING.LESSER) file for details
