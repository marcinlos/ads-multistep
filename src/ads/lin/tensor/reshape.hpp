#ifndef ADS_LIN_TENSOR_RESHAPE_HPP_
#define ADS_LIN_TENSOR_RESHAPE_HPP_

#include <array>
#include "ads/lin/tensor/base.hpp"
#include "ads/lin/tensor/view.hpp"


namespace ads {
namespace lin {

template <typename T, std::size_t Rank, typename Impl, typename... Sizes>
tensor_view<T, sizeof...(Sizes)> reshape(tensor_base<T, Rank, Impl>& tensor, Sizes... sizes) {
    constexpr auto N = sizeof...(Sizes);
    std::array<std::size_t, N> sz { sizes... };
    return { tensor.data(), sz };
}

template <typename T, std::size_t Rank, typename Impl, typename... Sizes>
tensor_view<T, sizeof...(Sizes)> reshape(const tensor_base<T, Rank, Impl>& tensor, Sizes... sizes) {
    constexpr auto N = sizeof...(Sizes);
    std::array<std::size_t, N> sz { sizes... };
    return { tensor.data(), sz };
}


}
}


#endif /* ADS_LIN_TENSOR_RESHAPE_HPP_ */
