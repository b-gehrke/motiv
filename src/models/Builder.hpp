/*
 * Marvelous OTF2 Traces Interactive Visualizer (MOTIV)
 * Copyright (C) 2023 Florian Gallrein, Björn Gehrke
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef MOTIV_BUILDER_HPP
#define MOTIV_BUILDER_HPP

// Makros allowing performing some operation on each element of a list
// Code from https://github.com/swansontec/map-macro/blob/master/map.h
#define EVAL0(...) __VA_ARGS__
#define EVAL1(...) EVAL0(EVAL0(EVAL0(__VA_ARGS__)))
#define EVAL2(...) EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL3(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL4(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL(...)  EVAL4(EVAL4(EVAL4(__VA_ARGS__)))

#define MAP_END(...)
#define MAP_OUT
#define MAP_COMMA ,

#define MAP_GET_END2() 0, MAP_END
#define MAP_GET_END1(...) MAP_GET_END2
#define MAP_GET_END(...) MAP_GET_END1
#define MAP_NEXT0(test, next, ...) next MAP_OUT
#define MAP_NEXT1(test, next) MAP_NEXT0(test, next, 0)
#define MAP_NEXT(test, next)  MAP_NEXT1(MAP_GET_END test, next)

#define MAP0(f, x, peek, ...) f(x) MAP_NEXT(peek, MAP1)(f, peek, __VA_ARGS__)
#define MAP1(f, x, peek, ...) f(x) MAP_NEXT(peek, MAP0)(f, peek, __VA_ARGS__)

#define MAP_LIST_NEXT1(test, next) MAP_NEXT0(test, MAP_COMMA next, 0)
#define MAP_LIST_NEXT(test, next)  MAP_LIST_NEXT1(MAP_GET_END test, next)

#define MAP_LIST0(f, x, peek, ...) f(x) MAP_LIST_NEXT(peek, MAP_LIST1)(f, peek, __VA_ARGS__)
#define MAP_LIST1(f, x, peek, ...) f(x) MAP_LIST_NEXT(peek, MAP_LIST0)(f, peek, __VA_ARGS__)

/**
 * Applies the function macro `f` to each of the remaining parameters.
 */
#define MAP(f, ...) EVAL(MAP1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

/**
 * Applies the function macro `f` to each of the remaining parameters and
 * inserts commas between the results.
 */
#define MAP_LIST(f, ...) EVAL(MAP_LIST1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

#define BUILDER_CHECK(field) check_ ## field();
#define BUILDER_DREF(field) *field ## _

/**
 * Macro to add a field to a BUILDER
 */
#define BUILDER_FIELD(type, name)                                       \
private:                                                                \
    std::shared_ptr<type> name ## _;                                    \
    void check_ ## name() {                                             \
        if(!name ## _)                                                  \
        throw std::invalid_argument("Field '"#name"'must be set!"); }   \
public:                                                                 \
    Builder * name(type & s) {                                          \
        name ## _ = std::make_shared<type>(s);                          \
        return this;                                                    \
    }                                                                   \
    std::shared_ptr<type> name() {                                                     \
        return name ## _;                                               \
    }

#define BUILDER_OPTIONAL_FIELD(type, name)                              \
private:                                                                \
    std::shared_ptr<type> name ## _;                                    \
public:                                                                 \
    type name() const { return *name ## _; }                            \
    Builder * name(type & s) {                                          \
        name ## _ = std::make_shared<type>(s);                          \
        return this;                                                    \
    }

/**
 * Macro generating a Builder subclass for a specific data type.
 * This macro should be used inside a class.
 * The second arguments should contain several BUILDER_FIELD calls (without comma in between).
 * The last arguments must be the list of names used in content
 *
 * @example @code
 * class SomeClass {
 * private:
 *    someType1 someField1;
 *    someType2 someField2;
 *
 *    BUILDER(SomeClass,
 *            BUILDER_FIELD(someType1, someField1)
 *            BUILDER_FIELD(someType2, someField2),
 *            someField1, someField1)
 * }
 */
#define BUILDER(type, content, ...)                     \
class Builder : public builder<type> {                  \
public:                                                 \
    Builder() = default;                                \
    type build(){                                       \
        MAP(BUILDER_CHECK, __VA_ARGS__)                 \
        return {MAP_LIST(BUILDER_DREF, __VA_ARGS__)};   \
    };                                                  \
    content                                             \
};

template<typename T>
class builder {
public:
    virtual ~builder() = default;

    /**
     * @brief Build the target object
     *
     * Before constructing the target object, all fields are checked.
     * If one has not been set, an @code std::invalid_argument_exception @endcode is thrown.
     *
     * @return Instance of target object
     */
    virtual T build() = 0;
};

#endif //MOTIV_BUILDER_HPP
