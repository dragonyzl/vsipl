/* Copyright (c) 2009 by CodeSourcery, LLC.  All rights reserved. */

/// Description: VSIPL++ Library: Views with User Datatypes
///
/// This example demonstrates the use of VSIPL++ View objects to
/// contain data of a user-defined type instead of the usual scalar
/// numbers.

#include <vsip/initfin.hpp>
#include <vsip/vector.hpp>

#include <iostream>
#include <vsip_csl/output.hpp>

// ====================================================================
// User-Defined Datatype

// We define a very basic four-float vector datatype struct with
// addition functions for other vectors and for scalar floats.
struct float4
{
  float data[4];

  // Standard constructor
  float4(float f0, float f1, float f2, float f3)
  {
    data[0] = f0;
    data[1] = f1;
    data[2] = f2;
    data[3] = f3;
  }

  // Add another float4 to this.
  float4 &operator+=(float4 const &v2)
  {
    data[0] += v2.data[0];
    data[1] += v2.data[1];
    data[2] += v2.data[2];
    data[3] += v2.data[3];
    return *this;
  }

  // Add a float to this.
  float4 &operator+=(float const f2)
  {
    data[0] += f2;
    data[1] += f2;
    data[2] += f2;
    data[3] += f2;
    return *this;
  }
};

// We also define overloads of + for combinations of float4 and
// float, in terms of the += operator.
inline float4
operator+(float4 const &v1, float4 const &v2)
{
  float4 result(v1);
  result += v2;
  return result;
}

inline float4
operator+(float4 const &v1, float const f2)
{
  float4 result(v1);
  result += f2;
  return result;
}

inline float4
operator+(float const f1, float4 const &v2)
{
  float4 result(v2);
  result += f1;
  return result;
}

// Finally, it's useful to have an easy way to print out the value
// of our float4 objects, so we'll overload the ostream << operator
// to do that.
inline std::ostream&
operator<<(
  std::ostream& out,
  float4 const &vec)
{
  out << "[" << vec.data[0] << ", " << vec.data[1] << ", "
	     << vec.data[2] << ", " << vec.data[3] << "]";
  return out;
}


// ====================================================================
// Main Program
int 
main(int argc, char **argv)
{
  // Initialize the Sourcery VSIPL++ library.
  vsip::vsipl init(argc, argv);

  // Define some vectors containing float4 data.
  vsip::Vector<float4> v1(2), v2(2), v3(2);

  // Give two of these vectors some initial data.  Note that this
  // uses the standard VSIPL++ "View<T> = T" pattern of assigning
  // a single value to all elements of a View.
  v1 = float4(1.0, 2.0, 3.0, 4.0);
  v2 = float4(2.1, 2.2, 2.3, 2.4);

  // Set the third vector to the sum of the first two.  This applies
  // the operator+ that we defined earlier to each element.
  v3 = v1 + v2;

  std::cout << "v3 = v1 + v2:\n" << v3 << std::endl;

  // Similarly, the VSIPL++ vector/scalar += definition allows us to
  // add a float4 value to all of the elements of v3.
  v3 += float4(0.1, 0.2, 0.3, 0.4);
  
  std::cout << "v3 += float4(0.1, 0.2, 0.3, 0.4):\n" << v3 << std::endl;

  // Finally, since the VSIPL++ definition of += relays to the one we
  // defined for the datatype, we can add a scalar float to all of
  // the float4 elements of v3.
  v3 += 0.1;

  std::cout << "v3 += 0.1:\n" << v3 << std::endl;
}
