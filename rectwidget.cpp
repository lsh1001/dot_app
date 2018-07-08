#include <QtWidgets>
#include <rectwidget.h>

RectDialog::RectDialog()
{
	setFixedSize(150,210);

	Xposition = 0;
	Yposition = 0;

	Xsize = 0;
	Ysize = 0;

	BW = 0;
	isCancel = 0;

	Xposition_label = new QLabel("Xposition",this);
	Xposition_label->setGeometry(10,10,70,30);

	Xposition_edits = new QLineEdit(this);
	Xposition_edits->setText("");
	Xposition_edits->setGeometry(80,10,50,30);

	Yposition_label = new QLabel("Yposition",this);
	Yposition_label->setGeometry(10,40,70,30);

	Yposition_edits = new QLineEdit(this);
	Yposition_edits->setText("");
	Yposition_edits->setGeometry(80,40,50,30);

	Xsize_label = new QLabel("Xsize",this);
	Xsize_label->setGeometry(10,80,70,30);

	Xsize_edits = new QLineEdit(this);
	Xsize_edits->setText("");
	Xsize_edits->setGeometry(80,80,50,30);

	Ysize_label = new QLabel("Ysize",this);
	Ysize_label->setGeometry(10,110,70,30);

	Ysize_edits = new QLineEdit(this);
	Ysize_edits->setText("");
	Ysize_edits->setGeometry(80,110,50,30);

	BW_label = new QLabel("W(0)/B(1)",this);
	BW_label->setGeometry(10,150,70,30);

	BW_edits = new QLineEdit(this);
	BW_edits->setText("");
	BW_edits->setGeometry(80,150,50,30);

	OK_button = new QPushButton(tr("OK"),this);
	OK_button->setGeometry(50,180,50,30);
	connect(OK_button,SIGNAL(clicked()),this,SLOT(OK_clicked()));
	
	Cancel_button = new QPushButton(tr("Cancel"),this);
	Cancel_button->setGeometry(100,180,50,30);
	connect(Cancel_button,SIGNAL(clicked()),this,SLOT(Cancel_clicked()));
}

void RectDialog::OK_clicked()
{
	QString X,Y,X_size,Y_size,color;

	X = this->Xposition_edits->text();
	Y = this->Yposition_edits->text();
	
	X_size = this->Xsize_edits->text();
	Y_size = this->Ysize_edits->text();
	
	color = this->BW_edits->text();

	this->Xposition = X.toInt();
	this->Yposition = Y.toInt();

	this->Xsize = X_size.toInt();
	this->Ysize = Y_size.toInt();

	this->BW = color.toInt();

	this->close();
}

void RectDialog::Cancel_clicked()
{
	this->isCancel = 1;
	this->close();
}

int RectDialog::getXposition()
{
	return this->Xposition;
}

int RectDialog::getYposition()
{
	return this->Yposition;
}

int RectDialog::getXsize()
{
	return this->Xsize;
}

int RectDialog::getYsize()
{
	return this->Ysize;
}

int RectDialog::getBW()
{
	return this->BW;
}

int RectDialog::isCanceled()
{
	return this->isCancel;
}
