#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "models.h"

namespace py = pybind11;

PYBIND11_MODULE(LNMM, m)
{
    py::class_<LNMM>(m, "LNMM")
        .def(py::init<double, double, int, int, double, bool>())
        .def("Fit", &LNMM::Fit)
        .def("get_beta", &LNMM::get_beta)
        .def("get_sigma", &LNMM::get_sigma)
}
