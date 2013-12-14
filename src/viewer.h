#include "visualization/viewer_adapter.h"
#include "visualization/draw_util.h"

#include "io/point.h"

#include "points_diameter.h"

using namespace visualization;
using geom::structures::point_type;
using geom::structures::contour_type;

struct point_diameter_viewer : viewer_adapter
{
    void draw(drawer_type & drawer)     const;
    void print(printer_type & printer)  const;

    bool on_double_click(point_type const & pt);
    bool on_key(int key);

private:
    std::vector<point_type>         pts_; 
    std::unique_ptr<segment_type>   cnt_;
};

void point_diameter_viewer::draw(drawer_type & drawer) const
{
    drawer.set_color(Qt::blue);
    for (point_type const & pt : pts_)
        drawer.draw_point(pt, 3);

    if (cnt_)
    {
        drawer.set_color(Qt::red);
        drawer.draw_line(*cnt_);
//        visualization::draw(drawer, *cnt_);
    }
}

void point_diameter_viewer::print(printer_type & printer) const
{
    printer.corner_stream() << "Points num: " << pts_.size() << endl;
//    if (cnt_)
//        printer.corner_stream() <<"Convex hull vertices num: " << cnt_->;
}

bool point_diameter_viewer::on_double_click(point_type const & pt)
{
    pts_.push_back(pt);
    cnt_.reset();
    return true;
}

bool point_diameter_viewer::on_key(int key)
{
    switch (key)
    {
    case Qt::Key_Return: 
        if (pts_.size() >= 2)
        {
            cnt_.reset(new segment_type(geom::algorithms::points_diameter::calc_points_diameter(pts_)));
            return true;
        }
        break;
    case Qt::Key_S:
        {
            std::string filename = QFileDialog::getSaveFileName(
                get_wnd(), 
                "Save Points"
            ).toStdString();
            if (filename != "")
            {
                std::ofstream out(filename.c_str());
                boost::copy(pts_, std::ostream_iterator<point_type>(out, "\n"));
            }
        }
        break;
    case Qt::Key_L:
        {
            std::string filename = QFileDialog::getOpenFileName(
                get_wnd(), 
                "Load Points"
            ).toStdString();
            if (filename != "")
            {
                std::ifstream in(filename.c_str());
                std::istream_iterator<point_type> beg(in), end;
                pts_.assign(beg, end);
                cnt_.reset();
                return true;
            }
        }
    }
    return false;
}
