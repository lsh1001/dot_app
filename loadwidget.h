#include <QDialog>

class QPushButton;
class QLabel;
class QLineEdit;

class LoadDialog : public QDialog
{
	Q_OBJECT

	public : 
		LoadDialog();
		
		int getXposition();
		int getYposition();

		int getXsize();
		int getYsize();

		int isCanceled();

	private slots:
		void OK_clicked();
		void Cancel_clicked();

	private :
		int Xposition;
		int Yposition;

		int Xsize;
		int Ysize;

		int isCancel;

		QLabel *Xposition_label;
		QLineEdit *Xposition_edits;

		QLabel *Yposition_label;
		QLineEdit *Yposition_edits;
	
		QLabel *Xsize_label;
		QLineEdit *Xsize_edits;

		QLabel *Ysize_label;
		QLineEdit *Ysize_edits;

		QPushButton *OK_button;
		QPushButton *Cancel_button;
};
