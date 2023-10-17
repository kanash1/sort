#pragma once

#ifndef SORT_H
#define SORT_H

#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <vector>
#include <cmath>
#include <type_traits>

namespace sort {

	template<class RandomIt, class Compare>
	void bubble(RandomIt first, RandomIt last, Compare comp) {

		if (first != last) {
			bool swapped = false;
			for (auto it_i = first; it_i + 1 != last; ++it_i) {
				swapped = false;
				for (auto it_j = first; it_j + 1 != last - (it_i - first); ++it_j)
					if (comp(*(it_j + 1), *it_j)) {
						std::iter_swap(it_j, it_j + 1);
						swapped = true;
					}

				if (!swapped) break;
			}
		}
	}

	template<class RandomIt>
	void bubble(RandomIt first, RandomIt last) {
		bubble(first, last, std::less<>());
	}

	template<class RandomIt, class Compare>
	void comb(RandomIt first, RandomIt last, Compare comp, const double factor = 1.247) {
		if (first != last) {
			if (!(factor > 1))
				throw std::out_of_range("The value of factor must be greater than one");

			double step = static_cast<double>(last - first) - 1;
			while (step >= 1) {
				for (auto it_i = first; it_i + static_cast<size_t>(step) != last; ++it_i)
					if (comp(*(it_i + static_cast<size_t>(step)), *it_i))
						std::iter_swap(it_i, it_i + static_cast<size_t>(step));

				step /= factor;
			}

			bubble(first, last);
		}
	}

	template<class RandomIt>
	void comb(RandomIt first, RandomIt last, const double factor = 1.247) {
		comb(first, last, std::less<>(), factor);
	}

	template<class RandomIt, class Compare>
	void insertion(RandomIt first, RandomIt last, Compare comp) {
		for (auto it = first; it != last; ++it)
			std::rotate(std::upper_bound(first, it, *it, comp), it, it + 1);
	}

	template<class RandomIt>
	void insertion(RandomIt first, RandomIt last) {
		insertion(first, last, std::less<>());
	}

	template<class RandomIt, class Compare>
	void shell(RandomIt first, RandomIt last, Compare comp) {
		for (auto diff = (last - first) / 2; diff != 0; diff /= 2)
			for (auto it_i = first + diff; it_i != last; ++it_i)
				for (auto it_j = it_i; it_j - first >= diff && comp(*it_j, *(it_j - diff)); it_j -= diff)
					std::iter_swap(it_j, it_j - diff);
	}

	template<class RandomIt>
	void shell(RandomIt first, RandomIt last) {
		shell(first, last, std::less<>());
	}

	template<class RandomIt, class Compare>
	void selection(RandomIt first, RandomIt last, Compare comp) {
		if (std::is_integral<std::iter_value_t<RandomIt>>::value)
			for (auto it = first; it != last; ++it)
				std::iter_swap(it, std::min_element(it, last, comp));
		else
			for (auto it_i = first; it_i != last; ++it_i) {
				auto min = *it_i;
				auto min_it = it_i;
				for (auto it_j = it_i + 1; it_j != last; ++it_j) {
					if (comp(*it_j, min)) {
						min = *it_j;
						min_it = it_j;
					}
				}
				std::iter_swap(it_i, min_it);
		}
	}

	template<class RandomIt>
	void selection(RandomIt first, RandomIt last) {
		selection(first, last, std::less<>());
	}

	template<class RandomIt, class Compare>
	void heap(RandomIt first, RandomIt last, Compare comp) {
		std::make_heap(first, last, comp);
		std::sort_heap(first, last, comp);
	}

	template<class RandomIt>
	void heap(RandomIt first, RandomIt last) {
		heap(first, last, std::less<>());
	}

	namespace detail {
		template<class RandomIt, class Compare>
		void __stooge(RandomIt first, RandomIt last, Compare comp) {
			if (first != last) {
				if (comp(*last, *first))
					std::iter_swap(first, last);

				if ((last - first) > 1) {
					auto offset = (last - first + 1) / 3;
					__stooge(first, last - offset, comp);
					__stooge(first + offset, last, comp);
					__stooge(first, last - offset, comp);
				}
			}
		}
	}

