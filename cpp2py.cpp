#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "models.h"

namespace py = pybind11;

PYBIND11_MODULE(LNMM, m)
{
    py::class_<LNMM>(m, "LNMM")
        .def(py::init<double, double, int, int, double, bool>())
        .def("fit", &LNMM::fit)
        .def("get_beta", &LNMM::get_beta)
        .def("get_sigma", &LNMM::get_sigma)
        .def("get_beta_trace", &LNMM::get_beta_trace)
        .def("get_sigma_trace", &LNMM::get_sigma_trace)
        .def("get_z_trace", &LNMM::get_z_trace);
}
