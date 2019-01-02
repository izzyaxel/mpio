#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include <array>
#include <iostream>

template <typename T> using SP = std::shared_ptr<T>;
template <typename T, typename... Args> SP<T> MS(Args&&... args)
{
	return std::make_shared<T>(std::forward<Args&&>(args)...);
}

template <typename T> using UP = std::unique_ptr<T>;
template <typename T, typename... Args> UP<T> MU(Args&&... args)
{
	return std::make_unique<T>(std::forward<Args&&>(args)...);
}

template <typename T> using WP = std::weak_ptr<T>;
template <typename T> WP<T> MW(SP<T> in)
{
	return std::weak_ptr<T>(in);
}

using i64 = int64_t;
using u64 = uint64_t;
using i32 = int32_t;
using u32 = uint32_t;
using i16 = int16_t;
using u16 = uint16_t;
using i8 = int8_t;
using u8 = uint8_t;

using String = std::string;

template <typename T> using Vector = std::vector<T>;
template <typename T, size_t U> using Array = std::array<T, U>;

#define LOG(severity, message) std::cout << "[" << severity << "] IN: " << __PRETTY_FUNCTION__ << " AT: " << __FILE__ << ":" << __LINE__ << " WHAT: " << message << std::endl;
