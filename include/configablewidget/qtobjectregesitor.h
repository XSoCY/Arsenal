/*
 * Qt常用对象注册
*/
#ifndef qtobjectregesitor_h_
#define qtobjectregesitor_h_

#include "configablewidgetfactory.h"
#include <QtCore>
#include <QtWidgets>
#include <QtXml>

template <class T>
class WidgetTemp : public T, public ObjectFactory::ConfigableObject {
public:
    WidgetTemp(QWidget* parent = Q_NULLPTR)
        : T(parent)
    {
    }
};

class Widget : public WidgetTemp<QWidget> {
    Q_OBJECT
public:
    Widget(QWidget* parent = Q_NULLPTR)
        : WidgetTemp<QWidget>(parent)
    {
    }
};
//Widget
BEGIN_REGIST_CONFIGABLEOBJECT_FUNC(Widget)
REGIST_CONFIGABLEOBJECT_FUNC(Widget)
END_REGIST_CONFIGABLEOBJECT_FUNC()

//QWidget
BEGIN_REGIST_CONFIGABLEOBJECT_FUNC(QWidget)
REGIST_CONFIGABLEOBJECT_FUNC(QWidget)
END_REGIST_CONFIGABLEOBJECT_FUNC()

class Frame : public WidgetTemp<QFrame> {
    Q_OBJECT
public:
    Frame(QWidget* parent = Q_NULLPTR)
        : WidgetTemp<QFrame>(parent)
    {
    }
};
//Frame
BEGIN_REGIST_CONFIGABLEOBJECT_FUNC(Frame)
REGIST_CONFIGABLEOBJECT_FUNC(Frame)
END_REGIST_CONFIGABLEOBJECT_FUNC()

//QFrame
BEGIN_REGIST_CONFIGABLEOBJECT_FUNC(QFrame)
REGIST_CONFIGABLEOBJECT_FUNC(QFrame)
END_REGIST_CONFIGABLEOBJECT_FUNC()

class Dialog : public WidgetTemp<QDialog> {
    Q_OBJECT
public:
    Dialog(QWidget* parent = Q_NULLPTR)
        : WidgetTemp<QDialog>(parent)
    {
    }
};
//Dialog
BEGIN_REGIST_CONFIGABLEOBJECT_FUNC(Dialog)
REGIST_CONFIGABLEOBJECT_FUNC(Dialog)
END_REGIST_CONFIGABLEOBJECT_FUNC()

//QDialog
BEGIN_REGIST_CONFIGABLEOBJECT_FUNC(QDialog)
REGIST_CONFIGABLEOBJECT_FUNC(QDialog)
END_REGIST_CONFIGABLEOBJECT_FUNC()

//class MainWindow : public WidgetTemp<QMainWindow> {
//    Q_OBJECT
//public:
//    MainWindow(QWidget* parent = Q_NULLPTR)
//        : WidgetTemp<QMainWindow>(parent)
//    {
//    }
//};
//MainWindow
//BEGIN_REGIST_CONFIGABLEOBJECT_FUNC(MainWindow)
//REGIST_CONFIGABLEOBJECT_FUNC(MainWindow)
//END_REGIST_CONFIGABLEOBJECT_FUNC()
//QMainWindow
BEGIN_REGIST_CONFIGABLEOBJECT_FUNC(QMainWindow)
REGIST_CONFIGABLEOBJECT_FUNC(QMainWindow)
END_REGIST_CONFIGABLEOBJECT_FUNC()

//QAction
BEGIN_REGIST_CONFIGABLEOBJECT_FUNC(QAction)
REGIST_CONFIGABLEOBJECT_FUNC(QAction)
END_REGIST_CONFIGABLEOBJECT_FUNC()

//QLabel
BEGIN_REGIST_CONFIGABLEOBJECT_FUNC(QLabel)
REGIST_CONFIGABLEOBJECT_FUNC(QLabel)
END_REGIST_CONFIGABLEOBJECT_FUNC()

class GroupBox : public WidgetTemp<QGroupBox> {
    Q_OBJECT
};
//GroupBox
BEGIN_REGIST_CONFIGABLEOBJECT_FUNC(GroupBox)
REGIST_CONFIGABLEOBJECT_FUNC(GroupBox)
END_REGIST_CONFIGABLEOBJECT_FUNC()

//QGroupBox
BEGIN_REGIST_CONFIGABLEOBJECT_FUNC(QGroupBox)
REGIST_CONFIGABLEOBJECT_FUNC(QGroupBox)
END_REGIST_CONFIGABLEOBJECT_FUNC()

//QPushButton
BEGIN_REGIST_CONFIGABLEOBJECT_FUNC(QPushButton)
REGIST_CONFIGABLEOBJECT_FUNC(QPushButton)
END_REGIST_CONFIGABLEOBJECT_FUNC()

