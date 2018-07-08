#include <QApplication>
#include "mywidget.cpp"

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
	MyWidget widget;

	widget.show();
	return app.exec();
}
