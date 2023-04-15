#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

#include "brt/hittables/axis_aligned_rectangle.hpp"
#include "brt/hittables/bounding_box.hpp"
#include "brt/hittables/box.hpp"
#include "brt/hittables/bvh_node.hpp"
#include "brt/hittables/constant_density_medium.hpp"
#include "brt/hittables/hit_info.hpp"
#include "brt/hittables/hittable.hpp"
#include "brt/hittables/hittable_list.hpp"
#include "brt/hittables/moving_sphere.hpp"
#include "brt/hittables/rotate.hpp"
#include "brt/hittables/sphere.hpp"
#include "brt/hittables/translate.hpp"

#include "brt/materials/dielectric.hpp"
#include "brt/materials/diffuse_light.hpp"
#include "brt/materials/isotropic.hpp"
#include "brt/materials/lambertian.hpp"
#include "brt/materials/material.hpp"
#include "brt/materials/metal.hpp"

#include "brt/misc/axis.hpp"
#include "brt/misc/orthonormal_basis.hpp"
#include "brt/misc/perlin.hpp"
#include "brt/misc/plane.hpp"

#include "brt/render/camera.hpp"
#include "brt/render/image.hpp"
#include "brt/render/pixel.hpp"
#include "brt/render/renderer.hpp"

#include "brt/textures/checker.hpp"
#include "brt/textures/image.hpp"
#include "brt/textures/noise.hpp"
#include "brt/textures/solid_color.hpp"
#include "brt/textures/texture.hpp"

#include "brt/color.hpp"
#include "brt/moving_point3.hpp"
#include "brt/point3.hpp"
#include "brt/progress.hpp"
#include "brt/ray.hpp"
#include "brt/utils.hpp"
#include "brt/vector3.hpp"
