#ifndef Window_cpp
#define Window_cpp

#include "Window.h"
#include "SmoothingFilter.hxx"



Window::Window() : QWidget()
{
    ManageWindow();

    /** Slots **/
    CheckboxConnect();
    FileConnect();
    OthersConnect();


}




void Window::ManageWindow()
{
    mainlayout = new QVBoxLayout();
        ManageBox1();
        ManageBox2();
        ManageBox3();
        ManageBox4();
    setLayout(mainlayout);

}



/** Box 1, vertical layoutbox1 :
 *              *checkbox2 3D
 *              *checkbox1 2D (checked)
 *                  *Box1_1
**/
void Window::ManageBox1()
{
    m_Box1 = new QGroupBox("Dimension");
        mainlayout->addWidget(m_Box1);
        layoutbox1 = new QVBoxLayout;

        checkbox1 = new QCheckBox("2D");
        checkbox2 = new QCheckBox("3D");
        checkbox1->setChecked(true);
        ManageBox1_1();
        ManageBox1_2();

        layoutbox1->addWidget(checkbox2);
        layoutbox1->addWidget(checkbox1);
        layoutbox1->addWidget(m_Box1_1);
        layoutbox1->addWidget(m_Box1_2);
    m_Box1->setLayout(layoutbox1);

}



/** Box 1_1, horizontal layoutbox1_1 :
 *              *checkbox1 V4 (checked)
 *              *checkbox2 V8
**/
void Window::ManageBox1_1()
{   
    m_Box1_1 = new QGroupBox("Neighbours");
        layoutbox1_1 = new QHBoxLayout;

        checkbox1_1 = new QCheckBox("V4");
        checkbox1_1->setChecked(true);
        checkbox1_2 = new QCheckBox("V8");

        layoutbox1_1->addWidget(checkbox1_1);
        layoutbox1_1->addWidget(checkbox1_2);
    m_Box1_1->setLayout(layoutbox1_1);
}



/** Box 1_2, horizontal layoutbox1_2 :
 *              *checkbox1 Slicer
 *              *checkbox2 ITKSnap
**/
void Window::ManageBox1_2()
{
    m_Box1_2 = new QGroupBox("Display 3D image");
        layoutbox1_2 = new QHBoxLayout;

        checkbox2_1 = new QCheckBox("Slicer");
        checkbox2_2 = new QCheckBox("ITKSnap");

        layoutbox1_2->addWidget(checkbox2_1);
        layoutbox1_2->addWidget(checkbox2_2);
        m_Box1_2->hide();
    m_Box1_2->setLayout(layoutbox1_2);
}



/** Box 2, horizontal layoutbox2 :
 *              *Box2_1
 *              *Box2_2
**/
void Window::ManageBox2()
{
    m_Box2 = new QGroupBox("Files");
        mainlayout->addWidget(m_Box2);
        layoutbox2 = new QHBoxLayout();

        ManageBox2_1();
        ManageBox2_2();

        layoutbox2->addWidget(m_Box2_1);
        layoutbox2->addWidget(m_Box2_2);
     m_Box2->setLayout(layoutbox2);

}



/** Box 2_1, form layoutbox2_1 :
 *              *QLineEdit File input
 *              *QLineEdit File ouput
**/
void Window::ManageBox2_1()
{
    m_Box2_1 = new QGroupBox();
        layoutbox2_1 = new QFormLayout;

        filenameInput = new QLineEdit;
        filenameOutput = new QLineEdit;
        filenameInput->setReadOnly(true);

        layoutbox2_1->addRow("File input :", filenameInput);
        layoutbox2_1->addRow("File output  :", filenameOutput);
    m_Box2_1->setLayout(layoutbox2_1);
}



/** Box 2_2, vertical layoutbox2_2 :
 *              *QPushButton Select file
 *              *QPushButton Select folder
**/
void Window::ManageBox2_2()
{
    m_Box2_2 = new QGroupBox();
        layoutbox2_2 = new QVBoxLayout;

        browse1 = new QPushButton("Select file");
        browse2 = new QPushButton("Select folder");
        browse1->setToolTip(".jpeg .jpg .png");
        browse1->setToolTipDuration(2000);

        layoutbox2_2->addWidget(browse1);
        layoutbox2_2->addWidget(browse2);
    m_Box2_2->setLayout(layoutbox2_2);
}



