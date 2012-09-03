//=================================================================================================
/*!
//  \file src/flens/Mat3TMat3Mult.cpp
//  \brief Source file for the FLENS 3D matrix/transpose matrix multiplication kernel
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
#include <vector>
#include <flens/flens.cxx>
#include <blaze/util/Timing.h>
#include <blazemark/flens/init/GeMatrix.h>
#include <blazemark/flens/Mat3TMat3Mult.h>
#include <blazemark/system/Config.h>


namespace blazemark {

namespace flens {

//=================================================================================================
//
//  KERNEL FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief FLENS 3-dimensional matrix/transpose matrix multiplication kernel.
//
// \param N The number of 3x3 matrices to be computed.
// \param steps The number of iteration steps to perform.
// \return Minimum runtime of the kernel function.
//
// This kernel function implements the 3-dimensional matrix/transpose matrix multiplication by
// means of the FLENS functionality.
*/
double mat3tmat3mult( size_t N, size_t steps )
{
   using ::blazemark::element_t;

   typedef ::flens::GeMatrix< ::flens::FullStorage<element_t,::flens::RowMajor> >  RowGeMatrix;
   typedef ::flens::GeMatrix< ::flens::FullStorage<element_t,::flens::ColMajor> >  ColGeMatrix;

   ::blaze::setSeed( seed );

   ::std::vector< RowGeMatrix > A( N ), C( N );
   ::std::vector< ColGeMatrix > B( N );
   ::blaze::timing::WcTimer timer;

   for( size_t i=0UL; i<N; ++i ) {
      A[i].resize( 3, 3 );
      B[i].resize( 3, 3 );
      C[i].resize( 3, 3 );
      init( A[i] );
      init( B[i] );
   }

   for( size_t i=0UL; i<N; ++i ) {
      C[i] = A[i] * B[i];
   }

   for( size_t rep=0UL; rep<reps; ++rep )
   {
      timer.start();
      for( size_t step=0UL, i=0UL; step<steps; ++step, ++i ) {
         if( i == N ) i = 0UL;
         C[i] = A[i] * B[i];
      }
      timer.end();

      for( size_t i=0UL; i<N; ++i )
         if( C[i](0,0) < element_t(0) )
            std::cerr << " Line " << __LINE__ << ": ERROR detected!!!\n";

      if( timer.last() > maxtime )
         break;
   }

   const double minTime( timer.min()     );
   const double avgTime( timer.average() );

   if( minTime * ( 1.0 + deviation*0.01 ) < avgTime )
      std::cerr << " FLENS kernel 'mat3tmat3mult': Time deviation too large!!!\n";

   return minTime;
}
//*************************************************************************************************

} // namespace flens

} // namespace blazemark
