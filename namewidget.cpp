#include <QtWidgets>
#include <namewidget.h>

NameDialog::NameDialog()
{
	setFixedSize(250,100);

	Name = "";

	isCancel = 0;

	Name_label = new QLabel("File Name",this);
	Name_label->setGeometry(10,30,70,30);

	Name_edits = new QLineEdit(this);
	Name_edits->setText("");
	Name_edits->setGeometry(110,30,120,30);

	OK_button = new QPushButton(tr("OK"),this);
	OK_button->setGeometry(100,70,50,30);
	connect(OK_button,SIGNAL(clicked()),this,SLOT(OK_clicked()));
	
	Cancel_button = new QPushButton(tr("Cancel"),this);
	Cancel_button->setGeometry(150,70,50,30);
	connect(Cancel_button,SIGNAL(clicked()),this,SLOT(Cancel_clicked()));
}

void NameDialog::OK_clicked()
{
	this->Name = this->Name_edits->text();

	this->close();
}

void NameDialog::Cancel_clicked()
{
	this->isCancel = 1;
	this->close();
}

QString NameDialog::getName()
{
	return this->Name;
}

int NameDialog::isCanceled()
{
	return this->isCancel;
}
