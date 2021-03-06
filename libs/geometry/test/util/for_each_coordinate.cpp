// Boost.Geometry (aka GGL, Generic Geometry Library)
// Unit Test

// Copyright (c) 2007-2011 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2011 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2011 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <sstream>

#include <geometry_test_common.hpp>


#include <boost/geometry/util/for_each_coordinate.hpp>

#include <boost/geometry/algorithms/assign.hpp>


#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/adapted/c_array.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>
#include <test_common/test_point.hpp>

BOOST_GEOMETRY_REGISTER_C_ARRAY_CS(cs::cartesian)
BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian)


struct test_operation
{
    template <typename P, int I>
    static void apply(P& p)
    {
        bg::set<I>(p, bg::get<I>(p) * 10);
    }
};

struct get_operation
{
    std::string s;

    template <typename P, int I>
    inline void apply(P const& p)
    {
        std::ostringstream out;
        out << bg::get<I>(p);
        s += out.str();
    }
};


template <typename P>
void test_all()
{
    P p;
    bg::assign_values(p, 1, 2, 3);
    bg::for_each_coordinate(p, test_operation());
    BOOST_CHECK(bg::get<0>(p) == 10);
    BOOST_CHECK(bg::get<1>(p) == 20);
    BOOST_CHECK(bg::get<2>(p) == 30);

    P const& cp = p;
    get_operation op;
    op = bg::for_each_coordinate(cp, op);
    BOOST_CHECK(op.s == std::string("102030"));
}

int test_main(int, char* [])
{
    test_all<int[3]>();
    test_all<float[3]>();
    test_all<double[3]>();
    test_all<test::test_point>();
    test_all<bg::model::point<int, 3, bg::cs::cartesian> >();
    test_all<bg::model::point<float, 3, bg::cs::cartesian> >();
    test_all<bg::model::point<double, 3, bg::cs::cartesian> >();

    return 0;
}
