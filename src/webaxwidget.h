#ifndef WEBAXWIDGET_H
#define WEBAXWIDGET_H

#include <ActiveQt/QAxWidget>
#include "windows.h"

class WebAxWidget : public QAxWidget
{
public:

    WebAxWidget(QWidget* parent = 0, Qt::WindowFlags f = 0)
        : QAxWidget(parent, f)
    {
        if(!setControl(QStringLiteral("{8856f961-340a-11d0-a96b-00c04fd705a2}")))
        {
            qWarning("Internet Explorer: initialisation failed");
            return;
        }
        setProperty("RegisterAsBrowser", QVariant(true));
        setProperty("Resizable", QVariant(false));
        setProperty("Silent", QVariant(true));
        setProperty("FullScreen", QVariant(true));

        setFocusPolicy(Qt::StrongFocus);//设置控件接收键盘焦点的方式：鼠标单击、Tab键
    }
protected:
    bool translateKeyEvent(int message, int keycode) const Q_DECL_OVERRIDE
    {
        if (message >= WM_KEYFIRST && message <= WM_KEYLAST)
            return true;
        else
            return QAxWidget::translateKeyEvent(message, keycode);
    }

};

#endif // WEBAXWIDGET_H

