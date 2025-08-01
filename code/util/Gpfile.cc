#include <unistd.h>
#include <string.h>
#include <fstream.h>
#include <stdio.h>

#include "General.h"
#include "Gpfile.h"

int WriteGpFile(const char* filename, const char* title, const char* xlabel, const char* ylabel, int dimension,
                int isDiscrete)
{
  gpInfo gpi(filename);

  gpi.NewFile();

  gpi.Title(title).xTitle(xlabel).yTitle(ylabel);

  if (dimension > 3) dimension = 3;
  switch (dimension)
  {
  case 3: gpi.using3(4).addOption(PLOT3D);
  case 2: gpi.using2(3);
  case 1: gpi.using1(2);
  }

  gpi.setPlotStyle(isDiscrete ? POINTS : LINES);

  gpi.pause();

  gpi.AppendToFile();

  return TRUE;
}


gpInfo::gpInfo(const char* _filename)
{
  gpfilename = _filename;
  gpfilename += ".gp";
  datafilename[0] = _filename;
  reset();
}


void gpInfo::reset()
{
  outputfile = "";
  title = "";
  xtitle = "";
  ytitle = "";

  plotStyle = POINTS;
  axisStyle = 0;
  options = 0;

  using1(1);
  using2(0);
  using3(0);

  plotColor = 1;

  datafilename[1] = "";
}


void CreateFilename(char* dest, const char* src, const char* ext)
{
  strcpy(dest, src);
  strcat(dest, ext);
}

void CreateFilename(char* dest, const char* src, int n)
{
  char ext[] = {char(48 + n / 10), char(48 + n % 10), 0};

  CreateFilename(dest, src, ext);
}


int gpInfo::NewFile()
{
  ofstream gpout;
  gpout.open(gpfilename, ios::out | ios::trunc);

  gpout.close();

  return TRUE;
}


void gpInfo::writeGpTitle(ofstream& gpout)
{
  if (title)
    gpout << "set title \"" << title << "\"" << endl;
  gpout << "set xlabel \"" << xtitle << "\"" << endl;
  gpout << "set ylabel \"" << ytitle << "\"" << endl;
}

void gpInfo::writeGpTerminal(ofstream& gpout)
{
  if (options & LATEX_OUTPUT) gpout << "set terminal latex" << endl;
#ifdef EPSHACK
  else if (options & PS_OUTPUT) gpout << "set terminal postscript eps enhanced monochrome" << endl;
#else
  else if (options & PS_OUTPUT) gpout << "set terminal postscript" << endl;
#endif

  else gpout << "set terminal x11" << endl;

  gpout << "set output \"" << outputfile << "\"" << endl;
}

void gpInfo::writeGpScaleRange(ofstream& gpout)
{
  if ((axisStyle & LOGSCALE_X) && (axisStyle & LOGSCALE_Y))
    gpout << "set logscale" << endl;
  else if (axisStyle & LOGSCALE_X)
    gpout << "set logscale x" << endl;
  else if (axisStyle & LOGSCALE_Y)
    gpout << "set logscale y" << endl;
  else
    gpout << "set nologscale" << endl;

  gpout << "set autoscale" << endl;
  if (options & SET_X_RANGE) gpout << "set xrange [" << xrange[0] << ":" << xrange[1] << "]" << endl;
  if (options & SET_Y_RANGE) gpout << "set yrange [" << yrange[0] << ":" << yrange[1] << "]" << endl;
  if (options & SET_Z_RANGE) gpout << "set zrange [" << zrange[0] << ":" << zrange[1] << "]" << endl;

  gpout << "set grid" << endl;
}

void gpInfo::writeGpParametric(ofstream& gpout)
{
  if (options & PLOT3D)
    gpout << "set parametric" << endl;
  else
    gpout << "set noparametric" << endl;
}


void getUseString(string& use, int x1, int x2, int x3)
{
  use = " u "; // using
  if (x1) use += toString(x1);
  if (x2) use += ":" + toString(x2);
  if (x3) use += ":" + toString(x3);
}

void gpInfo::writeGpPlottingStuff(ofstream& gpout)
{
  String use = "";

  int _plotStyle = plotStyle ? : POINTS;

  boolean alreadyPlotted = FALSE;

  for (int x1 = axis[0]; x1 <= axis[3]; x1++)
    for (int x2 = axis[1]; x2 <= axis[4]; x2++)
      for (int x3 = axis[2]; x3 <= axis[5]; x3++)
      {
        for (int style = ERRORBARS; style <= IMPULSES; style <<= 1)
        {
          if (!(_plotStyle & style)) continue;

          string styleName;
          switch (style)
          {
          case ERRORBARS: styleName = "e ";
            break;
          case LINES: styleName = "l lc 0 lt 1";
            break;
          case POINTS: styleName = "p pt 1";
            break;
          case LINESPOINTS: styleName = "linesp lc 0 lt 1 pt 1";
            break;
          case IMPULSES: styleName = "i ";
            break;
          default: ASSERT(FALSE);
            break;
          }

          getUseString(use, x1, x2, x3);

          if (!alreadyPlotted)
            gpout << ((options & PLOT3D) ? "sp " : "p "); // plot, splot
          else
            gpout << ",\\" << endl;

          // styleName = styleName + "lc 0 lt 1 pt ";
          for (int i = 0; i < MAX_DATA_FILES; i++)
          {
            if (datafilename[i] == "") break;
            if (i) gpout << ", ";
            // gpout << "\"" << datafilename[i] << '"' << use << " not w " << styleName << plotColor + i;
            gpout << "\"" << datafilename[i] << '"' << use << " not w " << styleName;
          }

          alreadyPlotted = TRUE;
        }
      }

  gpout << endl;
}


int gpInfo::AppendToFile()
{
  ofstream gpout(gpfilename, ios::out | ios::app);

#ifdef EPSHACK
  options &= ~PAUSE;
  outputfile = datafilename[0] + ".eps";
  options |= PS_OUTPUT;
  title = "";
#endif

  writeGpTitle(gpout);

  writeGpTerminal(gpout);

  writeGpScaleRange(gpout);

  writeGpParametric(gpout);

  writeGpPlottingStuff(gpout);

  if (options & PAUSE)
    gpout << "pause -1 \"Hit Return to continue...\"" << endl;

  gpout.close();

#ifdef EPSHACK
  ViewGpFile(datafilename[0], FALSE);
#endif

  return TRUE;
}


int ViewGpFile(const char* filename, boolean smallPoints)
{
  string filename_gp = filename;
  filename_gp += ".gp";

  if (smallPoints)
    return execlp("gnuplot", "gnuplot", "-pointsize", "0.01", "-geometry", "1024x768+0+0", (const char*)filename_gp,
                  NULL);
  else
    return execlp("gnuplot", "gnuplot", "-geometry", "1024x768+0+0", (const char*)filename_gp, NULL);
}







