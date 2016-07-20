#ifndef Window_h
#define Window_h

#include <QWidget>
#include <QGroupBox>
#include <QLayout>
#include <QLineEdit>
#include <QFormLayout>
#include <QCheckBox>
#include <QFileDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QCompleter>
#include <QDirModel>
#include <QFileInfo>
#include <QTabWidget>



class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

    /** Checkboxs **/
    QCheckBox *checkbox1;
        QCheckBox *checkbox1_1;
        QCheckBox *checkbox1_2;
    QCheckBox *checkbox2;

    /** String **/
    QLineEdit *filenameInput;
    QLineEdit *filenameOutput;
    QString folder;
    std::string exten;

    /** Dimension & number of neighbours **/
    unsigned int Dimension;
    unsigned int Neighbours;



public slots:
    /** Open file and folder **/
    void OpenFile();
    void OpenFolder();

    /** Allow to have always one of both checkboxs selected **/
    void IfChecked1();
    void IfChecked2();
    void IfChecked1_1();
    void IfChecked1_2();

    /** Check if all items are good and begin the process **/
    void Confirm();
    /** Manage Box 1_1 if 2D is selected **/
    void ChangeBox1_1();
    /** Get file extension and write it in QLineEdit "File output" **/
    void EditExten();

private:
    /** Checkboxs connect **/
    void CheckboxConnect();
    /** Files connect **/
    void FileConnect();
    /** Other connect **/
    void OthersConnect();



    /** Manage the mainwindow **/
    void ManageWindow();
    QVBoxLayout *mainlayout;

        /** Box 1 : 2D 3D **/
        void ManageBox1();
        QGroupBox *m_Box1;
        QVBoxLayout *layoutbox1;

            /** Box 1_1 : V4 V8 **/
            void ManageBox1_1();
            QGroupBox *m_Box1_1;
            QHBoxLayout *layoutbox1_1;

        /** Box 2 : Files **/
        void ManageBox2();
        QGroupBox *m_Box2;
        QHBoxLayout *layoutbox2;

            /** Box 2_1 : QLineEdit (File input, File output) **/
            void ManageBox2_1();
            QGroupBox *m_Box2_1;
            QFormLayout *layoutbox2_1;

            /** Box 2_2 : Path (Select file, select folder) **/
            void ManageBox2_2();
            QGroupBox *m_Box2_2;
            QPushButton *browse1;
            QPushButton *browse2;
            QVBoxLayout *layoutbox2_2;

        /** Box 3 : Confirm Quit **/
        void ManageBox3();
        QGroupBox *m_Box3;
        QHBoxLayout *layoutbox3;
            QPushButton *confirm;
            QPushButton *cancel;

        /** "Box 4"  Tab : Images display **/
        void ManageBox4();
        QTabWidget tab;
        QGroupBox *display;
        QGroupBox *display2;
        /** Display images when user confirms (only 2D image) **/
        void Display();


};





#endif
