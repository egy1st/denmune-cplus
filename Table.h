#include "stdafx.h"
#include<stack>
#include<fstream>
#include<iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <algorithm>
#include <time.h>
#include <vector>


/*  ContingencyTable.java

    Copyright (c) 2009 Andrew Rosenberg


    ContingencyTable.java is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ContingencyTable.java is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ContingencyTable.java.  If not, see <http://www.gnu.org/licenses/>.
 */


/**
 * A two dimensional array containing ContingencyTable data.
 *
 */

class ContingencyTable {
private:
    
   int numRows;
   int numCols;
   double data[10000][2];

  /**
   * Construct an empty ContingencyTable with specified dimensions.
   *
   * @param numRows the number of rows
   * @param numCols the number of columns
   */
  ContingencyTable(int nRows, int nCols) {
    numRows = nRows;
    numCols = nCols;
    //data = new double[nRows][nCols];
 }

  /**
   * Construct a new ContingengyTable containing data
   *
   * @param data the initial data for the ContingencyTable
   */
  ContingencyTable(double dt[][2]) {
    if (dt.size() > 0) {
      numRows = dt.size();
      numCols = dt[0].size();
      data = dt;
    }
  }

  /**
   * Get a value of a data cell
   *
   * @param i the row
   * @param j the column
   * @return the value
   */
   double get(int i, int j) {
    if ((0 <= i) && (i < numRows) && (0 <= j) && (j < numCols)) return data[i][j];
    else return Double.NaN;
  }

  /**
   * Set the value of a data cell.
   *
   * @param i the row
   * @param j the column
   * @param v the value
   */
  void set(int i, int j, double v) {
    if ((0 <= i) && (i < numRows) && (0 <= j) && (j < numCols)) data[i][j] = v;
  }

  /**
   * Set the data for the contingengy table from a 2-d array of doubles
   *
   * @param d a 2-d array.
   */
  void setData(double d[][2]) {
    this.data = d;
    this.numRows = d.length;
    this.numCols = d[0].length;
  }

  
  /**
   * Build a string representation of the ContingencyTable
   *
   * @return the data as a string
  
    
  string toString() {
    StringBuffer str = new StringBuffer();

    DecimalFormat fmt = new DecimalFormat("00000.0");
    for (int i = 0; i < numRows; ++i) {
      for (int j = 0; j < numCols; ++j) {
        str.append("\t");
        str.append(fmt.format(data[i][j]));
      }
      str.append("\n");
    }

    return str.toString();
  }

  */ 

  /**
   * Calculates the sum over the columns of the contingency table
   *
   * @return an array of doubles containing the row sums.
   */
  double* getRowSum() {

    double[] ret = new double[numRows];

    for (int i = 0; i < ret.length; ++i)
      ret[i] = 0.0;

    for (int i = 0; i < numRows; ++i) {
      for (int j = 0; j < numCols; ++j) {
        ret[i] += data[i][j];
      }
    }

    return ret;
  }

  /**
   * Calculates the sum over the rows of the contingency table
   *
   * @return an array of doubles containing the column sums.
   */
  double* getColSum() {
    double[] ret = new double[numCols];

    for (int i = 0; i < ret.length; ++i)
      ret[i] = 0.0;

    for (int i = 0; i < numRows; ++i) {
      for (int j = 0; j < numCols; ++j) {
        ret[j] += data[i][j];
      }
    }

    return ret;
  }

  /**
   * Get the number of data points in the table
   *
   * More specifically, this returns the sum of the weights stored in the table.
   *
   * @return the ammount of data stored in the table
   */
  double getN() {
    double sum = 0;
    for (int i = 0; i < numRows; ++i) {
      for (int j = 0; j < numCols; ++j) {
        sum += data[i][j];
      }
    }
    return sum;
  }

  /**
   * Get the number of rows.
   *
   * @return the number of rows
   */
  int getNumRows() {
    return numRows;
  }

  /**
   * Get the number of columns
   *
   * @return the number of columns
   */
  int getNumCols() {
    return numCols;
  }

  /**
   * Get an array representation of a single column
   *
   * @param j the column index
   * @return an array containing the column data from the Table
   */
  double* getCol(int j) {
    double[] col = new double[numRows];

    for (int i = 0; i < numRows; ++i) {
      col[i] = data[i][j];
    }
    return col;
  }

   /**
   * Get an array representation of a single row
   *
   * @param i the row index
   * @return an array containing the row data from the Table
   */
  double* getRow(int i) {
    double[] row = new double[numCols];

    for (int j = 0; j < numCols; ++j) {
      row[j] = data[i][j];
    }
    return row;
  }

  /**
   * Get the maximum value across rows in a given column
   * @param j the column index
   * @return the maximum value
   */
  double maxRowValue(int j) {
    double max = -1.0;

    for (int i = 0; i < numRows; ++i) {
      if (data[i][j] > max) max = data[i][j];
    }

    return max;
  }


  /**
   * Get the maximum value across columns in a given row
   * @param i the row index
   * @return the maximum value
   */
  double maxColValue(int i) {
    double max = -1.0;

    for (int j = 0; j < numCols; ++j) {
      if (data[i][j] > max) max = data[i][j];
    }

    return max;
  }

  /**
   * Reduce the contingency table to a 2x2 pairwise contingency table defined as follows
   * <p/>
   * a_00 = sum_c sum_k h(c,k) choose 2 -- the number of pairs that are found in the same class and same cluster a_01 = sum_c
   * h(c) choose 2 - a_00 -- the number of pairs that are found in the same class but different clusters a_10 = sum_k h(k)
   * choose 2 - a_00 -- the number of pairs that are found in the same cluster but different classes a_11 = n choose 2 - a_00 -
   * a_01 - a_10 -- the number of pairs that are found in different classes and different clusters
   *
   * @return a new ContingencyTable defined as above
   */
  ContingencyTable buildPairwiseContingencyTable() {

    ContingencyTable a = new ContingencyTable(2, 2);

    // a_00
    a.set(0, 0, 0.0);
    for (int i = 0; i < this.numRows; ++i) {
      for (int j = 0; j < this.numCols; ++j) {
        a.set(0, 0, a.get(0, 0) + (this.get(i, j) * (this.get(i, j) - 1)) / 2.0);
      }
    }

    // a_01
    a.set(0, 1, 0.0);
    double[] class_v = getColSum();
    for (int i = 0; i < this.numCols; ++i) {
      a.set(0, 1, a.get(0, 1) + (class_v[i] * (class_v[i] - 1)) / 2.0);
    }
    a.set(0, 1, a.get(0, 1) - a.get(0, 0));

    // a_10
    a.set(1, 0, 0.0);
    double[] cluster_v = getRowSum();
    for (int j = 0; j < this.numRows; ++j) {
      a.set(1, 0, a.get(1, 0) + (cluster_v[j] * (cluster_v[j] - 1)) / 2.0);
    }
    a.set(1, 0, a.get(1, 0) - a.get(0, 0));

    // a_11
    double n = 0;
    for (int i = 0; i < cluster_v.length; ++i){
      n += cluster_v[i];
    }
    a.set(1, 1, ((n * (n - 1)) / 2.0) - a.get(0, 0) - a.get(0, 1) - a.get(1, 0));

    return a;
  }

}