# opensim - SimTK OpenSim Musculoskeletal Simulation C++ library

This is a `build2` package repository for
[`opensim-core`](https://github.com/opensim-org/opensim-core), a C++ library
for developing models of musculoskeletal structures and creating dynamic
simulations of movement.

This file contains setup instructions and other details that are more
appropriate for development rather than consumption. If you want to use
`libopensim` in your `build2`-based project, then instead see the accompanying
[`PACKAGE-README.md`](libopensim/PACKAGE-README.md) file.

The development setup for `opensim` uses the standard `bdep`-based workflow.
For example:

```
git clone --recursive https://github.com/build2-packaging/opensim.git
cd opensim

bdep init -C @gcc cc config.cxx=g++
bdep update
bdep test
```
