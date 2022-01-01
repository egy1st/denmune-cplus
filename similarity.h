// GNU General Public License Agreement
// Copyright (C) 2004-2010 CodeCogs, Zyba Ltd, Broadwood, Holford, TA5 1DU, England.
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by CodeCogs. 
// You must retain a copy of this licence in all copies. 
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
// PARTICULAR PURPOSE. See the GNU General Public License for more details.
// ---------------------------------------------------------------------------------
//! Calculates the Pearson product for a given set of data.


#include<math.h>

namespace Stats
{

static double GetAverage( vector<double> data )
  {
   int len = data.size() ;
   //if ( len == 0 ) 
   // throw new Exception("No data");
    
   double sum = 0; 
   for ( int i = 0; i < len ; i++ )
    sum += data[i]; 
   return sum / len;
  }



 static double GetVariance( vector<double> data )
  {
   int len = data.size() ;
   // Get average
   double avg = GetAverage( data );
    
   double sum = 0; 
   for ( int i = 0; i < (int) data.size(); i++ )
	   sum += pow( ( data[i] - avg ), 2 ); 
      return sum / len;
    } 


  /// <summary>
  /// Get standard deviation
  /// </summary>
   static double GetStdev( vector<double> data )
   {
     return sqrt( GetVariance( data )  );
   } 


   static double  GetCorrelation( vector<double> x, vector<double> y)
  {
   //if ( x.size() != y.size() )
   //throw new Exception("Length of sources is different"); 
   double avgX = GetAverage( x );
   double stdevX = GetStdev( x );
   double avgY = GetAverage( y );
   double stdevY = GetStdev( y ); 
   int len = x.size(); 
    
   double covXY = 0 ;

   for ( int i = 0; i < len; i++ )
   {
     covXY +=  ( ( x[i] - avgX ) * ( y[i] - avgY ) ) ; 
   }
  
   covXY /= len; 
   return  covXY / ( stdevX * stdevY );

  }

 static double GetDotProduct( vector<double> data1 , vector<double> data2)
  {
   int len = data1.size() ;
   
   double sum = 0; 
   for ( int i = 0; i < len ; i++ )
	   sum += (data1[i] * data2[i]) ; 

   return sum ;
  } 


 static double GetNorm( vector<double> data)
  {
   int len = data.size() ;
       
   double sum = 0; 
   for ( int i = 0; i < len ; i++ )
	   sum +=  (data[i] * data[i]) ; 
   return sqrt(sum) ;
  } 


 static double GetCosine( vector<double> data1 , vector<double> data2 )
  {
   int len = data1.size() ;
   double norm1 = GetNorm (data1);
   double norm2 = GetNorm (data2);
   double prod = GetDotProduct(data1, data2); 
   
   return prod /(norm1*norm2) ;
  } 


}





