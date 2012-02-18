#include "visualization/viewer_adapter.h"
#include "visualization/draw_util.h"

#include "io/point.h"

#include "convex_hull.h"

using namespace visualization;
using geom::structures::point_type;
using geom::structures::contour_type;

struct convex_hull_viewer : viewer_adapter
{
    void draw(drawer_type & drawer)     const;
    void print(printer_type & printer)  const;

    bool on_double_click(point_type const & pt);
    bool on_key(int key);

private:
    std::vector<point_type>         pts_; 
    std::unique_ptr<contour_type>   cnt_;
};

void convex_hull_viewer::draw(drawer_type & drawer) const
{
    drawer.set_color(Qt::blue);
    for (point_type const & pt : pts_)
        drawer.draw_point(pt, 3);

    if (cnt_)
    {
        drawer.set_color(Qt::red);
        visualization::draw(drawer, *cnt_);
    }
}

void convex_hull_viewer::print(printer_type & printer) const
{
    printer.corner_stream() << "Points num: " << pts_.size() << endl;
    if (cnt_)
        printer.corner_stream() <<"Convex hull vertices num: " << cnt_->vertices_num();
}

bool convex_hull_viewer::on_double_click(point_type const & pt)
{
    pts_.push_back(pt);
    cnt_.reset();
    return true;
}

bool convex_hull_viewer::on_key(int key)
{
    switch (key)
    {
    case Qt::Key_Return: 
        if (pts_.size() >= 2)
        {
            cnt_.reset(new contour_type(geom::algorithms::convex_hull::andrews(pts_)));
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
