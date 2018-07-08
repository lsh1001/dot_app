#include <QDialog>

class QPushButton;
class QLabel;
class QLineEdit;

class RectDialog : public QDialog
{
	Q_OBJECT

	public : 
		RectDialog();
		
		int getXposition();
		int getYposition();

		int getXsize();
		int getYsize();

		int getBW();
		int isCanceled();

	private slots:
		void OK_clicked();
		void Cancel_clicked();

	private :
		int Xposition;
		int Yposition;

		int Xsize;
		int Ysize;

		int BW;
		int isCancel;

		QLabel *Xposition_label;
		QLineEdit *Xposition_edits;

		QLabel *Yposition_label;
		QLineEdit *Yposition_edits;
	
		QLabel *Xsize_label;
		QLineEdit *Xsize_edits;

		QLabel *Ysize_label;
		QLineEdit *Ysize_edits;
	
		QLabel *BW_label;
		QLineEdit *BW_edits;

		QPushButton *OK_button;
		QPushButton *Cancel_button;
};
