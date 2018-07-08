#include <QDialog>
#include <QString>

class QPushButton;
class QLabel;
class QLineEdit;

class NameDialog : public QDialog
{
	Q_OBJECT

	public : 
		NameDialog();
		
		QString getName();

		int isCanceled();

	private slots:
		void OK_clicked();
		void Cancel_clicked();

	private :
		QString Name;
		int isCancel;

		QLabel *Name_label;
		QLineEdit *Name_edits;

		QPushButton *OK_button;
		QPushButton *Cancel_button;
};
