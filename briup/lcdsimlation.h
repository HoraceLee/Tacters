#ifndef LCDSIMLATION_H
#define LCDSIMLATION_H

#include <QWidget>
#include <QSerialPort>
#include <QTimer>

namespace Ui {
class lcdsimlation;
}

class lcdsimlation : public QWidget
{
    Q_OBJECT

public:
    explicit lcdsimlation(QWidget *parent = 0);
    ~lcdsimlation();

private slots:
    void clearscreen();
    void on_key1_clicked();

    void on_key2_clicked();

    void on_key3_clicked();

    void on_key4_clicked();

    void on_key5_clicked();

    void on_key6_clicked();

    void on_key7_clicked();

    void on_key8_clicked();

    void on_key9_clicked();

    void on_key0_clicked();

    void on_keyq_clicked();

    void on_keyw_clicked();

    void on_keye_clicked();

    void on_keyr_clicked();

    void on_keyt_clicked();

    void on_keyy_clicked();

    void on_keyu_clicked();

    void on_keyi_clicked();

    void on_keyo_clicked();

    void on_keyp_clicked();

    void on_keya_clicked();

    void on_keys_clicked();

    void on_keyd_clicked();

    void on_keyf_clicked();

    void on_keyg_clicked();

    void on_keyh_clicked();

    void on_keyj_clicked();

    void on_keyk_clicked();

    void on_keyl_clicked();

    void on_keyz_clicked();

    void on_keyx_clicked();

    void on_keyc_clicked();

    void on_keyv_clicked();

    void on_keyb_clicked();

    void on_keyn_clicked();

    void on_keym_clicked();

    void on_space_clicked();

    void on_enter_clicked();

    void readSlot();

    void on_capslk_clicked();

    void on_closeBtn_clicked();

private:
    Ui::lcdsimlation *ui;
    QSerialPort*   serialport;
    bool           isPortOpen;
    QTimer          readTimer;
};

#endif // LCDSIMLATION_H
