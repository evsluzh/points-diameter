#include "points_diameter.h"
#include "convex_hull.h"
#include <cmath>

namespace geom {
namespace algorithms {
namespace points_diameter {

    segment_type calc_points_diameter(std::vector<point_type> points) {
        contour_type hull = geom::algorithms::convex_hull::andrews(points);
        int n = hull.vertices_num();
        int current_point = -1;
        int64 ans_value = -1;
        int ans_p1 = -1, ans_p2 = -1;

        for (int i = 0; i < n; ++i) {
            int ni = (i == n - 1) ? 0 : i + 1;
            segment_type cur_edge = segment_type(hull[i], hull[ni]);

            int32 a = cur_edge[1].y - cur_edge[0].y;
            int32 b = cur_edge[0].x - cur_edge[1].x;
            int32 c = - cur_edge[0].x * a - cur_edge[0].y * b;
            if (current_point == -1) {
                int32 cmax = 0;
                for (int j = 0; j < n; ++j) {
                    int32 d = abs(a * hull[j].x + b * hull[j].y + c);
                    if (current_point == -1 || d > cmax) {
                        current_point = j;
                        cmax = d;
                    }
                }
            } else {
                int32 current_distance = abs(a * hull[current_point].x + b * hull[current_point].y + c);
                while (true) {
                    int next_point = (current_point == n - 1) ? 0 : current_point + 1;
                    int32 next_distance = abs(a * hull[next_point].x + b * hull[next_point].y + c);
                    if (next_distance <= current_distance) {
                        break;
                    }
                    current_distance = next_distance;
                    current_point = next_point;
                    next_point = (next_point == n - 1) ? 0 : next_point + 1;
                }
            }
            std::cout << "Edge " << i << " Point " << current_point << std::endl;

            int32 dx = cur_edge[0].x - hull[current_point].x;
            int32 dy = cur_edge[0].y - hull[current_point].y;
            int64 d = (int64)dx * dx + (int64)dy * dy;

            if (d > ans_value) {
                ans_value = d;
                ans_p1 = current_point;
                ans_p2 = i;
            }

            dx = cur_edge[1].x - hull[current_point].x;
            dy = cur_edge[1].y - hull[current_point].y;
            d = (int64)dx * dx + (int64)dy * dy;

            if (d > ans_value) {
                ans_value = d;
                ans_p1 = current_point;
                ans_p2 = ni;
            }
        }
        std::cout << "ANS =" <<  ans_value << std::endl;
//        ans_value = 0;
//        for (int i = 0; i < n; ++i) {
//            for (int j = 0; j < n; ++j) if (i != j) {
//                int32 dx = hull[i].x - hull[j].x;
//                int32 dy = hull[i].y - hull[j].y;
//                int64 d = (int64)dx * dx + (int64)dy * dy;
//                if (d > ans_value) {
//                    ans_value = d;
//                }
//            }
//        }
//        std::cout << "OPTIMAL =" <<  ans_value << std::endl;
        return segment_type(hull[ans_p1], hull[ans_p2]);
    }
}
}
}
