#include "mainwindow.h"
#include <QApplication>

extern "C"{
  int test_();
  int test2_();
}

extern "C"{
#include "Blas.h"
#include "Lapack.h"
}


int main(int argc, char *argv[])
{
  int* pt;
  int nl='\n',ff='\f',cr='\r';

  int nalfa = 1;
  int info;
  double work[nalfa], kinv[nalfa*nalfa];
  int iwork[nalfa];
  dgetrf(&nalfa, &nalfa, kinv, &nalfa, iwork, &info);
  dgetri(&nalfa, kinv, &nalfa, iwork, work, &nalfa, &info);

  printf("nl %d , ff %d , cr %d\n",nl,ff,cr);
  printf("Hello, World! size of long, int, pt, double  = %lu %lu %lu %lu \n",sizeof(long),sizeof(int),sizeof(pt),sizeof(double));
    
  test_();
  test2_();

  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}
