#pragma once

#ifndef SORT_H
#define SORT_H

#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <vector>
#include <cmath>

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
		bubble(first, last, std::less<std::iter_value_t<RandomIt>>());
	}

	template<class Collection, class Compare>
	void bubble(Collection& coll, Compare comp) {
		bubble(coll.begin(), coll.end(), comp);
	}

	template<class Collection>
	void bubble(Collection& coll) {
		bubble(coll.begin(), coll.end());
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
		comb(first, last, std::less<std::iter_value_t<RandomIt>>(), factor);
	}

	template<class Collection, class Compare>
	void comb(Collection& coll, Compare comp, const double factor = 1.247) {
		comb(coll.begin(), coll.end(), comp, factor);
	}

	template<class Collection>
	void comb(Collection& coll, const double factor = 1.247) {
		comb(coll.begin(), coll.end(), factor);
	}

	template<class RandomIt, class Compare>
	void insertion(RandomIt first, RandomIt last, Compare comp) {
		for (auto it = first; it != last; ++it)
			std::rotate(std::upper_bound(first, it, *it, comp), it, it + 1);
	}

	template<class RandomIt>
	void insertion(RandomIt first, RandomIt last) {
		insertion(first, last, std::less<std::iter_value_t<RandomIt>>());
	}

	template<class Collection>
	void insertion(Collection& coll) {
		insertion(coll.begin(), coll.end());
	}

	template<class Collection, class Compare>
	void insertion(Collection& coll, Compare comp) {
		insertion(coll.begin(), coll.end(), comp);
	}

	template<class RandomIt, class Compare>
	void selection(RandomIt first, RandomIt last, Compare comp) {
		for (auto it = first; it != last; ++it)
			std::iter_swap(it, std::min_element(it, last, comp));
	}

	template<class RandomIt>
	void selection(RandomIt first, RandomIt last) {
		selection(first, last, std::less<std::iter_value_t<RandomIt>>());
	}

	template<class Collection, class Compare>
	void selection(Collection& coll, Compare comp) {
		selection(coll.begin(), coll.end(), comp);
	}

	template<class Collection>
	void selection(Collection& coll) {
		selection(coll.begin(), coll.end());
	}

	template<class RandomIt, class Compare>
	void heap(RandomIt first, RandomIt last, Compare comp) {
		std::make_heap(first, last, comp);
		std::sort_heap(first, last, comp);
	}

	template<class RandomIt>
	void heap(RandomIt first, RandomIt last) {
		heap(first, last, std::less<std::iter_value_t<RandomIt>>());
	}

	template<class Collection, class Compare>
	void heap(Collection& coll, Compare comp) {
		heap(coll.begin(), coll.end(), comp);
	}

	template<class Collection>
	void heap(Collection& coll) {
		heap(coll.begin(), coll.end());
	}

	template<class RandomIt, class Compare>
	void stooge(RandomIt first, RandomIt last, Compare comp) {
		if (first != last) {
			if (comp(*(last - 1), *first))
				std::iter_swap(first, (last - 1));

			if ((last - first) > 2) {
				auto offset = (last - first) / 3;
				stooge(first, last - 1 - offset);
				stooge(first + offset, last - 1);
				stooge(first, last - 1 - offset);
			}
		}
	}

	template<class RandomIt>
	void stooge(RandomIt first, RandomIt last) {
		stooge(first, last, std::less<std::iter_value_t<RandomIt>>());
	}

	template<class Collection, class Compare>
	void stooge(Collection& coll, Compare comp) {
		stooge(coll.begin(), coll.end(), comp);
	}

	template<class Collection>
	void stooge(Collection& coll) {
		stooge(coll.begin(), coll.end());
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
		gnome(first, last, std::less<std::iter_value_t<RandomIt>>());
	}

	template<class Collection, class Compare>
	void gnome(Collection& coll, Compare comp) {
		gnome(coll.begin(), coll.end(), comp);
	}

	template<class Collection>
	void gnome(Collection& coll) {
		gnome(coll.begin(), coll.end());
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
		merge(first, last, std::less<std::iter_value_t<RandomIt>>());
	}

	template<class Collection, class Compare>
	void merge(Collection& coll, Compare comp) {
		merge(coll.begin(), coll.end(), comp);
	}

	template<class Collection>
	void merge(Collection& coll) {
		merge(coll.begin(), coll.end());
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
		intro(first, last, std::less<std::iter_value_t<RandomIt>>());
	}

	template<class Collection, class Compare>
	void intro(Collection& coll, Compare comp) {
		intro(coll.begin(), coll.end(), comp);
	}

	template<class Collection>
	void intro(Collection& coll) {
		intro(coll.begin(), coll.end());
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
		quick(first, last, std::less<std::iter_value_t<RandomIt>>());
	}

	template<class Collection, class Compare>
	void quick(Collection& coll, Compare comp) {
		quick(coll.begin(), coll.end(), comp);
	}

	template<class Collection>
	void quick(Collection& coll) {
		quick(coll.begin(), coll.end());
	}

}

#endif // !SORT_H