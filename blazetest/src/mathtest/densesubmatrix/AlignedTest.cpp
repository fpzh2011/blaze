//=================================================================================================
/*!
//  \file src/mathtest/densesubmatrix/AlignedTest.cpp
//  \brief Source file for the aligned DenseSubmatrix class test
//
//  Copyright (C) 2013 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. You can redistribute it and/or modify it under
//  the terms of the New (Revised) BSD License. Redistribution and use in source and binary
//  forms, with or without modification, are permitted provided that the following conditions
//  are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//     of conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//  3. Neither the names of the Blaze development group nor the names of its contributors
//     may be used to endorse or promote products derived from this software without specific
//     prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
*/
//=================================================================================================


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <cstdlib>
#include <iostream>
#include <blaze/math/CompressedMatrix.h>
#include <blaze/math/CustomMatrix.h>
#include <blaze/math/Views.h>
#include <blaze/util/Memory.h>
#include <blaze/util/policies/Deallocate.h>
#include <blaze/util/typetraits/AlignmentOf.h>
#include <blaze/util/UniqueArray.h>
#include <blazetest/mathtest/densesubmatrix/AlignedTest.h>
#include <blazetest/mathtest/RandomMaximum.h>
#include <blazetest/mathtest/RandomMinimum.h>


namespace blazetest {

namespace mathtest {

namespace densesubmatrix {

//=================================================================================================
//
//  CONSTRUCTORS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Constructor for the DenseSubmatrix class test.
//
// \exception std::runtime_error Operation error detected.
*/
AlignedTest::AlignedTest()
   : mat1_ ( 64UL, 64UL )
   , mat2_ ( 64UL, 64UL )
   , tmat1_( 64UL, 64UL )
   , tmat2_( 64UL, 64UL )
{
   testConstructors();
   testAssignment();
   testAddAssign();
   testSubAssign();
   testMultAssign();
   testScaling();
   testFunctionCall();
   testIterator();
   testNonZeros();
   testReset();
   testClear();
   testTranspose();
   testCTranspose();
   testIsDefault();
   testIsSame();
   testSubmatrix();
   testRow();
   testColumn();
}
//*************************************************************************************************




//=================================================================================================
//
//  TEST FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Test of the DenseSubmatrix constructors.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of all constructors of the DenseSubmatrix class template.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void AlignedTest::testConstructors()
{
   using blaze::submatrix;
   using blaze::aligned;
   using blaze::unaligned;


   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      test_ = "Row-major DenseSubmatrix constructor";

      initialize();

      const size_t alignment = blaze::AlignmentOf<int>::value;

      for( size_t row=0UL; row<mat1_.rows(); row+=alignment ) {
         for( size_t column=0UL; column<mat1_.columns(); column+=alignment ) {
            for( size_t maxm=0UL; ; maxm+=alignment ) {
               for( size_t maxn=0UL; ; maxn+=alignment )
               {
                  const size_t m( blaze::min( maxm, mat1_.rows()-row ) );
                  const size_t n( blaze::min( maxn, mat1_.columns()-column ) );

                  const ASMT sm1 = submatrix<aligned>  ( mat1_, row, column, m, n );
                  const USMT sm2 = submatrix<unaligned>( mat2_, row, column, m, n );

                  if( sm1 != sm2 ) {
                     std::ostringstream oss;
                     oss << " Test: " << test_ << "\n"
                         << " Error: Setup of dense submatrix failed\n"
                         << " Details:\n"
                         << "   Index of first row    = " << row << "\n"
                         << "   Index of first column = " << column << "\n"
                         << "   Number of rows        = " << m << "\n"
                         << "   Number of columns     = " << n << "\n"
                         << "   Submatrix:\n" << sm1 << "\n"
                         << "   Reference:\n" << sm2 << "\n";
                     throw std::runtime_error( oss.str() );
                  }

                  if( column+maxn > mat1_.columns() ) break;
               }

               if( row+maxm > mat1_.rows() ) break;
            }
         }
      }

      try {
         ASMT sm = submatrix<aligned>( mat1_, 0UL, 8UL, 64UL, 64UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      try {
         ASMT sm = submatrix<aligned>( mat1_, 8UL, 0UL, 64UL, 64UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      try {
         ASMT sm = submatrix<aligned>( mat1_, 72UL, 0UL, 8UL, 8UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      try {
         ASMT sm = submatrix<aligned>( mat1_, 0UL, 72UL, 8UL, 8UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      try {
         ASMT sm = submatrix<aligned>( mat1_, 8UL, 7UL, 8UL, 8UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of unaligned submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      test_ = "Column-major DenseSubmatrix constructor";

      initialize();

      const size_t alignment = blaze::AlignmentOf<int>::value;

      for( size_t column=0UL; column<mat1_.columns(); column+=alignment ) {
         for( size_t row=0UL; row<mat1_.rows(); row+=alignment ) {
            for( size_t maxn=0UL; ; maxn+=alignment ) {
               for( size_t maxm=0UL; ; maxm+=alignment )
               {
                  const size_t n( blaze::min( maxn, mat1_.columns()-column ) );
                  const size_t m( blaze::min( maxm, mat1_.rows()-row ) );

                  const AOSMT sm1 = submatrix<aligned>  ( tmat1_, row, column, m, n );
                  const UOSMT sm2 = submatrix<unaligned>( tmat2_, row, column, m, n );

                  if( sm1 != sm2 ) {
                     std::ostringstream oss;
                     oss << " Test: " << test_ << "\n"
                         << " Error: Setup of dense submatrix failed\n"
                         << " Details:\n"
                         << "   Index of first row    = " << row << "\n"
                         << "   Index of first column = " << column << "\n"
                         << "   Number of rows        = " << m << "\n"
                         << "   Number of columns     = " << n << "\n"
                         << "   Submatrix:\n" << sm1 << "\n"
                         << "   Reference:\n" << sm2 << "\n";
                     throw std::runtime_error( oss.str() );
                  }

                  if( row+maxm > mat1_.rows() ) break;
               }

               if( column+maxn > mat1_.columns() ) break;
            }
         }
      }

      try {
         AOSMT sm = submatrix<aligned>( tmat1_, 0UL, 8UL, 64UL, 64UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      try {
         AOSMT sm = submatrix<aligned>( tmat1_, 8UL, 0UL, 64UL, 64UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      try {
         AOSMT sm = submatrix<aligned>( tmat1_, 72UL, 0UL, 8UL, 8UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      try {
         AOSMT sm = submatrix<aligned>( tmat1_, 0UL, 72UL, 8UL, 8UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      try {
         AOSMT sm = submatrix<aligned>( tmat1_, 7UL, 8UL, 8UL, 8UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of unaligned submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the DenseSubmatrix assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of all assignment operators of the DenseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void AlignedTest::testAssignment()
{
   using blaze::submatrix;
   using blaze::aligned;
   using blaze::unaligned;
   using blaze::padded;
   using blaze::unpadded;
   using blaze::rowMajor;
   using blaze::columnMajor;


   //=====================================================================================
   // Row-major homogeneous assignment
   //=====================================================================================

   {
      test_ = "Row-major DenseSubmatrix homogeneous assignment";

      initialize();

      // Assigning to a 8x16 submatrix
      {
         ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
         USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );
         sm1 = 12;
         sm2 = 12;

         checkRows   ( sm1,  8UL );
         checkColumns( sm1, 16UL );
         checkRows   ( sm2,  8UL );
         checkColumns( sm2, 16UL );

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Assigning to a 16x8 submatrix
      {
         ASMT sm1 = submatrix<aligned>  ( mat1_, 16UL, 8UL, 16UL, 8UL );
         USMT sm2 = submatrix<unaligned>( mat2_, 16UL, 8UL, 16UL, 8UL );
         sm1 = 15;
         sm2 = 15;

         checkRows   ( sm1, 16UL );
         checkColumns( sm1,  8UL );
         checkRows   ( sm2, 16UL );
         checkColumns( sm2,  8UL );

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Row-major copy assignment
   //=====================================================================================

   {
      test_ = "Row-major DenseSubmatrix copy assignment (no aliasing)";

      initialize();

      MT mat1( 64UL, 64UL );
      MT mat2( 64UL, 64UL );
      randomize( mat1, int(randmin), int(randmax) );
      mat2 = mat1;

      ASMT sm1 = submatrix<aligned>  ( mat1, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2, 8UL, 16UL, 8UL, 16UL );
      sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major DenseSubmatrix copy assignment (aliasing)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );
      sm1 = submatrix<aligned>  ( mat1_, 24UL, 24UL, 8UL, 16UL );
      sm2 = submatrix<unaligned>( mat2_, 24UL, 24UL, 8UL, 16UL );

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major dense matrix assignment
   //=====================================================================================

   {
      test_ = "Row-major/row-major dense matrix assignment (aligned/padded)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      typedef blaze::CustomMatrix<int,aligned,padded,rowMajor>  AlignedPadded;
      AlignedPadded mat( blaze::allocate<int>( 128UL ), 8UL, 16UL, 16UL, blaze::Deallocate() );
      randomize( mat, int(randmin), int(randmax) );

      sm1 = mat;
      sm2 = mat;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/row-major dense matrix assignment (unaligned/unpadded)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      typedef blaze::CustomMatrix<int,unaligned,unpadded,rowMajor>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[129UL] );
      UnalignedUnpadded mat( array.get()+1UL, 8UL, 16UL );
      randomize( mat, int(randmin), int(randmax) );

      sm1 = mat;
      sm2 = mat;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/column-major dense matrix assignment (aligned/padded)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      typedef blaze::CustomMatrix<int,aligned,padded,columnMajor>  AlignedPadded;
      AlignedPadded mat( blaze::allocate<int>( 256UL ), 8UL, 16UL, 16UL, blaze::Deallocate() );
      randomize( mat, int(randmin), int(randmax) );

      sm1 = mat;
      sm2 = mat;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/column-major dense matrix assignment (unaligned/unpadded)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      typedef blaze::CustomMatrix<int,unaligned,unpadded,columnMajor>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[129UL] );
      UnalignedUnpadded mat( array.get()+1UL, 8UL, 16UL );
      randomize( mat, int(randmin), int(randmax) );

      sm1 = mat;
      sm2 = mat;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major sparse matrix assignment
   //=====================================================================================

   {
      test_ = "Row-major/row-major sparse matrix assignment";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      blaze::CompressedMatrix<int,rowMajor> mat( 8UL, 16UL );
      randomize( mat, 30UL, int(randmin), int(randmax) );

      sm1 = mat;
      sm2 = mat;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/column-major sparse matrix assignment";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      blaze::CompressedMatrix<int,columnMajor> mat( 8UL, 16UL );
      randomize( mat, 30UL, int(randmin), int(randmax) );

      sm1 = mat;
      sm2 = mat;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major homogeneous assignment
   //=====================================================================================

   {
      test_ = "Column-major DenseSubmatrix homogeneous assignment";

      initialize();

      // Assigning to a 8x16 submatrix
      {
         AOSMT sm1 = submatrix<aligned>  ( tmat1_, 8UL, 16UL, 8UL, 16UL );
         UOSMT sm2 = submatrix<unaligned>( tmat2_, 8UL, 16UL, 8UL, 16UL );
         sm1 = 12;
         sm2 = 12;

         checkRows   ( sm1,  8UL );
         checkColumns( sm1, 16UL );
         checkRows   ( sm2,  8UL );
         checkColumns( sm2, 16UL );

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Assigning to a 16x8 submatrix
      {
         AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
         UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );
         sm1 = 15;
         sm2 = 15;

         checkRows   ( sm1, 16UL );
         checkColumns( sm1,  8UL );
         checkRows   ( sm2, 16UL );
         checkColumns( sm2,  8UL );

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major copy assignment
   //=====================================================================================

   {
      test_ = "Column-major DenseSubmatrix copy assignment (no aliasing)";

      initialize();

      OMT mat1( 64UL, 64UL );
      OMT mat2( 64UL, 64UL );
      randomize( mat1, int(randmin), int(randmax) );
      mat2 = mat1;

      AOSMT sm1 = submatrix<aligned>  ( mat1, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( mat2, 16UL, 8UL, 16UL, 8UL );
      sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major DenseSubmatrix copy assignment (aliasing)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );
      sm1 = submatrix<aligned>  ( tmat1_, 24UL, 24UL, 16UL, 8UL );
      sm2 = submatrix<unaligned>( tmat2_, 24UL, 24UL, 16UL, 8UL );

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense matrix assignment
   //=====================================================================================

   {
      test_ = "Column-major/row-major dense matrix assignment (aligned/padded)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      typedef blaze::CustomMatrix<int,aligned,padded,rowMajor>  AlignedPadded;
      AlignedPadded mat( blaze::allocate<int>( 256UL ), 16UL, 8UL, 16UL, blaze::Deallocate() );
      randomize( mat, int(randmin), int(randmax) );

      sm1 = mat;
      sm2 = mat;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/row-major dense matrix assignment (unaligned/unpadded)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      typedef blaze::CustomMatrix<int,unaligned,unpadded,rowMajor>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[129UL] );
      UnalignedUnpadded mat( array.get()+1UL, 16UL, 8UL );
      randomize( mat, int(randmin), int(randmax) );

      sm1 = mat;
      sm2 = mat;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/column-major dense matrix assignment (aligned/padded)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      typedef blaze::CustomMatrix<int,aligned,padded,columnMajor>  AlignedPadded;
      AlignedPadded mat( blaze::allocate<int>( 128UL ), 16UL, 8UL, 16UL, blaze::Deallocate() );
      randomize( mat, int(randmin), int(randmax) );

      sm1 = mat;
      sm2 = mat;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/column-major dense matrix assignment (unaligned/unpadded)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      typedef blaze::CustomMatrix<int,unaligned,unpadded,columnMajor>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[129UL] );
      UnalignedUnpadded mat( array.get()+1UL, 16UL, 8UL );
      randomize( mat, int(randmin), int(randmax) );

      sm1 = mat;
      sm2 = mat;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major sparse matrix assignment
   //=====================================================================================

   {
      test_ = "Column-major/row-major sparse matrix assignment";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      blaze::CompressedMatrix<int,rowMajor> mat( 16UL, 8UL );
      randomize( mat, 30UL, int(randmin), int(randmax) );

      sm1 = mat;
      sm2 = mat;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/column-major sparse matrix assignment";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      blaze::CompressedMatrix<int,columnMajor> mat( 16UL, 8UL );
      randomize( mat, 30UL, int(randmin), int(randmax) );

      sm1 = mat;
      sm2 = mat;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the DenseSubmatrix addition assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the addition assignment operators of the DenseSubmatrix
// class template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void AlignedTest::testAddAssign()
{
   using blaze::submatrix;
   using blaze::aligned;
   using blaze::unaligned;
   using blaze::padded;
   using blaze::unpadded;
   using blaze::rowMajor;
   using blaze::columnMajor;


   //=====================================================================================
   // Row-major DenseSubmatrix addition assignment
   //=====================================================================================

   {
      test_ = "Row-major DenseSubmatrix addition assignment (no aliasing)";

      initialize();

      MT mat1( 64UL, 64UL );
      MT mat2( 64UL, 64UL );
      randomize( mat1, int(randmin), int(randmax) );
      mat2 = mat1;

      ASMT sm1 = submatrix<aligned>  ( mat1, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2, 8UL, 16UL, 8UL, 16UL );
      sm1 += submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      sm2 += submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major DenseSubmatrix addition assignment (aliasing)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );
      sm1 += submatrix<aligned>  ( mat1_, 24UL, 24UL, 8UL, 16UL );
      sm2 += submatrix<unaligned>( mat2_, 24UL, 24UL, 8UL, 16UL );

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major dense matrix addition assignment
   //=====================================================================================

   {
      test_ = "Row-major/row-major dense matrix addition assignment (aligned/padded)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      typedef blaze::CustomMatrix<int,aligned,padded,rowMajor>  AlignedPadded;
      AlignedPadded mat( blaze::allocate<int>( 128UL ), 8UL, 16UL, 16UL, blaze::Deallocate() );
      randomize( mat, int(randmin), int(randmax) );

      sm1 += mat;
      sm2 += mat;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/row-major dense matrix addition assignment (unaligned/unpadded)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      typedef blaze::CustomMatrix<int,unaligned,unpadded,rowMajor>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[129UL] );
      UnalignedUnpadded mat( array.get()+1UL, 8UL, 16UL );
      randomize( mat, int(randmin), int(randmax) );

      sm1 += mat;
      sm2 += mat;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/column-major dense matrix addition assignment (aligned/padded)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      typedef blaze::CustomMatrix<int,aligned,padded,columnMajor>  AlignedPadded;
      AlignedPadded mat( blaze::allocate<int>( 256UL ), 8UL, 16UL, 16UL, blaze::Deallocate() );
      randomize( mat, int(randmin), int(randmax) );

      sm1 += mat;
      sm2 += mat;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/column-major dense matrix addition assignment (unaligned/unpadded)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      typedef blaze::CustomMatrix<int,unaligned,unpadded,columnMajor>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[129UL] );
      UnalignedUnpadded mat( array.get()+1UL, 8UL, 16UL );
      randomize( mat, int(randmin), int(randmax) );

      sm1 += mat;
      sm2 += mat;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major sparse matrix addition assignment
   //=====================================================================================

   {
      test_ = "Row-major/row-major sparse matrix addition assignment";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      blaze::CompressedMatrix<int,rowMajor> mat( 8UL, 16UL );
      randomize( mat, 30UL, int(randmin), int(randmax) );

      sm1 += mat;
      sm2 += mat;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/column-major sparse matrix addition assignment";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      blaze::CompressedMatrix<int,columnMajor> mat( 8UL, 16UL );
      randomize( mat, 30UL, int(randmin), int(randmax) );

      sm1 += mat;
      sm2 += mat;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major DenseSubmatrix addition assignment
   //=====================================================================================

   {
      test_ = "Column-major DenseSubmatrix addition assignment (no aliasing)";

      initialize();

      OMT mat1( 64UL, 64UL );
      OMT mat2( 64UL, 64UL );
      randomize( mat1, int(randmin), int(randmax) );
      mat2 = mat1;

      AOSMT sm1 = submatrix<aligned>  ( mat1, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( mat2, 16UL, 8UL, 16UL, 8UL );
      sm1 += submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      sm2 += submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major DenseSubmatrix addition assignment (aliasing)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );
      sm1 += submatrix<aligned>  ( tmat1_, 24UL, 24UL, 16UL, 8UL );
      sm2 += submatrix<unaligned>( tmat2_, 24UL, 24UL, 16UL, 8UL );

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense matrix addition assignment
   //=====================================================================================

   {
      test_ = "Column-major/row-major dense matrix addition assignment (aligned/padded)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      typedef blaze::CustomMatrix<int,aligned,padded,rowMajor>  AlignedPadded;
      AlignedPadded mat( blaze::allocate<int>( 256UL ), 16UL, 8UL, 16UL, blaze::Deallocate() );
      randomize( mat, int(randmin), int(randmax) );

      sm1 += mat;
      sm2 += mat;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/row-major dense matrix addition assignment (unaligned/unpadded)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      typedef blaze::CustomMatrix<int,unaligned,unpadded,rowMajor>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[129UL] );
      UnalignedUnpadded mat( array.get()+1UL, 16UL, 8UL );
      randomize( mat, int(randmin), int(randmax) );

      sm1 += mat;
      sm2 += mat;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/column-major dense matrix addition assignment (aligned/padded)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      typedef blaze::CustomMatrix<int,aligned,padded,columnMajor>  AlignedPadded;
      AlignedPadded mat( blaze::allocate<int>( 128UL ), 16UL, 8UL, 16UL, blaze::Deallocate() );
      randomize( mat, int(randmin), int(randmax) );

      sm1 += mat;
      sm2 += mat;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/column-major dense matrix addition assignment (unaligned/unpadded)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      typedef blaze::CustomMatrix<int,unaligned,unpadded,columnMajor>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[129UL] );
      UnalignedUnpadded mat( array.get()+1UL, 16UL, 8UL );
      randomize( mat, int(randmin), int(randmax) );

      sm1 += mat;
      sm2 += mat;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major sparse matrix addition assignment
   //=====================================================================================

   {
      test_ = "Column-major/row-major sparse matrix addition assignment";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      blaze::CompressedMatrix<int,rowMajor> mat( 16UL, 8UL );
      randomize( mat, 30UL, int(randmin), int(randmax) );

      sm1 += mat;
      sm2 += mat;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/column-major sparse matrix addition assignment";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      blaze::CompressedMatrix<int,columnMajor> mat( 16UL, 8UL );
      randomize( mat, 30UL, int(randmin), int(randmax) );

      sm1 += mat;
      sm2 += mat;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the DenseSubmatrix subtraction assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the subtraction assignment operators of the DenseSubmatrix
// class template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void AlignedTest::testSubAssign()
{
   using blaze::submatrix;
   using blaze::aligned;
   using blaze::unaligned;
   using blaze::padded;
   using blaze::unpadded;
   using blaze::rowMajor;
   using blaze::columnMajor;


   //=====================================================================================
   // Row-major DenseSubmatrix subtraction assignment
   //=====================================================================================

   {
      test_ = "Row-major DenseSubmatrix subtraction assignment (no aliasing)";

      initialize();

      MT mat1( 64UL, 64UL );
      MT mat2( 64UL, 64UL );
      randomize( mat1, int(randmin), int(randmax) );
      mat2 = mat1;

      ASMT sm1 = submatrix<aligned>  ( mat1, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2, 8UL, 16UL, 8UL, 16UL );
      sm1 -= submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      sm2 -= submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major DenseSubmatrix subtraction assignment (aliasing)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );
      sm1 -= submatrix<aligned>  ( mat1_, 24UL, 24UL, 8UL, 16UL );
      sm2 -= submatrix<unaligned>( mat2_, 24UL, 24UL, 8UL, 16UL );

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major dense matrix subtraction assignment
   //=====================================================================================

   {
      test_ = "Row-major/row-major dense matrix subtraction assignment (aligned/padded)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      typedef blaze::CustomMatrix<int,aligned,padded,rowMajor>  AlignedPadded;
      AlignedPadded mat( blaze::allocate<int>( 128UL ), 8UL, 16UL, 16UL, blaze::Deallocate() );
      randomize( mat, int(randmin), int(randmax) );

      sm1 -= mat;
      sm2 -= mat;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/row-major dense matrix subtraction assignment (unaligned/unpadded)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      typedef blaze::CustomMatrix<int,unaligned,unpadded,rowMajor>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[129UL] );
      UnalignedUnpadded mat( array.get()+1UL, 8UL, 16UL );
      randomize( mat, int(randmin), int(randmax) );

      sm1 -= mat;
      sm2 -= mat;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/column-major dense matrix subtraction assignment (aligned/padded)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      typedef blaze::CustomMatrix<int,aligned,padded,columnMajor>  AlignedPadded;
      AlignedPadded mat( blaze::allocate<int>( 256UL ), 8UL, 16UL, 16UL, blaze::Deallocate() );
      randomize( mat, int(randmin), int(randmax) );

      sm1 -= mat;
      sm2 -= mat;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/column-major dense matrix subtraction assignment (unaligned/unpadded)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      typedef blaze::CustomMatrix<int,unaligned,unpadded,columnMajor>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[129UL] );
      UnalignedUnpadded mat( array.get()+1UL, 8UL, 16UL );
      randomize( mat, int(randmin), int(randmax) );

      sm1 -= mat;
      sm2 -= mat;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major sparse matrix subtraction assignment
   //=====================================================================================

   {
      test_ = "Row-major/row-major sparse matrix subtraction assignment";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      blaze::CompressedMatrix<int,rowMajor> mat( 8UL, 16UL );
      randomize( mat, 30UL, int(randmin), int(randmax) );

      sm1 -= mat;
      sm2 -= mat;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/column-major sparse matrix subtraction assignment";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      blaze::CompressedMatrix<int,columnMajor> mat( 8UL, 16UL );
      randomize( mat, 30UL, int(randmin), int(randmax) );

      sm1 -= mat;
      sm2 -= mat;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major DenseSubmatrix subtraction assignment
   //=====================================================================================

   {
      test_ = "Column-major DenseSubmatrix subtraction assignment (no aliasing)";

      initialize();

      OMT mat1( 64UL, 64UL );
      OMT mat2( 64UL, 64UL );
      randomize( mat1, int(randmin), int(randmax) );
      mat2 = mat1;

      AOSMT sm1 = submatrix<aligned>  ( mat1, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( mat2, 16UL, 8UL, 16UL, 8UL );
      sm1 -= submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      sm2 -= submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major DenseSubmatrix subtraction assignment (aliasing)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );
      sm1 -= submatrix<aligned>  ( tmat1_, 24UL, 24UL, 16UL, 8UL );
      sm2 -= submatrix<unaligned>( tmat2_, 24UL, 24UL, 16UL, 8UL );

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense matrix subtraction assignment
   //=====================================================================================

   {
      test_ = "Column-major/row-major dense matrix subtraction assignment (aligned/padded)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      typedef blaze::CustomMatrix<int,aligned,padded,rowMajor>  AlignedPadded;
      AlignedPadded mat( blaze::allocate<int>( 256UL ), 16UL, 8UL, 16UL, blaze::Deallocate() );
      randomize( mat, int(randmin), int(randmax) );

      sm1 -= mat;
      sm2 -= mat;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/row-major dense matrix subtraction assignment (unaligned/unpadded)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      typedef blaze::CustomMatrix<int,unaligned,unpadded,rowMajor>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[129UL] );
      UnalignedUnpadded mat( array.get()+1UL, 16UL, 8UL );
      randomize( mat, int(randmin), int(randmax) );

      sm1 -= mat;
      sm2 -= mat;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/column-major dense matrix subtraction assignment (aligned/padded)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      typedef blaze::CustomMatrix<int,aligned,padded,columnMajor>  AlignedPadded;
      AlignedPadded mat( blaze::allocate<int>( 128UL ), 16UL, 8UL, 16UL, blaze::Deallocate() );
      randomize( mat, int(randmin), int(randmax) );

      sm1 -= mat;
      sm2 -= mat;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/column-major dense matrix subtraction assignment (unaligned/unpadded)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      typedef blaze::CustomMatrix<int,unaligned,unpadded,columnMajor>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[129UL] );
      UnalignedUnpadded mat( array.get()+1UL, 16UL, 8UL );
      randomize( mat, int(randmin), int(randmax) );

      sm1 -= mat;
      sm2 -= mat;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major sparse matrix subtraction assignment
   //=====================================================================================

   {
      test_ = "Column-major/row-major sparse matrix subtraction assignment";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      blaze::CompressedMatrix<int,rowMajor> mat( 16UL, 8UL );
      randomize( mat, 30UL, int(randmin), int(randmax) );

      sm1 -= mat;
      sm2 -= mat;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/column-major sparse matrix subtraction assignment";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      blaze::CompressedMatrix<int,columnMajor> mat( 16UL, 8UL );
      randomize( mat, 30UL, int(randmin), int(randmax) );

      sm1 -= mat;
      sm2 -= mat;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the DenseSubmatrix multiplication assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the multiplication assignment operators of the DenseSubmatrix
// class template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void AlignedTest::testMultAssign()
{
   using blaze::submatrix;
   using blaze::aligned;
   using blaze::unaligned;
   using blaze::padded;
   using blaze::unpadded;
   using blaze::rowMajor;
   using blaze::columnMajor;


   //=====================================================================================
   // Row-major DenseSubmatrix multiplication assignment
   //=====================================================================================

   {
      test_ = "Row-major DenseSubmatrix multiplication assignment (no aliasing)";

      initialize();

      MT mat1( 64UL, 64UL );
      MT mat2( 64UL, 64UL );
      randomize( mat1, int(randmin), int(randmax) );
      mat2 = mat1;

      ASMT sm1 = submatrix<aligned>  ( mat1, 16UL, 16UL, 8UL, 8UL );
      USMT sm2 = submatrix<unaligned>( mat2, 16UL, 16UL, 8UL, 8UL );
      sm1 *= submatrix<aligned>  ( mat1_, 16UL, 16UL, 8UL, 8UL );
      sm2 *= submatrix<unaligned>( mat2_, 16UL, 16UL, 8UL, 8UL );

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major DenseSubmatrix multiplication assignment (aliasing)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 16UL, 16UL, 8UL, 8UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 16UL, 16UL, 8UL, 8UL );
      sm1 *= submatrix<aligned>  ( mat1_, 24UL, 24UL, 8UL, 8UL );
      sm2 *= submatrix<unaligned>( mat2_, 24UL, 24UL, 8UL, 8UL );

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major dense matrix multiplication assignment
   //=====================================================================================

   {
      test_ = "Row-major/row-major dense matrix multiplication assignment (aligned/padded)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 16UL, 16UL, 8UL, 8UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 16UL, 16UL, 8UL, 8UL );

      typedef blaze::CustomMatrix<int,aligned,padded,rowMajor>  AlignedPadded;
      AlignedPadded mat( blaze::allocate<int>( 128UL ), 8UL, 8UL, 16UL, blaze::Deallocate() );
      randomize( mat, int(randmin), int(randmax) );

      sm1 *= mat;
      sm2 *= mat;

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/row-major dense matrix multiplication assignment (unaligned/unpadded)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 16UL, 16UL, 8UL, 8UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 16UL, 16UL, 8UL, 8UL );

      typedef blaze::CustomMatrix<int,unaligned,unpadded,rowMajor>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[65UL] );
      UnalignedUnpadded mat( array.get()+1UL, 8UL, 8UL );
      randomize( mat, int(randmin), int(randmax) );

      sm1 *= mat;
      sm2 *= mat;

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/column-major dense matrix multiplication assignment (aligned/padded)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 16UL, 16UL, 8UL, 8UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 16UL, 16UL, 8UL, 8UL );

      typedef blaze::CustomMatrix<int,aligned,padded,columnMajor>  AlignedPadded;
      AlignedPadded mat( blaze::allocate<int>( 128UL ), 8UL, 8UL, 16UL, blaze::Deallocate() );
      randomize( mat, int(randmin), int(randmax) );

      sm1 *= mat;
      sm2 *= mat;

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/column-major dense matrix multiplication assignment (unaligned/unpadded)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 16UL, 16UL, 8UL, 8UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 16UL, 16UL, 8UL, 8UL );

      typedef blaze::CustomMatrix<int,unaligned,unpadded,columnMajor>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[65UL] );
      UnalignedUnpadded mat( array.get()+1UL, 8UL, 8UL );
      randomize( mat, int(randmin), int(randmax) );

      sm1 *= mat;
      sm2 *= mat;

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major sparse matrix multiplication assignment
   //=====================================================================================

   {
      test_ = "Row-major/row-major sparse matrix multiplication assignment";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 16UL, 16UL, 8UL, 8UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 16UL, 16UL, 8UL, 8UL );

      blaze::CompressedMatrix<int,rowMajor> mat( 8UL, 8UL );
      randomize( mat, 30UL, int(randmin), int(randmax) );

      sm1 *= mat;
      sm2 *= mat;

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/column-major sparse matrix multiplication assignment";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 16UL, 16UL, 8UL, 8UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 16UL, 16UL, 8UL, 8UL );

      blaze::CompressedMatrix<int,columnMajor> mat( 8UL, 8UL );
      randomize( mat, 30UL, int(randmin), int(randmax) );

      sm1 *= mat;
      sm2 *= mat;

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major DenseSubmatrix multiplication assignment
   //=====================================================================================

   {
      test_ = "Column-major DenseSubmatrix multiplication assignment (no aliasing)";

      initialize();

      OMT mat1( 64UL, 64UL );
      OMT mat2( 64UL, 64UL );
      randomize( mat1, int(randmin), int(randmax) );
      mat2 = mat1;

      AOSMT sm1 = submatrix<aligned>  ( mat1, 16UL, 16UL, 8UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( mat2, 16UL, 16UL, 8UL, 8UL );
      sm1 *= submatrix<aligned>  ( tmat1_, 16UL, 16UL, 8UL, 8UL );
      sm2 *= submatrix<unaligned>( tmat2_, 16UL, 16UL, 8UL, 8UL );

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major DenseSubmatrix multiplication assignment (aliasing)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 16UL, 8UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 16UL, 8UL, 8UL );
      sm1 *= submatrix<aligned>  ( tmat1_, 24UL, 24UL, 8UL, 8UL );
      sm2 *= submatrix<unaligned>( tmat2_, 24UL, 24UL, 8UL, 8UL );

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense matrix multiplication assignment
   //=====================================================================================

   {
      test_ = "Column-major/row-major dense matrix multiplication assignment (aligned/padded)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 16UL, 8UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 16UL, 8UL, 8UL );

      typedef blaze::CustomMatrix<int,aligned,padded,rowMajor>  AlignedPadded;
      AlignedPadded mat( blaze::allocate<int>( 128UL ), 8UL, 8UL, 16UL, blaze::Deallocate() );
      randomize( mat, int(randmin), int(randmax) );

      sm1 *= mat;
      sm2 *= mat;

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/row-major dense matrix multiplication assignment (unaligned/unpadded)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 16UL, 8UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 16UL, 8UL, 8UL );

      typedef blaze::CustomMatrix<int,unaligned,unpadded,rowMajor>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[65UL] );
      UnalignedUnpadded mat( array.get()+1UL, 8UL, 8UL );
      randomize( mat, int(randmin), int(randmax) );

      sm1 *= mat;
      sm2 *= mat;

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/column-major dense matrix multiplication assignment (aligned/padded)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 16UL, 8UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 16UL, 8UL, 8UL );

      typedef blaze::CustomMatrix<int,aligned,padded,columnMajor>  AlignedPadded;
      AlignedPadded mat( blaze::allocate<int>( 128UL ), 8UL, 8UL, 16UL, blaze::Deallocate() );
      randomize( mat, int(randmin), int(randmax) );

      sm1 *= mat;
      sm2 *= mat;

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/column-major dense matrix multiplication assignment (unaligned/unpadded)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 16UL, 8UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 16UL, 8UL, 8UL );

      typedef blaze::CustomMatrix<int,unaligned,unpadded,columnMajor>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[65UL] );
      UnalignedUnpadded mat( array.get()+1UL, 8UL, 8UL );
      randomize( mat, int(randmin), int(randmax) );

      sm1 *= mat;
      sm2 *= mat;

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major sparse matrix multiplication assignment
   //=====================================================================================

   {
      test_ = "Column-major/row-major sparse matrix multiplication assignment";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 16UL, 8UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 16UL, 8UL, 8UL );

      blaze::CompressedMatrix<int,rowMajor> mat( 8UL, 8UL );
      randomize( mat, 30UL, int(randmin), int(randmax) );

      sm1 *= mat;
      sm2 *= mat;

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/column-major sparse matrix multiplication assignment";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 16UL, 8UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 16UL, 8UL, 8UL );

      blaze::CompressedMatrix<int,columnMajor> mat( 8UL, 8UL );
      randomize( mat, 30UL, int(randmin), int(randmax) );

      sm1 *= mat;
      sm2 *= mat;

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of all DenseSubmatrix (self-)scaling operations.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of all available ways to scale an instance of the DenseSubmatrix
// class template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void AlignedTest::testScaling()
{
   using blaze::submatrix;
   using blaze::aligned;
   using blaze::unaligned;


   //=====================================================================================
   // Row-major self-scaling (M*=s)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M*=s) (8x16)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      sm1 *= 3;
      sm2 *= 3;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major self-scaling (M*=s) (16x8)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 16UL, 8UL, 16UL, 8UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 16UL, 8UL, 16UL, 8UL );

      sm1 *= 3;
      sm2 *= 3;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major self-scaling (M=M*s)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M=M*s) (8x16)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      sm1 = sm1 * 3;
      sm2 = sm2 * 3;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major self-scaling (M=M*s) (16x8)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 16UL, 8UL, 16UL, 8UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 16UL, 8UL, 16UL, 8UL );

      sm1 = sm1 * 3;
      sm2 = sm2 * 3;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major self-scaling (M=s*M)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M=s*M) (8x16)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      sm1 = 3 * sm1;
      sm2 = 3 * sm2;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major self-scaling (M=s*M) (16x8)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 16UL, 8UL, 16UL, 8UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 16UL, 8UL, 16UL, 8UL );

      sm1 = 3 * sm1;
      sm2 = 3 * sm2;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major self-scaling (M/=s)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M/=s) (8x16)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      sm1 /= 0.5;
      sm2 /= 0.5;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major self-scaling (M/=s) (16x8)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 16UL, 8UL, 16UL, 8UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 16UL, 8UL, 16UL, 8UL );

      sm1 /= 0.5;
      sm2 /= 0.5;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major self-scaling (M=M/s)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M=M/s) (8x16)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      sm1 = sm1 / 0.5;
      sm2 = sm2 / 0.5;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major self-scaling (M=M/s) (16x8)";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 16UL, 8UL, 16UL, 8UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 16UL, 8UL, 16UL, 8UL );

      sm1 = sm1 / 0.5;
      sm2 = sm2 / 0.5;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major DenseSubmatrix::scale()
   //=====================================================================================

   {
      test_ = "Row-major DenseSubmatrix::scale()";

      initialize();

      // Initialization check
      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      // Integral scaling of the matrix
      sm1.scale( 2 );
      sm2.scale( 2 );

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Integral scale operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }

      // Floating point scaling of the matrix
      sm1.scale( 0.5 );
      sm2.scale( 0.5 );

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Floating point scale operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (M*=s)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M*=s) (8x16)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 8UL, 16UL, 8UL, 16UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 8UL, 16UL, 8UL, 16UL );

      sm1 *= 3;
      sm2 *= 3;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major self-scaling (M*=s) (16x8)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      sm1 *= 3;
      sm2 *= 3;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (M=M*s)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M=M*s) (8x16)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 8UL, 16UL, 8UL, 16UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 8UL, 16UL, 8UL, 16UL );

      sm1 = sm1 * 3;
      sm2 = sm2 * 3;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major self-scaling (M=M*s) (16x8)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      sm1 = sm1 * 3;
      sm2 = sm2 * 3;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (M=s*M)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M=s*M) (8x16)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 8UL, 16UL, 8UL, 16UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 8UL, 16UL, 8UL, 16UL );

      sm1 = 3 * sm1;
      sm2 = 3 * sm2;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major self-scaling (M=s*M) (16x8)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      sm1 = 3 * sm1;
      sm2 = 3 * sm2;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (M/=s)
   //=====================================================================================

   {
      test_ = "Column-major self-scaling (M/=s) (8x16)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 8UL, 16UL, 8UL, 16UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 8UL, 16UL, 8UL, 16UL );

      sm1 /= 0.5;
      sm2 /= 0.5;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major self-scaling (M/=s) (16x8)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      sm1 /= 0.5;
      sm2 /= 0.5;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (M=M/s)
   //=====================================================================================

   {
      test_ = "Column-major self-scaling (M=M/s) (8x16)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 8UL, 16UL, 8UL, 16UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 8UL, 16UL, 8UL, 16UL );

      sm1 = sm1 / 0.5;
      sm2 = sm2 / 0.5;

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major self-scaling (M=M/s) (16x8)";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      sm1 = sm1 / 0.5;
      sm2 = sm2 / 0.5;

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major DenseSubmatrix::scale()
   //=====================================================================================

   {
      test_ = "Column-major DenseSubmatrix::scale()";

      initialize();

      // Initialization check
      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      // Integral scaling of the matrix
      sm1.scale( 2 );
      sm2.scale( 2 );

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Integral scale operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }

      // Floating point scaling of the matrix
      sm1.scale( 0.5 );
      sm2.scale( 0.5 );

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Floating point scale operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the DenseSubmatrix function call operator.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of adding and accessing elements via the function call operator
// of the DenseSubmatrix class template. In case an error is detected, a \a std::runtime_error
// exception is thrown.
*/
void AlignedTest::testFunctionCall()
{
   using blaze::submatrix;
   using blaze::aligned;
   using blaze::unaligned;


   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      test_ = "Row-major DenseSubmatrix::operator()";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      // Assignment to the element (1,4)
      {
         sm1(1,4) = 9;
         sm2(1,4) = 9;

         checkRows   ( sm1,  8UL );
         checkColumns( sm1, 16UL );
         checkRows   ( sm2,  8UL );
         checkColumns( sm2, 16UL );

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Assignment to the element (3,10)
      {
         sm1(3,10) = 0;
         sm2(3,10) = 0;

         checkRows   ( sm1,  8UL );
         checkColumns( sm1, 16UL );
         checkRows   ( sm2,  8UL );
         checkColumns( sm2, 16UL );

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Assignment to the element (6,8)
      {
         sm1(6,8) = -7;
         sm2(6,8) = -7;

         checkRows   ( sm1,  8UL );
         checkColumns( sm1, 16UL );
         checkRows   ( sm2,  8UL );
         checkColumns( sm2, 16UL );

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Addition assignment to the element (5,7)
      {
         sm1(5,7) += 3;
         sm2(5,7) += 3;

         checkRows   ( sm1,  8UL );
         checkColumns( sm1, 16UL );
         checkRows   ( sm2,  8UL );
         checkColumns( sm2, 16UL );

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Subtraction assignment to the element (2,14)
      {
         sm1(2,14) -= -8;
         sm2(2,14) -= -8;

         checkRows   ( sm1,  8UL );
         checkColumns( sm1, 16UL );
         checkRows   ( sm2,  8UL );
         checkColumns( sm2, 16UL );

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Multiplication assignment to the element (1,1)
      {
         sm1(1,1) *= 3;
         sm2(1,1) *= 3;

         checkRows   ( sm1,  8UL );
         checkColumns( sm1, 16UL );
         checkRows   ( sm2,  8UL );
         checkColumns( sm2, 16UL );

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Division assignment to the element (3,4)
      {
         sm1(3,4) /= 2;
         sm2(3,4) /= 2;

         checkRows   ( sm1,  8UL );
         checkColumns( sm1, 16UL );
         checkRows   ( sm2,  8UL );
         checkColumns( sm2, 16UL );

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      test_ = "Column-major DenseSubmatrix::operator()";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      // Assignment to the element (4,1)
      {
         sm1(4,1) = 9;
         sm2(4,1) = 9;

         checkRows   ( sm1, 16UL );
         checkColumns( sm1,  8UL );
         checkRows   ( sm2, 16UL );
         checkColumns( sm2,  8UL );

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Assignment to the element (10,3)
      {
         sm1(10,3) = 0;
         sm2(10,3) = 0;

         checkRows   ( sm1, 16UL );
         checkColumns( sm1,  8UL );
         checkRows   ( sm2, 16UL );
         checkColumns( sm2,  8UL );

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Assignment to the element (8,6)
      {
         sm1(8,6) = -7;
         sm2(8,6) = -7;

         checkRows   ( sm1, 16UL );
         checkColumns( sm1,  8UL );
         checkRows   ( sm2, 16UL );
         checkColumns( sm2,  8UL );

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Addition assignment to the element (7,5)
      {
         sm1(7,5) += 3;
         sm2(7,5) += 3;

         checkRows   ( sm1, 16UL );
         checkColumns( sm1,  8UL );
         checkRows   ( sm2, 16UL );
         checkColumns( sm2,  8UL );

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Subtraction assignment to the element (14,2)
      {
         sm1(14,2) -= -8;
         sm2(14,2) -= -8;

         checkRows   ( sm1, 16UL );
         checkColumns( sm1,  8UL );
         checkRows   ( sm2, 16UL );
         checkColumns( sm2,  8UL );

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Multiplication assignment to the element (1,1)
      {
         sm1(1,1) *= 3;
         sm2(1,1) *= 3;

         checkRows   ( sm1, 16UL );
         checkColumns( sm1,  8UL );
         checkRows   ( sm2, 16UL );
         checkColumns( sm2,  8UL );

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Division assignment to the element (4,3)
      {
         sm1(4,3) /= 2;
         sm2(4,3) /= 2;

         checkRows   ( sm1, 16UL );
         checkColumns( sm1,  8UL );
         checkRows   ( sm2, 16UL );
         checkColumns( sm2,  8UL );

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the DenseSubmatrix iterator implementation.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the iterator implementation of the DenseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void AlignedTest::testIterator()
{
   using blaze::submatrix;
   using blaze::aligned;
   using blaze::unaligned;


   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      initialize();

      // Testing the Iterator default constructor
      {
         test_ = "Row-major Iterator default constructor";

         ASMT::Iterator it = ASMT::Iterator();

         if( it != ASMT::Iterator() ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator default constructor\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing the ConstIterator default constructor
      {
         test_ = "Row-major ConstIterator default constructor";

         ASMT::ConstIterator it = ASMT::ConstIterator();

         if( it != ASMT::ConstIterator() ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator default constructor\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing conversion from Iterator to ConstIterator
      {
         test_ = "Row-major Iterator/ConstIterator conversion";

         ASMT sm = submatrix<aligned>( mat1_, 8UL, 16UL, 8UL, 16UL );
         ASMT::ConstIterator it( begin( sm, 2UL ) );

         if( it == end( sm, 2UL ) || *it != sm(2,0) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator conversion detected\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 0th row of a 8x16 matrix via Iterator
      {
         test_ = "Row-major Iterator subtraction";

         ASMT sm = submatrix<aligned>( mat1_, 8UL, 16UL, 8UL, 16UL );
         const size_t number( end( sm, 0UL ) - begin( sm, 0UL ) );

         if( number != 16UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 16\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 15th row of a 16x8 matrix via ConstIterator
      {
         test_ = "Row-major ConstIterator subtraction";

         ASMT sm = submatrix<aligned>( mat1_, 16UL, 8UL, 16UL, 8UL );
         const size_t number( cend( sm, 15UL ) - cbegin( sm, 15UL ) );

         if( number != 8UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 8\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing read-only access via ConstIterator
      {
         test_ = "Row-major read-only access via ConstIterator";

         ASMT sm = submatrix<aligned>( mat1_, 8UL, 16UL, 8UL, 16UL );
         ASMT::ConstIterator it ( cbegin( sm, 2UL ) );
         ASMT::ConstIterator end( cend( sm, 2UL ) );

         if( it == end || *it != sm(2,0) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid initial iterator detected\n";
            throw std::runtime_error( oss.str() );
         }

         ++it;

         if( it == end || *it != sm(2,1) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator pre-increment failed\n";
            throw std::runtime_error( oss.str() );
         }

         --it;

         if( it == end || *it != sm(2,0) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator pre-decrement failed\n";
            throw std::runtime_error( oss.str() );
         }

         it++;

         if( it == end || *it != sm(2,1) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator post-increment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it--;

         if( it == end || *it != sm(2,0) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator post-decrement failed\n";
            throw std::runtime_error( oss.str() );
         }

         it += 2UL;

         if( it == end || *it != sm(2,2) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator addition assignment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it -= 2UL;

         if( it == end || *it != sm(2,0) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator subtraction assignment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = it + 2UL;

         if( it == end || *it != sm(2,2) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator/scalar addition failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = it - 2UL;

         if( it == end || *it != sm(2,0) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator/scalar subtraction failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = 16UL + it;

         if( it != end ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Scalar/iterator addition failed\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing assignment via Iterator
      {
         test_ = "Row-major assignment via Iterator";

         ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
         USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );
         int value = 7;

         ASMT::Iterator it1( begin( sm1, 2UL ) );
         USMT::Iterator it2( begin( sm2, 2UL ) );

         for( ; it1!=end( sm1, 2UL ); ++it1, ++it2 ) {
            *it1 = value;
            *it2 = value;
            ++value;
         }

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing addition assignment via Iterator
      {
         test_ = "Row-major addition assignment via Iterator";

         ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
         USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );
         int value = 4;

         ASMT::Iterator it1( begin( sm1, 2UL ) );
         USMT::Iterator it2( begin( sm2, 2UL ) );

         for( ; it1!=end( sm1, 2UL ); ++it1, ++it2 ) {
            *it1 += value;
            *it2 += value;
            ++value;
         }

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Addition assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing subtraction assignment via Iterator
      {
         test_ = "Row-major subtraction assignment via Iterator";

         ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
         USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );
         int value = 4;

         ASMT::Iterator it1( begin( sm1, 2UL ) );
         USMT::Iterator it2( begin( sm2, 2UL ) );

         for( ; it1!=end( sm1, 2UL ); ++it1, ++it2 ) {
            *it1 -= value;
            *it2 -= value;
            ++value;
         }

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subtraction assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing multiplication assignment via Iterator
      {
         test_ = "Row-major multiplication assignment via Iterator";

         ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
         USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );
         int value = 2;

         ASMT::Iterator it1( begin( sm1, 2UL ) );
         USMT::Iterator it2( begin( sm2, 2UL ) );

         for( ; it1!=end( sm1, 2UL ); ++it1, ++it2 ) {
            *it1 *= value;
            *it2 *= value;
            ++value;
         }

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Multiplication assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing division assignment via Iterator
      {
         test_ = "Row-major division assignment via Iterator";

         ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
         USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

         ASMT::Iterator it1( begin( sm1, 2UL ) );
         USMT::Iterator it2( begin( sm2, 2UL ) );

         for( ; it1!=end( sm1, 2UL ); ++it1, ++it2 ) {
            *it1 /= 2;
            *it2 /= 2;
         }

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Division assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      initialize();

      // Testing the Iterator default constructor
      {
         test_ = "Column-major Iterator default constructor";

         AOSMT::Iterator it = AOSMT::Iterator();

         if( it != AOSMT::Iterator() ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator default constructor\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing the ConstIterator default constructor
      {
         test_ = "Column-major ConstIterator default constructor";

         AOSMT::ConstIterator it = AOSMT::ConstIterator();

         if( it != AOSMT::ConstIterator() ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator default constructor\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing conversion from Iterator to ConstIterator
      {
         test_ = "Column-major Iterator/ConstIterator conversion";

         AOSMT sm = submatrix<aligned>( tmat1_, 8UL, 16UL, 8UL, 16UL );
         AOSMT::ConstIterator it( begin( sm, 2UL ) );

         if( it == end( sm, 2UL ) || *it != sm(0,2) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator conversion detected\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 0th column of a 16x8 matrix via Iterator
      {
         test_ = "Column-major Iterator subtraction";

         AOSMT sm = submatrix<aligned>( tmat1_, 16UL, 8UL, 16UL, 8UL );
         const size_t number( end( sm, 0UL ) - begin( sm, 0UL ) );

         if( number != 16UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 16\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 15th column of a 8x16 matrix via ConstIterator
      {
         test_ = "Column-major ConstIterator subtraction";

         AOSMT sm = submatrix<aligned>( tmat1_, 8UL, 16UL, 8UL, 16UL );
         const size_t number( cend( sm, 15UL ) - cbegin( sm, 15UL ) );

         if( number != 8UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 8\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing read-only access via ConstIterator
      {
         test_ = "Column-major read-only access via ConstIterator";

         AOSMT sm = submatrix<aligned>( tmat1_, 16UL, 8UL, 16UL, 8UL );
         AOSMT::ConstIterator it ( cbegin( sm, 2UL ) );
         AOSMT::ConstIterator end( cend( sm, 2UL ) );

         if( it == end || *it != sm(0,2) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid initial iterator detected\n";
            throw std::runtime_error( oss.str() );
         }

         ++it;

         if( it == end || *it != sm(1,2) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator pre-increment failed\n";
            throw std::runtime_error( oss.str() );
         }

         --it;

         if( it == end || *it != sm(0,2) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator pre-decrement failed\n";
            throw std::runtime_error( oss.str() );
         }

         it++;

         if( it == end || *it != sm(1,2) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator post-increment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it--;

         if( it == end || *it != sm(0,2) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator post-decrement failed\n";
            throw std::runtime_error( oss.str() );
         }

         it += 2UL;

         if( it == end || *it != sm(2,2) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator addition assignment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it -= 2UL;

         if( it == end || *it != sm(0,2) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator subtraction assignment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = it + 2UL;

         if( it == end || *it != sm(2,2) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator/scalar addition failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = it - 2UL;

         if( it == end || *it != sm(0,2) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator/scalar subtraction failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = 16UL + it;

         if( it != end ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Scalar/iterator addition failed\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing assignment via Iterator
      {
         test_ = "Column-major assignment via Iterator";

         AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
         UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );
         int value = 7;

         AOSMT::Iterator it1( begin( sm1, 2UL ) );
         UOSMT::Iterator it2( begin( sm2, 2UL ) );

         for( ; it1!=end( sm1, 2UL ); ++it1, ++it2 ) {
            *it1 = value;
            *it2 = value;
            ++value;
         }

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing addition assignment via Iterator
      {
         test_ = "Column-major addition assignment via Iterator";

         AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
         UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );
         int value = 4;

         AOSMT::Iterator it1( begin( sm1, 2UL ) );
         UOSMT::Iterator it2( begin( sm2, 2UL ) );

         for( ; it1!=end( sm1, 2UL ); ++it1, ++it2 ) {
            *it1 += value;
            *it2 += value;
            ++value;
         }

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Addition assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing subtraction assignment via Iterator
      {
         test_ = "Column-major subtraction assignment via Iterator";

         AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
         UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );
         int value = 4;

         AOSMT::Iterator it1( begin( sm1, 2UL ) );
         UOSMT::Iterator it2( begin( sm2, 2UL ) );

         for( ; it1!=end( sm1, 2UL ); ++it1, ++it2 ) {
            *it1 -= value;
            *it2 -= value;
            ++value;
         }

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subtraction assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing multiplication assignment via Iterator
      {
         test_ = "Column-major multiplication assignment via Iterator";

         AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
         UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );
         int value = 2;

         AOSMT::Iterator it1( begin( sm1, 2UL ) );
         UOSMT::Iterator it2( begin( sm2, 2UL ) );

         for( ; it1!=end( sm1, 2UL ); ++it1, ++it2 ) {
            *it1 *= value;
            *it2 *= value;
            ++value;
         }

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Multiplication assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing division assignment via Iterator
      {
         test_ = "Column-major division assignment via Iterator";

         AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
         UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

         AOSMT::Iterator it1( begin( sm1, 2UL ) );
         UOSMT::Iterator it2( begin( sm2, 2UL ) );

         for( ; it1!=end( sm1, 2UL ); ++it1, ++it2 ) {
            *it1 /= 2;
            *it2 /= 2;
         }

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Division assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c nonZeros() member function of the DenseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c nonZeros() member function of the DenseSubmatrix
// class template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void AlignedTest::testNonZeros()
{
   using blaze::submatrix;
   using blaze::aligned;
   using blaze::unaligned;


   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      test_ = "Row-major DenseSubmatrix::nonZeros()";

      initialize();

      // Initialization check
      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1.nonZeros() != sm2.nonZeros() ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Invalid number of non-zeros\n"
             << " Details:\n"
             << "   Result:\n" << sm1.nonZeros() << "\n"
             << "   Expected result:\n" << sm2.nonZeros() << "\n"
             << "   Submatrix:\n" << sm1 << "\n"
             << "   Reference:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }

      for( size_t i=0UL; i<sm1.rows(); ++i ) {
         if( sm1.nonZeros(i) != sm2.nonZeros(i) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of non-zeros in row " << i << "\n"
                << " Details:\n"
                << "   Result:\n" << sm1.nonZeros(i) << "\n"
                << "   Expected result:\n" << sm2.nonZeros(i) << "\n"
                << "   Submatrix:\n" << sm1 << "\n"
                << "   Reference:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      test_ = "Column-major DenseSubmatrix::nonZeros()";

      initialize();

      // Initialization check
      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1.nonZeros() != sm2.nonZeros() ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Invalid number of non-zeros\n"
             << " Details:\n"
             << "   Result:\n" << sm1.nonZeros() << "\n"
             << "   Expected result:\n" << sm2.nonZeros() << "\n"
             << "   Submatrix:\n" << sm1 << "\n"
             << "   Reference:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }

      for( size_t j=0UL; j<sm1.columns(); ++j ) {
         if( sm1.nonZeros(j) != sm2.nonZeros(j) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of non-zeros in column " << j << "\n"
                << " Details:\n"
                << "   Result:\n" << sm1.nonZeros(j) << "\n"
                << "   Expected result:\n" << sm2.nonZeros(j) << "\n"
                << "   Submatrix:\n" << sm1 << "\n"
                << "   Reference:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c reset() member function of the DenseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c reset() member function of the DenseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void AlignedTest::testReset()
{
   using blaze::submatrix;
   using blaze::aligned;
   using blaze::unaligned;
   using blaze::reset;


   //=====================================================================================
   // Row-major single element reset
   //=====================================================================================

   {
      test_ = "Row-major reset() function";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      reset( sm1(4,4) );
      reset( sm2(4,4) );

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major reset
   //=====================================================================================

   {
      test_ = "Row-major DenseSubmatrix::reset()";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      reset( sm1 );
      reset( sm2 );

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( !isDefault( sm1 ) || !isDefault( sm2 ) || sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major row-wise reset
   //=====================================================================================

   {
      test_ = "Row-major DenseSubmatrix::reset( size_t )";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      for( size_t i=0UL; i<sm1.rows(); ++i )
      {
         reset( sm1, i );
         reset( sm2, i );

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Reset operation failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major single element reset
   //=====================================================================================

   {
      test_ = "Column-major reset() function";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      reset( sm1(4,4) );
      reset( sm2(4,4) );

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major reset
   //=====================================================================================

   {
      test_ = "Column-major DenseSubmatrix::reset()";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      reset( sm1 );
      reset( sm2 );

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( !isDefault( sm1 ) || !isDefault( sm2 ) || sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major row-wise reset
   //=====================================================================================

   {
      test_ = "Column-major DenseSubmatrix::reset( size_t )";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      for( size_t j=0UL; j<sm1.columns(); ++j )
      {
         reset( sm1, j );
         reset( sm2, j );

         if( sm1 != sm2 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Reset operation failed\n"
                << " Details:\n"
                << "   Result:\n" << sm1 << "\n"
                << "   Expected result:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c clear() function with the DenseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c clear() function with the DenseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void AlignedTest::testClear()
{
   using blaze::submatrix;
   using blaze::aligned;
   using blaze::unaligned;
   using blaze::clear;


   //=====================================================================================
   // Row-major single element clear
   //=====================================================================================

   {
      test_ = "Row-major clear() function";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );

      clear( sm1(4,4) );
      clear( sm2(4,4) );

      checkRows   ( sm1,  8UL );
      checkColumns( sm1, 16UL );
      checkRows   ( sm2,  8UL );
      checkColumns( sm2, 16UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Clear operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major single element clear
   //=====================================================================================

   {
      test_ = "Column-major clear() function";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );

      clear( sm1(4,4) );
      clear( sm2(4,4) );

      checkRows   ( sm1, 16UL );
      checkColumns( sm1,  8UL );
      checkRows   ( sm2, 16UL );
      checkColumns( sm2,  8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Clear operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c transpose() member function of the DenseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c transpose() member function of the DenseSubmatrix
// class template. Additionally, it performs a test of self-transpose via the \c trans()
// function. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void AlignedTest::testTranspose()
{
   using blaze::submatrix;
   using blaze::aligned;
   using blaze::unaligned;


   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      test_ = "Row-major self-transpose via transpose()";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 8UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 8UL );

      transpose( sm1 );
      transpose( sm2 );

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major self-transpose via trans()";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 8UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 8UL );

      sm1 = trans( sm1 );
      sm2 = trans( sm2 );

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      test_ = "Column-major self-transpose via transpose()";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 8UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 8UL, 8UL );

      transpose( sm1 );
      transpose( sm2 );

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major self-transpose via trans()";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 8UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 8UL, 8UL );

      sm1 = trans( sm1 );
      sm2 = trans( sm2 );

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c ctranspose() member function of the DenseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c ctranspose() member function of the DenseSubmatrix
// class template. Additionally, it performs a test of self-transpose via the \c ctrans()
// function. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void AlignedTest::testCTranspose()
{
   using blaze::submatrix;
   using blaze::aligned;
   using blaze::unaligned;


   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      test_ = "Row-major self-transpose via ctranspose()";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 8UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 8UL );

      ctranspose( sm1 );
      ctranspose( sm2 );

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major self-transpose via ctrans()";

      initialize();

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 8UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 8UL );

      sm1 = ctrans( sm1 );
      sm2 = ctrans( sm2 );

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      test_ = "Column-major self-transpose via ctranspose()";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 8UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 8UL, 8UL );

      ctranspose( sm1 );
      ctranspose( sm2 );

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major self-transpose via ctrans()";

      initialize();

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 8UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 8UL, 8UL );

      sm1 = ctrans( sm1 );
      sm2 = ctrans( sm2 );

      checkRows   ( sm1, 8UL );
      checkColumns( sm1, 8UL );
      checkRows   ( sm2, 8UL );
      checkColumns( sm2, 8UL );

      if( sm1 != sm2 || mat1_ != mat2_ ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm1 << "\n"
             << "   Expected result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c isDefault() function with the DenseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c isDefault() function with the DenseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void AlignedTest::testIsDefault()
{
   using blaze::submatrix;
   using blaze::aligned;
   using blaze::isDefault;


   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      test_ = "Row-major isDefault() function";

      initialize();

      // isDefault with default submatrix
      {
         MT mat( 64UL, 64UL, 0 );
         ASMT sm = submatrix<aligned>( mat, 8UL, 16UL, 8UL, 16UL );

         if( isDefault( sm(4,4) ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Submatrix element: " << sm(1,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( sm ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isDefault with non-default submatrix
      {
         ASMT sm = submatrix<aligned>( mat1_, 8UL, 16UL, 8UL, 16UL );

         if( isDefault( sm ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      test_ = "Column-major isDefault() function";

      initialize();

      // isDefault with default submatrix
      {
         OMT mat( 64UL, 64UL, 0 );
         AOSMT sm = submatrix<aligned>( mat, 16UL, 8UL, 16UL, 8UL );

         if( isDefault( sm(4,4) ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Submatrix element: " << sm(1,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( sm ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isDefault with non-default submatrix
      {
         AOSMT sm = submatrix<aligned>( tmat1_, 16UL, 8UL, 16UL, 8UL );

         if( isDefault( sm ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c isSame() function with the DenseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c isSame() function with the DenseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void AlignedTest::testIsSame()
{
   using blaze::submatrix;
   using blaze::aligned;


   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      test_ = "Row-major isSame() function";

      // isSame with matrix and matching submatrix
      {
         ASMT sm = submatrix<aligned>( mat1_, 0UL, 0UL, 64UL, 64UL );

         if( blaze::isSame( sm, mat1_ ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << mat1_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( mat1_, sm ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << mat1_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matrix and non-matching submatrix (different number of rows)
      {
         ASMT sm = submatrix<aligned>( mat1_, 0UL, 0UL, 32UL, 64UL );

         if( blaze::isSame( sm, mat1_ ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << mat1_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( mat1_, sm ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << mat1_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matrix and non-matching submatrix (different number of columns)
      {
         ASMT sm = submatrix<aligned>( mat1_, 0UL, 0UL, 64UL, 32UL );

         if( blaze::isSame( sm, mat1_ ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << mat1_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( mat1_, sm ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << mat1_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matrix and non-matching submatrix (different row index)
      {
         ASMT sm = submatrix<aligned>( mat1_, 16UL, 0UL, 48UL, 64UL );

         if( blaze::isSame( sm, mat1_ ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << mat1_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( mat1_, sm ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << mat1_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matrix and non-matching submatrix (different column index)
      {
         ASMT sm = submatrix<aligned>( mat1_, 0UL, 16UL, 64UL, 48UL );

         if( blaze::isSame( sm, mat1_ ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << mat1_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( mat1_, sm ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << mat1_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matching submatrices
      {
         ASMT sm1 = submatrix<aligned>( mat1_, 16UL, 0UL, 32UL, 16UL );
         ASMT sm2 = submatrix<aligned>( mat1_, 16UL, 0UL, 32UL, 16UL );

         if( blaze::isSame( sm1, sm2 ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First submatrix:\n" << sm1 << "\n"
                << "   Second submatrix:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching submatrices (different number of rows)
      {
         ASMT sm1 = submatrix<aligned>( mat1_, 16UL, 0UL, 32UL, 16UL );
         ASMT sm2 = submatrix<aligned>( mat1_, 16UL, 0UL, 16UL, 16UL );

         if( blaze::isSame( sm1, sm2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First submatrix:\n" << sm1 << "\n"
                << "   Second submatrix:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching submatrices (different number of columns)
      {
         ASMT sm1 = submatrix<aligned>( mat1_, 16UL, 0UL, 32UL, 16UL );
         ASMT sm2 = submatrix<aligned>( mat1_, 16UL, 0UL, 32UL, 32UL );

         if( blaze::isSame( sm1, sm2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First submatrix:\n" << sm1 << "\n"
                << "   Second submatrix:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching submatrices (different row index)
      {
         ASMT sm1 = submatrix<aligned>( mat1_, 16UL, 0UL, 32UL, 16UL );
         ASMT sm2 = submatrix<aligned>( mat1_, 32UL, 0UL, 32UL, 16UL );

         if( blaze::isSame( sm1, sm2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First submatrix:\n" << sm1 << "\n"
                << "   Second submatrix:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching submatrices (different column index)
      {
         ASMT sm1 = submatrix<aligned>( mat1_, 16UL,  0UL, 32UL, 16UL );
         ASMT sm2 = submatrix<aligned>( mat1_, 16UL, 16UL, 32UL, 16UL );

         if( blaze::isSame( sm1, sm2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First submatrix:\n" << sm1 << "\n"
                << "   Second submatrix:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      test_ = "Column-major isSame() function";

      // isSame with matrix and matching submatrix
      {
         AOSMT sm = submatrix<aligned>( tmat1_, 0UL, 0UL, 64UL, 64UL );

         if( blaze::isSame( sm, tmat1_ ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << tmat1_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( tmat1_, sm ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << tmat1_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matrix and non-matching submatrix (different number of rows)
      {
         AOSMT sm = submatrix<aligned>( tmat1_, 0UL, 0UL, 32UL, 64UL );

         if( blaze::isSame( sm, tmat1_ ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << tmat1_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( tmat1_, sm ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << tmat1_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matrix and non-matching submatrix (different number of columns)
      {
         AOSMT sm = submatrix<aligned>( tmat1_, 0UL, 0UL, 64UL, 32UL );

         if( blaze::isSame( sm, tmat1_ ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << tmat1_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( tmat1_, sm ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << tmat1_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matrix and non-matching submatrix (different row index)
      {
         AOSMT sm = submatrix<aligned>( tmat1_, 16UL, 0UL, 48UL, 64UL );

         if( blaze::isSame( sm, tmat1_ ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << tmat1_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( tmat1_, sm ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << tmat1_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matrix and non-matching submatrix (different column index)
      {
         AOSMT sm = submatrix<aligned>( tmat1_, 0UL, 16UL, 64UL, 48UL );

         if( blaze::isSame( sm, tmat1_ ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << tmat1_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( tmat1_, sm ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << tmat1_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matching submatrices
      {
         AOSMT sm1 = submatrix<aligned>( tmat1_, 16UL, 0UL, 32UL, 16UL );
         AOSMT sm2 = submatrix<aligned>( tmat1_, 16UL, 0UL, 32UL, 16UL );

         if( blaze::isSame( sm1, sm2 ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First submatrix:\n" << sm1 << "\n"
                << "   Second submatrix:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching submatrices (different number of rows)
      {
         AOSMT sm1 = submatrix<aligned>( tmat1_, 16UL, 0UL, 32UL, 16UL );
         AOSMT sm2 = submatrix<aligned>( tmat1_, 16UL, 0UL, 16UL, 16UL );

         if( blaze::isSame( sm1, sm2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First submatrix:\n" << sm1 << "\n"
                << "   Second submatrix:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching submatrices (different number of columns)
      {
         AOSMT sm1 = submatrix<aligned>( tmat1_, 16UL, 0UL, 32UL, 16UL );
         AOSMT sm2 = submatrix<aligned>( tmat1_, 16UL, 0UL, 32UL, 32UL );

         if( blaze::isSame( sm1, sm2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First submatrix:\n" << sm1 << "\n"
                << "   Second submatrix:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching submatrices (different row index)
      {
         AOSMT sm1 = submatrix<aligned>( tmat1_, 16UL, 0UL, 32UL, 16UL );
         AOSMT sm2 = submatrix<aligned>( tmat1_, 32UL, 0UL, 32UL, 16UL );

         if( blaze::isSame( sm1, sm2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First submatrix:\n" << sm1 << "\n"
                << "   Second submatrix:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching submatrices (different column index)
      {
         AOSMT sm1 = submatrix<aligned>( tmat1_, 16UL,  0UL, 32UL, 16UL );
         AOSMT sm2 = submatrix<aligned>( tmat1_, 16UL, 16UL, 32UL, 16UL );

         if( blaze::isSame( sm1, sm2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First submatrix:\n" << sm1 << "\n"
                << "   Second submatrix:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c submatrix() function with the DenseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c submatrix() function with the DenseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void AlignedTest::testSubmatrix()
{
   using blaze::submatrix;
   using blaze::aligned;
   using blaze::unaligned;


   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major submatrix() function";

      initialize();

      {
         ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 8UL, 16UL, 32UL );
         ASMT sm2 = submatrix<aligned>  ( sm1  , 8UL, 8UL,  8UL, 16UL );
         USMT sm3 = submatrix<unaligned>( mat2_, 8UL, 8UL, 16UL, 32UL );
         USMT sm4 = submatrix<unaligned>( sm3  , 8UL, 8UL,  8UL, 16UL );

         if( sm2 != sm4 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Submatrix function failed\n"
                << " Details:\n"
                << "   Result:\n" << sm2 << "\n"
                << "   Expected result:\n" << sm4 << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( sm2(1,1) != sm4(1,1) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator access failed\n"
                << " Details:\n"
                << "   Result: " << sm2(1,1) << "\n"
                << "   Expected result: " << sm4(1,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( *sm2.begin(1UL) != *sm4.begin(1UL) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator access failed\n"
                << " Details:\n"
                << "   Result: " << *sm2.begin(1UL) << "\n"
                << "   Expected result: " << *sm4.begin(1UL) << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      try {
         ASMT sm1 = submatrix<aligned>( mat1_,  8UL, 8UL, 16UL, 32UL );
         ASMT sm2 = submatrix<aligned>( sm1  , 16UL, 8UL,  8UL,  8UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      try {
         ASMT sm1 = submatrix<aligned>( mat1_, 8UL,  8UL, 16UL, 32UL );
         ASMT sm2 = submatrix<aligned>( sm1  , 8UL, 32UL,  8UL,  8UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      try {
         ASMT sm1 = submatrix<aligned>( mat1_, 8UL, 8UL, 16UL, 32UL );
         ASMT sm2 = submatrix<aligned>( sm1  , 8UL, 8UL, 16UL, 24UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      try {
         ASMT sm1 = submatrix<aligned>( mat1_, 8UL, 8UL, 16UL, 32UL );
         ASMT sm2 = submatrix<aligned>( sm1  , 8UL, 8UL,  8UL, 32UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major submatrix() function";

      initialize();

      {
         AOSMT sm1 = submatrix<aligned>  ( tmat1_, 8UL, 8UL, 32UL, 16UL );
         AOSMT sm2 = submatrix<aligned>  ( sm1   , 8UL, 8UL, 16UL,  8UL );
         UOSMT sm3 = submatrix<unaligned>( tmat2_, 8UL, 8UL, 32UL, 16UL );
         UOSMT sm4 = submatrix<unaligned>( sm3   , 8UL, 8UL, 16UL,  8UL );

         if( sm2 != sm4 || mat1_ != mat2_ ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Submatrix function failed\n"
                << " Details:\n"
                << "   Result:\n" << sm2 << "\n"
                << "   Expected result:\n" << sm4 << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( sm2(1,1) != sm4(1,1) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator access failed\n"
                << " Details:\n"
                << "   Result: " << sm2(1,1) << "\n"
                << "   Expected result: " << sm4(1,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( *sm2.begin(1UL) != *sm4.begin(1UL) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator access failed\n"
                << " Details:\n"
                << "   Result: " << *sm2.begin(1UL) << "\n"
                << "   Expected result: " << *sm4.begin(1UL) << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      try {
         ASMT sm1 = submatrix<aligned>( mat1_,  8UL, 8UL, 32UL, 16UL );
         ASMT sm2 = submatrix<aligned>( sm1  , 32UL, 8UL,  8UL,  8UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      try {
         ASMT sm1 = submatrix<aligned>( mat1_, 8UL,  8UL, 32UL, 16UL );
         ASMT sm2 = submatrix<aligned>( sm1  , 8UL, 16UL,  8UL,  8UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      try {
         ASMT sm1 = submatrix<aligned>( mat1_, 8UL, 8UL, 32UL, 16UL );
         ASMT sm2 = submatrix<aligned>( sm1  , 8UL, 8UL, 32UL,  8UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      try {
         ASMT sm1 = submatrix<aligned>( mat1_, 8UL, 8UL, 32UL, 16UL );
         ASMT sm2 = submatrix<aligned>( sm1  , 8UL, 8UL, 24UL, 16UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c row() function with the DenseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c row() function with the DenseSubmatrix class template.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void AlignedTest::testRow()
{
   using blaze::submatrix;
   using blaze::aligned;
   using blaze::unaligned;


   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major row() function";

      initialize();

      typedef blaze::DenseRow<ASMT>  AlignedRowType;
      typedef blaze::DenseRow<USMT>  UnalignedRowType;

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );
      AlignedRowType   row1 = row( sm1, 1UL );
      UnalignedRowType row2 = row( sm2, 1UL );

      if( row1 != row2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row function failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n" << row2 << "\n";
         throw std::runtime_error( oss.str() );
      }

      if( row1[1] != row2[1] ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator access failed\n"
             << " Details:\n"
             << "   Result: " << row1[1] << "\n"
             << "   Expected result: " << row2[1] << "\n";
         throw std::runtime_error( oss.str() );
      }

      if( *row1.begin() != *row2.begin() ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << *row1.begin() << "\n"
             << "   Expected result: " << *row2.begin() << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major row() function";

      initialize();

      typedef blaze::DenseRow<AOSMT>  AlignedRowType;
      typedef blaze::DenseRow<UOSMT>  UnalignedRowType;

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );
      AlignedRowType   row1 = row( sm1, 1UL );
      UnalignedRowType row2 = row( sm2, 1UL );

      if( row1 != row2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row function failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n" << row2 << "\n";
         throw std::runtime_error( oss.str() );
      }

      if( row1[1] != row2[1] ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator access failed\n"
             << " Details:\n"
             << "   Result: " << row1[1] << "\n"
             << "   Expected result: " << row2[1] << "\n";
         throw std::runtime_error( oss.str() );
      }

      if( *row1.begin() != *row2.begin() ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << *row1.begin() << "\n"
             << "   Expected result: " << *row2.begin() << "\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c column() function with the DenseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c column() function with the DenseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void AlignedTest::testColumn()
{
   using blaze::submatrix;
   using blaze::aligned;
   using blaze::unaligned;


   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major column() function";

      initialize();

      typedef blaze::DenseColumn<ASMT>  AlignedColumnType;
      typedef blaze::DenseColumn<USMT>  UnalignedColumnType;

      ASMT sm1 = submatrix<aligned>  ( mat1_, 8UL, 16UL, 8UL, 16UL );
      USMT sm2 = submatrix<unaligned>( mat2_, 8UL, 16UL, 8UL, 16UL );
      AlignedColumnType   col1 = column( sm1, 1UL );
      UnalignedColumnType col2 = column( sm2, 1UL );

      if( col1 != col2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column function failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n" << col2 << "\n";
         throw std::runtime_error( oss.str() );
      }

      if( col1[1] != col2[1] ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator access failed\n"
             << " Details:\n"
             << "   Result: " << col1[1] << "\n"
             << "   Expected result: " << col2[1] << "\n";
         throw std::runtime_error( oss.str() );
      }

      if( *col1.begin() != *col2.begin() ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << *col1.begin() << "\n"
             << "   Expected result: " << *col2.begin() << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major column() function";

      initialize();

      typedef blaze::DenseColumn<AOSMT>  AlignedColumnType;
      typedef blaze::DenseColumn<UOSMT>  UnalignedColumnType;

      AOSMT sm1 = submatrix<aligned>  ( tmat1_, 16UL, 8UL, 16UL, 8UL );
      UOSMT sm2 = submatrix<unaligned>( tmat2_, 16UL, 8UL, 16UL, 8UL );
      AlignedColumnType   col1 = column( sm1, 1UL );
      UnalignedColumnType col2 = column( sm2, 1UL );

      if( col1 != col2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column function failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n" << col2 << "\n";
         throw std::runtime_error( oss.str() );
      }

      if( col1[1] != col2[1] ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator access failed\n"
             << " Details:\n"
             << "   Result: " << col1[1] << "\n"
             << "   Expected result: " << col2[1] << "\n";
         throw std::runtime_error( oss.str() );
      }

      if( *col1.begin() != *col2.begin() ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << *col1.begin() << "\n"
             << "   Expected result: " << *col2.begin() << "\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************




//=================================================================================================
//
//  UTILITY FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Initialization of all member matrices.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function initializes all member matrices to specific predetermined values.
*/
void AlignedTest::initialize()
{
   // Initializing the row-major dynamic matrices
   randomize( mat1_, int(randmin), int(randmax) );
   mat2_ = mat1_;

   // Initializing the column-major dynamic matrices
   randomize( tmat1_, int(randmin), int(randmax) );
   tmat2_ = tmat1_;
}
//*************************************************************************************************

} // namespace densesubmatrix

} // namespace mathtest

} // namespace blazetest




//=================================================================================================
//
//  MAIN FUNCTION
//
//=================================================================================================

//*************************************************************************************************
int main()
{
   std::cout << "   Running aligned DenseSubmatrix class test..." << std::endl;

   try
   {
      RUN_DENSESUBMATRIX_ALIGNED_TEST;
   }
   catch( std::exception& ex ) {
      std::cerr << "\n\n ERROR DETECTED during aligned DenseSubmatrix class test:\n"
                << ex.what() << "\n";
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
//*************************************************************************************************
