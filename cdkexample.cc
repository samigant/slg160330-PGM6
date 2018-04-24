// Saamntha Gant
// slg160330@utdallas.edu
// CS3377.502
// Prog 6 CDK Example File (Modified)

/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Author: Stephen Perkins
 * Email:  stephen.perkins@utdallas.edu
 */

#include <string.h>
#include <iostream>
#include <fstream>
#include "cdk.h"
#include <sstream>
#include <stdint.h>
#include <algorithm>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

class BinaryFileHeader{
public:

  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

const int maxRecordStringLength = 25;

class BinaryFileRecord{
public:

  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"", "a", "b", "c"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  // Opening binary file to fill matrix and creater objects for reading
  BinaryFileHeader *header = new BinaryFileHeader();
  BinaryFileRecord *record = new BinaryFileRecord();

  ifstream binfile("cs3377.bin", ios::in | ios::binary);
  
  // Reading binary file header and placing in matrix
  binfile.read((char *) header, sizeof(BinaryFileHeader));
  std::stringstream ss;
  ss << "Magic: 0x" << std::uppercase << std::hex << header->magicNumber;
  setCDKMatrixCell(myMatrix, 1, 1,ss.str().c_str());
  std::stringstream sss;
  sss << "Version: " << header->versionNumber;
  setCDKMatrixCell(myMatrix, 1, 2, sss.str().c_str());
  std::stringstream ssss;
  ssss << "NumRecords: " << header->numRecords;
  setCDKMatrixCell(myMatrix, 1, 3, ssss.str().c_str());
  /*
   * Display a message
   */
  setCDKMatrixCell(myMatrix, 2, 2, "Test Message");
  drawCDKMatrix(myMatrix, true);    /* required  */

  // Closing binary file
  binfile.close();

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
