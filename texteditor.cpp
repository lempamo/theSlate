#include "texteditor.h"

TextEditor::TextEditor(QWidget *parent) : QTextEdit(parent)
{
    button = new TabButton(this);
    button->setText("New Document");
    this->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));

    connect(this, &TextEditor::textChanged, [=] {
        edited = true;
    });
}

TabButton* TextEditor::getTabButton() {
    return button;
}

void TextEditor::setActive(bool active) {
    button->setActive(active);
    this->active = active;
}

QString TextEditor::filename() {
    return fn;
}

bool TextEditor::isEdited() {
    return edited;
}