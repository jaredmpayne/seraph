#pragma once

// Allows an overridable syntax for `std::visit` calls.
//
// Example:
//
// ```
// std::visit(
//     VisitSet {
//         [](const T1 &) { ... },
//         [](const T2 &) { ... },
//         [](const auto &) { (default case) }
//     },
//     variant
// );
// ```
template<class... Ts>
struct VisitSet : Ts... {
    
    using Ts::operator()...;
};
