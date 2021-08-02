#pragma once

#include <QtWidgets/QWidget>
#include "ui_ToDoApps.h"
#include <QDate>
#include <QDir>

class ToDoApps : public QWidget
{
    Q_OBJECT

public:
    ToDoApps(QWidget *parent = Q_NULLPTR);

private:
    Ui::ToDoAppsClass ui;

public:
    void initStylesheet();
    void createNewTask(QString taskName, QString date);

public slots:
    void SlotAddNewTask();
    void SlotDeleteTask();

signals:
    void SignalAddNewTask(QString taskName, QString date); // incase you wonder how to create custom signal. Useful when you want to call this signal in other classes/widgets

};
