#pragma once
#include "geom/primitives/segment.h"
#include "geom/primitives/contour.h"

namespace geom {
namespace algorithms {
namespace points_diameter {
    using geom::structures::point_type;
    using geom::structures::segment_type;
    using geom::structures::contour_type;

    segment_type calc_points_diameter(std::vector<point_type> pts);
}
}
}
