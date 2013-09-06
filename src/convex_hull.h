#pragma once

#include "geom/primitives/contour.h"

namespace geom {
namespace algorithms {
namespace convex_hull {

    using geom::structures::point_type;
    using geom::structures::contour_type;

    contour_type andrews(std::vector<point_type> pts); 

}}}