class GridLayout : public QGridLayout, public ObjectFactory::ConfigableObject {
    Q_OBJECT
protected:
    void readProperty(QObject* obj, int& row, int& col, int& rowSpan, int& colSpan, Qt::Alignment& align)
    {
        if (obj) {
            row = obj->property("row").toInt();
            col = obj->property("column").toInt();
            rowSpan = obj->dynamicPropertyNames().contains("rowSpan") ? obj->property("rowSpan").toInt() : 1;
            colSpan = obj->dynamicPropertyNames().contains("columnSpan") ? obj->property("columnSpan").toInt() : 1;
            Qt::Alignment alignment = Qt::Alignment();
            if (obj->dynamicPropertyNames().contains("alignment")) {
                const QStringList alignStrs = obj->property("alignment").toString().trimmed().toLower().split("|");
                Q_FOREACH (QString str, alignStrs) {
                    if (str.trimmed() == QString("AlignLeft").toLower()) {
                        alignment |= Qt::AlignLeft;
                    } else if (str.trimmed() == QString("AlignLeading").toLower()) {
                        alignment |= Qt::AlignLeading;
                    } else if (str.trimmed() == QString("AlignRight").toLower()) {
                        alignment |= Qt::AlignRight;
                    } else if (str.trimmed() == QString("AlignTrailing").toLower()) {
                        alignment |= Qt::AlignTrailing;
                    } else if (str.trimmed() == QString("AlignHCenter").toLower()) {
                        alignment |= Qt::AlignHCenter;
                    } else if (str.trimmed() == QString("AlignJustify").toLower()) {
                        alignment |= Qt::AlignJustify;
                    } else if (str.trimmed() == QString("AlignAbsolute").toLower()) {
                        alignment |= Qt::AlignAbsolute;
                    } else if (str.trimmed() == QString("AlignHorizontal_Mask").toLower()) {
                        alignment |= Qt::AlignHorizontal_Mask;
                    } else if (str.trimmed() == QString("AlignTop").toLower()) {
                        alignment |= Qt::AlignTop;
                    } else if (str.trimmed() == QString("AlignBottom").toLower()) {
                        alignment |= Qt::AlignBottom;
                    } else if (str.trimmed() == QString("AlignVCenter").toLower()) {
                        alignment |= Qt::AlignVCenter;
                    } else if (str.trimmed() == QString("AlignBaseline").toLower()) {
                        alignment |= Qt::AlignBaseline;
                    } else if (str.trimmed() == QString("AlignVertical_Mask").toLower()) {
                        alignment |= Qt::AlignVertical_Mask;
                    } else if (str.trimmed() == QString("AlignCenter").toLower()) {
                        alignment |= Qt::AlignCenter;
                    }
                }
            }
        }
    }
    /**
   * @brief onLayoutObjectCreatedEvent 布局对象创建事件
   * @param classname 类名
   * @param layout 布局对象
   */
    bool onLayoutObjectCreatedEvent(const QString& classname, QLayout* layout) override
    {
        int row, column, rowSpan, columnSpan;
        Qt::Alignment alignment;
        readProperty(layout, row, column, rowSpan, columnSpan, alignment);
        addLayout(layout, row, column, rowSpan, columnSpan, alignment);
        return true;
    }

    /**
   * @brief onWidgetObjectCreatedEvent 窗体对象创建事件
   * @param classname 类名
   * @param layout 窗体对象
   */
    bool onWidgetObjectCreatedEvent(const QString& classname, QWidget* widget) override
    {
        int row, column, rowSpan, columnSpan;
        Qt::Alignment alignment;
        readProperty(widget, row, column, rowSpan, columnSpan, alignment);
        addWidget(widget, row, column, rowSpan, columnSpan, alignment);
        return true;
    }
};
//GridLayout
BEGIN_REGIST_CONFIGABLEOBJECT_FUNC(GridLayout)
REGIST_CONFIGABLEOBJECT_FUNC(GridLayout)
END_REGIST_CONFIGABLEOBJECT_FUNC()

class HBoxLayout : public QHBoxLayout, public ObjectFactory::ConfigableObject {
    Q_OBJECT
protected:
    /**
   * @brief onLayoutObjectCreatedEvent 布局对象创建事件
   * @param classname 类名
   * @param layout 布局对象
   */
    bool onLayoutObjectCreatedEvent(const QString& classname, QLayout* layout) override
    {
        addLayout(layout);
        return true;
    }

    /**
   * @brief onWidgetObjectCreatedEvent 窗体对象创建事件
   * @param classname 类名
   * @param layout 窗体对象
   */
    bool onWidgetObjectCreatedEvent(const QString& classname, QWidget* widget) override
    {
        addWidget(widget);
        return true;
    }
};

//HBoxLayout
BEGIN_REGIST_CONFIGABLEOBJECT_FUNC(HBoxLayout)
REGIST_CONFIGABLEOBJECT_FUNC(HBoxLayout)
END_REGIST_CONFIGABLEOBJECT_FUNC()

class VBoxLayout : public QVBoxLayout, public ObjectFactory::ConfigableObject {
    Q_OBJECT
protected:
    /**
   * @brief onLayoutObjectCreatedEvent 布局对象创建事件
   * @param classname 类名
   * @param layout 布局对象
   */
    bool onLayoutObjectCreatedEvent(const QString& classname, QLayout* layout) override
    {
        addLayout(layout);
        return true;
    }

    /**
   * @brief onWidgetObjectCreatedEvent 窗体对象创建事件
   * @param classname 类名
   * @param layout 窗体对象
   */
    bool onWidgetObjectCreatedEvent(const QString& classname, QWidget* widget) override
    {
        addWidget(widget);
        return true;
    }
};
//VBoxLayout
BEGIN_REGIST_CONFIGABLEOBJECT_FUNC(VBoxLayout)
REGIST_CONFIGABLEOBJECT_FUNC(VBoxLayout)
END_REGIST_CONFIGABLEOBJECT_FUNC()
#endif // qtobjectregesitor_h_
