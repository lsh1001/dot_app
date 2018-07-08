#include <QtWidgets>
#include <mywidget.h>
#include <loadwidget.h>
#include <namewidget.h>
#include <rectwidget.h>

#include <math.h>

#include <fstream>
#include <iostream>

MyWidget::MyWidget()
{
	int i,j;

	setFixedSize(COLUMN*BOX_SIZE,ROW*BOX_SIZE+50);

	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COLUMN;j++)
		{
			clicked[i][j] = 0;
			button_array[i][j] = new QPushButton(tr(""),this);
			button_array[i][j]->setGeometry(BOX_SIZE*j,BOX_SIZE*i,BOX_SIZE,BOX_SIZE);
			button_array[i][j]->setStyleSheet(QString("QPushButton {background-color: white;}"));
			connect(button_array[i][j],SIGNAL(clicked()),this,SLOT(bit_clicked()));
		}
	}

	if(COLUMN>8)
	{
		rect_button = new QPushButton(tr("set rect"),this);
		rect_button->setGeometry(0,ROW*BOX_SIZE+10,70,30);
		connect(rect_button,SIGNAL(clicked()),this,SLOT(rect_clicked()));

		sym_button = new QPushButton(tr("y_sym"),this);
		sym_button->setGeometry(70,ROW*BOX_SIZE+10,70,30);
		connect(sym_button,SIGNAL(clicked()),this,SLOT(sym_clicked()));
		
		rshift_button = new QPushButton(tr("R"),this);
		rshift_button->setGeometry(140,ROW*BOX_SIZE+10,30,30);
		connect(rshift_button,SIGNAL(clicked()),this,SLOT(rshift_clicked()));
		
		lshift_button = new QPushButton(tr("L"),this);
		lshift_button->setGeometry(170,ROW*BOX_SIZE+10,30,30);
		connect(lshift_button,SIGNAL(clicked()),this,SLOT(lshift_clicked()));
		
		dshift_button = new QPushButton(tr("D"),this);
		dshift_button->setGeometry(200,ROW*BOX_SIZE+10,30,30);
		connect(dshift_button,SIGNAL(clicked()),this,SLOT(dshift_clicked()));
		
		ushift_button = new QPushButton(tr("U"),this);
		ushift_button->setGeometry(230,ROW*BOX_SIZE+10,30,30);
		connect(ushift_button,SIGNAL(clicked()),this,SLOT(ushift_clicked()));
	}

	clear_button = new QPushButton(tr("clear"),this);
	clear_button->setGeometry(COLUMN*BOX_SIZE-350,ROW*BOX_SIZE+10,50,30);
	connect(clear_button,SIGNAL(clicked()),this,SLOT(clear_clicked()));

	reverse_button = new QPushButton(tr("reverse"),this);
	reverse_button->setGeometry(COLUMN*BOX_SIZE-300,ROW*BOX_SIZE+10,50,30);
	connect(reverse_button,SIGNAL(clicked()),this,SLOT(reverse_clicked()));

	save_button = new QPushButton(tr("save"),this);
	save_button->setGeometry(COLUMN*BOX_SIZE-250,ROW*BOX_SIZE+10,50,30);
	connect(save_button,SIGNAL(clicked()),this,SLOT(save_clicked()));
	
	save_as_button = new QPushButton(tr("save as"),this);
	save_as_button->setGeometry(COLUMN*BOX_SIZE-200,ROW*BOX_SIZE+10,50,30);
	connect(save_as_button,SIGNAL(clicked()),this,SLOT(save_as_clicked()));
	
	load_button = new QPushButton(tr("load"),this);
	load_button->setGeometry(COLUMN*BOX_SIZE-150,ROW*BOX_SIZE+10,50,30);
	connect(load_button,SIGNAL(clicked()),this,SLOT(load_clicked()));
	
	load_as_button = new QPushButton(tr("load as"),this);
	load_as_button->setGeometry(COLUMN*BOX_SIZE-100,ROW*BOX_SIZE+10,50,30);
	connect(load_as_button,SIGNAL(clicked()),this,SLOT(load_as_clicked()));
	
	exit_button = new QPushButton(tr("exit"),this);
	exit_button->setGeometry(COLUMN*BOX_SIZE-50,ROW*BOX_SIZE+10,50,30);
	connect(exit_button,SIGNAL(clicked()),qApp,SLOT(quit()));

	position_label = new QLabel("",this);
	position_label->setGeometry(COLUMN*BOX_SIZE-410,ROW*BOX_SIZE+10,60,30);
}

