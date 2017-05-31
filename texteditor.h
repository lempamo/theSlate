#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QApplication>
#include <QFontDatabase>
#include "tabbutton.h"

class TabButton;

class TextEditor : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEditor(QWidget *parent = nullptr);

    QString filename();
    bool isEdited();
signals:

public slots:
    TabButton* getTabButton();
    void setActive(bool active);

private:
    TabButton* button;
    bool active;
    bool edited = false;
    QString fn;
};

#endif // TEXTEDITOR_H