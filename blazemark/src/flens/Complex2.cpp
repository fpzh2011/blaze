//=================================================================================================
/*!
//  \file src/flens/Complex2.cpp
//  \brief Source file for the FLENS kernel for the complex expression d = A * ( a + b + c )
//
//  Copyright (C) 2011 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. This library is free software; you can redistribute
//  it and/or modify it under the terms of the GNU General Public License as published by the
//  Free Software Foundation; either version 3, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
//  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//  See the GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License along with a special
//  exception for linking and compiling against the Blaze library, the so-called "runtime
//  exception"; see the file COPYING. If not, see http://www.gnu.org/licenses/.
*/
//=================================================================================================


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <iostream>
#include <boost/cast.hpp>
#include <flens/flens.cxx>
#include <blaze/util/Timing.h>
#include <blazemark/flens/Complex2.h>
#include <blazemark/flens/init/DenseVector.h>
#include <blazemark/flens/init/GeMatrix.h>
#include <blazemark/system/Config.h>


namespace blazemark {

namespace flens {

//=================================================================================================
//
//  KERNEL FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief FLENS kernel for the complex expression d = A * ( a + b + c ).
//
// \param N The number of rows and columns of the matrix and the size of the vectors.
// \param steps The number of iteration steps to perform.
// \return Minimum runtime of the kernel function.
//
// This kernel function implements the complex expression d = A * ( a + b + c ) by means of the
// FLENS functionality.
*/
double complex2( size_t N, size_t steps )
{
   using ::blazemark::element_t;
   using ::boost::numeric_cast;

   typedef ::flens::GeMatrix< ::flens::FullStorage<element_t,::flens::ColMajor> >  ColGeMatrix;
   typedef ::flens::DenseVector< ::flens::Array<element_t> >  DenseVector;

   ::blaze::setSeed( seed );

   ColGeMatrix A( N, N );
   DenseVector a( N ), b( N ), c( N ), d( N );
   ::blaze::timing::WcTimer timer;

   init( A );
   init( a );
   init( b );
   init( c );

   {
      const DenseVector tmp( a + b + c );
      d = A * tmp;
   }

   for( size_t rep=0UL; rep<reps; ++rep )
   {
      timer.start();
      for( size_t step=0UL; step<steps; ++step ) {
         const DenseVector tmp( a + b + c );
         d = A * tmp;
      }
      timer.end();

      if( numeric_cast<size_t>( d.length() ) != N )
         std::cerr << " Line " << __LINE__ << ": ERROR detected!!!\n";

      if( timer.last() > maxtime )
         break;
   }

   const double minTime( timer.min()     );
   const double avgTime( timer.average() );

   if( minTime * ( 1.0 + deviation*0.01 ) < avgTime )
      std::cerr << " FLENS kernel 'complex2': Time deviation too large!!!\n";

   return minTime;
}
//*************************************************************************************************

} // namespace flens

} // namespace blazemark
