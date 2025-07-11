#pragma once

#include "state.hpp"

namespace openturbine {

template <typename DeviceType>
inline void CopyStateData(State<DeviceType>& copy, const State<DeviceType>& old) {
    copy.time_step = old.time_step;
    Kokkos::deep_copy(copy.x, old.x);
    Kokkos::deep_copy(copy.q_delta, old.q_delta);
    Kokkos::deep_copy(copy.q_prev, old.q_prev);
    Kokkos::deep_copy(copy.q, old.q);
    Kokkos::deep_copy(copy.v, old.v);
    Kokkos::deep_copy(copy.vd, old.vd);
    Kokkos::deep_copy(copy.a, old.a);
    Kokkos::deep_copy(copy.f, old.f);
    Kokkos::deep_copy(copy.tangent, old.tangent);
}

}  // namespace openturbine
