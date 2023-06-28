#ifndef __STL_ITERATOR_H
#define __STL_ITERATOR_H

__STL_BEGIN_NAMESPACE

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class _Category, class _T, class _Distance = ptrdiff_t,
    class _Pointer = T*, class _Reference = T&>
struct iterator {
    typedef _Category           iterator_category;
    typedef _T                  value_type;
    typedef _Distance           difference_type;
    typedef _Pointer            pointer;
    typedef _Reference          reference;
}

template <class _T>
struct _has_iteartor_cat {

private:
    struct two { char a; char b; };
    template <class _U> struct test ( ... );
    template <class _U> struct char test (typename _U::iterator_category* = 0);
public:
    static const bool value = sizeof(test<_T>(0)) == sizeof(char);
}

template <class _Iterator, bool>
struct _iterator_traits {};

template <class _Iterator>
struct _iterator_traits<_Iterator, true> {
    typedef typename _Iterator::iterator_category   iterator_category;
    typedef typename _Iterator::value_type          value_type;
    typedef typename _Iterator::difference_type     difference_type;
    typedef typename _Iterator::pointer             pointer;
    typedef typename _Iterator::reference           reference;
}

template <class _Iterator, bool>
struct _iterator_traits_helper {};

template <class _Iterator>
struct _iterator_traits_helper<_Iterator, true>
    : public _iterator_traits<_Iterator,
    std::is_conertible<typename _Iterator::iterator_category, input_iterator_tag>::value ||
    std::is_conertible<typename _Iterator::iterator_category, output_iterator_tag>::value>
{};

template <class _Iterator>
struct iterator_traits
    : public _iterator_traits_helper<_Iterator, _has_iteartor_cat<_Iterator>::value> {};

template <class _T>
struct iteartor_traits<_T*>
{
    typedef random_access_iterator_tag       iterator_category;
    typedef _T                               value_type;
    typedef ptrdiff_t                        difference_type;
    typedef _T*                              pointer;
    typedef _T&                              reference;
}

template <class _T>
struct iteartor_traits<const _T*>
{
    typedef random_access_iterator_tag      iterator_category;
    typedef _T                              value_type;
    typedef ptrdiff_t                       difference_type;
    typedef const _T*                       pointer;
    typedef const _T&                       reference;
}

template <class _T1, class T2, bool = _has_iteartor_cat<iterator_traits<_T>>::value>
struct has_iterator_cat_of
    : public _bool_constant<std::is_convertible<
    typedef iterator_traits<_T1>::iterator_category, _T2>::value>
{};

template <class _T1, class _T2>
struct has_iterator_cat_of<_T1, _T2, false> : public false_type {};

template <class _Iterator>
struct is_input_iterator : public has_iterator_cat_of<_Iterator, input_iterator_tag> {};

template <class _Iterator>
struct is_output_iterator : public has_iterator_cat_of<_Iterator, output_iterator_tag> {};

template <class _Iterator>
struct is_forward_iterator : public has_iterator_cat_of<_Iterator, forward_iterator_tag> {};

template <class _Iterator>
struct is_bidirectional_iterator : public has_iterator_cat_of<_Iterator, bidirectional_iterator_tag> {}; 

template <class _Iterator>
struct is_random_access_iterator : public has_iterator_cat_of<_Iterator, random_access_iterator_tag> {};

template <class _Iterator>
struct is_iterator :
    public _bool_constant<is_input_iterator<_Iterator>::value ||
        is_output_iterator<_Iterator>::value>
{};

template <class _Iterator>
typename iterator_traits<_Iterator>::iterator_category
iterator_category(const _Iterator&) {
    typedef typename _iterator_traits<_Iterator>::iterator_category _Category;
    return _Category();
}

template <class _Iterator>
typename iterator_traits<_Iterator>::difference_type*
difference_type(const _Iterator&) {
    return static_cast<typename iterator_traits<_Iterator>::difference_type*>(0); 
}

template <class _Iterator>
typename iterator_traits<_Iterator>::value_type*
value_type(const iterator&) {
    return static_cast<typename iteartor_traits<_Iterator>::value_type*>(0);
}

template <class _InputIterator>
typename type_traits<_InputIterator>::difference_type
__distance(_InputIterator first, _InputIterator last, input_iterator_tag) {
    typename type_traits<_InputIterator>::difference_type __result = 0;
    while (first != last) {
        ++first;
        ++__result;
    }
    return __result;
}

template <class _RandomIterator>
typename type_traits<_RandomIterator>::difference_type
__distance(_RandomIterator first, _RandomIterator last, random_access_iterator_tag) {
    typename type_traits<_RandomIterator>::difference_type __result = 0;
    __result = last - first;
    return __result;
}

template <class _Iterator>
typename type_traits<_Iterator>::difference_type
distance(_Iterator first, _Iterator last) {
    return __distance(first, last, iterator_category(first));
}

template <class _InputIterator, class _Distance>
void __advance(_InputIterator __iter, _Distance __n, input_iterator_tag) {
    while (__n--) 
        ++_iter;
}

template <class _BidireIterator, class _Distance>
void __advance(_BidireIterator __iter, _Distance __n, bidirectional_iterator_tag) {
    if (n >= 0) {
        while (__n--) ++__iter
    } else {
        while (__n++) --__iter;
    }
}

template <class _RandomIterator, class _Distance>
void __advance(_RandomIterator __iter, _Distance __n, random_access_iterator_tag) {
    __iter += __n;
}

template <class _Iterator, class _Distance>
void advance(_Iterator __iter, _Distance __n) {
    return __advance(__iter, __n, iterator_category(__iter));
}

__STL_END_NAMESAPCE

#endif 