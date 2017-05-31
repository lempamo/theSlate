#include "syntaxhighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    //Set up colours

    keywordFormat.setForeground(QColor(200, 200, 0));
    classFormat.setForeground(Qt::darkMagenta);
    commentFormat.setForeground(Qt::gray);
    quotationFormat.setForeground(Qt::red);
    functionFormat.setForeground(Qt::blue);

    controlFormat.setForeground(Qt::blue);
    controlFormat.setFontWeight(500);
}

void SyntaxHighlighter::highlightBlock(const QString &text) {
    for (HighlightingRule rule : highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}

void SyntaxHighlighter::setCodeType(codeType type) {
    highlightingRules.clear();

    HighlightingRule rule;
    switch (type) {
        case cpp: {
            //Keywords
            QStringList keywordPatterns;
            keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                            << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                            << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                            << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                            << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                            << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                            << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                            << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                            << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                            << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bbool\\b";
            for (QString pattern : keywordPatterns) {
                rule.pattern = QRegularExpression(pattern);
                rule.format = keywordFormat;
                highlightingRules.append(rule);
            }

            //Controls
            QStringList controlPatterns;
            controlPatterns << "\\bif\\b" << "\\bwhile\\b" << "\\bdo\\b"
                            << "\\bfor\\b" << "\\bswtich\\b" << "\\bcase\\b"
                            << "\\belse\\b";
            for (QString pattern : controlPatterns) {
                rule.pattern = QRegularExpression(pattern);
                rule.format = controlFormat;
                highlightingRules.append(rule);
            }

            //Class
            rule.pattern = QRegularExpression("\\b[A-Za-z]+(?=(\\.))\\b");
            rule.format = classFormat;
            highlightingRules.append(rule);

            //String
            rule.pattern = QRegularExpression("\".*\"");
            rule.format = quotationFormat;
            highlightingRules.append(rule);

            //Function
            rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
            rule.format = functionFormat;
            highlightingRules.append(rule);

            //Comments
            rule.pattern = QRegularExpression("\\/\\*(\\w|\\s)*\\*\\/");
            rule.format = commentFormat;
            highlightingRules.append(rule);

            rule.pattern = QRegularExpression("\\/\\/(.)*");
            highlightingRules.append(rule);

            commentStartExpression = QRegularExpression("/\\*");
            commentEndExpression = QRegularExpression("\\*/");
            break;
        }
        case js: {
            //Keywords
            QStringList keywordPatterns;
            keywordPatterns << "\\bvar\\b" << "\\blet\\b" << "\\bfunction\\b";
            for (QString pattern : keywordPatterns) {
                rule.pattern = QRegularExpression(pattern);
                rule.format = keywordFormat;
                highlightingRules.append(rule);
            }

            //Controls
            QStringList controlPatterns;
            controlPatterns << "\\bif\\b" << "\\bwhile\\b" << "\\bdo\\b"
                            << "\\bfor\\b" << "\\bswtich\\b" << "\\bcase\\b"
                            << "\\bof\\b" << "\\belse\\b";
            for (QString pattern : controlPatterns) {
                rule.pattern = QRegularExpression(pattern);
                rule.format = controlFormat;
                highlightingRules.append(rule);
            }

            //String
            rule.pattern = QRegularExpression("\".*\"");
            rule.format = quotationFormat;
            highlightingRules.append(rule);

            //Function
            rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
            rule.format = functionFormat;
            highlightingRules.append(rule);

            //Comments
            rule.pattern = QRegularExpression("\\/\\*(\\w|\\s)*\\*\\/");
            rule.format = commentFormat;
            highlightingRules.append(rule);

            rule.pattern = QRegularExpression("\\/\\/(.)*");
            highlightingRules.append(rule);

            commentStartExpression = QRegularExpression("/\\*");
            commentEndExpression = QRegularExpression("\\*/");
            break;
        }
    }

    rehighlight();
}