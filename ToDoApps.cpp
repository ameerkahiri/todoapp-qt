#include "ToDoApps.h"

ToDoApps::ToDoApps(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    // Set stylesheet
    initStylesheet();

    // Connect the add new task button
    connect(ui.AddNewBtn, SIGNAL(clicked()), this, SLOT(SlotAddNewTask()));

    ui.NewTask->deleteLater(); // this is just for reference before i did the code

    ui.NewTaskLineEdit->setText("Today, I want to...");
    ui.NewDateText->setText(QDate::currentDate().toString());

}


void ToDoApps::initStylesheet() {

    // You have to create the css file first in the main project directory

    // Get the css file
    QFile style("style_Generic.css");
    bool ok = style.open(QFile::ReadOnly);
    QString s = QString::fromLatin1(style.readAll());

    setStyleSheet(s);

}


void ToDoApps::SlotAddNewTask() {

    // Get the line edit text
    QString taskName = ui.NewTaskLineEdit->text();
    // Get current date
    QString date = QDate::currentDate().toString();

    createNewTask(taskName, date);

    // This is how to trigger signal
    //emit SignalAddNewTask(taskName, date);
    
    // Then in other class/widget connect it like
    //ToDoApps* obj;
    //connect(obj, SIGNAL(SignalAddNewTask(QString, QString)), this, SLOT(SlotToSomethingInThatClass()));

}


// This is the part where widget created using code / the reference is in .ui file
void ToDoApps::createNewTask(QString taskName, QString date) {

    {
        // The hierarchy of this widget will be like this
        /*
            + Hframe (Frame)
                + Vframe (Frame)
                    + titlelabel (Label)
                    + tasklabel (Label)
                    + datelabel (Label)
                + spacer (Horizontal spacer)
                + deleteBtn (PushButton)
        */
    }

    // Get the parent widget which the widget created to be child in
    QVBoxLayout* vMainLayout = qobject_cast<QVBoxLayout*>(ui.AllNewTasksContents->layout());

    // Create Frame for the main widget container
    QFrame* Hframe = new QFrame();
    Hframe->setFrameStyle(QFrame::StyledPanel);
    // Create Horizontal Box Layout as the Frame layout and also for easily add widget inside it
    // This is like a virtual layout. It doesn't added into ui as a ui things bcos it is just a layout.
    QHBoxLayout* newTask = new QHBoxLayout(Hframe);
    Hframe->setLayout(newTask);

    // Create Frame for the details container; task title, task name, task date created
    QFrame* Vframe = new QFrame();
    QVBoxLayout* taskDetails = new QVBoxLayout(Vframe);
    Vframe->setLayout(taskDetails);

    QLabel* titlelabel = new QLabel(tr("Task #%1").arg(vMainLayout->count())); // task title
    taskDetails->addWidget(titlelabel);
    QLabel* tasklabel = new QLabel(taskName); // task name
    taskDetails->addWidget(tasklabel);
    QLabel* datelabel = new QLabel(date); // task date created
    taskDetails->addWidget(datelabel);

    // Insert the task details frame inside main task box layout
    newTask->insertWidget(0, Vframe);

    // Insert horizontal spacer in between Vframe and deleteBtn
    QSpacerItem* spacer = new QSpacerItem(100, 100, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
    newTask->insertSpacerItem(1, spacer);

    // Insert delete button
    QPushButton* deleteBtn = new QPushButton("Delete");
    newTask->insertWidget(2, deleteBtn);

    // Store the current duplicated widget to the delete button property for easy reference
    // This is a useful function if you want to reference any widgets to the specific button
    deleteBtn->setProperty("CurrentTask", QVariant(QVariant::fromValue<QFrame*>(Hframe)));

    // Insert into parent ui frame
    vMainLayout->insertWidget(vMainLayout->count()-1, Hframe);

    // Connect the delete button
    connect(deleteBtn, SIGNAL(clicked()), this, SLOT(SlotDeleteTask()));


    // This part is how you can set stylesheet in code
    {
        QVector<QString> colors = { "rgba(66, 165, 245,1.0)", "rgba(41, 182, 246,1.0)", "rgba(38, 198, 218,1.0)", "rgba(38, 166, 154,1.0)", "rgba(102, 187, 106,1.0)", "rgba(156, 204, 101,1.0)", "rgba(212, 225, 87,1.0)", "rgba(255, 238, 88,1.0)", "rgba(255, 202, 40,1.0)", "rgba(255, 167, 38,1.0)"};
        int randomVal = (((rand() % 50) % 100) % (colors.size() - 1));

        Hframe->setObjectName("NewTask");
        Hframe->setStyleSheet("#NewTask { border-radius: 10px; border: 1px solid black; background-color: " + colors[randomVal] + "; }");

        tasklabel->setObjectName("TaskName");
        tasklabel->setStyleSheet("#TaskName { font: bold 11pt black 'Verdana'; }");

        deleteBtn->setObjectName("DeleteBtn");
        deleteBtn->setStyleSheet("#DeleteBtn { color: white; background-color: #ff2264; border-color: #b91043; }  #DeleteBtn:hover{ background-color: #b91043; border-color: #ff2264; }");
    }

}


void ToDoApps::SlotDeleteTask() {

    // Get the sender widget
    QPushButton* fromButton = (QPushButton*)sender();

    // Get the widget referenced in the property
    QVariant var;
    var = fromButton->property("CurrentTask");
    QFrame* taskHBox = qvariant_cast<QFrame*>(var);

    taskHBox->deleteLater();
    delete taskHBox;

}