#ifndef ADS_OUTPUT_OUTPUT_MANAGER_BASE_HPP_
#define ADS_OUTPUT_OUTPUT_MANAGER_BASE_HPP_

#include <cstddef>
#include <string>
#include <fstream>
#include <boost/format.hpp>


namespace ads {

template <typename Derived>
class output_manager_base {
public:

    template <typename Solution>
    void to_file(const Solution& sol, const std::string& file_pattern, int iter) {
        auto name = str(boost::format(file_pattern) % iter);
        derived()->to_file(sol, name);
    }

    template <typename Solution>
    void to_file(const Solution& sol, const std::string& output_file) {
        std::ofstream os { output_file };
        derived()->write(sol, os);
    }

private:
    Derived* derived() {
        return static_cast<Derived*>(this);
    }
};

}

#endif /* ADS_OUTPUT_OUTPUT_MANAGER_BASE_HPP_ */
