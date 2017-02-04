#pragma once

#include <set>

#include "rec/util/STL.h"

namespace rec {
namespace util {

template <typename Type>
struct Range {
    Type begin_;
    Type end_;

    Range() { clear(); }
    Range(Type b, Type e) : begin_(b), end_(e) { DCHECK_LE(b, e); }

    using Set = std::set<Range>;
    using Vector = vector<Range>;

    void clear() { begin_ = end_ = Type(0); }
    Type size() const { return end_ - begin_; }
    bool empty() const { return !size(); }

    bool operator<(const Range& x) const {
        return begin_ < x.begin_ || (begin_ == x.begin_ && end_ < x.end_);
    }

    bool operator<=(const Range& x) const { return !(x < *this); }
    bool operator>(const Range& x) const { return x < *this; }
    bool operator>=(const Range& x) const { return x <= *this; }
    bool operator!=(const Range& x) const { return !(x == *this); }

    bool operator==(const Range& x) const {
        return begin_ == x.begin_ && end_ == x.end_;
    }

    const String toString() const {
        return String(begin_) + "-" + String(end_);
    }

  private:
    JUCE_LEAK_DETECTOR(Range);
};

template <typename Type>
Range<Type> makeRange(Type begin, Type end) {
    return Range<Type>(begin, end);
}

template <typename Type, typename Selection>
void insertRange(const Range<Type>& range, Selection *selection) {
    if (!range.empty())
        stl::insert(range, selection);
}

template <typename Type, typename Selection>
void insertRange(Type begin, Type end, Selection *selection) {
    insertRange(makeRange(begin, end), selection);
}

}  // namespace util
}  // namespace rec
