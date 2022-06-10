#ifndef __OBSERVER_PTR_HPP__
#define __OBSERVER_PTR_HPP__

// I was reading an article by Bjarne Stroustrup:
// "Abandon observer_ptr": https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1408r0.pdf
// In essence, when requiring a pointer that does not require ownership semantics we can use this
// alias to denote that we do not control the lifetime of the resource in question.

template <typename T>
using observer_ptr = T*;

#endif