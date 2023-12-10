#include <QtWidgets/QApplication>
#include "widget.h"
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Widget w; // widget 선언
  w.show(); // widget 출력
  return a.exec(); // 실행
}