void MyWidget::bit_clicked()
{
	int i,j;
	int flag = 0;
	QString position;

	QPushButton *tmp = (QPushButton*)sender();

	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COLUMN;j++)
		{
			if(button_array[i][j]==tmp)
			{
				flag = 1;
				break;
			}	
		}	
		if(flag)
			break;
	}	
	
	std::cout<<"( "<<std::dec<<i<<", "<<std::dec<<j<<" ) "<<clicked[i][j]<<std::endl;
	position = QString("( %1, %2 )").arg(j).arg(i);
	position_label->setText(position);

	if(!clicked[i][j])
	{
		clicked[i][j] = 1;
		tmp->setStyleSheet(QString("QPushButton {background-color: black;}"));
	}
	else
	{
		clicked[i][j] = 0;
		tmp->setStyleSheet(QString("QPushButton {background-color: white;}"));
	}
}

void MyWidget::rect_clicked()
{
	int i,j;
	int Xposition,Yposition,Xsize,Ysize,BW;

	RectDialog *rdialog = new RectDialog();
	rdialog->exec();

	if(rdialog->isCanceled())
		return;
	
	Xposition = rdialog->getXposition();
	Yposition = rdialog->getYposition();
	Xsize = rdialog->getXsize();
	Ysize = rdialog->getYsize();
	BW = rdialog->getBW();

	for(i=Yposition;i<Yposition+Ysize;i++)
	{
		for(j=Xposition;j<Xposition+Xsize;j++)
		{
			if(BW)
			{
				clicked[i][j] = 1;
				button_array[i][j]->setStyleSheet(QString("QPushButton {background-color: black;}"));
			}
			else
			{
				clicked[i][j] = 0;
				button_array[i][j]->setStyleSheet(QString("QPushButton {background-color: white;}"));
			}	
		}
	}
}

void MyWidget::sym_clicked()
{
	bool tmp[ROW][COLUMN];
	int i,j;

	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COLUMN;j++)
		{
			tmp[i][j] = clicked[i][j];
			clicked[i][j] = 0;
			button_array[i][j]->setStyleSheet(QString("QPushButton {background-color: white;}"));
		}
	}

	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COLUMN;j++)
		{
			if(tmp[i][j])
			{
				clicked[i][COLUMN-j-1] = 1;
				button_array[i][COLUMN-j-1]->setStyleSheet(QString("QPushButton {background-color: black;}"));
			}
		}
	}
}

void MyWidget::rshift_clicked()
{
	bool tmp[ROW][COLUMN];
	int i,j;

	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COLUMN;j++)
		{
			tmp[i][j] = clicked[i][j];
			clicked[i][j] = 0;
			button_array[i][j]->setStyleSheet(QString("QPushButton {background-color: white;}"));
		}
	}

	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COLUMN;j++)
		{
			if(j == COLUMN-1 && tmp[i][j])
			{
				clicked[i][0] = 1;
				button_array[i][0]->setStyleSheet(QString("QPushButton {background-color: black;}"));
				continue;
			}

			if(tmp[i][j])
			{
				clicked[i][j+1] = 1;
				button_array[i][j+1]->setStyleSheet(QString("QPushButton {background-color: black;}"));
			}
		}
	}
}

void MyWidget::lshift_clicked()
{
	bool tmp[ROW][COLUMN];
	int i,j;

	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COLUMN;j++)
		{
			tmp[i][j] = clicked[i][j];
			clicked[i][j] = 0;
			button_array[i][j]->setStyleSheet(QString("QPushButton {background-color: white;}"));
		}
	}

	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COLUMN;j++)
		{
			if(j == 0 && tmp[i][j])
			{
				clicked[i][COLUMN-1] = 1;
				button_array[i][COLUMN-1]->setStyleSheet(QString("QPushButton {background-color: black;}"));
				continue;
			}

			if(tmp[i][j])
			{
				clicked[i][j-1] = 1;
				button_array[i][j-1]->setStyleSheet(QString("QPushButton {background-color: black;}"));
			}
		}
	}
}

