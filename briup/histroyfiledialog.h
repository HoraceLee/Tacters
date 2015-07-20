#ifndef HISTROYFILEDIALOG_H
#define HISTROYFILEDIALOG_H

#include <QDialog>

namespace Ui {
class HistroyFileDialog;
}

class HistroyFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HistroyFileDialog(QWidget *parent = 0);
    ~HistroyFileDialog();

private slots:
    void on_submitBtn_clicked();
    void on_cancelBtn_clicked();

private:
    Ui::HistroyFileDialog *ui;
};

#endif // HISTROYFILEDIALOG_H
