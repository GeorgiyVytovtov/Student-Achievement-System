#ifndef CREATENAMECLASS_H
#define CREATENAMECLASS_H

#include <QDialog>

namespace Ui {
class CreateNameClass;
}

class CreateNameClass : public QDialog
{
    Q_OBJECT

public:
    explicit CreateNameClass(QWidget* parent = nullptr);
    ~CreateNameClass();
    QString nameClass() const;

private:
    Ui::CreateNameClass *ui;

private slots:
    void OkEnabled();
};

#endif // CREATENAMECLASS_H
