# Basic Ray Tracing (BRT)

An implementation of a CPU Ray Tracing engine, created by following the "Ray Tracing in One Weekend" tutorial (actually, it took me nearly one week for the first part).

![Sample render](images/lots-of-features.png)

## Build

Use `cmake` and `make` to build the project:

```
cd build
cmake ..
make
```

## Usage

Simply run the build executable, and place the output PPM on a file:

```
build/BasicRayTracing > output.ppm
```

## Resources

- [Ray Tracing in One Weekend - The Book Series](https://raytracing.github.io/): the main tutorial
- [stb](https://github.com/nothings/stb): header-only image library
