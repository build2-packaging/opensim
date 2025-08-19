# libopensim - SimTK OpenSim Musculoskeletal Simulation C++ library

This is a `build2` package for the [`opensim`](https://opensim.stanford.edu)
C++ library. OpenSim is software that lets users develop models of
musculoskeletal structures and create dynamic simulations of movement.

## Unsupported components:

- The OpenSim applications (`opensim-cmd`, `opensense`, etc.) are not
  supported.

- CasADi support for the OpenSim Moco library is disabled.

## Supported platforms

- Windows
- Linux
- macOS

See the package `manifest` for disabled build configurations. Note that most
platform issues are due to the dependency on `libsimbody` so see that
package's `PACKAGE-README.md` for more information.

## Usage

To start using `libopensim` in your project, add the following `depends` value
to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libopensim ^4.5.2
```

Then import the required library in your `buildfile`:

```
import libs = libopensim%lib{osimAnalyses}
```

Note that due to the way the library dependency graph is arranged only one
library needs to be imported and linked:

```
osimLepton
 └─osimCommon
    └─osimSimulation
       └─osimActuators
          └─osimAnalyses
             └─osimTools
                └─osimMoco
```

So for example if you need `osimSimulation` and `osimAnalyses` you only need
to import and link to `osimAnalyses`.

## Importable targets

This package provides the following importable targets:

```
lib{osimLepton}
lib{osimCommon}
lib{osimSimulation}
lib{osimActuators}
lib{osimAnalyses}
lib{osimTools}
lib{osimMoco}
```

- `osimLepton`: A small C++ library for parsing, evaluating, differentiating,
  and analyzing mathematical expressions.

- `osimMoco`: Solves optimal control problems with musculoskeletal models
  defined in OpenSim, using direct collocation.

## Configuration variables

This package does not provide any configuration variables.
