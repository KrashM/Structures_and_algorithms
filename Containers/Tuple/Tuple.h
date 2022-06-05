#pragma once

template <typename First, typename... Rest>
struct Tuple: public Tuple<Rest...>{

    First first;

    Tuple(First first, Rest... rest): Tuple<Rest...>(rest...), first(first){}

};

template<typename First>
struct Tuple<First>{

    First first;
    Tuple(First first): first(first){}

};

template<int index, typename First, typename... Rest>
struct GetImpl{

    static auto value(const Tuple<First, Rest...>* t) -> decltype(GetImpl<index - 1, Rest...>::value(t)){ return GetImpl<index - 1, Rest...>::value(t); }
    
};

template<typename First, typename... Rest>
struct GetImpl<0, First, Rest...>{

    static First value(const Tuple<First, Rest...>* t){ return t -> first; }

};

template<int index, typename First, typename... Rest>
auto get(const Tuple<First, Rest...>& t) -> decltype(GetImpl<index, First, Rest...>::value(&t)){ return GetImpl<index, First, Rest...>::value(&t); }