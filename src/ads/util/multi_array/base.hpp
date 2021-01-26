#ifndef ADS_UTIL_MULTI_ARRAY_BASE_HPP_
#define ADS_UTIL_MULTI_ARRAY_BASE_HPP_

#include <cstddef>
#include <type_traits>
#include "ads/util/meta.hpp"
#include "ads/util/multi_array/ordering/standard.hpp"


namespace ads {

template <
    typename T,
    std::size_t Rank,
    typename Array,
    template <std::size_t> class Order = standard_ordering
>
struct multi_array_base: private Order<Rank> {
public:
    using Ordering = Order<Rank>;
    using Self = multi_array_base<T, Rank, Array>;
    using size_array = typename Ordering::size_array;

    multi_array_base(const size_array& sizes)
    : Ordering { sizes }
    { }

    template <typename... Indices>
    const T& operator ()(Indices... indices) const {
        check_indices_(indices...);
        std::size_t lin_idx = Ordering::linear_index(indices...);
        return static_cast<const Array*>(this)->storage_(lin_idx);
    }

    template <typename... Indices>
    T& operator ()(Indices... indices) {
        check_indices_(indices...);
        std::size_t lin_idx = Ordering::linear_index(indices...);
        return static_cast<Array*>(this)->storage_(lin_idx);
    }

    std::size_t size(std::size_t dim) const {
        return Ordering::size(dim);
    }

    std::size_t size() const {
        return Ordering::size();
    }

    size_array sizes() const {
        return Ordering::sizes();
    }

private:
    template <typename... Indices>
    void check_indices_(Indices...) const {
        static_assert(sizeof...(Indices) == Rank, "Invalid number of indices");
        static_assert(util::all_<std::is_integral, Indices...>::value, "Indices need to be of integral type");
    }
};

}


#endif /* ADS_UTIL_MULTI_ARRAY_BASE_HPP_ */
