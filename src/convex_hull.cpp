#include "stdafx.h"

#include "convex_hull.h"

namespace geom {
namespace predicates {

    using geom::structures::point_type;
    
    enum turn_type
    {
        COLLINEAR = 0, LEFT, RIGHT
    };
    
    namespace
    {
        template<typename Scalar>
        int sgn(Scalar x)
        {
            if (x == 0)
                return 0;
            else
                return x < 0 ? -1 : 1;
        }
    }

    turn_type turn( point_type const & a,
                    point_type const & b,
                    point_type const & c )
    {
        auto v1 = b - a;
        auto v2 = c - a;
        
        auto sign = sgn(v1 ^ v2);
        
        switch (sign)
        {
            case -1: return RIGHT;
            case  1: return LEFT;
            default: return COLLINEAR;
        }
    }
}}

namespace geom {
namespace structures {
    
    contour_type::contour_type(std::vector<point_type> && pts)
        : pts_(std::move(pts))
    {}
    
    struct contour_builder_type
    {
        void add_point(point_type const & pt)
        {
            pts_.push_back(pt);
        }
        
        contour_type get_result()
        {
            return contour_type(std::move(pts_));
        }
        
    private:
        std::vector<point_type> pts_;
    };
}}


namespace geom {
namespace algorithms {
namespace convex_hull {

    template<class Iter, class Func>
    void find_chain(Iter beg, Iter end, Func f)
    {
        using namespace geom::predicates;

        std::vector<Iter> stack;
        stack.push_back(beg);
        while (++beg != end)
        {
            size_t N = stack.size();

            while ((N > 1) && (turn(*stack[N - 2], *stack[N - 1], *beg) == RIGHT))
            {
                stack.pop_back();
                --N;
            }
            stack.push_back(beg);
        }
        for (auto it = stack.begin() + 1, end = stack.end() - 1; it != end; ++it)
            f(**it);
    }

    contour_type andrews(std::vector<point_type> pts)
    {
        boost::sort(pts);
        pts.erase(boost::unique<boost::return_found>(pts), pts.end());
        if (pts.size() < 2)
            throw std::logic_error("not enough points to build convex hull");

        geom::structures::contour_builder_type builder;

        auto f = [&] (point_type const & pt) { builder.add_point(pt); };

        builder.add_point(pts.front());
        find_chain(pts.begin(), pts.end(), f);
        builder.add_point(pts.back());
        find_chain(pts.rbegin(), pts.rend(), f);

        return builder.get_result();
    }

}}}
