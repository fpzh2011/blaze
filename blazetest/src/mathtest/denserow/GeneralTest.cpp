//=================================================================================================
/*!
//  \file src/mathtest/denserow/GeneralTest.cpp
//  \brief Source file for the general DenseRow class test
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
#include <blaze/math/CompressedVector.h>
#include <blaze/math/CustomVector.h>
#include <blaze/math/DynamicVector.h>
#include <blaze/math/Views.h>
#include <blaze/util/policies/Deallocate.h>
#include <blaze/util/UniqueArray.h>
#include <blazetest/mathtest/denserow/GeneralTest.h>


namespace blazetest {

namespace mathtest {

namespace denserow {

//=================================================================================================
//
//  CONSTRUCTORS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Constructor for the general DenseRow class test.
//
// \exception std::runtime_error Operation error detected.
*/
GeneralTest::GeneralTest()
   : mat_ ( 5UL, 4UL )
   , tmat_( 5UL, 4UL )
{
   testConstructors();
   testAssignment();
   testAddAssign();
   testSubAssign();
   testMultAssign();
   testScaling();
   testSubscript();
   testIterator();
   testNonZeros();
   testReset();
   testClear();
   testIsDefault();
   testIsSame();
   testSubvector();
}
//*************************************************************************************************




//=================================================================================================
//
//  TEST FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Test of the DenseRow constructors.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of all constructors of the DenseRow class template.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void GeneralTest::testConstructors()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major DenseRow constructor";

      initialize();

      // 0th matrix row
      {
         RT row0 = row( mat_, 0UL );

         checkSize    ( row0, 4UL );
         checkCapacity( row0, 4UL );
         checkNonZeros( row0, 0UL );

         if( row0[0] != 0 || row0[1] != 0 || row0[2] != 0 || row0[3] != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Setup of 0th dense row failed\n"
                << " Details:\n"
                << "   Result:\n" << row0 << "\n"
                << "   Expected result:\n( 0 0 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // 1st matrix row
      {
         RT row1 = row( mat_, 1UL );

         checkSize    ( row1, 4UL );
         checkCapacity( row1, 4UL );
         checkNonZeros( row1, 1UL );

         if( row1[0] != 0 || row1[1] != 1 || row1[2] != 0 || row1[3] != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Setup of 1st dense row failed\n"
                << " Details:\n"
                << "   Result:\n" << row1 << "\n"
                << "   Expected result:\n( 0 1 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // 2nd matrix row
      {
         RT row2 = row( mat_, 2UL );

         checkSize    ( row2, 4UL );
         checkCapacity( row2, 4UL );
         checkNonZeros( row2, 2UL );

         if( row2[0] != -2 || row2[1] != 0 || row2[2] != -3 || row2[3] != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Setup of 2nd dense row failed\n"
                << " Details:\n"
                << "   Result:\n" << row2 << "\n"
                << "   Expected result:\n( -2 0 -3 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // 3rd matrix row
      {
         RT row3 = row( mat_, 3UL );

         checkSize    ( row3, 4UL );
         checkCapacity( row3, 4UL );
         checkNonZeros( row3, 3UL );

         if( row3[0] != 0 || row3[1] != 4 || row3[2] != 5 || row3[3] != -6 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Setup of 3rd dense row failed\n"
                << " Details:\n"
                << "   Result:\n" << row3 << "\n"
                << "   Expected result:\n( 0 4 5 -6 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // 4th matrix row
      {
         RT row4 = row( mat_, 4UL );

         checkSize    ( row4, 4UL );
         checkCapacity( row4, 4UL );
         checkNonZeros( row4, 4UL );

         if( row4[0] != 7 || row4[1] != -8 || row4[2] != 9 || row4[3] != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Setup of 4th dense row failed\n"
                << " Details:\n"
                << "   Result:\n" << row4 << "\n"
                << "   Expected result:\n( 7 -8 9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major DenseRow constructor";

      initialize();

      // 0th matrix row
      {
         ORT row0 = row( tmat_, 0UL );

         checkSize    ( row0, 4UL );
         checkCapacity( row0, 4UL );
         checkNonZeros( row0, 0UL );

         if( row0[0] != 0 || row0[1] != 0 || row0[2] != 0 || row0[3] != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Setup of 0th dense row failed\n"
                << " Details:\n"
                << "   Result:\n" << row0 << "\n"
                << "   Expected result:\n( 0 0 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // 1st matrix row
      {
         ORT row1 = row( tmat_, 1UL );

         checkSize    ( row1, 4UL );
         checkCapacity( row1, 4UL );
         checkNonZeros( row1, 1UL );

         if( row1[0] != 0 || row1[1] != 1 || row1[2] != 0 || row1[3] != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Setup of 1st dense row failed\n"
                << " Details:\n"
                << "   Result:\n" << row1 << "\n"
                << "   Expected result:\n( 0 1 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // 2nd matrix row
      {
         ORT row2 = row( tmat_, 2UL );

         checkSize    ( row2, 4UL );
         checkCapacity( row2, 4UL );
         checkNonZeros( row2, 2UL );

         if( row2[0] != -2 || row2[1] != 0 || row2[2] != -3 || row2[3] != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Setup of 2nd dense row failed\n"
                << " Details:\n"
                << "   Result:\n" << row2 << "\n"
                << "   Expected result:\n( -2 0 -3 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // 3rd matrix row
      {
         ORT row3 = row( tmat_, 3UL );

         checkSize    ( row3, 4UL );
         checkCapacity( row3, 4UL );
         checkNonZeros( row3, 3UL );

         if( row3[0] != 0 || row3[1] != 4 || row3[2] != 5 || row3[3] != -6 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Setup of 3rd dense row failed\n"
                << " Details:\n"
                << "   Result:\n" << row3 << "\n"
                << "   Expected result:\n( 0 4 5 -6 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // 4th matrix row
      {
         ORT row4 = row( tmat_, 4UL );

         checkSize    ( row4, 4UL );
         checkCapacity( row4, 4UL );
         checkNonZeros( row4, 4UL );

         if( row4[0] != 7 || row4[1] != -8 || row4[2] != 9 || row4[3] != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Setup of 4th dense row failed\n"
                << " Details:\n"
                << "   Result:\n" << row4 << "\n"
                << "   Expected result:\n( 7 -8 9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the DenseRow assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of all assignment operators of the DenseRow class template.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void GeneralTest::testAssignment()
{
   //=====================================================================================
   // Row-major homogeneous assignment
   //=====================================================================================

   {
      test_ = "Row-major DenseRow homogeneous assignment";

      initialize();

      RT row1 = row( mat_, 1UL );
      row1 = 8;

      checkSize    ( row1,  4UL );
      checkCapacity( row1,  4UL );
      checkNonZeros( row1,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 13UL );

      if( row1[0] != 8 || row1[1] != 8 || row1[2] != 8 || row1[3] != 8 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 8 8 8 8 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  8 || mat_(1,1) !=  8 || mat_(1,2) !=  8 || mat_(1,3) !=  8 ||
          mat_(2,0) != -2 || mat_(2,1) !=  0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  8  8  8  8 )\n"
                                     "( -2  0 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major copy assignment
   //=====================================================================================

   {
      test_ = "Row-major DenseRow copy assignment";

      initialize();

      RT row1 = row( mat_, 1UL );
      row1 = row( mat_, 2UL );

      checkSize    ( row1,  4UL );
      checkCapacity( row1,  4UL );
      checkNonZeros( row1,  2UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( row1[0] != -2 || row1[1] != 0 || row1[2] != -3 || row1[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( -2 0 -3 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) != -2 || mat_(1,1) !=  0 || mat_(1,2) != -3 || mat_(1,3) !=  0 ||
          mat_(2,0) != -2 || mat_(2,1) !=  0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "( -2  0 -3  0 )\n"
                                     "( -2  0 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major dense vector assignment
   //=====================================================================================

   {
      test_ = "Row-major dense vector assignment (aligned/padded)";

      using blaze::aligned;
      using blaze::padded;
      using blaze::rowVector;

      initialize();

      RT row1 = row( mat_, 1UL );

      typedef blaze::CustomVector<int,aligned,padded,rowVector>  AlignedPadded;
      AlignedPadded vec1( blaze::allocate<int>( 16UL ), 4UL, 16UL, blaze::Deallocate() );
      vec1[0] = 0;
      vec1[1] = 8;
      vec1[2] = 0;
      vec1[3] = 9;

      row1 = vec1;

      checkSize    ( row1,  4UL );
      checkCapacity( row1,  4UL );
      checkNonZeros( row1,  2UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( row1[0] != 0 || row1[1] != 8 || row1[2] != 0 || row1[3] != 9 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 0 8 0 9 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  8 || mat_(1,2) !=  0 || mat_(1,3) !=  9 ||
          mat_(2,0) != -2 || mat_(2,1) !=  0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  8  0  9 )\n"
                                     "( -2  0 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major dense vector assignment (unaligned/unpadded)";

      using blaze::unaligned;
      using blaze::unpadded;
      using blaze::rowVector;

      initialize();

      RT row1 = row( mat_, 1UL );

      typedef blaze::CustomVector<int,unaligned,unpadded,rowVector>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[5] );
      UnalignedUnpadded vec1( array.get()+1UL, 4UL );
      vec1[0] = 0;
      vec1[1] = 8;
      vec1[2] = 0;
      vec1[3] = 9;

      row1 = vec1;

      checkSize    ( row1,  4UL );
      checkCapacity( row1,  4UL );
      checkNonZeros( row1,  2UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( row1[0] != 0 || row1[1] != 8 || row1[2] != 0 || row1[3] != 9 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 0 8 0 9 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  8 || mat_(1,2) !=  0 || mat_(1,3) !=  9 ||
          mat_(2,0) != -2 || mat_(2,1) !=  0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  8  0  9 )\n"
                                     "( -2  0 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major sparse vector assignment
   //=====================================================================================

   {
      test_ = "Row-major sparse vector assignment";

      initialize();

      RT row4 = row( mat_, 4UL );

      blaze::CompressedVector<int,blaze::rowVector> vec1( 4UL );
      vec1[3] = 9;

      row4 = vec1;

      checkSize    ( row4, 4UL );
      checkCapacity( row4, 4UL );
      checkNonZeros( row4, 1UL );
      checkRows    ( mat_, 5UL );
      checkColumns ( mat_, 4UL );
      checkNonZeros( mat_, 7UL );

      if( row4[0] != 0 || row4[1] != 0 || row4[2] != 0 || row4[3] != 9 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row4 << "\n"
             << "   Expected result:\n( 0 0 0 9 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) != 0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) != 1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -2 || mat_(2,1) != 0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) != 4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  0 || mat_(4,1) != 0 || mat_(4,2) !=  0 || mat_(4,3) !=  9 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -2  0 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  0  0  0  9 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major homogeneous assignment
   //=====================================================================================

   {
      test_ = "Column-major DenseRow homogeneous assignment";

      initialize();

      ORT row1 = row( tmat_, 1UL );
      row1 = 8;

      checkSize    ( row1 ,  4UL );
      checkCapacity( row1 ,  4UL );
      checkNonZeros( row1 ,  4UL );
      checkRows    ( tmat_,  5UL );
      checkColumns ( tmat_,  4UL );
      checkNonZeros( tmat_, 13UL );

      if( row1[0] != 8 || row1[1] != 8 || row1[2] != 8 || row1[3] != 8 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 8 8 8 8 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) !=  0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  8 || tmat_(1,1) !=  8 || tmat_(1,2) !=  8 || tmat_(1,3) !=  8 ||
          tmat_(2,0) != -2 || tmat_(2,1) !=  0 || tmat_(2,2) != -3 || tmat_(2,3) !=  0 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  8  8  8  8 )\n"
                                     "( -2  0 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major copy assignment
   //=====================================================================================

   {
      test_ = "Column-major DenseRow copy assignment";

      initialize();

      ORT row1 = row( tmat_, 1UL );
      row1 = row( tmat_, 2UL );

      checkSize    ( row1 ,  4UL );
      checkCapacity( row1 ,  4UL );
      checkNonZeros( row1 ,  2UL );
      checkRows    ( tmat_,  5UL );
      checkColumns ( tmat_,  4UL );
      checkNonZeros( tmat_, 11UL );

      if( row1[0] != -2 || row1[1] != 0 || row1[2] != -3 || row1[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( -2 0 -3 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) !=  0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) != -2 || tmat_(1,1) !=  0 || tmat_(1,2) != -3 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -2 || tmat_(2,1) !=  0 || tmat_(2,2) != -3 || tmat_(2,3) !=  0 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "( -2  0 -3  0 )\n"
                                     "( -2  0 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense vector assignment
   //=====================================================================================

   {
      test_ = "Column-major dense vector assignment (aligned/padded)";

      using blaze::aligned;
      using blaze::padded;
      using blaze::rowVector;

      initialize();

      ORT row1 = row( tmat_, 1UL );

      typedef blaze::CustomVector<int,aligned,padded,rowVector>  AlignedPadded;
      AlignedPadded vec1( blaze::allocate<int>( 16UL ), 4UL, 16UL, blaze::Deallocate() );
      vec1[0] = 0;
      vec1[1] = 8;
      vec1[2] = 0;
      vec1[3] = 9;

      row1 = vec1;

      checkSize    ( row1 ,  4UL );
      checkCapacity( row1 ,  4UL );
      checkNonZeros( row1 ,  2UL );
      checkRows    ( tmat_,  5UL );
      checkColumns ( tmat_,  4UL );
      checkNonZeros( tmat_, 11UL );

      if( row1[0] != 0 || row1[1] != 8 || row1[2] != 0 || row1[3] != 9 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 0 8 0 9 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) !=  0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  8 || tmat_(1,2) !=  0 || tmat_(1,3) !=  9 ||
          tmat_(2,0) != -2 || tmat_(2,1) !=  0 || tmat_(2,2) != -3 || tmat_(2,3) !=  0 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  8  0  9 )\n"
                                     "( -2  0 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major dense vector assignment (unaligned/unpadded)";

      using blaze::unaligned;
      using blaze::unpadded;
      using blaze::rowVector;

      initialize();

      ORT row1 = row( tmat_, 1UL );

      typedef blaze::CustomVector<int,unaligned,unpadded,rowVector>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[5] );
      UnalignedUnpadded vec1( array.get()+1UL, 4UL );
      vec1[0] = 0;
      vec1[1] = 8;
      vec1[2] = 0;
      vec1[3] = 9;

      row1 = vec1;

      checkSize    ( row1 ,  4UL );
      checkCapacity( row1 ,  4UL );
      checkNonZeros( row1 ,  2UL );
      checkRows    ( tmat_,  5UL );
      checkColumns ( tmat_,  4UL );
      checkNonZeros( tmat_, 11UL );

      if( row1[0] != 0 || row1[1] != 8 || row1[2] != 0 || row1[3] != 9 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 0 8 0 9 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) !=  0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  8 || tmat_(1,2) !=  0 || tmat_(1,3) !=  9 ||
          tmat_(2,0) != -2 || tmat_(2,1) !=  0 || tmat_(2,2) != -3 || tmat_(2,3) !=  0 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  8  0  9 )\n"
                                     "( -2  0 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major sparse vector assignment
   //=====================================================================================

   {
      test_ = "Column-major sparse vector assignment";

      initialize();

      ORT row4 = row( tmat_, 4UL );

      blaze::CompressedVector<int,blaze::rowVector> vec1( 4UL );
      vec1[3] = 9;

      row4 = vec1;

      checkSize    ( row4 , 4UL );
      checkCapacity( row4 , 4UL );
      checkNonZeros( row4 , 1UL );
      checkRows    ( tmat_, 5UL );
      checkColumns ( tmat_, 4UL );
      checkNonZeros( tmat_, 7UL );

      if( row4[0] != 0 || row4[1] != 0 || row4[2] != 0 || row4[3] != 9 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row4 << "\n"
             << "   Expected result:\n( 0 0 0 9 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) != 0 || tmat_(0,2) !=  0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) != 1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -2 || tmat_(2,1) != 0 || tmat_(2,2) != -3 || tmat_(2,3) !=  0 ||
          tmat_(3,0) !=  0 || tmat_(3,1) != 4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  0 || tmat_(4,1) != 0 || tmat_(4,2) !=  0 || tmat_(4,3) !=  9 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -2  0 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  0  0  0  9 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the DenseRow addition assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the addition assignment operators of the DenseRow class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void GeneralTest::testAddAssign()
{
   //=====================================================================================
   // Row-major DenseRow addition assignment
   //=====================================================================================

   {
      test_ = "Row-major DenseRow addition assignment";

      initialize();

      RT row2 = row( mat_, 2UL );
      row2 += row( mat_, 3UL );

      checkSize    ( row2,  4UL );
      checkCapacity( row2,  4UL );
      checkNonZeros( row2,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 12UL );

      if( row2[0] != -2 || row2[1] != 4 || row2[2] != 2 || row2[3] != -6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -2 4 2 -6 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) != 0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) != 0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -2 || mat_(2,1) !=  4 || mat_(2,2) != 2 || mat_(2,3) != -6 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) != 5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) != 9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -2  4  2 -6 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major dense vector addition assignment
   //=====================================================================================

   {
      test_ = "Row-major dense vector addition assignment (aligned/padded)";

      using blaze::aligned;
      using blaze::padded;
      using blaze::rowVector;

      initialize();

      RT row2 = row( mat_, 2UL );

      typedef blaze::CustomVector<int,aligned,padded,rowVector>  AlignedPadded;
      AlignedPadded vec( blaze::allocate<int>( 16UL ), 4UL, 16UL, blaze::Deallocate() );
      vec[0] =  2;
      vec[1] = -4;
      vec[2] =  0;
      vec[3] =  0;

      row2 += vec;

      checkSize    ( row2,  4UL );
      checkCapacity( row2,  4UL );
      checkNonZeros( row2,  2UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );

      if( row2[0] != 0 || row2[1] != -4 || row2[2] != -3 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( 0 -4 -3 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) != 0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) != 0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 0 || mat_(2,1) != -4 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) != 0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) != 7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n( 0  0  0  0 )\n"
                                     "( 0  1  0  0 )\n"
                                     "( 0 -4 -3  0 )\n"
                                     "( 0  4  5 -6 )\n"
                                     "( 7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major dense vector addition assignment (unaligned/unpadded)";

      using blaze::unaligned;
      using blaze::unpadded;
      using blaze::rowVector;

      initialize();

      RT row2 = row( mat_, 2UL );

      typedef blaze::CustomVector<int,unaligned,unpadded,rowVector>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[5] );
      UnalignedUnpadded vec( array.get()+1UL, 4UL );
      vec[0] =  2;
      vec[1] = -4;
      vec[2] =  0;
      vec[3] =  0;

      row2 += vec;

      checkSize    ( row2,  4UL );
      checkCapacity( row2,  4UL );
      checkNonZeros( row2,  2UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );

      if( row2[0] != 0 || row2[1] != -4 || row2[2] != -3 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( 0 -4 -3 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) != 0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) != 0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 0 || mat_(2,1) != -4 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) != 0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) != 7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n( 0  0  0  0 )\n"
                                     "( 0  1  0  0 )\n"
                                     "( 0 -4 -3  0 )\n"
                                     "( 0  4  5 -6 )\n"
                                     "( 7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major sparse vector addition assignment
   //=====================================================================================

   {
      test_ = "Row-major sparse vector addition assignment";

      initialize();

      RT row2 = row( mat_, 2UL );

      blaze::CompressedVector<int,blaze::rowVector> vec( 4UL );
      vec[0] =  2;
      vec[1] = -4;

      row2 += vec;

      checkSize    ( row2,  4UL );
      checkCapacity( row2,  4UL );
      checkNonZeros( row2,  2UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );

      if( row2[0] != 0 || row2[1] != -4 || row2[2] != -3 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( 0 -4 -3 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) != 0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) != 0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 0 || mat_(2,1) != -4 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) != 0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) != 7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n( 0  0  0  0 )\n"
                                     "( 0  1  0  0 )\n"
                                     "( 0 -4 -3  0 )\n"
                                     "( 0  4  5 -6 )\n"
                                     "( 7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major DenseRow addition assignment
   //=====================================================================================

   {
      test_ = "Column-major DenseRow addition assignment";

      initialize();

      ORT row2 = row( tmat_, 2UL );
      row2 += row( tmat_, 3UL );

      checkSize    ( row2 ,  4UL );
      checkCapacity( row2 ,  4UL );
      checkNonZeros( row2 ,  4UL );
      checkRows    ( tmat_,  5UL );
      checkColumns ( tmat_,  4UL );
      checkNonZeros( tmat_, 12UL );

      if( row2[0] != -2 || row2[1] != 4 || row2[2] != 2 || row2[3] != -6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -2 4 2 -6 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) != 0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) != 0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -2 || tmat_(2,1) !=  4 || tmat_(2,2) != 2 || tmat_(2,3) != -6 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) != 5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) != 9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -2  4  2 -6 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense vector addition assignment
   //=====================================================================================

   {
      test_ = "Column-major dense vector addition assignment (aligned/padded)";

      using blaze::aligned;
      using blaze::padded;
      using blaze::rowVector;

      initialize();

      ORT row2 = row( tmat_, 2UL );

      typedef blaze::CustomVector<int,aligned,padded,rowVector>  AlignedPadded;
      AlignedPadded vec( blaze::allocate<int>( 16UL ), 4UL, 16UL, blaze::Deallocate() );
      vec[0] =  2;
      vec[1] = -4;
      vec[2] =  0;
      vec[3] =  0;

      row2 += vec;

      checkSize    ( row2 ,  4UL );
      checkCapacity( row2 ,  4UL );
      checkNonZeros( row2 ,  2UL );
      checkRows    ( tmat_,  5UL );
      checkColumns ( tmat_,  4UL );
      checkNonZeros( tmat_, 10UL );

      if( row2[0] != 0 || row2[1] != -4 || row2[2] != -3 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( 0 -4 -3 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) !=  0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) != 0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != 0 || tmat_(2,1) != -4 || tmat_(2,2) != -3 || tmat_(2,3) !=  0 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
          tmat_(4,0) != 7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0  0  0 )\n"
                                     "( 0  1  0  0 )\n"
                                     "( 0 -4 -3  0 )\n"
                                     "( 0  4  5 -6 )\n"
                                     "( 7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major dense vector addition assignment (unaligned/unpadded)";

      using blaze::unaligned;
      using blaze::unpadded;
      using blaze::rowVector;

      initialize();

      ORT row2 = row( tmat_, 2UL );

      typedef blaze::CustomVector<int,unaligned,unpadded,rowVector>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[5] );
      UnalignedUnpadded vec( array.get()+1UL, 4UL );
      vec[0] =  2;
      vec[1] = -4;
      vec[2] =  0;
      vec[3] =  0;

      row2 += vec;

      checkSize    ( row2 ,  4UL );
      checkCapacity( row2 ,  4UL );
      checkNonZeros( row2 ,  2UL );
      checkRows    ( tmat_,  5UL );
      checkColumns ( tmat_,  4UL );
      checkNonZeros( tmat_, 10UL );

      if( row2[0] != 0 || row2[1] != -4 || row2[2] != -3 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( 0 -4 -3 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) !=  0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) != 0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != 0 || tmat_(2,1) != -4 || tmat_(2,2) != -3 || tmat_(2,3) !=  0 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
          tmat_(4,0) != 7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0  0  0 )\n"
                                     "( 0  1  0  0 )\n"
                                     "( 0 -4 -3  0 )\n"
                                     "( 0  4  5 -6 )\n"
                                     "( 7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major sparse vector addition assignment
   //=====================================================================================

   {
      test_ = "Column-major sparse vector addition assignment";

      initialize();

      ORT row2 = row( tmat_, 2UL );

      blaze::CompressedVector<int,blaze::rowVector> vec( 4UL );
      vec[0] =  2;
      vec[1] = -4;

      row2 += vec;

      checkSize    ( row2 ,  4UL );
      checkCapacity( row2 ,  4UL );
      checkNonZeros( row2 ,  2UL );
      checkRows    ( tmat_,  5UL );
      checkColumns ( tmat_,  4UL );
      checkNonZeros( tmat_, 10UL );

      if( row2[0] != 0 || row2[1] != -4 || row2[2] != -3 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( 0 -4 -3 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) !=  0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) != 0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != 0 || tmat_(2,1) != -4 || tmat_(2,2) != -3 || tmat_(2,3) !=  0 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
          tmat_(4,0) != 7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0  0  0 )\n"
                                     "( 0  1  0  0 )\n"
                                     "( 0 -4 -3  0 )\n"
                                     "( 0  4  5 -6 )\n"
                                     "( 7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the DenseRow subtraction assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the subtraction assignment operators of the DenseRow class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void GeneralTest::testSubAssign()
{
   //=====================================================================================
   // Row-major DenseRow subtraction assignment
   //=====================================================================================

   {
      test_ = "Row-major DenseRow subtraction assignment";

      initialize();

      RT row2 = row( mat_, 2UL );
      row2 -= row( mat_, 3UL );

      checkSize    ( row2,  4UL );
      checkCapacity( row2,  4UL );
      checkNonZeros( row2,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 12UL );

      if( row2[0] != -2 || row2[1] != -4 || row2[2] != -8 || row2[3] != 6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -2 -4 -8 6 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -2 || mat_(2,1) != -4 || mat_(2,2) != -8 || mat_(2,3) !=  6 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -2 -4 -8  6 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major dense vector subtraction assignment
   //=====================================================================================

   {
      test_ = "Row-major dense vector subtraction assignment (aligned/padded)";

      using blaze::aligned;
      using blaze::padded;
      using blaze::rowVector;

      initialize();

      RT row2 = row( mat_, 2UL );

      typedef blaze::CustomVector<int,aligned,padded,rowVector>  AlignedPadded;
      AlignedPadded vec( blaze::allocate<int>( 16UL ), 4UL, 16UL, blaze::Deallocate() );
      vec[0] =  2;
      vec[1] = -4;
      vec[2] =  0;
      vec[3] =  0;

      row2 -= vec;

      checkSize    ( row2,  4UL );
      checkCapacity( row2,  4UL );
      checkNonZeros( row2,  3UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( row2[0] != -4 || row2[1] != 4 || row2[2] != -3 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -4 4 -3 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -4 || mat_(2,1) !=  4 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -4  4 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major dense vector subtraction assignment (unaligned/unpadded)";

      using blaze::unaligned;
      using blaze::unpadded;
      using blaze::rowVector;

      initialize();

      RT row2 = row( mat_, 2UL );

      typedef blaze::CustomVector<int,unaligned,unpadded,rowVector>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[5] );
      UnalignedUnpadded vec( array.get()+1UL, 4UL );
      vec[0] =  2;
      vec[1] = -4;
      vec[2] =  0;
      vec[3] =  0;

      row2 -= vec;

      checkSize    ( row2,  4UL );
      checkCapacity( row2,  4UL );
      checkNonZeros( row2,  3UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( row2[0] != -4 || row2[1] != 4 || row2[2] != -3 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -4 4 -3 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -4 || mat_(2,1) !=  4 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -4  4 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major sparse vector subtraction assignment
   //=====================================================================================

   {
      test_ = "Row-major sparse vector subtraction assignment";

      initialize();

      RT row2 = row( mat_, 2UL );

      blaze::CompressedVector<int,blaze::rowVector> vec( 4UL );
      vec[0] =  2;
      vec[1] = -4;

      row2 -= vec;

      checkSize    ( row2,  4UL );
      checkCapacity( row2,  4UL );
      checkNonZeros( row2,  3UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( row2[0] != -4 || row2[1] != 4 || row2[2] != -3 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -4 4 -3 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -4 || mat_(2,1) !=  4 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -4  4 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major DenseRow subtraction assignment
   //=====================================================================================

   {
      test_ = "Column-major DenseRow subtraction assignment";

      initialize();

      ORT row2 = row( tmat_, 2UL );
      row2 -= row( tmat_, 3UL );

      checkSize    ( row2 ,  4UL );
      checkCapacity( row2 ,  4UL );
      checkNonZeros( row2 ,  4UL );
      checkRows    ( tmat_,  5UL );
      checkColumns ( tmat_,  4UL );
      checkNonZeros( tmat_, 12UL );

      if( row2[0] != -2 || row2[1] != -4 || row2[2] != -8 || row2[3] != 6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -2 -4 -8 6 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) !=  0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -2 || tmat_(2,1) != -4 || tmat_(2,2) != -8 || tmat_(2,3) !=  6 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -2 -4 -8  6 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense vector subtraction assignment
   //=====================================================================================

   {
      test_ = "Column-major dense vector subtraction assignment (aligned/padded)";

      using blaze::aligned;
      using blaze::padded;
      using blaze::rowVector;

      initialize();

      ORT row2 = row( tmat_, 2UL );

      typedef blaze::CustomVector<int,aligned,padded,rowVector>  AlignedPadded;
      AlignedPadded vec( blaze::allocate<int>( 16UL ), 4UL, 16UL, blaze::Deallocate() );
      vec[0] =  2;
      vec[1] = -4;
      vec[2] =  0;
      vec[3] =  0;

      row2 -= vec;

      checkSize    ( row2 ,  4UL );
      checkCapacity( row2 ,  4UL );
      checkNonZeros( row2 ,  3UL );
      checkRows    ( tmat_,  5UL );
      checkColumns ( tmat_,  4UL );
      checkNonZeros( tmat_, 11UL );

      if( row2[0] != -4 || row2[1] != 4 || row2[2] != -3 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -4 4 -3 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) !=  0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -4 || tmat_(2,1) !=  4 || tmat_(2,2) != -3 || tmat_(2,3) !=  0 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -4  4 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major dense vector subtraction assignment (unaligned/unpadded)";

      using blaze::unaligned;
      using blaze::unpadded;
      using blaze::rowVector;

      initialize();

      ORT row2 = row( tmat_, 2UL );

      typedef blaze::CustomVector<int,unaligned,unpadded,rowVector>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[5] );
      UnalignedUnpadded vec( array.get()+1UL, 4UL );
      vec[0] =  2;
      vec[1] = -4;
      vec[2] =  0;
      vec[3] =  0;

      row2 -= vec;

      checkSize    ( row2 ,  4UL );
      checkCapacity( row2 ,  4UL );
      checkNonZeros( row2 ,  3UL );
      checkRows    ( tmat_,  5UL );
      checkColumns ( tmat_,  4UL );
      checkNonZeros( tmat_, 11UL );

      if( row2[0] != -4 || row2[1] != 4 || row2[2] != -3 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -4 4 -3 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) !=  0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -4 || tmat_(2,1) !=  4 || tmat_(2,2) != -3 || tmat_(2,3) !=  0 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -4  4 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major sparse vector subtraction assignment
   //=====================================================================================

   {
      test_ = "Column-major sparse vector subtraction assignment";

      initialize();

      ORT row2 = row( tmat_, 2UL );

      blaze::CompressedVector<int,blaze::rowVector> vec( 4UL );
      vec[0] =  2;
      vec[1] = -4;

      row2 -= vec;

      checkSize    ( row2 ,  4UL );
      checkCapacity( row2 ,  4UL );
      checkNonZeros( row2 ,  3UL );
      checkRows    ( tmat_,  5UL );
      checkColumns ( tmat_,  4UL );
      checkNonZeros( tmat_, 11UL );

      if( row2[0] != -4 || row2[1] != 4 || row2[2] != -3 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -4 4 -3 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) !=  0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -4 || tmat_(2,1) !=  4 || tmat_(2,2) != -3 || tmat_(2,3) !=  0 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -4  4 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the DenseRow multiplication assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the multiplication assignment operators of the DenseRow class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void GeneralTest::testMultAssign()
{
   //=====================================================================================
   // Row-major DenseRow multiplication assignment
   //=====================================================================================

   {
      test_ = "Row-major DenseRow multiplication assignment";

      initialize();

      RT row2 = row( mat_, 2UL );
      row2 *= row( mat_, 3UL );

      checkSize    ( row2, 4UL );
      checkCapacity( row2, 4UL );
      checkNonZeros( row2, 1UL );
      checkRows    ( mat_, 5UL );
      checkColumns ( mat_, 4UL );
      checkNonZeros( mat_, 9UL );

      if( row2[0] != 0 || row2[1] != 0 || row2[2] != -15 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( 0 0 -15 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) != 0 || mat_(0,1) !=  0 || mat_(0,2) !=   0 || mat_(0,3) !=  0 ||
          mat_(1,0) != 0 || mat_(1,1) !=  1 || mat_(1,2) !=   0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 0 || mat_(2,1) !=  0 || mat_(2,2) != -15 || mat_(2,3) !=  0 ||
          mat_(3,0) != 0 || mat_(3,1) !=  4 || mat_(3,2) !=   5 || mat_(3,3) != -6 ||
          mat_(4,0) != 7 || mat_(4,1) != -8 || mat_(4,2) !=   9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0   0  0 )\n"
                                     "(  0  1   0  0 )\n"
                                     "(  0  0 -15  0 )\n"
                                     "(  0  4   5 -6 )\n"
                                     "(  7 -8   9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major dense vector multiplication assignment
   //=====================================================================================

   {
      test_ = "Row-major dense vector multiplication assignment (aligned/padded)";

      using blaze::aligned;
      using blaze::padded;
      using blaze::rowVector;

      initialize();

      RT row2 = row( mat_, 2UL );

      typedef blaze::CustomVector<int,aligned,padded,rowVector>  AlignedPadded;
      AlignedPadded vec( blaze::allocate<int>( 16UL ), 4UL, 16UL, blaze::Deallocate() );
      vec[0] =  2;
      vec[1] = -4;
      vec[2] =  0;
      vec[3] =  0;

      row2 *= vec;

      checkSize    ( row2, 4UL );
      checkCapacity( row2, 4UL );
      checkNonZeros( row2, 1UL );
      checkRows    ( mat_, 5UL );
      checkColumns ( mat_, 4UL );
      checkNonZeros( mat_, 9UL );

      if( row2[0] != -4 || row2[1] != 0 || row2[2] != 0 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -4 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) != 0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) != 0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -4 || mat_(2,1) !=  0 || mat_(2,2) != 0 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) != 5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) != 9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -4  0  0  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major dense vector multiplication assignment (unaligned/unpadded)";

      using blaze::unaligned;
      using blaze::unpadded;
      using blaze::rowVector;

      initialize();

      RT row2 = row( mat_, 2UL );

      typedef blaze::CustomVector<int,unaligned,unpadded,rowVector>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[5] );
      UnalignedUnpadded vec( array.get()+1UL, 4UL );
      vec[0] =  2;
      vec[1] = -4;
      vec[2] =  0;
      vec[3] =  0;

      row2 *= vec;

      checkSize    ( row2, 4UL );
      checkCapacity( row2, 4UL );
      checkNonZeros( row2, 1UL );
      checkRows    ( mat_, 5UL );
      checkColumns ( mat_, 4UL );
      checkNonZeros( mat_, 9UL );

      if( row2[0] != -4 || row2[1] != 0 || row2[2] != 0 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -4 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) != 0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) != 0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -4 || mat_(2,1) !=  0 || mat_(2,2) != 0 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) != 5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) != 9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -4  0  0  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major sparse vector multiplication assignment
   //=====================================================================================

   {
      test_ = "Row-major sparse vector multiplication assignment";

      initialize();

      RT row2 = row( mat_, 2UL );

      blaze::CompressedVector<int,blaze::rowVector> vec( 4UL );
      vec[0] =  2;
      vec[1] = -4;

      row2 *= vec;

      checkSize    ( row2, 4UL );
      checkCapacity( row2, 4UL );
      checkNonZeros( row2, 1UL );
      checkRows    ( mat_, 5UL );
      checkColumns ( mat_, 4UL );
      checkNonZeros( mat_, 9UL );

      if( row2[0] != -4 || row2[1] != 0 || row2[2] != 0 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -4 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) != 0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) != 0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -4 || mat_(2,1) !=  0 || mat_(2,2) != 0 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) != 5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) != 9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -4  0  0  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major DenseRow multiplication assignment
   //=====================================================================================

   {
      test_ = "Column-major DenseRow multiplication assignment";

      initialize();

      ORT row2 = row( tmat_, 2UL );
      row2 *= row( tmat_, 3UL );

      checkSize    ( row2 , 4UL );
      checkCapacity( row2 , 4UL );
      checkNonZeros( row2 , 1UL );
      checkRows    ( tmat_, 5UL );
      checkColumns ( tmat_, 4UL );
      checkNonZeros( tmat_, 9UL );

      if( row2[0] != 0 || row2[1] != 0 || row2[2] != -15 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( 0 0 -15 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) !=   0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) != 0 || tmat_(1,1) !=  1 || tmat_(1,2) !=   0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != -15 || tmat_(2,3) !=  0 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  4 || tmat_(3,2) !=   5 || tmat_(3,3) != -6 ||
          tmat_(4,0) != 7 || tmat_(4,1) != -8 || tmat_(4,2) !=   9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0   0  0 )\n"
                                     "(  0  1   0  0 )\n"
                                     "(  0  0 -15  0 )\n"
                                     "(  0  4   5 -6 )\n"
                                     "(  7 -8   9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense vector multiplication assignment
   //=====================================================================================

   {
      test_ = "Column-major dense vector multiplication assignment (aligned/padded)";

      using blaze::aligned;
      using blaze::padded;
      using blaze::rowVector;

      initialize();

      ORT row2 = row( tmat_, 2UL );

      typedef blaze::CustomVector<int,aligned,padded,rowVector>  AlignedPadded;
      AlignedPadded vec( blaze::allocate<int>( 16UL ), 4UL, 16UL, blaze::Deallocate() );
      vec[0] =  2;
      vec[1] = -4;
      vec[2] =  0;
      vec[3] =  0;

      row2 *= vec;

      checkSize    ( row2 , 4UL );
      checkCapacity( row2 , 4UL );
      checkNonZeros( row2 , 1UL );
      checkRows    ( tmat_, 5UL );
      checkColumns ( tmat_, 4UL );
      checkNonZeros( tmat_, 9UL );

      if( row2[0] != -4 || row2[1] != 0 || row2[2] != 0 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -4 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) != 0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) != 0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -4 || tmat_(2,1) !=  0 || tmat_(2,2) != 0 || tmat_(2,3) !=  0 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) != 5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) != 9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -4  0  0  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major dense vector multiplication assignment (unaligned/unpadded)";

      using blaze::unaligned;
      using blaze::unpadded;
      using blaze::rowVector;

      initialize();

      ORT row2 = row( tmat_, 2UL );

      typedef blaze::CustomVector<int,unaligned,unpadded,rowVector>  UnalignedUnpadded;
      blaze::UniqueArray<int> array( new int[5] );
      UnalignedUnpadded vec( array.get()+1UL, 4UL );
      vec[0] =  2;
      vec[1] = -4;
      vec[2] =  0;
      vec[3] =  0;

      row2 *= vec;

      checkSize    ( row2 , 4UL );
      checkCapacity( row2 , 4UL );
      checkNonZeros( row2 , 1UL );
      checkRows    ( tmat_, 5UL );
      checkColumns ( tmat_, 4UL );
      checkNonZeros( tmat_, 9UL );

      if( row2[0] != -4 || row2[1] != 0 || row2[2] != 0 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -4 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) != 0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) != 0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -4 || tmat_(2,1) !=  0 || tmat_(2,2) != 0 || tmat_(2,3) !=  0 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) != 5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) != 9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -4  0  0  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major sparse vector multiplication assignment
   //=====================================================================================

   {
      test_ = "Column-major sparse vector multiplication assignment";

      initialize();

      ORT row2 = row( tmat_, 2UL );

      blaze::CompressedVector<int,blaze::rowVector> vec( 4UL );
      vec[0] =  2;
      vec[1] = -4;

      row2 *= vec;

      checkSize    ( row2 , 4UL );
      checkCapacity( row2 , 4UL );
      checkNonZeros( row2 , 1UL );
      checkRows    ( tmat_, 5UL );
      checkColumns ( tmat_, 4UL );
      checkNonZeros( tmat_, 9UL );

      if( row2[0] != -4 || row2[1] != 0 || row2[2] != 0 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -4 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) != 0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) != 0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -4 || tmat_(2,1) !=  0 || tmat_(2,2) != 0 || tmat_(2,3) !=  0 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) != 5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) != 9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -4  0  0  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of all DenseRow (self-)scaling operations.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of all available ways to scale an instance of the DenseRow
// class template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void GeneralTest::testScaling()
{
   //=====================================================================================
   // Row-major self-scaling (v*=2)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (v*=2)";

      initialize();

      RT row2 = row( mat_, 2UL );

      row2 *= 3;

      checkSize    ( row2,  4UL );
      checkCapacity( row2,  4UL );
      checkNonZeros( row2,  2UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );

      if( row2[0] != -6 || row2[1] != 0 || row2[2] != -9 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -6 0 -9 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -6 || mat_(2,1) !=  0 || mat_(2,2) != -9 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -6  0 -9  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major self-scaling (v=v*2)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (v=v*2)";

      initialize();

      RT row2 = row( mat_, 2UL );

      row2 = row2 * 3;

      checkSize    ( row2,  4UL );
      checkCapacity( row2,  4UL );
      checkNonZeros( row2,  2UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );

      if( row2[0] != -6 || row2[1] != 0 || row2[2] != -9 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -6 0 -9 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -6 || mat_(2,1) !=  0 || mat_(2,2) != -9 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -6  0 -9  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major self-scaling (v=2*v)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (v=2*v)";

      initialize();

      RT row2 = row( mat_, 2UL );

      row2 = 3 * row2;

      checkSize    ( row2,  4UL );
      checkCapacity( row2,  4UL );
      checkNonZeros( row2,  2UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );

      if( row2[0] != -6 || row2[1] != 0 || row2[2] != -9 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -6 0 -9 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -6 || mat_(2,1) !=  0 || mat_(2,2) != -9 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -6  0 -9  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major self-scaling (v/=s)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (v/=s)";

      initialize();

      RT row2 = row( mat_, 2UL );

      row2 /= 0.5;

      checkSize    ( row2,  4UL );
      checkCapacity( row2,  4UL );
      checkNonZeros( row2,  2UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );

      if( row2[0] != -4 || row2[1] != 0 || row2[2] != -6 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -4 0 -6 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -4 || mat_(2,1) !=  0 || mat_(2,2) != -6 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -4  0 -6  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major self-scaling (v=v/s)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (v=v/s)";

      initialize();

      RT row2 = row( mat_, 2UL );

      row2 = row2 / 0.5;

      checkSize    ( row2,  4UL );
      checkCapacity( row2,  4UL );
      checkNonZeros( row2,  2UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );

      if( row2[0] != -4 || row2[1] != 0 || row2[2] != -6 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -4 0 -6 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -4 || mat_(2,1) !=  0 || mat_(2,2) != -6 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -4  0 -6  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major DenseRow::scale()
   //=====================================================================================

   {
      test_ = "Row-major DenseRow::scale()";

      initialize();

      // Integral scaling the 3rd row
      {
         RT row3 = row( mat_, 3UL );
         row3.scale( 3 );

         checkSize    ( row3,  4UL );
         checkCapacity( row3,  4UL );
         checkNonZeros( row3,  3UL );
         checkRows    ( mat_,  5UL );
         checkColumns ( mat_,  4UL );
         checkNonZeros( mat_, 10UL );

         if( row3[0] != 0 || row3[1] != 12 || row3[2] != 15 || row3[3] != -18 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Integral scale operation of 3rd row failed\n"
                << " Details:\n"
                << "   Result:\n" << row3 << "\n"
                << "   Expected result:\n( 0 12 15 -18 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=   0 ||
             mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=   0 ||
             mat_(2,0) != -2 || mat_(2,1) !=  0 || mat_(2,2) != -3 || mat_(2,3) !=   0 ||
             mat_(3,0) !=  0 || mat_(3,1) != 12 || mat_(3,2) != 15 || mat_(3,3) != -18 ||
             mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) !=  10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Integral scale operation of 3rd row failed\n"
                << " Details:\n"
                << "   Result:\n" << mat_ << "\n"
                << "   Expected result:\n(  0   0   0   0 )\n"
                                        "(  0   1   0   0 )\n"
                                        "( -2   0  -3   0 )\n"
                                        "(  0  12  15 -18 )\n"
                                        "(  7  -8   9  10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Floating point scaling the 3rd row
      {
         RT row3 = row( mat_, 3UL );
         row3.scale( 0.5 );

         checkSize    ( row3,  4UL );
         checkCapacity( row3,  4UL );
         checkNonZeros( row3,  3UL );
         checkRows    ( mat_,  5UL );
         checkColumns ( mat_,  4UL );
         checkNonZeros( mat_, 10UL );

         if( row3[0] != 0 || row3[1] != 6 || row3[2] != 7 || row3[3] != -9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Floating point scale operation of 3rd row failed\n"
                << " Details:\n"
                << "   Result:\n" << row3 << "\n"
                << "   Expected result:\n( 0 6 7 -9 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
             mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
             mat_(2,0) != -2 || mat_(2,1) !=  0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
             mat_(3,0) !=  0 || mat_(3,1) !=  6 || mat_(3,2) !=  7 || mat_(3,3) != -9 ||
             mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Floating point scale operation of 3rd row failed\n"
                << " Details:\n"
                << "   Result:\n" << mat_ << "\n"
                << "   Expected result:\n(  0   0   0   0 )\n"
                                        "(  0   1   0   0 )\n"
                                        "( -2   0  -3   0 )\n"
                                        "(  0   6   7  -9 )\n"
                                        "(  7  -8   9  10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major self-scaling (v*=s)
   //=====================================================================================

   {
      test_ = "Column-major self-scaling (v*=s)";

      initialize();

      ORT row2 = row( tmat_, 2UL );

      row2 *= 3;

      checkSize    ( row2 ,  4UL );
      checkCapacity( row2 ,  4UL );
      checkNonZeros( row2 ,  2UL );
      checkRows    ( tmat_,  5UL );
      checkColumns ( tmat_,  4UL );
      checkNonZeros( tmat_, 10UL );

      if( row2[0] != -6 || row2[1] != 0 || row2[2] != -9 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -6 0 -9 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) !=  0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -6 || tmat_(2,1) !=  0 || tmat_(2,2) != -9 || tmat_(2,3) !=  0 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -6  0 -9  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (v=v*s)
   //=====================================================================================

   {
      test_ = "Column-major self-scaling (v=v*s)";

      initialize();

      ORT row2 = row( tmat_, 2UL );

      row2 = row2 * 3;

      checkSize    ( row2 ,  4UL );
      checkCapacity( row2 ,  4UL );
      checkNonZeros( row2 ,  2UL );
      checkRows    ( tmat_,  5UL );
      checkColumns ( tmat_,  4UL );
      checkNonZeros( tmat_, 10UL );

      if( row2[0] != -6 || row2[1] != 0 || row2[2] != -9 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -6 0 -9 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) !=  0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -6 || tmat_(2,1) !=  0 || tmat_(2,2) != -9 || tmat_(2,3) !=  0 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -6  0 -9  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (v=s*v)
   //=====================================================================================

   {
      test_ = "Column-major self-scaling (v=s*v)";

      initialize();

      ORT row2 = row( tmat_, 2UL );

      row2 = 3 * row2;

      checkSize    ( row2 ,  4UL );
      checkCapacity( row2 ,  4UL );
      checkNonZeros( row2 ,  2UL );
      checkRows    ( tmat_,  5UL );
      checkColumns ( tmat_,  4UL );
      checkNonZeros( tmat_, 10UL );

      if( row2[0] != -6 || row2[1] != 0 || row2[2] != -9 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -6 0 -9 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) !=  0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -6 || tmat_(2,1) !=  0 || tmat_(2,2) != -9 || tmat_(2,3) !=  0 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -6  0 -9  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (v/=s)
   //=====================================================================================

   {
      test_ = "Column-major self-scaling (v/=s)";

      initialize();

      ORT row2 = row( tmat_, 2UL );

      row2 /= 0.5;

      checkSize    ( row2 ,  4UL );
      checkCapacity( row2 ,  4UL );
      checkNonZeros( row2 ,  2UL );
      checkRows    ( tmat_,  5UL );
      checkColumns ( tmat_,  4UL );
      checkNonZeros( tmat_, 10UL );

      if( row2[0] != -4 || row2[1] != 0 || row2[2] != -6 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -4 0 -6 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) !=  0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -4 || tmat_(2,1) !=  0 || tmat_(2,2) != -6 || tmat_(2,3) !=  0 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -4  0 -6  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (v=v/s)
   //=====================================================================================

   {
      test_ = "Column-major self-scaling (v=v/s)";

      initialize();

      ORT row2 = row( tmat_, 2UL );

      row2 = row2 / 0.5;

      checkSize    ( row2 ,  4UL );
      checkCapacity( row2 ,  4UL );
      checkNonZeros( row2 ,  2UL );
      checkRows    ( tmat_,  5UL );
      checkColumns ( tmat_,  4UL );
      checkNonZeros( tmat_, 10UL );

      if( row2[0] != -4 || row2[1] != 0 || row2[2] != -6 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -4 0 -6 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) !=  0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -4 || tmat_(2,1) !=  0 || tmat_(2,2) != -6 || tmat_(2,3) !=  0 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -4  0 -6  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major DenseRow::scale()
   //=====================================================================================

   {
      test_ = "Column-major DenseRow::scale()";

      initialize();

      // Integral scaling the 3rd row
      {
         ORT row3 = row( tmat_, 3UL );
         row3.scale( 3 );

         checkSize    ( row3 ,  4UL );
         checkCapacity( row3 ,  4UL );
         checkNonZeros( row3 ,  3UL );
         checkRows    ( tmat_,  5UL );
         checkColumns ( tmat_,  4UL );
         checkNonZeros( tmat_, 10UL );

         if( row3[0] != 0 || row3[1] != 12 || row3[2] != 15 || row3[3] != -18 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Integral scale operation of 3rd row failed\n"
                << " Details:\n"
                << "   Result:\n" << row3 << "\n"
                << "   Expected result:\n( 0 12 15 -18 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) !=  0 || tmat_(0,3) !=   0 ||
             tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=   0 ||
             tmat_(2,0) != -2 || tmat_(2,1) !=  0 || tmat_(2,2) != -3 || tmat_(2,3) !=   0 ||
             tmat_(3,0) !=  0 || tmat_(3,1) != 12 || tmat_(3,2) != 15 || tmat_(3,3) != -18 ||
             tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) !=  10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Integral scale operation of 3rd row failed\n"
                << " Details:\n"
                << "   Result:\n" << tmat_ << "\n"
                << "   Expected result:\n(  0   0   0   0 )\n"
                                        "(  0   1   0   0 )\n"
                                        "( -2   0  -3   0 )\n"
                                        "(  0  12  15 -18 )\n"
                                        "(  7  -8   9  10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Floating point scaling the 3rd row
      {
         ORT row3 = row( tmat_, 3UL );
         row3.scale( 0.5 );

         checkSize    ( row3 ,  4UL );
         checkCapacity( row3 ,  4UL );
         checkNonZeros( row3 ,  3UL );
         checkRows    ( tmat_,  5UL );
         checkColumns ( tmat_,  4UL );
         checkNonZeros( tmat_, 10UL );

         if( row3[0] != 0 || row3[1] != 6 || row3[2] != 7 || row3[3] != -9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Floating point scale operation of 3rd row failed\n"
                << " Details:\n"
                << "   Result:\n" << row3 << "\n"
                << "   Expected result:\n( 0 6 7 -9 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) !=  0 || tmat_(0,3) !=  0 ||
             tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  0 ||
             tmat_(2,0) != -2 || tmat_(2,1) !=  0 || tmat_(2,2) != -3 || tmat_(2,3) !=  0 ||
             tmat_(3,0) !=  0 || tmat_(3,1) !=  6 || tmat_(3,2) !=  7 || tmat_(3,3) != -9 ||
             tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Integral scale operation of 3rd row failed\n"
                << " Details:\n"
                << "   Result:\n" << tmat_ << "\n"
                << "   Expected result:\n(  0   0   0   0 )\n"
                                        "(  0   1   0   0 )\n"
                                        "( -2   0  -3   0 )\n"
                                        "(  0   6   7  -9 )\n"
                                        "(  7  -8   9  10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the DenseRow subscript operator.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of adding and accessing elements via the subscript operator
// of the DenseRow class template. In case an error is detected, a \a std::runtime_error
// exception is thrown.
*/
void GeneralTest::testSubscript()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major DenseRow::operator[]";

      initialize();

      RT row2 = row( mat_, 2UL );

      // Assignment to the element at index 1
      row2[1] = 9;

      checkSize    ( row2, 4UL );
      checkCapacity( row2, 4UL );
      checkNonZeros( row2, 3UL );

      if( row2[0] != -2 || row2[1] != 9 || row2[2] != -3 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -2 9 -3 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -2 || mat_(2,1) !=  9 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -2  9 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Assignment to the element at index 2
      row2[2] = 0;

      checkSize    ( row2, 4UL );
      checkCapacity( row2, 4UL );
      checkNonZeros( row2, 2UL );

      if( row2[0] != -2 || row2[1] != 9 || row2[2] != 0 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -2 9 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) != 0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) != 0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -2 || mat_(2,1) !=  9 || mat_(2,2) != 0 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) != 5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) != 9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -2  9  0  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Assignment to the element at index 3
      row2[3] = -8;

      checkSize    ( row2, 4UL );
      checkCapacity( row2, 4UL );
      checkNonZeros( row2, 3UL );

      if( row2[0] != -2 || row2[1] != 9 || row2[2] != 0 || row2[3] != -8 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -2 9 0 -8 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) != 0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) != 0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -2 || mat_(2,1) !=  9 || mat_(2,2) != 0 || mat_(2,3) != -8 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) != 5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) != 9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -2  9  0 -8 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Addition assignment to the element at index 0
      row2[0] += -3;

      checkSize    ( row2, 4UL );
      checkCapacity( row2, 4UL );
      checkNonZeros( row2, 3UL );

      if( row2[0] != -5 || row2[1] != 9 || row2[2] != 0 || row2[3] != -8 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -5 9 0 -8 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) != 0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) != 0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -5 || mat_(2,1) !=  9 || mat_(2,2) != 0 || mat_(2,3) != -8 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) != 5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) != 9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -5  9  0 -8 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Subtraction assignment to the element at index 1
      row2[1] -= 6;

      checkSize    ( row2, 4UL );
      checkCapacity( row2, 4UL );
      checkNonZeros( row2, 3UL );

      if( row2[0] != -5 || row2[1] != 3 || row2[2] != 0 || row2[3] != -8 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -5 3 0 -8 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) != 0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) != 0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -5 || mat_(2,1) !=  3 || mat_(2,2) != 0 || mat_(2,3) != -8 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) != 5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) != 9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -5  3  0 -8 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Multiplication assignment to the element at index 1
      row2[1] *= -3;

      checkSize    ( row2, 4UL );
      checkCapacity( row2, 4UL );
      checkNonZeros( row2, 3UL );

      if( row2[0] != -5 || row2[1] != -9 || row2[2] != 0 || row2[3] != -8 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -5 -9 0 -8 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) != 0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) != 0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -5 || mat_(2,1) != -9 || mat_(2,2) != 0 || mat_(2,3) != -8 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) != 5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) != 9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -5 -9  0 -8 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Division assignment to the element at index 3
      row2[3] /= 2;

      checkSize    ( row2, 4UL );
      checkCapacity( row2, 4UL );
      checkNonZeros( row2, 3UL );

      if( row2[0] != -5 || row2[1] != -9 || row2[2] != 0 || row2[3] != -4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -5 -9 0 -4 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) != 0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) != 0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -5 || mat_(2,1) != -9 || mat_(2,2) != 0 || mat_(2,3) != -4 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) != 5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) != 9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -5 -9  0 -4 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major DenseRow::operator[]";

      initialize();

      ORT row2 = row( tmat_, 2UL );

      // Assignment to the element at index 1
      row2[1] = 9;

      checkSize    ( row2, 4UL );
      checkCapacity( row2, 4UL );
      checkNonZeros( row2, 3UL );

      if( row2[0] != -2 || row2[1] != 9 || row2[2] != -3 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -2 9 -3 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) !=  0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -2 || tmat_(2,1) !=  9 || tmat_(2,2) != -3 || tmat_(2,3) !=  0 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -2  9 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Assignment to the element at index 2
      row2[2] = 0;

      checkSize    ( row2, 4UL );
      checkCapacity( row2, 4UL );
      checkNonZeros( row2, 2UL );

      if( row2[0] != -2 || row2[1] != 9 || row2[2] != 0 || row2[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -2 9 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) != 0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) != 0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -2 || tmat_(2,1) !=  9 || tmat_(2,2) != 0 || tmat_(2,3) !=  0 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) != 5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) != 9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -2  9  0  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Assignment to the element at index 3
      row2[3] = -8;

      checkSize    ( row2, 4UL );
      checkCapacity( row2, 4UL );
      checkNonZeros( row2, 3UL );

      if( row2[0] != -2 || row2[1] != 9 || row2[2] != 0 || row2[3] != -8 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -2 9 0 -8 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) != 0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) != 0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -2 || tmat_(2,1) !=  9 || tmat_(2,2) != 0 || tmat_(2,3) != -8 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) != 5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) != 9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -2  9  0 -8 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Addition assignment to the element at index 0
      row2[0] += -3;

      checkSize    ( row2, 4UL );
      checkCapacity( row2, 4UL );
      checkNonZeros( row2, 3UL );

      if( row2[0] != -5 || row2[1] != 9 || row2[2] != 0 || row2[3] != -8 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -5 9 0 -8 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) != 0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) != 0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -5 || tmat_(2,1) !=  9 || tmat_(2,2) != 0 || tmat_(2,3) != -8 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) != 5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) != 9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -5  9  0 -8 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Subtraction assignment to the element at index 1
      row2[1] -= 6;

      checkSize    ( row2, 4UL );
      checkCapacity( row2, 4UL );
      checkNonZeros( row2, 3UL );

      if( row2[0] != -5 || row2[1] != 3 || row2[2] != 0 || row2[3] != -8 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -5 3 0 -8 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) != 0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) != 0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -5 || tmat_(2,1) !=  3 || tmat_(2,2) != 0 || tmat_(2,3) != -8 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) != 5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) != 9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -5  3  0 -8 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Multiplication assignment to the element at index 1
      row2[1] *= -3;

      checkSize    ( row2, 4UL );
      checkCapacity( row2, 4UL );
      checkNonZeros( row2, 3UL );

      if( row2[0] != -5 || row2[1] != -9 || row2[2] != 0 || row2[3] != -8 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -5 -9 0 -8 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) != 0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) != 0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -5 || tmat_(2,1) != -9 || tmat_(2,2) != 0 || tmat_(2,3) != -8 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) != 5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) != 9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -5 -9  0 -8 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Division assignment to the element at index 3
      row2[3] /= 2;

      checkSize    ( row2, 4UL );
      checkCapacity( row2, 4UL );
      checkNonZeros( row2, 3UL );

      if( row2[0] != -5 || row2[1] != -9 || row2[2] != 0 || row2[3] != -4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << row2 << "\n"
             << "   Expected result:\n( -5 -9 0 -4 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) !=  0 || tmat_(0,1) !=  0 || tmat_(0,2) != 0 || tmat_(0,3) !=  0 ||
          tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) != 0 || tmat_(1,3) !=  0 ||
          tmat_(2,0) != -5 || tmat_(2,1) != -9 || tmat_(2,2) != 0 || tmat_(2,3) != -4 ||
          tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) != 5 || tmat_(3,3) != -6 ||
          tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) != 9 || tmat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -5 -9  0 -4 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the DenseRow iterator implementation.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the iterator implementation of the DenseRow class template.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void GeneralTest::testIterator()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      initialize();

      // Testing the Iterator default constructor
      {
         test_ = "Row-major Iterator default constructor";

         RT::Iterator it = RT::Iterator();

         if( it != RT::Iterator() ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator default constructor\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing the ConstIterator default constructor
      {
         test_ = "Row-major ConstIterator default constructor";

         RT::ConstIterator it = RT::ConstIterator();

         if( it != RT::ConstIterator() ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator default constructor\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing conversion from Iterator to ConstIterator
      {
         test_ = "Row-major Iterator/ConstIterator conversion";

         RT row2 = row( mat_, 2UL );
         RT::ConstIterator it( begin( row2 ) );

         if( it == end( row2 ) || *it != -2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator conversion detected\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 1st row via Iterator
      {
         test_ = "Row-major Iterator subtraction";

         RT row1 = row( mat_, 1UL );
         const size_t number( end( row1 ) - begin( row1 ) );

         if( number != 4UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 4\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 2nd row via ConstIterator
      {
         test_ = "Row-major ConstIterator subtraction";

         RT row2 = row( mat_, 2UL );
         const size_t number( cend( row2 ) - cbegin( row2 ) );

         if( number != 4UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 4\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing read-only access via ConstIterator
      {
         test_ = "Row-major read-only access via ConstIterator";

         RT row3 = row( mat_, 3UL );
         RT::ConstIterator it ( cbegin( row3 ) );
         RT::ConstIterator end( cend( row3 ) );

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid initial iterator detected\n";
            throw std::runtime_error( oss.str() );
         }

         ++it;

         if( it == end || *it != 4 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator pre-increment failed\n";
            throw std::runtime_error( oss.str() );
         }

         --it;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator pre-decrement failed\n";
            throw std::runtime_error( oss.str() );
         }

         it++;

         if( it == end || *it != 4 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator post-increment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it--;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator post-decrement failed\n";
            throw std::runtime_error( oss.str() );
         }

         it += 2UL;

         if( it == end || *it != 5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator addition assignment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it -= 2UL;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator subtraction assignment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = it + 3UL;

         if( it == end || *it != -6 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator/scalar addition failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = it - 3UL;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator/scalar subtraction failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = 4UL + it;

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

         RT row0 = row( mat_, 0UL );
         int value = 6;

         for( RT::Iterator it=begin( row0 ); it!=end( row0 ); ++it ) {
            *it = value++;
         }

         if( row0[0] != 6 || row0[1] != 7 || row0[2] != 8 || row0[3] != 9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << row0 << "\n"
                << "   Expected result:\n( 6 7 8 9 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( mat_(0,0) !=  6 || mat_(0,1) !=  7 || mat_(0,2) !=  8 || mat_(0,3) !=  9 ||
             mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
             mat_(2,0) != -2 || mat_(2,1) !=  0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
             mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
             mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << mat_ << "\n"
                << "   Expected result:\n(  6  7  8  9 )\n"
                                        "(  0  1  0  0 )\n"
                                        "( -2  0 -3  0 )\n"
                                        "(  0  4  5 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing addition assignment via Iterator
      {
         test_ = "Row-major addition assignment via Iterator";

         RT row0 = row( mat_, 0UL );
         int value = 2;

         for( RT::Iterator it=begin( row0 ); it!=end( row0 ); ++it ) {
            *it += value++;
         }

         if( row0[0] != 8 || row0[1] != 10 || row0[2] != 12 || row0[3] != 14 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Addition assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << row0 << "\n"
                << "   Expected result:\n( 8 10 12 14 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( mat_(0,0) !=  8 || mat_(0,1) != 10 || mat_(0,2) != 12 || mat_(0,3) != 14 ||
             mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
             mat_(2,0) != -2 || mat_(2,1) !=  0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
             mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
             mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Addition assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << mat_ << "\n"
                << "   Expected result:\n(  8 10 12 14 )\n"
                                        "(  0  1  0  0 )\n"
                                        "( -2  0 -3  0 )\n"
                                        "(  0  4  5 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing subtraction assignment via Iterator
      {
         test_ = "Row-major subtraction assignment via Iterator";

         RT row0 = row( mat_, 0UL );
         int value = 2;

         for( RT::Iterator it=begin( row0 ); it!=end( row0 ); ++it ) {
            *it -= value++;
         }

         if( row0[0] != 6 || row0[1] != 7 || row0[2] != 8 || row0[3] != 9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subtraction assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << row0 << "\n"
                << "   Expected result:\n( 6 7 8 9 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( mat_(0,0) !=  6 || mat_(0,1) !=  7 || mat_(0,2) !=  8 || mat_(0,3) !=  9 ||
             mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
             mat_(2,0) != -2 || mat_(2,1) !=  0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
             mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
             mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subtraction assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << mat_ << "\n"
                << "   Expected result:\n(  6  7  8  9 )\n"
                                        "(  0  1  0  0 )\n"
                                        "( -2  0 -3  0 )\n"
                                        "(  0  4  5 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing multiplication assignment via Iterator
      {
         test_ = "Row-major multiplication assignment via Iterator";

         RT row0 = row( mat_, 0UL );
         int value = 1;

         for( RT::Iterator it=begin( row0 ); it!=end( row0 ); ++it ) {
            *it *= value++;
         }

         if( row0[0] != 6 || row0[1] != 14 || row0[2] != 24 || row0[3] != 36 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Multiplication assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << row0 << "\n"
                << "   Expected result:\n( 6 14 24 36 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( mat_(0,0) !=  6 || mat_(0,1) != 14 || mat_(0,2) != 24 || mat_(0,3) != 36 ||
             mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
             mat_(2,0) != -2 || mat_(2,1) !=  0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
             mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
             mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Multiplication assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << mat_ << "\n"
                << "   Expected result:\n(  6 14 24 36 )\n"
                                        "(  0  1  0  0 )\n"
                                        "( -2  0 -3  0 )\n"
                                        "(  0  4  5 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing division assignment via Iterator
      {
         test_ = "Row-major division assignment via Iterator";

         RT row0 = row( mat_, 0UL );

         for( RT::Iterator it=begin( row0 ); it!=end( row0 ); ++it ) {
            *it /= 2;
         }

         if( row0[0] != 3 || row0[1] != 7 || row0[2] != 12 || row0[3] != 18 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Division assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << row0 << "\n"
                << "   Expected result:\n( 3 7 12 18 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( mat_(0,0) !=  3 || mat_(0,1) !=  7 || mat_(0,2) != 12 || mat_(0,3) != 18 ||
             mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
             mat_(2,0) != -2 || mat_(2,1) !=  0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
             mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
             mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Division assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << mat_ << "\n"
                << "   Expected result:\n(  3  7 12 18 )\n"
                                        "(  0  1  0  0 )\n"
                                        "( -2  0 -3  0 )\n"
                                        "(  0  4  5 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      initialize();

      // Testing the Iterator default constructor
      {
         test_ = "Column-major Iterator default constructor";

         ORT::Iterator it = ORT::Iterator();

         if( it != ORT::Iterator() ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator default constructor\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing the ConstIterator default constructor
      {
         test_ = "Column-major ConstIterator default constructor";

         ORT::ConstIterator it = ORT::ConstIterator();

         if( it != ORT::ConstIterator() ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator default constructor\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing conversion from Iterator to ConstIterator
      {
         test_ = "Column-major Iterator/ConstIterator conversion";

         ORT row2 = row( tmat_, 2UL );
         ORT::ConstIterator it( begin( row2 ) );

         if( it == end( row2 ) || *it != -2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator conversion detected\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 1st row via Iterator
      {
         test_ = "Column-major Iterator subtraction";

         ORT row1 = row( tmat_, 1UL );
         const size_t number( end( row1 ) - begin( row1 ) );

         if( number != 4UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 4\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 2nd row via ConstIterator
      {
         test_ = "Column-major ConstIterator subtraction";

         ORT row2 = row( tmat_, 2UL );
         const size_t number( cend( row2 ) - cbegin( row2 ) );

         if( number != 4UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 4\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing read-only access via ConstIterator
      {
         test_ = "Column-major read-only access via ConstIterator";

         ORT row3 = row( tmat_, 3UL );
         ORT::ConstIterator it ( cbegin( row3 ) );
         ORT::ConstIterator end( cend( row3 ) );

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid initial iterator detected\n";
            throw std::runtime_error( oss.str() );
         }

         ++it;

         if( it == end || *it != 4 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator pre-increment failed\n";
            throw std::runtime_error( oss.str() );
         }

         --it;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator pre-decrement failed\n";
            throw std::runtime_error( oss.str() );
         }

         it++;

         if( it == end || *it != 4 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator post-increment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it--;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator post-decrement failed\n";
            throw std::runtime_error( oss.str() );
         }

         it += 2UL;

         if( it == end || *it != 5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator addition assignment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it -= 2UL;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator subtraction assignment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = it + 3UL;

         if( it == end || *it != -6 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator/scalar addition failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = it - 3UL;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator/scalar subtraction failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = 4UL + it;

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

         ORT row0 = row( tmat_, 0UL );
         int value = 6;

         for( ORT::Iterator it=begin( row0 ); it!=end( row0 ); ++it ) {
            *it = value++;
         }

         if( row0[0] != 6 || row0[1] != 7 || row0[2] != 8 || row0[3] != 9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << row0 << "\n"
                << "   Expected result:\n( 6 7 8 9 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( tmat_(0,0) !=  6 || tmat_(0,1) !=  7 || tmat_(0,2) !=  8 || tmat_(0,3) !=  9 ||
             tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  0 ||
             tmat_(2,0) != -2 || tmat_(2,1) !=  0 || tmat_(2,2) != -3 || tmat_(2,3) !=  0 ||
             tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
             tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << tmat_ << "\n"
                << "   Expected result:\n(  6  7  8  9 )\n"
                                        "(  0  1  0  0 )\n"
                                        "( -2  0 -3  0 )\n"
                                        "(  0  4  5 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing addition assignment via Iterator
      {
         test_ = "Column-major addition assignment via Iterator";

         ORT row0 = row( tmat_, 0UL );
         int value = 2;

         for( ORT::Iterator it=begin( row0 ); it!=end( row0 ); ++it ) {
            *it += value++;
         }

         if( row0[0] != 8 || row0[1] != 10 || row0[2] != 12 || row0[3] != 14 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Addition assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << row0 << "\n"
                << "   Expected result:\n( 8 10 12 14 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( tmat_(0,0) !=  8 || tmat_(0,1) != 10 || tmat_(0,2) != 12 || tmat_(0,3) != 14 ||
             tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  0 ||
             tmat_(2,0) != -2 || tmat_(2,1) !=  0 || tmat_(2,2) != -3 || tmat_(2,3) !=  0 ||
             tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
             tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Addition assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << tmat_ << "\n"
                << "   Expected result:\n(  8 10 12 14 )\n"
                                        "(  0  1  0  0 )\n"
                                        "( -2  0 -3  0 )\n"
                                        "(  0  4  5 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing subtraction assignment via Iterator
      {
         test_ = "Column-major subtraction assignment via Iterator";

         ORT row0 = row( tmat_, 0UL );
         int value = 2;

         for( ORT::Iterator it=begin( row0 ); it!=end( row0 ); ++it ) {
            *it -= value++;
         }

         if( row0[0] != 6 || row0[1] != 7 || row0[2] != 8 || row0[3] != 9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subtraction assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << row0 << "\n"
                << "   Expected result:\n( 6 7 8 9 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( tmat_(0,0) !=  6 || tmat_(0,1) !=  7 || tmat_(0,2) !=  8 || tmat_(0,3) !=  9 ||
             tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  0 ||
             tmat_(2,0) != -2 || tmat_(2,1) !=  0 || tmat_(2,2) != -3 || tmat_(2,3) !=  0 ||
             tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
             tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subtraction assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << tmat_ << "\n"
                << "   Expected result:\n(  6  7  8  9 )\n"
                                        "(  0  1  0  0 )\n"
                                        "( -2  0 -3  0 )\n"
                                        "(  0  4  5 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing multiplication assignment via Iterator
      {
         test_ = "Column-major multiplication assignment via Iterator";

         ORT row0 = row( tmat_, 0UL );
         int value = 1;

         for( ORT::Iterator it=begin( row0 ); it!=end( row0 ); ++it ) {
            *it *= value++;
         }

         if( row0[0] != 6 || row0[1] != 14 || row0[2] != 24 || row0[3] != 36 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Multiplication assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << row0 << "\n"
                << "   Expected result:\n( 6 14 24 36 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( tmat_(0,0) !=  6 || tmat_(0,1) != 14 || tmat_(0,2) != 24 || tmat_(0,3) != 36 ||
             tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  0 ||
             tmat_(2,0) != -2 || tmat_(2,1) !=  0 || tmat_(2,2) != -3 || tmat_(2,3) !=  0 ||
             tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
             tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Multiplication assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << tmat_ << "\n"
                << "   Expected result:\n(  6 14 24 36 )\n"
                                        "(  0  1  0  0 )\n"
                                        "( -2  0 -3  0 )\n"
                                        "(  0  4  5 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing division assignment via Iterator
      {
         test_ = "Column-major division assignment via Iterator";

         ORT row0 = row( tmat_, 0UL );

         for( ORT::Iterator it=begin( row0 ); it!=end( row0 ); ++it ) {
            *it /= 2;
         }

         if( row0[0] != 3 || row0[1] != 7 || row0[2] != 12 || row0[3] != 18 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Division assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << row0 << "\n"
                << "   Expected result:\n( 3 7 12 18 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( tmat_(0,0) !=  3 || tmat_(0,1) !=  7 || tmat_(0,2) != 12 || tmat_(0,3) != 18 ||
             tmat_(1,0) !=  0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  0 ||
             tmat_(2,0) != -2 || tmat_(2,1) !=  0 || tmat_(2,2) != -3 || tmat_(2,3) !=  0 ||
             tmat_(3,0) !=  0 || tmat_(3,1) !=  4 || tmat_(3,2) !=  5 || tmat_(3,3) != -6 ||
             tmat_(4,0) !=  7 || tmat_(4,1) != -8 || tmat_(4,2) !=  9 || tmat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Division assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << tmat_ << "\n"
                << "   Expected result:\n(  3  7 12 18 )\n"
                                        "(  0  1  0  0 )\n"
                                        "( -2  0 -3  0 )\n"
                                        "(  0  4  5 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c nonZeros() member function of the DenseRow class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c nonZeros() member function of the DenseRow class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void GeneralTest::testNonZeros()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major DenseRow::nonZeros()";

      initialize();

      // Initialization check
      RT row3 = row( mat_, 3UL );

      checkSize    ( row3, 4UL );
      checkCapacity( row3, 4UL );
      checkNonZeros( row3, 3UL );

      if( row3[0] != 0 || row3[1] != 4 || row3[2] != 5 || row3[3] != -6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << row3 << "\n"
             << "   Expected result:\n( 0 4 5 -6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Changing the number of non-zeros via the dense row
      row3[2] = 0;

      checkSize    ( row3, 4UL );
      checkCapacity( row3, 4UL );
      checkNonZeros( row3, 2UL );

      if( row3[0] != 0 || row3[1] != 4 || row3[2] != 0 || row3[3] != -6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << row3 << "\n"
             << "   Expected result:\n( 0 4 0 -6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Changing the number of non-zeros via the dense matrix
      mat_(3,0) = 5;

      checkSize    ( row3, 4UL );
      checkCapacity( row3, 4UL );
      checkNonZeros( row3, 3UL );

      if( row3[0] != 5 || row3[1] != 4 || row3[2] != 0 || row3[3] != -6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << row3 << "\n"
             << "   Expected result:\n( 5 4 0 -6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major DenseRow::nonZeros()";

      initialize();

      // Initialization check
      ORT row3 = row( tmat_, 3UL );

      checkSize    ( row3, 4UL );
      checkCapacity( row3, 4UL );
      checkNonZeros( row3, 3UL );

      if( row3[0] != 0 || row3[1] != 4 || row3[2] != 5 || row3[3] != -6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << row3 << "\n"
             << "   Expected result:\n( 0 4 5 -6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Changing the number of non-zeros via the dense row
      row3[2] = 0;

      checkSize    ( row3, 4UL );
      checkCapacity( row3, 4UL );
      checkNonZeros( row3, 2UL );

      if( row3[0] != 0 || row3[1] != 4 || row3[2] != 0 || row3[3] != -6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << row3 << "\n"
             << "   Expected result:\n( 0 4 0 -6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Changing the number of non-zeros via the dense matrix
      tmat_(3,0) = 5;

      checkSize    ( row3, 4UL );
      checkCapacity( row3, 4UL );
      checkNonZeros( row3, 3UL );

      if( row3[0] != 5 || row3[1] != 4 || row3[2] != 0 || row3[3] != -6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << row3 << "\n"
             << "   Expected result:\n( 5 4 0 -6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c reset() member function of the DenseRow class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c reset() member function of the DenseRow class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void GeneralTest::testReset()
{
   using blaze::reset;


   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major DenseRow::reset()";

      initialize();

      // Resetting a single element in row 3
      {
         RT row3 = row( mat_, 3UL );
         reset( row3[1] );

         checkSize    ( row3, 4UL );
         checkCapacity( row3, 4UL );
         checkNonZeros( row3, 2UL );
         checkRows    ( mat_, 5UL );
         checkColumns ( mat_, 4UL );
         checkNonZeros( mat_, 9UL );

         if( row3[0] != 0 || row3[1] != 0 || row3[2] != 5 || row3[3] != -6 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Reset operation failed\n"
                << " Details:\n"
                << "   Result:\n" << row3 << "\n"
                << "   Expected result:\n( 0 0 5 -6 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Resetting the 4th row
      {
         RT row4 = row( mat_, 4UL );
         reset( row4 );

         checkSize    ( row4, 4UL );
         checkCapacity( row4, 4UL );
         checkNonZeros( row4, 0UL );
         checkRows    ( mat_, 5UL );
         checkColumns ( mat_, 4UL );
         checkNonZeros( mat_, 5UL );

         if( row4[0] != 0 || row4[1] != 0 || row4[2] != 0 || row4[3] != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Reset operation of 4th row failed\n"
                << " Details:\n"
                << "   Result:\n" << row4 << "\n"
                << "   Expected result:\n( 0 0 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major DenseRow::reset()";

      initialize();

      // Resetting a single element in row 3
      {
         ORT row3 = row( tmat_, 3UL );
         reset( row3[1] );

         checkSize    ( row3 , 4UL );
         checkCapacity( row3 , 4UL );
         checkNonZeros( row3 , 2UL );
         checkRows    ( tmat_, 5UL );
         checkColumns ( tmat_, 4UL );
         checkNonZeros( tmat_, 9UL );

         if( row3[0] != 0 || row3[1] != 0 || row3[2] != 5 || row3[3] != -6 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Reset operation failed\n"
                << " Details:\n"
                << "   Result:\n" << row3 << "\n"
                << "   Expected result:\n( 0 0 5 -6 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Resetting the 4th row
      {
         ORT row4 = row( tmat_, 4UL );
         reset( row4 );

         checkSize    ( row4 , 4UL );
         checkCapacity( row4 , 4UL );
         checkNonZeros( row4 , 0UL );
         checkRows    ( tmat_, 5UL );
         checkColumns ( tmat_, 4UL );
         checkNonZeros( tmat_, 5UL );

         if( row4[0] != 0 || row4[1] != 0 || row4[2] != 0 || row4[3] != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Reset operation of 4th row failed\n"
                << " Details:\n"
                << "   Result:\n" << row4 << "\n"
                << "   Expected result:\n( 0 0 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c clear() function with the DenseRow class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c clear() function with the DenseRow class template.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void GeneralTest::testClear()
{
   using blaze::clear;


   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major clear() function";

      initialize();

      // Clearing a single element in row 3
      {
         RT row3 = row( mat_, 3UL );
         clear( row3[1] );

         checkSize    ( row3, 4UL );
         checkCapacity( row3, 4UL );
         checkNonZeros( row3, 2UL );
         checkRows    ( mat_, 5UL );
         checkColumns ( mat_, 4UL );
         checkNonZeros( mat_, 9UL );

         if( row3[0] != 0 || row3[1] != 0 || row3[2] != 5 || row3[3] != -6 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Clear operation failed\n"
                << " Details:\n"
                << "   Result:\n" << row3 << "\n"
                << "   Expected result:\n( 0 0 5 -6 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major clear() function";

      initialize();

      // Clearing a single element in row 3
      {
         ORT row3 = row( tmat_, 3UL );
         clear( row3[1] );

         checkSize    ( row3 , 4UL );
         checkCapacity( row3 , 4UL );
         checkNonZeros( row3 , 2UL );
         checkRows    ( tmat_, 5UL );
         checkColumns ( tmat_, 4UL );
         checkNonZeros( tmat_, 9UL );

         if( row3[0] != 0 || row3[1] != 0 || row3[2] != 5 || row3[3] != -6 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Clear operation failed\n"
                << " Details:\n"
                << "   Result:\n" << row3 << "\n"
                << "   Expected result:\n( 0 0 5 -6 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c isDefault() function with the DenseRow class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c isDefault() function with the DenseRow class template.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void GeneralTest::testIsDefault()
{
   using blaze::isDefault;


   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major isDefault() function";

      initialize();

      // isDefault with default row
      {
         RT row0 = row( mat_, 0UL );

         if( isDefault( row0[1] ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Row element: " << row0[1] << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( row0 ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Row:\n" << row0 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isDefault with non-default row
      {
         RT row1 = row( mat_, 1UL );

         if( isDefault( row1[1] ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Row element: " << row1[1] << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( row1 ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Row:\n" << row1 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major isDefault() function";

      initialize();

      // isDefault with default row
      {
         ORT row0 = row( tmat_, 0UL );

         if( isDefault( row0[1] ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Row element: " << row0[1] << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( row0 ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Row:\n" << row0 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isDefault with non-default row
      {
         ORT row1 = row( tmat_, 1UL );

         if( isDefault( row1[1] ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Row element: " << row1[1] << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( row1 ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Row:\n" << row1 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c isSame() function with the DenseRow class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c isSame() function with the DenseRow class template.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void GeneralTest::testIsSame()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major isSame() function";

      // isSame with matching rows
      {
         RT row1 = row( mat_, 1UL );
         RT row2 = row( mat_, 1UL );

         if( blaze::isSame( row1, row2 ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First row:\n" << row1 << "\n"
                << "   Second row:\n" << row2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching rows
      {
         RT row1 = row( mat_, 1UL );
         RT row2 = row( mat_, 2UL );

         if( blaze::isSame( row1, row2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First row:\n" << row1 << "\n"
                << "   Second row:\n" << row2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with row and matching subvector
      {
         typedef blaze::DenseSubvector<RT>  SubvectorType;

         RT row1 = row( mat_, 1UL );
         SubvectorType sv = subvector( row1, 0UL, 4UL );

         if( blaze::isSame( row1, sv ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Dense row:\n" << row1 << "\n"
                << "   Dense subvector:\n" << sv << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( sv, row1 ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Dense row:\n" << row1 << "\n"
                << "   Dense subvector:\n" << sv << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with row and non-matching subvector (different size)
      {
         typedef blaze::DenseSubvector<RT>  SubvectorType;

         RT row1 = row( mat_, 1UL );
         SubvectorType sv = subvector( row1, 0UL, 3UL );

         if( blaze::isSame( row1, sv ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Dense row:\n" << row1 << "\n"
                << "   Dense subvector:\n" << sv << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( sv, row1 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Dense row:\n" << row1 << "\n"
                << "   Dense subvector:\n" << sv << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with row and non-matching subvector (different offset)
      {
         typedef blaze::DenseSubvector<RT>  SubvectorType;

         RT row1 = row( mat_, 1UL );
         SubvectorType sv = subvector( row1, 1UL, 3UL );

         if( blaze::isSame( row1, sv ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Dense row:\n" << row1 << "\n"
                << "   Dense subvector:\n" << sv << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( sv, row1 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Dense row:\n" << row1 << "\n"
                << "   Dense subvector:\n" << sv << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matching rows on submatrices
      {
         typedef blaze::DenseSubmatrix<MT>       SubmatrixType;
         typedef blaze::DenseRow<SubmatrixType>  RowType;

         SubmatrixType sm = submatrix( mat_, 1UL, 1UL, 2UL, 3UL );
         RowType row1 = row( sm, 1UL );
         RowType row2 = row( sm, 1UL );

         if( blaze::isSame( row1, row2 ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First row:\n" << row1 << "\n"
                << "   Second row:\n" << row2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching rows on submatrices
      {
         typedef blaze::DenseSubmatrix<MT>       SubmatrixType;
         typedef blaze::DenseRow<SubmatrixType>  RowType;

         SubmatrixType sm = submatrix( mat_, 1UL, 1UL, 2UL, 3UL );
         RowType row1 = row( sm, 0UL );
         RowType row2 = row( sm, 1UL );

         if( blaze::isSame( row1, row2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First row:\n" << row1 << "\n"
                << "   Second row:\n" << row2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matching row subvectors on submatrices
      {
         typedef blaze::DenseSubmatrix<MT>       SubmatrixType;
         typedef blaze::DenseRow<SubmatrixType>  RowType;
         typedef blaze::DenseSubvector<RowType>  SubvectorType;

         SubmatrixType sm = submatrix( mat_, 1UL, 1UL, 2UL, 3UL );
         RowType row1 = row( sm, 1UL );
         SubvectorType sv1 = subvector( row1, 0UL, 2UL );
         SubvectorType sv2 = subvector( row1, 0UL, 2UL );

         if( blaze::isSame( sv1, sv2 ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First subvector:\n" << sv1 << "\n"
                << "   Second subvector:\n" << sv2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching row subvectors on submatrices (different size)
      {
         typedef blaze::DenseSubmatrix<MT>       SubmatrixType;
         typedef blaze::DenseRow<SubmatrixType>  RowType;
         typedef blaze::DenseSubvector<RowType>  SubvectorType;

         SubmatrixType sm = submatrix( mat_, 1UL, 1UL, 2UL, 3UL );
         RowType row1 = row( sm, 1UL );
         SubvectorType sv1 = subvector( row1, 0UL, 2UL );
         SubvectorType sv2 = subvector( row1, 0UL, 3UL );

         if( blaze::isSame( sv1, sv2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First subvector:\n" << sv1 << "\n"
                << "   Second subvector:\n" << sv2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching row subvectors on submatrices (different offset)
      {
         typedef blaze::DenseSubmatrix<MT>       SubmatrixType;
         typedef blaze::DenseRow<SubmatrixType>  RowType;
         typedef blaze::DenseSubvector<RowType>  SubvectorType;

         SubmatrixType sm = submatrix( mat_, 1UL, 1UL, 2UL, 3UL );
         RowType row1 = row( sm, 1UL );
         SubvectorType sv1 = subvector( row1, 0UL, 2UL );
         SubvectorType sv2 = subvector( row1, 1UL, 2UL );

         if( blaze::isSame( sv1, sv2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First subvector:\n" << sv1 << "\n"
                << "   Second subvector:\n" << sv2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major isSame() function";

      // isSame with matching rows
      {
         ORT row1 = row( tmat_, 1UL );
         ORT row2 = row( tmat_, 1UL );

         if( blaze::isSame( row1, row2 ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First row:\n" << row1 << "\n"
                << "   Second row:\n" << row2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching rows
      {
         ORT row1 = row( tmat_, 1UL );
         ORT row2 = row( tmat_, 2UL );

         if( blaze::isSame( row1, row2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First row:\n" << row1 << "\n"
                << "   Second row:\n" << row2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with row and matching subvector
      {
         typedef blaze::DenseSubvector<ORT>  SubvectorType;

         ORT row1 = row( tmat_, 1UL );
         SubvectorType sv = subvector( row1, 0UL, 4UL );

         if( blaze::isSame( row1, sv ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Dense row:\n" << row1 << "\n"
                << "   Dense subvector:\n" << sv << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( sv, row1 ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Dense row:\n" << row1 << "\n"
                << "   Dense subvector:\n" << sv << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with row and non-matching subvector (different size)
      {
         typedef blaze::DenseSubvector<ORT>  SubvectorType;

         ORT row1 = row( tmat_, 1UL );
         SubvectorType sv = subvector( row1, 0UL, 3UL );

         if( blaze::isSame( row1, sv ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Dense row:\n" << row1 << "\n"
                << "   Dense subvector:\n" << sv << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( sv, row1 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Dense row:\n" << row1 << "\n"
                << "   Dense subvector:\n" << sv << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with row and non-matching subvector (different offset)
      {
         typedef blaze::DenseSubvector<ORT>  SubvectorType;

         ORT row1 = row( tmat_, 1UL );
         SubvectorType sv = subvector( row1, 1UL, 3UL );

         if( blaze::isSame( row1, sv ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Dense row:\n" << row1 << "\n"
                << "   Dense subvector:\n" << sv << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( sv, row1 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Dense row:\n" << row1 << "\n"
                << "   Dense subvector:\n" << sv << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matching rows on submatrices
      {
         typedef blaze::DenseSubmatrix<OMT>      SubmatrixType;
         typedef blaze::DenseRow<SubmatrixType>  RowType;

         SubmatrixType sm = submatrix( tmat_, 1UL, 1UL, 2UL, 3UL );
         RowType row1 = row( sm, 1UL );
         RowType row2 = row( sm, 1UL );

         if( blaze::isSame( row1, row2 ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First row:\n" << row1 << "\n"
                << "   Second row:\n" << row2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching rows on submatrices
      {
         typedef blaze::DenseSubmatrix<OMT>      SubmatrixType;
         typedef blaze::DenseRow<SubmatrixType>  RowType;

         SubmatrixType sm = submatrix( tmat_, 1UL, 1UL, 2UL, 3UL );
         RowType row1 = row( sm, 0UL );
         RowType row2 = row( sm, 1UL );

         if( blaze::isSame( row1, row2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First row:\n" << row1 << "\n"
                << "   Second row:\n" << row2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matching row subvectors on submatrices
      {
         typedef blaze::DenseSubmatrix<OMT>      SubmatrixType;
         typedef blaze::DenseRow<SubmatrixType>  RowType;
         typedef blaze::DenseSubvector<RowType>  SubvectorType;

         SubmatrixType sm = submatrix( tmat_, 1UL, 1UL, 2UL, 3UL );
         RowType row1 = row( sm, 1UL );
         SubvectorType sv1 = subvector( row1, 0UL, 2UL );
         SubvectorType sv2 = subvector( row1, 0UL, 2UL );

         if( blaze::isSame( sv1, sv2 ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First subvector:\n" << sv1 << "\n"
                << "   Second subvector:\n" << sv2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching row subvectors on submatrices (different size)
      {
         typedef blaze::DenseSubmatrix<OMT>      SubmatrixType;
         typedef blaze::DenseRow<SubmatrixType>  RowType;
         typedef blaze::DenseSubvector<RowType>  SubvectorType;

         SubmatrixType sm = submatrix( tmat_, 1UL, 1UL, 2UL, 3UL );
         RowType row1 = row( sm, 1UL );
         SubvectorType sv1 = subvector( row1, 0UL, 2UL );
         SubvectorType sv2 = subvector( row1, 0UL, 3UL );

         if( blaze::isSame( sv1, sv2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First subvector:\n" << sv1 << "\n"
                << "   Second subvector:\n" << sv2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching row subvectors on submatrices (different offset)
      {
         typedef blaze::DenseSubmatrix<OMT>      SubmatrixType;
         typedef blaze::DenseRow<SubmatrixType>  RowType;
         typedef blaze::DenseSubvector<RowType>  SubvectorType;

         SubmatrixType sm = submatrix( tmat_, 1UL, 1UL, 2UL, 3UL );
         RowType row1 = row( sm, 1UL );
         SubvectorType sv1 = subvector( row1, 0UL, 2UL );
         SubvectorType sv2 = subvector( row1, 1UL, 2UL );

         if( blaze::isSame( sv1, sv2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First subvector:\n" << sv1 << "\n"
                << "   Second subvector:\n" << sv2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c subvector() function with the DenseRow class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c subvector() function used with the DenseRow class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void GeneralTest::testSubvector()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major subvector() function";

      initialize();

      typedef blaze::DenseSubvector<RT>  SubvectorType;

      RT row1 = row( mat_, 1UL );
      SubvectorType sv = subvector( row1, 0UL, 4UL );

      if( sv[1] != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator access failed\n"
             << " Details:\n"
             << "   Result: " << sv[1] << "\n"
             << "   Expected result: 1\n";
         throw std::runtime_error( oss.str() );
      }

      if( *sv.begin() != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << *sv.begin() << "\n"
             << "   Expected result: 0\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major subvector() function";

      initialize();

      typedef blaze::DenseSubvector<ORT>  SubvectorType;

      ORT row1 = row( tmat_, 1UL );
      SubvectorType sv = subvector( row1, 0UL, 4UL );

      if( sv[1] != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator access failed\n"
             << " Details:\n"
             << "   Result: " << sv[1] << "\n"
             << "   Expected result: 1\n";
         throw std::runtime_error( oss.str() );
      }

      if( *sv.begin() != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << *sv.begin() << "\n"
             << "   Expected result: 0\n";
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
void GeneralTest::initialize()
{
   // Initializing the row-major dynamic matrix
   mat_.reset();
   mat_(1,1) =  1;
   mat_(2,0) = -2;
   mat_(2,2) = -3;
   mat_(3,1) =  4;
   mat_(3,2) =  5;
   mat_(3,3) = -6;
   mat_(4,0) =  7;
   mat_(4,1) = -8;
   mat_(4,2) =  9;
   mat_(4,3) = 10;

   // Initializing the column-major dynamic matrix
   tmat_.reset();
   tmat_(1,1) =  1;
   tmat_(2,0) = -2;
   tmat_(2,2) = -3;
   tmat_(3,1) =  4;
   tmat_(3,2) =  5;
   tmat_(3,3) = -6;
   tmat_(4,0) =  7;
   tmat_(4,1) = -8;
   tmat_(4,2) =  9;
   tmat_(4,3) = 10;
}
//*************************************************************************************************

} // namespace denserow

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
   std::cout << "   Running general DenseRow class test..." << std::endl;

   try
   {
      RUN_DENSEROW_CLASS_TEST;
   }
   catch( std::exception& ex ) {
      std::cerr << "\n\n ERROR DETECTED during general DenseRow class test:\n"
                << ex.what() << "\n";
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
//*************************************************************************************************