void MyWidget::dshift_clicked()
{
	bool tmp[ROW][COLUMN];
	int i,j;

	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COLUMN;j++)
		{
			tmp[i][j] = clicked[i][j];
			clicked[i][j] = 0;
			button_array[i][j]->setStyleSheet(QString("QPushButton {background-color: white;}"));
		}
	}

	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COLUMN;j++)
		{
			if(i == ROW-1 && tmp[i][j])
			{
				clicked[0][j] = 1;
				button_array[0][j]->setStyleSheet(QString("QPushButton {background-color: black;}"));
				continue;
			}

			if(tmp[i][j])
			{
				clicked[i+1][j] = 1;
				button_array[i+1][j]->setStyleSheet(QString("QPushButton {background-color: black;}"));
			}
		}
	}
}

void MyWidget::ushift_clicked()
{
	bool tmp[ROW][COLUMN];
	int i,j;

	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COLUMN;j++)
		{
			tmp[i][j] = clicked[i][j];
			clicked[i][j] = 0;
			button_array[i][j]->setStyleSheet(QString("QPushButton {background-color: white;}"));
		}
	}

	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COLUMN;j++)
		{
			if(i == 0 && tmp[i][j])
			{
				clicked[ROW-1][j] = 1;
				button_array[ROW-1][j]->setStyleSheet(QString("QPushButton {background-color: black;}"));
				continue;
			}

			if(tmp[i][j])
			{
				clicked[i-1][j] = 1;
				button_array[i-1][j]->setStyleSheet(QString("QPushButton {background-color: black;}"));
			}
		}
	}
}

void MyWidget::clear_clicked()
{
	int i,j;

	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COLUMN;j++)
		{
			clicked[i][j] = 0;
			button_array[i][j]->setStyleSheet(QString("QPushButton {background-color: white;}"));
		}
	}
}

void MyWidget::reverse_clicked()
{
	int i,j;

	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COLUMN;j++)
		{
			if(clicked[i][j])
			{	
				clicked[i][j] = 0;
				button_array[i][j]->setStyleSheet(QString("QPushButton {background-color: white;}"));
			}
			else
			{
				clicked[i][j] = 1;
				button_array[i][j]->setStyleSheet(QString("QPushButton {background-color: black;}"));
			}
		}
	}
}

void MyWidget::save_tmp_clicked()
{
	int i;
	char file_name[NAME_SIZE];
	std::ofstream fout;

	NameDialog *ndialog = new NameDialog();
	ndialog->exec();

	strcpy(file_name, ndialog->getName().toStdString().c_str());

	fout.open(file_name);
	
	if(!fout.is_open())
		return;
	
	binToByte(0,0,COLUMN,ROW);
	
	for(i=0;i<ROW*COLUMN/4;i++)
	{
		fout<<std::hex<<byte_array[i];
	}
	fout.close();
}

void MyWidget::save_clicked()
{
	int i;
	char file_name[NAME_SIZE];
	std::ofstream fout;
	
	NameDialog *ndialog = new NameDialog();
	ndialog->exec();

	if(ndialog->isCanceled())
		return;

	strcpy(file_name, ndialog->getName().toStdString().c_str());

	fout.open(file_name);
	
	if(!fout.is_open())
		return;

	binToByte(0,0,COLUMN,ROW);

	fout<<COLUMN<<"_"<<ROW<<std::endl;

	for(i=0;i<ROW*COLUMN/4;i+=2)
	{
		if((i>0)&&(i%(COLUMN/2)==0))
			fout<<std::endl;

		fout<<"0x"<<std::hex<<byte_array[i]<<byte_array[i+1];

		if(i!=ROW*COLUMN/4-2)
			fout<<", ";
	}
	fout.close();
}

