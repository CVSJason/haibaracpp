#pragma once

#include <memory>

namespace Haibara {

/// @brief 共享指针。相当于 Haibara Script 中的引用类型。
/// @tparam T 被指向的类型。
template <typename T>
using h_shared  = std::shared_ptr<T>;

/// @brief 独有指针。相当于 Haibara Script 中的 own 类型。
/// @tparam T 被指向的类型。
template <typename T>
using h_own     = std::unique_ptr<T>;

/// @brief 弱指针。相当于 Haibara Script 中的 weak 类型。
/// @tparam T 被指向的类型。
template <typename T>
using h_weak    = std::weak_ptr<T>;

/// @brief 一般指针。相当于 Haibara Script 中的 weak! 类型。
/// @tparam T 被指向的类型。
template <typename T>
using h_unowned = T *;
}