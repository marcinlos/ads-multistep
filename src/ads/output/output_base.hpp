#ifndef ADS_OUTPUT_OUTPUT_BASE_HPP_
#define ADS_OUTPUT_OUTPUT_BASE_HPP_

#include "ads/output/output_format.hpp"

namespace ads {
namespace output {


struct output_base {

    output_format format;

    output_base(const output_format& format)
    : format { format }
    { }

    void prepare_stream(std::ostream& os) const {
        os.precision(format.precision());
        os.setf(format.flags(), format.mask());
    }

    template <typename T>
    void print_one(T value, std::ostream& os) const {
        os.width(format.width());
        os << value;
    }

    template <typename Value, typename... Values>
    void print_row(std::ostream& os, Value x, Values... values) const {
        print_one(x, os);
        print_row(os, values...);
    }

    template <typename... Values>
    void print_row(std::ostream& os) const {
        os << '\n';
    }
};


}
}


#endif /* ADS_OUTPUT_OUTPUT_BASE_HPP_ */
