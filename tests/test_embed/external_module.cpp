#include <pybind11/pybind11.h>

namespace py = pybind11;

/* Simple test module/test class to check that the referenced internals data of external pybind11
 * modules aren't preserved over a finalize/initialize.
 */

PYBIND11_MODULE(external_module,
                m,
                py::mod_gil_not_used(),
                py::multiple_interpreters::per_interpreter_gil()) {

    class A {
    public:
        explicit A(int value) : v{value} {};
        int v;
    };

    py::class_<A>(m, "A").def(py::init<int>()).def_readwrite("value", &A::v);

    m.def("internals_at",
          []() { return reinterpret_cast<uintptr_t>(&py::detail::get_internals()); });
}
