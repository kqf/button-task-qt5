#ifndef TITLEBUTTON_H
#define TITLEBUTTON_H

#include <QAbstractButton>
#include <QPainter>

class TitleButton : public QAbstractButton
{
    Q_OBJECT
public:
    enum ButtonType { BUTTON_MINIMIZE, BUTTON_MAXIMIZE, BUTTON_CLOSE };

    explicit TitleButton(ButtonType t = BUTTON_MAXIMIZE, QWidget *parent = 0);
    QSize sizeHint() const;

    ~TitleButton();

protected:
    void paintEvent(QPaintEvent  *event);


private slots:
   void changeStateToClicked();

private:
    ButtonType  type;
    QPixmap * currentPicture;
    QPixmap  normalPicture;
    QPixmap  clickedPicture;
    QPixmap  hoveredPicture;
};

#endif // TITLEBUTTON_H
