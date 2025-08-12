./: {*/ -build/} doc{README.md PACKAGE-README.md CHANGELOG.md} legal{LICENSE.txt} manifest

# Don't install tests.
#
tests/: install = false
