#include <QWidget>

#define ROW 24
#define COLUMN 24
#define BOX_SIZE 30
#define NAME_SIZE 32
#define SIZE_STRING 7

class QPushButton;
class QLabel;

struct XYsize
{
	int x;
	int y;
};

class MyWidget : public QWidget
{
	Q_OBJECT

	public :
		MyWidget();
		
		int charToDec(char ch);
		void binToByte(int X,int Y,int Xsize,int Ysize);
		void byteToBin(int *load_array,int X,int Y,int Xsize,int Ysize);
		XYsize getXYSize(char *size);

	private slots :
		void bit_clicked();

		void rect_clicked();
		void sym_clicked();
		void rshift_clicked();
		void lshift_clicked();
		void dshift_clicked();
		void ushift_clicked();
		void save_clicked();
		void save_as_clicked();
		void load_clicked();
		void load_as_clicked();
		void clear_clicked();
		void reverse_clicked();
		
		void save_tmp_clicked();
		void load_tmp_clicked();

	private : 
		QPushButton *button_array[ROW][COLUMN];

		QPushButton *rect_button;
		QPushButton *sym_button;
		QPushButton *rshift_button;
		QPushButton *lshift_button;
		QPushButton *dshift_button;
		QPushButton *ushift_button;

		QPushButton *save_button;
		QPushButton *save_as_button;
		QPushButton *load_button;
		QPushButton *load_as_button;
		QPushButton *clear_button;
		QPushButton *reverse_button;
		QPushButton *exit_button;

		QLabel *position_label;

		bool clicked[ROW][COLUMN];
		int byte_array[ROW*COLUMN/4];
};


