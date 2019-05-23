#include <boost/python.hpp>
#include <string>

/**
 * Print greeting
 * 
 * Args:
 *  name: str, name that receives greeting
*/
std::string greet(std::string name)
{
  return std::string("Hello, ") + name;
}


/**
 * Sum of 2 values
 * 
 * Args:
 *  a: int, 1st number
 *  b: int, 2nd number
*/
int sum(int a, int b)
{
  return a + b;
}

// ! This MODULE must have the exactly same name as defined in CMakeLists.txt
BOOST_PYTHON_MODULE(hello_ext)
{
  using namespace boost::python;
  def("greet", greet);
  def("sum", sum);
}