/** Box 3, horizontal layoutbox3 :
 *              *QPushButton Confirm
 *              *QPushButton Quit
**/
void Window::ManageBox3()
{
    m_Box3 = new QGroupBox();
        mainlayout->addWidget(m_Box3);
        layoutbox3 = new QHBoxLayout;

        confirm = new QPushButton("Confirm");
        cancel = new QPushButton("Quit");

        layoutbox3->addWidget(confirm);
        layoutbox3->addWidget(cancel);
    m_Box3->setLayout(layoutbox3);
}



/** "Box 4" Tab :
 *              *QGroupBox display "Original image"
 *              *QGroupBox display2 "Filltered image"
**/
void Window::ManageBox4()
{
    display = new QGroupBox;
    display2 = new QGroupBox;
    display->setMinimumHeight(200);


    tab.addTab(display,"Original image");
    tab.addTab(display2,"Filtered image");
    mainlayout->addWidget(&tab);

    tab.hide();
}



/** Display images (only for 2D image) when user confirm **/
void Window::Display2D()
{

    if(Dimension == 2)
    {
        std::string inputname = "border-image: url(" + filenameInput->text().toStdString() + ") 3 10 3 10";
        std::string outputname = "border-image: url(" + folder.toStdString() + '/' + filenameOutput->text().toStdString() + exten + ") 3 10 3 10";
        tab.show();
        display->setStyleSheet(QString::fromStdString(inputname));
        display2->setStyleSheet(QString::fromStdString(outputname));
    }
    else
    {
        tab.hide();
        this->adjustSize();
    }
}



/** Display images (only for 3D image) when user confirm **/
void Window::Display3D()
{

    if(checkbox2_1->checkState()==2)
    {
        std::string outputname = folder.toStdString() + '/' + filenameOutput->text().toStdString() + exten;
        std::string strcommand = "slicer " + outputname + " 2";
        const char *charcommand = strcommand.c_str();
        popen(charcommand,"r");
    }

    if(checkbox2_2->checkState()==2)
    {
        std::string outputname = folder.toStdString() + '/' + filenameOutput->text().toStdString() + exten;
        std::string strcommand = "itksnap " + outputname;
        const char *charcommand = strcommand.c_str();
        popen(charcommand,"r");
    }
}



/** Checkboxs connect :
 * SLOTS :             SIGNALS :        OBJECTS :
 *   *IfChecked()       *clicked()          *checkboxs
 *   *ChangeBox1_1()    *stateChanged()     *checkbox1
 **/
void Window::CheckboxConnect()
{
    QObject::connect(checkbox1,SIGNAL(clicked(bool)),this,SLOT(IfChecked1()));
    QObject::connect(checkbox1,SIGNAL(stateChanged(int)),this,SLOT(ChangeBox1_1()));
        QObject::connect(checkbox1_1,SIGNAL(clicked(bool)),this,SLOT(IfChecked1_1()));
        QObject::connect(checkbox1_2,SIGNAL(clicked(bool)),this,SLOT(IfChecked1_2()));

    QObject::connect(checkbox2,SIGNAL(clicked(bool)),this,SLOT(IfChecked2()));
        QObject::connect(checkbox2_1,SIGNAL(clicked(bool)),this,SLOT(IfChecked2_1()));
        QObject::connect(checkbox2_2,SIGNAL(clicked(bool)),this,SLOT(IfChecked2_2()));

}



/** Files connect :
 * SLOTS :             SIGNALS :     OBJECTS :
 *   *OpenFile()       *clicked()       *browse1
 *   *OpenFolder()     *clicked()       *browse2
 **/
void Window::FileConnect()
{
    QObject::connect(browse1,SIGNAL(clicked(bool)),this,SLOT(OpenFile()));
    QObject::connect(browse2,SIGNAL(clicked(bool)),this,SLOT(OpenFolder()));
}



/** Checkboxs connect :
 * SLOTS :             SIGNALS :        OBJECTS :
 *   *close()        *clicked()         *cancel
 *   *EditExten()    *textChanged()     *filenameInput
 **/
void Window::OthersConnect()
{

    QObject::connect(cancel,SIGNAL(clicked(bool)),this,SLOT(close()));

    QObject::connect(confirm,SIGNAL(clicked(bool)),this,SLOT(Confirm()));

    QObject::connect(filenameInput,SIGNAL(textChanged(QString)), this, SLOT(EditExten()));

}



/** ********************** SLOTS ************************* **/

/** Change Box1_1 state (hide or show) and change text below browse1 (".nrrd .mha .mhd" or ".jpeg .jpg .png") according to 2D or 3D **/
void Window::ChangeBox1_1()
{
    if(checkbox1->checkState()==0)
    {
        m_Box1_1->hide();
        m_Box1_2->show();
        browse1->setToolTip(".nrrd .mha .mhd");
    }

    if(checkbox1->checkState() == 2)
    {
        m_Box1_2->hide();
        m_Box1_1->show();
        browse1->setToolTip(".jpeg .jpg .png");
    }
}



