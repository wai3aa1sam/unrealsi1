#pragma once

#include <type_traits>
#include <limits>

template<class BASE, class DERIVED> using				  ursIsBaseOfT = typename std::is_base_of<BASE, DERIVED>;
template<class BASE, class DERIVED> inline constexpr bool ursIsBaseOf  = ursIsBaseOfT<BASE, DERIVED>::value;


#if 0
#pragma mark --- ursUeTypeTraits-Decl ---
#endif // 0
#if 1

template<class T> struct ursRemoveAllPointerT;

template<class T> 
struct ursRemoveAllPointerT<T*>
{
	using Type = T;
};

template<class T> 
struct ursRemoveAllPointerT<TObjectPtr<T> >
{
	using Type = T;
};

template<class T> using ursRemoveAllPointer	= typename ursRemoveAllPointerT<T>::Type;

#endif // 0
