/* 
   Copyright (c) Marshall Clow 2010-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    For more information, see http://www.boost.org
*/

#include <boost/config.hpp>
#include <boost/algorithm/cxx11/any_of.hpp>
#include <boost/test/included/test_exec_monitor.hpp>

#include <functional>
#include <vector>
#include <list>

template<typename T>
struct is_ : public std::unary_function<T, bool> {
    is_ ( T v ) : val_ ( v ) {}
    ~is_ () {}
    bool operator () ( T comp ) const { return val_ == comp; }
private:
    is_ (); // need a value

    T val_;
    };

namespace ba = hexerboost::algorithm;

void test_any ()
{
//  Note: The literal values here are tested against directly, careful if you change them:
    int some_numbers[] = { 1, 5, 0, 18, 10 };
    std::vector<int> vi(some_numbers, some_numbers + 5);
    std::list<int>   li(vi.begin(), vi.end ());

    int some_letters[] = { 'a', 'q', 'n', 'y', 'n' };
    std::vector<char> vc(some_letters, some_letters + 5);
    
    BOOST_CHECK ( ba::any_of_equal ( vi,                                   1 ));
    BOOST_CHECK ( ba::any_of       ( vi,                       is_<int> (  1 )));
    BOOST_CHECK ( ba::any_of_equal ( vi.begin(),     vi.end(),             1 ));
    BOOST_CHECK ( ba::any_of       ( vi.begin(),     vi.end(), is_<int> (  1 )));

    BOOST_CHECK (!ba::any_of_equal ( vi,                                   9 ));
    BOOST_CHECK (!ba::any_of       ( vi,                       is_<int> (  9 )));
    BOOST_CHECK (!ba::any_of_equal ( vi.begin(),     vi.end(),             9 ));
    BOOST_CHECK (!ba::any_of       ( vi.begin(),     vi.end(), is_<int> (  9 )));

    BOOST_CHECK ( ba::any_of_equal ( vi,                                  10 ));
    BOOST_CHECK ( ba::any_of       ( vi,                       is_<int> ( 10 )));
    BOOST_CHECK (!ba::any_of_equal ( vi,                                   4 ));
    BOOST_CHECK (!ba::any_of       ( vi,                       is_<int> (  4 )));

    BOOST_CHECK (!ba::any_of_equal ( vi.end(),       vi.end(),            0 ));
    BOOST_CHECK (!ba::any_of       ( vi.end(),       vi.end(), is_<int> ( 0 )));

//   5 is not in { 0, 18, 10 }, but 10 is
    BOOST_CHECK ( ba::any_of_equal ( vi.begin() + 2, vi.end(),            10 ));
    BOOST_CHECK ( ba::any_of       ( vi.begin() + 2, vi.end(), is_<int> ( 10 )));

    BOOST_CHECK (!ba::any_of_equal ( vi.begin() + 2, vi.end(),             5 ));
    BOOST_CHECK (!ba::any_of       ( vi.begin() + 2, vi.end(), is_<int> (  5 )));

//  18 is not in { 1, 5, 0 }, but 5 is
    BOOST_CHECK ( ba::any_of_equal ( vi.begin(), vi.begin() + 3,             5 ));
    BOOST_CHECK ( ba::any_of       ( vi.begin(), vi.begin() + 3, is_<int> (  5 )));

    BOOST_CHECK (!ba::any_of_equal ( vi.begin(), vi.begin() + 3,            18 ));
    BOOST_CHECK (!ba::any_of       ( vi.begin(), vi.begin() + 3, is_<int> ( 18 )));

    BOOST_CHECK ( ba::any_of_equal ( vc,             'q' ));
    BOOST_CHECK ( ba::any_of       ( vc, is_<char> ( 'q' )));

    BOOST_CHECK (!ba::any_of_equal ( vc,             '!' ));
    BOOST_CHECK (!ba::any_of       ( vc, is_<char> ( '!' )));

    BOOST_CHECK ( ba::any_of_equal ( vc,             'n' ));
    BOOST_CHECK ( ba::any_of       ( vc, is_<char> ( 'n' )));

    BOOST_CHECK (!ba::any_of_equal ( vi.begin(), vi.begin(),   1 ));
    BOOST_CHECK (!ba::any_of_equal ( vc.begin(), vc.begin(), 'a' ));
    BOOST_CHECK (!ba::any_of       ( vi.begin(), vi.begin(), is_<int>  (   1 )));
    BOOST_CHECK (!ba::any_of       ( vc.begin(), vc.begin(), is_<char> ( 'a' )));

    BOOST_CHECK ( ba::any_of_equal ( li,                                   1 ));
    BOOST_CHECK ( ba::any_of       ( li,                       is_<int> (  1 )));
    BOOST_CHECK ( ba::any_of_equal ( li.begin(),     li.end(),             1 ));
    BOOST_CHECK ( ba::any_of       ( li.begin(),     li.end(), is_<int> (  1 )));
    
    std::list<int>::iterator l_iter = li.begin ();
    l_iter++; l_iter++; l_iter++;
    BOOST_CHECK ( ba::any_of_equal ( li.begin(), l_iter,             5 ));
    BOOST_CHECK ( ba::any_of       ( li.begin(), l_iter, is_<int> (  5 )));
    BOOST_CHECK (!ba::any_of_equal ( li.begin(), l_iter,            18 ));
    BOOST_CHECK (!ba::any_of       ( li.begin(), l_iter, is_<int> ( 18 )));
}


int test_main( int , char* [] )
{
  test_any ();
  return 0;
}
