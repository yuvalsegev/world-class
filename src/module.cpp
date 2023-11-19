#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "harvest.hpp"
#include "iostream"
namespace py = pybind11;
using namespace world_class;

// Function that adds two NumPy arrays of type double
py::tuple harvest(py::array_t<double> array, int fs, double f0_floor, double f0_ceil, double frame_period) {

    // if (audio.size != buf2.size) {
    //     throw std::runtime_error("Input arrays must have the same size");
    // }

    // Pointers to the data in the NumPy arrays
    auto x_array = array.request();
    double *x = static_cast<double *>(x_array.ptr);
    int x_length = x_array.size;
    HarvestOption option;
    option.f0_floor = f0_floor;
    option.f0_ceil = f0_ceil;
    option.frame_period = frame_period;

    Harvest harvest = Harvest(fs, option);
    int f0_length = harvest.getSamples(fs, x_length);
    py::array_t<double> f0({f0_length});
    py::array_t<double> time_axis({f0_length});
    // for (size_t i = 0; i < x_length; i++)
    // {
    //     std::cout << i << " : " << x[i] << std::endl;
    // }
    
    py::print(f0_length);

	harvest.compute(x, x_length, static_cast<double *>(time_axis.request().ptr), static_cast<double *>(f0.request().ptr));

	for (size_t i = 0; i < f0_length; i++)
	{
		std::cout << i << " : " << static_cast<double *>(f0.request().ptr)[i] << std::endl;
	}


    return py::make_tuple(f0, time_axis);
}

// Create a Python module
PYBIND11_MODULE(harvest_lib, m) {
    m.def("harvest", &harvest, "Add two NumPy arrays of type double");
}