void MyWidget::save_as_clicked()
{
	int i;
	int Xposition,Yposition,Xsize,Ysize;
	char file_name[NAME_SIZE];
	std::ofstream fout;
	
	NameDialog *ndialog = new NameDialog();
	ndialog->exec();

	if(ndialog->isCanceled())
		return;

	strcpy(file_name, ndialog->getName().toStdString().c_str());

	fout.open(file_name);
	
	if(!fout.is_open())
		return;

	LoadDialog *ldialog = new LoadDialog();
	ldialog->exec();
	
	if(ldialog->isCanceled())
		return;
	
	Xposition = ldialog->getXposition();
	Yposition = ldialog->getYposition();
	Xsize = ldialog->getXsize();
	Ysize = ldialog->getYsize();

	binToByte(Xposition,Yposition,Xsize,Ysize);
	
	fout<<Xsize<<"_"<<Ysize<<std::endl;

	for(i=0;i<Ysize*Xsize/4;i+=2)
	{
		if((i>0)&&(i%(Xsize/2)==0))
			fout<<std::endl;

		fout<<"0x"<<std::hex<<byte_array[i]<<byte_array[i+1];

		if(i!=Ysize*Xsize/4-2)
			fout<<", ";
	}
	fout.close();
}

void MyWidget::load_tmp_clicked()
{
	char ch;
	char file_name[NAME_SIZE];
	int Xposition,Yposition,Xsize,Ysize;
	int position = 0;
	int load_array[ROW*COLUMN/4];
	std::ifstream fin;

	NameDialog *ndialog = new NameDialog();
	ndialog->exec();

	strcpy(file_name, ndialog->getName().toStdString().c_str());

	fin.open(file_name);
	if(!fin.is_open())
		return;

	LoadDialog *ldialog = new LoadDialog();
	ldialog->exec();
	
	Xposition = ldialog->getXposition();
	Yposition = ldialog->getYposition();
	Xsize = ldialog->getXsize();
	Ysize = ldialog->getYsize();

	while(fin.get(ch))
	{
		load_array[position++] = charToDec(ch);
	}

	byteToBin(load_array,Xposition,Yposition,Xsize,Ysize);
	
	fin.close();
}

void MyWidget::load_clicked()
{
	char ch;
	char file_name[NAME_SIZE];
	char size[SIZE_STRING];
	XYsize xy;
	int Xposition,Yposition,Xsize,Ysize;
	int position = 0;
	int load_array[ROW*COLUMN/4];
	std::ifstream fin;

	NameDialog *ndialog = new NameDialog();
	ndialog->exec();

	if(ndialog->isCanceled())
		return;

	strcpy(file_name, ndialog->getName().toStdString().c_str());

	fin.open(file_name);
	if(!fin.is_open())
		return;

	LoadDialog *ldialog = new LoadDialog();
	ldialog->exec();
	
	if(ldialog->isCanceled())
		return;

	Xposition = ldialog->getXposition();
	Yposition = ldialog->getYposition();

	fin.getline(size,SIZE_STRING);
	xy = getXYSize(size);
	Xsize = xy.x;
	Ysize = xy.y;

	std::cout<<Xsize<<", "<<Ysize<<std::endl;

	while(fin.get(ch))
	{
		if((ch>'0' && ch<='9') || (ch>='A' && ch<='F') || (ch>='a' && ch<='f'))
			load_array[position++] = charToDec(ch);
		else if(ch == '0')
		{
			if(!fin.get(ch))
			{
				load_array[position++] = charToDec('0');
				break;
			}

			if(ch == 'x')
				continue;
			else
			{
				load_array[position++] = charToDec('0');
				
				if((ch>='0' && ch<='9') || (ch>='A' && ch<='F') || (ch>='a' && ch<='f'))
					load_array[position++] = charToDec(ch);
			}
		}
		else
			continue;
	}

	for(int k=0;k<Ysize*Xsize/4;k++)
		std::cout<<std::hex<<load_array[k];
	std::cout<<std::endl;

	byteToBin(load_array,Xposition,Yposition,Xsize,Ysize);
	
	fin.close();
}

