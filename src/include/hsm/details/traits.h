#pragma once

#include <boost/hana.hpp>

namespace hsm {

    namespace bh{
        using namespace boost::hana; 
    };

    auto has_transition_table = bh::is_valid([](auto&& state) -> decltype(state.make_transition_table()) { });
}