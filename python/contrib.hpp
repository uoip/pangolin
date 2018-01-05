#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <pangolin/pangolin.h>


namespace py = pybind11;
using namespace pybind11::literals;



namespace pangolin {

namespace {

void DrawPoints(py::array_t<double> points) {
    auto r = points.unchecked<2>();
    glBegin(GL_POINTS);
    for (ssize_t i = 0; i < r.shape(0); ++i) {
        glVertex3d(r(i, 0), r(i, 1), r(i, 2));
    }
    glEnd();
}

void DrawPoints(py::array_t<double> points, py::array_t<double> colors) {
    auto r = points.unchecked<2>();
    auto rc = colors.unchecked<2>();

    glBegin(GL_POINTS);
    for (ssize_t i = 0; i < r.shape(0); ++i) {
        glColor3f(rc(i, 0), rc(i, 1), rc(i, 2));
        glVertex3d(r(i, 0), r(i, 1), r(i, 2));
    }
    glEnd();
}


void DrawCameras(py::array_t<double> cameras, float w=1.0, float h_ratio=0.75, float z_ratio=0.6) {
    auto r = cameras.unchecked<3>();

    float h = w * h_ratio;
    float z = w * z_ratio;

    for (ssize_t i = 0; i < r.shape(0); ++i) {
        glPushMatrix();
        // glMultMatrixd(r.data(i, 0, 0));
        glMultTransposeMatrixd(r.data(i, 0, 0));

        glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(w,h,z);
        glVertex3f(0,0,0);
        glVertex3f(w,-h,z);
        glVertex3f(0,0,0);
        glVertex3f(-w,-h,z);
        glVertex3f(0,0,0);
        glVertex3f(-w,h,z);

        glVertex3f(w,h,z);
        glVertex3f(w,-h,z);

        glVertex3f(-w,h,z);
        glVertex3f(-w,-h,z);

        glVertex3f(-w,h,z);
        glVertex3f(w,h,z);

        glVertex3f(-w,-h,z);
        glVertex3f(w,-h,z);
        glEnd();

        glPopMatrix();
    }
}

void DrawCamera(py::array_t<double> camera, float w=1.0, float h_ratio=0.75, float z_ratio=0.6) {
    auto r = camera.unchecked<2>();

    float h = w * h_ratio;
    float z = w * z_ratio;

    glPushMatrix();
    // glMultMatrixd(r.data(0, 0));
    glMultTransposeMatrixd(r.data(0, 0));

    glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(w,h,z);
    glVertex3f(0,0,0);
    glVertex3f(w,-h,z);
    glVertex3f(0,0,0);
    glVertex3f(-w,-h,z);
    glVertex3f(0,0,0);
    glVertex3f(-w,h,z);

    glVertex3f(w,h,z);
    glVertex3f(w,-h,z);

    glVertex3f(-w,h,z);
    glVertex3f(-w,-h,z);

    glVertex3f(-w,h,z);
    glVertex3f(w,h,z);

    glVertex3f(-w,-h,z);
    glVertex3f(w,-h,z);
    glEnd();

    glPopMatrix();
}


void DrawLine(py::array_t<double> points, float point_size=0) {
    auto r = points.unchecked<2>();
    glBegin(GL_LINES);
    for (ssize_t i = 0; i < r.shape(0)-1; ++i) {
        glVertex3d(r(i, 0), r(i, 1), r(i, 2));
        glVertex3d(r(i+1, 0), r(i+1, 1), r(i+1, 2));
    }
    glEnd();

    if(point_size > 0) {
        glPointSize(point_size);
        glBegin(GL_POINTS);
        for (ssize_t i = 0; i < r.shape(0); ++i) {
            glVertex3d(r(i, 0), r(i, 1), r(i, 2));
        }
        glEnd();
    }
}



void DrawLines(py::array_t<double> points, float point_size=0) {
    auto r = points.unchecked<2>();

    glBegin(GL_LINES);
    for (ssize_t i = 0; i < r.shape(0); ++i) {
        glVertex3d(r(i, 0), r(i, 1), r(i, 2));
        glVertex3d(r(i, 3), r(i, 4), r(i, 5));
    }
    glEnd();

    if(point_size > 0) {
        glPointSize(point_size);
        glBegin(GL_POINTS);
        for (ssize_t i = 0; i < r.shape(0); ++i) {
            glVertex3d(r(i, 0), r(i, 1), r(i, 2));
            glVertex3d(r(i, 3), r(i, 4), r(i, 5));
        }
        glEnd();
    }
}


void DrawLines(py::array_t<double> points, py::array_t<double> points2, float point_size=0) {
    auto r = points.unchecked<2>();
    auto r2 = points2.unchecked<2>();
    glBegin(GL_LINES);
    for (ssize_t i = 0; i < std::min(r.shape(0), r2.shape(0)); ++i) {
        glVertex3d(r(i, 0), r(i, 1), r(i, 2));
        glVertex3d(r2(i, 0), r2(i, 1), r2(i, 2));
    }
    glEnd();

    if(point_size > 0) {
        glPointSize(point_size);
        glBegin(GL_POINTS);
        for (ssize_t i = 0; i < std::min(r.shape(0), r2.shape(0)); ++i) {
            glVertex3d(r(i, 0), r(i, 1), r(i, 2));
            glVertex3d(r2(i, 0), r2(i, 1), r2(i, 2));
        }
        glEnd();
    }
}


void DrawBoxes(py::array_t<double> cameras, py::array_t<double> sizes) {
    auto r = cameras.unchecked<3>();
    auto rs = sizes.unchecked<2>();

    for (ssize_t i = 0; i < r.shape(0); ++i) {
        glPushMatrix();
        // glMultMatrixd(r.data(i, 0, 0));
        glMultTransposeMatrixd(r.data(i, 0, 0));

        float w = *rs.data(i, 0) / 2.0;  // w/2
        float h = *rs.data(i, 1) / 2.0;
        float z = *rs.data(i, 2) / 2.0;

        glBegin(GL_LINES);
        glVertex3f(-w, -h, -z);
        glVertex3f(w, -h, -z);
        glVertex3f(-w, -h, -z);
        glVertex3f(-w, h, -z);
        glVertex3f(-w, -h, -z);
        glVertex3f(-w, -h, z);

        glVertex3f(w, h, -z);
        glVertex3f(-w, h, -z);
        glVertex3f(w, h, -z);
        glVertex3f(w, -h, -z);
        glVertex3f(w, h, -z);
        glVertex3f(w, h, z);

        glVertex3f(-w, h, z);
        glVertex3f(w, h, z);
        glVertex3f(-w, h, z);
        glVertex3f(-w, -h, z);
        glVertex3f(-w, h, z);
        glVertex3f(-w, h, -z);

        glVertex3f(w, -h, z);
        glVertex3f(-w, -h, z);
        glVertex3f(w, -h, z);
        glVertex3f(w, h, z);
        glVertex3f(w, -h, z);
        glVertex3f(w, -h, -z);
        glEnd();

        glPopMatrix();
    }
}


// TODO:
// draw surface

}




void declareContrib(py::module & m) {

    m.def("DrawPoints", (void (*) (py::array_t<double>)) &DrawPoints, 
        "points"_a);
    m.def("DrawPoints", (void (*) (py::array_t<double>, py::array_t<double>)) &DrawPoints,
        "points"_a, "colors"_a);

    m.def("DrawLine", (void (*) (py::array_t<double>, float)) &DrawLine,
        "points"_a, "point_size"_a=0);
    m.def("DrawLines", (void (*) (py::array_t<double>, float)) &DrawLines,
        "points"_a, "point_size"_a=0);
    m.def("DrawLines", (void (*) (py::array_t<double>, py::array_t<double>, float)) &DrawLines,
        "points"_a, "points2"_a, "point_size"_a=0);

    m.def("DrawCameras", &DrawCameras,
        "poses"_a, "w"_a=1.0, "h_ratio"_a=0.75, "z_ratio"_a=0.6);
    m.def("DrawCamera", &DrawCamera,
    "poses"_a, "w"_a=1.0, "h_ratio"_a=0.75, "z_ratio"_a=0.6);

    m.def("DrawBoxes", &DrawBoxes,
        "poses"_a, "sizes"_a);

}

}