void MyWidget::load_as_clicked()
{
	char ch;
	char file_name[NAME_SIZE];
	char size[SIZE_STRING];
	int Xposition,Yposition,Xsize,Ysize;
	int position = 0;
	int load_array[ROW*COLUMN/4];
	std::ifstream fin;

	NameDialog *ndialog = new NameDialog();
	ndialog->exec();

	if(ndialog->isCanceled())
		return;

	strcpy(file_name, ndialog->getName().toStdString().c_str());

	fin.open(file_name);
	if(!fin.is_open())
		return;

	LoadDialog *ldialog = new LoadDialog();
	ldialog->exec();
	
	if(ldialog->isCanceled())
		return;

	Xposition = ldialog->getXposition();
	Yposition = ldialog->getYposition();
	Xsize = ldialog->getXsize();
	Ysize = ldialog->getYsize();

	fin.getline(size,SIZE_STRING);

	while(fin.get(ch))
	{
		if((ch>'0' && ch<='9') || (ch>='A' && ch<='F') || (ch>='a' && ch<='f'))
			load_array[position++] = charToDec(ch);
		else if(ch == '0')
		{
			if(!fin.get(ch))
			{
				load_array[position++] = charToDec('0');
				break;
			}

			if(ch == 'x')
				continue;
			else
			{
				load_array[position++] = charToDec('0');
				
				if((ch>='0' && ch<='9') || (ch>='A' && ch<='F') || (ch>='a' && ch<='f'))
					load_array[position++] = charToDec(ch);
			}
		}
		else
			continue;
	}

	for(int k=0;k<Ysize*Xsize/4;k++)
		std::cout<<std::hex<<load_array[k];
	std::cout<<std::endl;

	byteToBin(load_array,Xposition,Yposition,Xsize,Ysize);
	
	fin.close();
}

int MyWidget::charToDec(char ch)
{
	int dec;

	if(ch<'A')
		dec = ch-'0';
	else if(ch>='A' && ch<'a')
		dec = ch-'A'+10;
	else
		dec = ch-'a'+10;
	
	return dec;
}

void MyWidget::binToByte(int X,int Y,int Xsize,int Ysize)
{
	int i,j;
	int position = 0;
	int bit_4 = 0;

	for(i=Y;i<Y+Ysize;i++)
	{
		for(j=X;j<X+Xsize;j++)
		{
			switch(j%4)
			{
				case 0:
					bit_4 += clicked[i][j] * 8;
					break;
				case 1:
					bit_4 += clicked[i][j] * 4;
					break;
				case 2:
					bit_4 += clicked[i][j] * 2;
					break;
				case 3:
					bit_4 += clicked[i][j];
					byte_array[position++] = bit_4;
					bit_4 = 0;
					break;
				default :
					break;
			}
		}
	}
}

void MyWidget::byteToBin(int *load_array, int X, int Y,int Xsize, int Ysize)
{
	int i,j;
	int position = 0;
	int byte_cnt = 0;
	
	for(i=Y;i<Y+Ysize;i++)
	{
		for(j=X;j<X+Xsize;j++)
		{
			switch(byte_cnt++%4)
			{
				case 0:
					clicked[i][j] = (((load_array[position])&8)==8);
					break;
				case 1:
					clicked[i][j] = (((load_array[position])&4)==4);
					break;
				case 2:
					clicked[i][j] = (((load_array[position])&2)==2);
					break;
				case 3:
					clicked[i][j] = (((load_array[position++])&1)==1);
					break;
				default :
					break;
			}
			if(clicked[i][j])
				button_array[i][j]->setStyleSheet(QString("QPushButton {background-color: black;}"));
		}
	}
}

XYsize MyWidget::getXYSize(char *size)
{
	XYsize xy;
	int w = 0;
	int h = 0;
	int	index,length;

	length = strlen(size)-1;
	for(index=0;index<length;index++)
	{
		if(size[index] == '_')
			break;
	}

	std::cout<<length<<", "<<index<<std::endl;

	for(int i=0;i<index;i++)
		w += (size[i]-'0')*(pow(10,(index-i-1)));
	
	for(int j=0;j<length-index;j++)
		h += (size[index+j+1]-'0')*(pow(10,length-index-j-1));

	xy.x = w;
	xy.y = h;

	return xy;
}


