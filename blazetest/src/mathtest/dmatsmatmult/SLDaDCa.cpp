//=================================================================================================
/*!
//  \file src/mathtest/dmatsmatmult/SLDaDCa.cpp
//  \brief Source file for the SLDaDCa dense matrix/sparse matrix multiplication math test
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
#include <blaze/math/DiagonalMatrix.h>
#include <blaze/math/DynamicMatrix.h>
#include <blaze/math/StrictlyLowerMatrix.h>
#include <blazetest/mathtest/Creator.h>
#include <blazetest/mathtest/dmatsmatmult/OperationTest.h>
#include <blazetest/system/MathTest.h>


//=================================================================================================
//
//  MAIN FUNCTION
//
//=================================================================================================

//*************************************************************************************************
int main()
{
   std::cout << "   Running 'SLDaDCa'..." << std::endl;

   using blazetest::mathtest::TypeA;

   try
   {
      // Matrix type definitions
      typedef blaze::StrictlyLowerMatrix< blaze::DynamicMatrix<TypeA> >  SLDa;
      typedef blaze::DiagonalMatrix< blaze::CompressedMatrix<TypeA> >    DCa;

      // Creator type definitions
      typedef blazetest::Creator<SLDa>  CSLDa;
      typedef blazetest::Creator<DCa>   CDCa;

      // Running tests with small matrices
      for( size_t i=0UL; i<=6UL; ++i ) {
         for( size_t j=0UL; j<=i; ++j ) {
            RUN_DMATSMATMULT_OPERATION_TEST( CSLDa( i ), CDCa( i, j ) );
         }
      }

      // Running tests with large matrices
      RUN_DMATSMATMULT_OPERATION_TEST( CSLDa(  31UL ), CDCa(  31UL,  7UL ) );
      RUN_DMATSMATMULT_OPERATION_TEST( CSLDa(  67UL ), CDCa(  67UL,  7UL ) );
      RUN_DMATSMATMULT_OPERATION_TEST( CSLDa( 127UL ), CDCa( 127UL, 13UL ) );
      RUN_DMATSMATMULT_OPERATION_TEST( CSLDa(  32UL ), CDCa(  32UL,  8UL ) );
      RUN_DMATSMATMULT_OPERATION_TEST( CSLDa(  64UL ), CDCa(  64UL,  8UL ) );
      RUN_DMATSMATMULT_OPERATION_TEST( CSLDa( 128UL ), CDCa( 128UL, 16UL ) );
   }
   catch( std::exception& ex ) {
      std::cerr << "\n\n ERROR DETECTED during dense matrix/sparse matrix multiplication:\n"
                << ex.what() << "\n";
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
//*************************************************************************************************