/** Allow to select a file when we push on "select file" **/
void Window::OpenFile()
{
    QString file;
    if(checkbox1->checkState() == 2)
        file = QFileDialog::getOpenFileName(this,"Select File", QString(), "Images (*.png *.jpg *.jpeg)");
    else
        file = QFileDialog::getOpenFileName(this,"Select File", QString(), "Images (*.nrrd *.mha *.mhd)");

    if(file.isNull())
        QMessageBox::information(this, "File", "You have selected nothing");
    else
    {
        QMessageBox::information(this, "File", "You have selected :\n" + file);
        filenameInput->setText(file);
    }


}



/** Allow to select a folder for output image when we push on "select folder" **/
void Window::OpenFolder()
{
    folder = QFileDialog::getExistingDirectory(this,"Select Folder");
    if(folder.isNull())
        QMessageBox::information(this, "Folder", "You have selected nothing");
    else
        QMessageBox::information(this, "Folder", "You have selected :\n" + folder);
}



/** Allow to add the file extension once an output image has been chosen **/
void Window::EditExten()

{
    exten = SetExten(filenameInput->text().toStdString());
    layoutbox2_1->labelForField(filenameOutput)->deleteLater();
    layoutbox2_1->removeWidget(filenameOutput);
    layoutbox2_1->insertRow(1,"File output : (" + QString::fromStdString(exten) + ')', filenameOutput);

}



/** IfChecked allow to to have always one of both checkboxs selected **/
void Window::IfChecked1()
{

    if(0==checkbox1->checkState() || checkbox2->checkState()==2){
        checkbox1->setChecked(true);
        checkbox2->setChecked(false);
    }
}

void Window::IfChecked2()
{
    if(0==checkbox2->checkState() || checkbox1->checkState()==2){
        checkbox2->setChecked(true);
        checkbox1->setChecked(false);
    }
}


void Window::IfChecked1_1()
{

    if(0==checkbox1_1->checkState() || checkbox1_2->checkState()==2){
        checkbox1_1->setChecked(true);
        checkbox1_2->setChecked(false);
    }
}

void Window::IfChecked1_2()
{
    if(0==checkbox1_2->checkState() || checkbox1_1->checkState()==2){
        checkbox1_2->setChecked(true);
        checkbox1_1->setChecked(false);
    }
}

void Window::IfChecked2_1()
{

    if(2==checkbox2_1->checkState() || checkbox2_2->checkState()==2){
        checkbox2_1->setChecked(true);
        checkbox2_2->setChecked(false);
    }
}

void Window::IfChecked2_2()
{
    if(2==checkbox2_2->checkState() || checkbox2_1->checkState()==2){
        checkbox2_2->setChecked(true);
        checkbox2_1->setChecked(false);
    }
}



/** Check all items are good when we push on confirm **/
void Window::Confirm()
{

    //We check if file name input is full
    if(filenameInput->text().isEmpty() == true)
    {
        QMessageBox::critical(this, "Warning !", "You must select an image");
        return;
    }
    //We check if foler name is full
    else if(folder.isNull() == true)
    {
        QMessageBox::critical(this,"Warning !","You must select a folder");
        return;
    }
    //We check if file name output is full
    else if(filenameOutput->text().isEmpty() == true)
    {
        QMessageBox::critical(this,"Warning !","You must select an output name");
        return;
    }
    //We check if file extension match with dimension
    else if((exten == ".nrrd" || exten == ".mha" || exten == ".mhd") && checkbox1->checkState()==2)
    {
        QMessageBox::critical(this,"Warning !","Mismatch between file and dimension");
        return;
    }
    else if((exten == ".jpeg" || exten == ".png" || exten == ".jpg") && checkbox2->checkState()==2)
    {
        QMessageBox::critical(this,"Warning !","Mismatch between file and dimension");
        return;
    }
    else
    {
        //Dimension and Neighbours setting, according to checkboxs state
        if(checkbox1->checkState()==0)
            Dimension = 3;
        else
            Dimension = 2;

        if(checkbox1_2->checkState()==0 || checkbox1->checkState()==0)
            Neighbours = 4;
        else
            Neighbours = 8;



        //Filter processing
        TypeImageFilterDefine(Dimension,filenameInput->text().toStdString(),Neighbours,filenameOutput->text().toStdString(),folder.toStdString());

        //Display results
        if(Dimension == 2)
            Display2D();
        else
            Display3D();
    }

}


#endif
