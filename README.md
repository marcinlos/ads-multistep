# IGA-ADS is a C++ framework designed to facilitate creating parallel numerical simulations for time-dependent PDEs using isogeometric finite element method.

**Table of contents**
- [Requirements](#requirements)
  - [Dependencies](#dependencies)
  - [Tools](#tools)
- [usage](#usage)

## Requirements

### Dependencies
- LAPACK, BLAS
- Boost, version 1.58 or higher (http://www.boost.org/)
-  Galois framework, version 2.2.1 (http://iss.ices.utexas.edu/?p=projects/galois)
- (optional) libunittest (http://libunittest.sourceforge.net/)

Galois is required for parallelism, libunittest for unit tests only.

On Ubuntu 16.04 LTS issue the following command
```bash
export WORKSPACE=/tmp/workspace

apt update && apt install -y \
    wget \
    cmake \
    libblas-dev \
    liblapack-dev \
    build-essential \
    libboost-all-dev doxygen

    wget http://iss.ices.utexas.edu/projects/galois/downloads/Galois-2.2.1.tar.gz \
    && rm -rf Galois-2.2.1 || true \
    && tar xzvf Galois-2.2.1.tar.gz \
    && cd Galois-2.2.1/build \
    && mkdir release \
    && cd release \
    && cmake -DBoost_INCLUDE_DIR=/usr/include -DSKIP_COMPILE_APPS=ON ../..  \
    && make \
    && make install \
    && rm -rf $WORKSPACE
```

### Tools
- compiler: reasonable C++14 support is required (framework has been tested with GCC 5.3.1)
- build system: CMake 3.1 or higher


## Compilation

To compile the code, create a directory for the build and execute following commands:

```bash
cmake <options> ${PROJECT_DIR} \
make
```

where ${PROJECT_DIR} is the root directory of the project source. Options allow customizing which
parts of the project are compiled. By default tests are skipped.

- COMPILE_TESTS - wether the unit tests are compiled. This should be disabled if libunittest is not available (default: OFF)

Options are specified as -Doption=value, e.g. 
$ cmake -DCOMPILE_TESTS=ON ..


## Usage

This codebase contains a number of solvers based on this framework for common engineering problems.

```
multistep <dim> <p> <n> <scheme> <order> <steps> <dt>
```

```
./multistep 2 4 15 "1 | -1 | 0.5 0.5" 2 1000 0.001
```