	template<class RandomIt, class Compare>
	void stooge(RandomIt first, RandomIt last, Compare comp) {
		if (first != last) {
			detail::__stooge(first, last - 1, comp);
		}
	}

	template<class RandomIt>
	void stooge(RandomIt first, RandomIt last) {
		stooge(first, last, std::less<>());
	}

	template<class RandomIt, class Compare>
	void gnome(RandomIt first, RandomIt last, Compare comp) {
		if (first != last) {
			size_t stop_offset = 2;
			auto it = first + 1;

			while (it != last) {
				if (comp(*it, *(it - 1))) {
					std::iter_swap(it, it - 1);
					if (--it == first)
						it = first + stop_offset++;
				} else
					it = first + stop_offset++;
			}
		}
	}

	template<class RandomIt>
	void gnome(RandomIt first, RandomIt last) {
		gnome(first, last, std::less<>());
	}

	namespace detail {
		template<class RandomIt, class OutIt, class Compare>
		void __merge(RandomIt first, RandomIt last, OutIt dest, Compare comp) {
			auto size = last - first;
			if (size < 2) return;

			auto mid = first + size / 2;
			__merge(first, mid, dest, comp);
			__merge(mid, last, dest, comp);

			std::merge(std::make_move_iterator(first), std::make_move_iterator(mid),
				std::make_move_iterator(mid), std::make_move_iterator(last), dest, comp);

			std::copy(std::make_move_iterator(dest), std::make_move_iterator(dest + size), first);
		}
	}

	template<class RandomIt, class Compare>
	void merge(RandomIt first, RandomIt last, Compare comp) {
		auto size = last - first;
		if (size < 2) return;
		std::vector<std::iter_value_t<RandomIt>> buffer(size);
		detail::__merge(first, last, buffer.begin(), comp);
	}

	template<class RandomIt>
	void merge(RandomIt first, RandomIt last) {
		merge(first, last, std::less<>());
	}

	namespace detail {
		template<class RandomIt, class Compare>
		RandomIt __pivot(RandomIt first, RandomIt last, Compare comp) {
			auto mid = first + (last - first) / 2;
			if (comp(*mid, *first))
				std::iter_swap(mid, first);
			if (comp(*(last - 1), *first))
				std::iter_swap((last - 1), first);
			if (comp(*(last - 1), *mid))
				std::iter_swap((last - 1), mid);
			return mid;
		}

		template<class RandomIt, class Compare>
		std::pair<RandomIt, RandomIt> __partition(RandomIt first, RandomIt last, Compare comp) {
			auto pivot = *__pivot(first, last, comp);
			auto middle_before_pivot = std::partition(first, last, [pivot, comp](const auto& val) { return comp(val, pivot); });
			auto middle_after_pivot = std::partition(middle_before_pivot, last, [pivot, comp](const auto& val) { return !comp(pivot, val); });
			return std::make_pair(middle_before_pivot, middle_after_pivot);
		}

		template<class RandomIt, class Compare>
		void __intro(RandomIt first, RandomIt last, Compare comp, size_t depth_limit) {
			if (last - first < 16)
				insertion(first, last, comp);
			else if (depth_limit == 0)
				heap(first, last, comp);
			else {
				auto middle = __partition(first, last, comp);
				--depth_limit;
				__intro(first, middle.first, comp, depth_limit);
				__intro(middle.second, last, comp, depth_limit);
			}
		}
	}

	template<class RandomIt, class Compare>
	void intro(RandomIt first, RandomIt last, Compare comp) {
		if (first != last) {
			const size_t depth_limit = static_cast<size_t>(std::log2(last - first));
			detail::__intro(first, last, comp, depth_limit);
		}
	}

	template<class RandomIt>
	void intro(RandomIt first, RandomIt last) {
		intro(first, last, std::less<>());
	}

	template<class RandomIt, class Compare>
	void quick(RandomIt first, RandomIt last, Compare comp) {
		if (first != last) {
			auto middle = detail::__partition(first, last, comp);
			quick(first, middle.first, comp);
			quick(middle.second, last, comp);
		}
	}

	template<class RandomIt>
	void quick(RandomIt first, RandomIt last) {
		quick(first, last, std::less<>());
	}
}

#endif // !SORT_H