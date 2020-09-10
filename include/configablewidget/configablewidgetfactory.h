/*
 * 可配置界面工厂类
*/
#ifndef configablewidgetfactory_H
#define configablewidgetfactory_H

#include <QtCore>
#include <QtWidgets>
#include <QtXml>

class ObjectFactory {
public:
    /**
     * @brief The ConfigableObject class 需要通过xml配置的object类对象
     */
    class ConfigableObject {
    public:
        virtual ~ConfigableObject() {}

    public:
        /**
         * @brief initUIByConfig 根据配置文件初始化界面
         * @param node xml
         */
        virtual void initWithConfig(const QDomElement& dom_element)
        {
            QDomNode docNode = dom_element.firstChild();

            QObject* thisObject = dynamic_cast<QObject*>(this);

            while (!docNode.isNull()) {
                QDomElement sub_doc_element = docNode.toElement();
                QString tag_name = sub_doc_element.tagName();
                if (!sub_doc_element.isNull()) {
                    QObject* obj = createObject(tag_name, sub_doc_element);
                    if (obj) {
                        if (ObjectFactory::isLayoutObject(obj)) {
                            //QLayout对象或子对象
                            if (onLayoutObjectCreatedEvent(tag_name, ObjectFactory::toLayoutObject(obj))) {
                                m_subLayouts << ObjectFactory::toLayoutObject(obj);
                            } else {
                                qWarning() << QStringLiteral("%1的QLayout子对象%2未处理, 已被销毁").arg(dom_element.tagName()).arg(tag_name);
                                delete obj;
                                obj = 0;
                            }
                        } else if (ObjectFactory::isWidgetObject(obj)) {
                            //QWidget对象或子对象
                            if (onWidgetObjectCreatedEvent(tag_name, ObjectFactory::toWidgetObject(obj))) {
                                m_subWidgets << ObjectFactory::toWidgetObject(obj);
                            } else {
                                qWarning() << QStringLiteral("%1的QWidget子对象%2未处理, 已被销毁").arg(dom_element.tagName()).arg(tag_name);
                                delete obj;
                                obj = 0;
                            }
                        } else {
                            //QObject对象或子对象(除QLayout和QWidget对象或子对象)
                                m_subObjects << obj;
                                obj->setParent(thisObject);
                            if (onObjectCreatedEvent(tag_name, obj)) {
                            } else {
                                qWarning() << QStringLiteral("%1的QObject子对象%2未处理, 已被销毁").arg(dom_element.tagName()).arg(tag_name);
                                delete obj;
                                obj = 0;
                            }
                        }
                    } else {
                        //节点创建失败
                        onSubObjectCreateFailedEvent(tag_name);
                    }
                }
                docNode = docNode.nextSibling();
            }

            if (thisObject) {
                //连接Qt的on_对象名_信号();函数
                QMetaObject::connectSlotsByName(thisObject);
            }
        }

        /**
         * @brief subObjects 子对象
         * @return
         */
        QList<QObject*> subObjects() const
        {
            return m_subObjects;
        }

        /**
         * @brief subLayouts 子布局
         * @return
         */
        QList<QLayout*> subLayouts() const
        {
            return m_subLayouts;
        }

        /**
         * @brief subWidgets 子窗体
         * @return
         */
        QList<QWidget*> subWidgets() const
        {
            return m_subWidgets;
        }

    protected:
        /**
         * @brief contentWidget 容器窗体
         * @return
         */
        virtual QWidget* contentWidget()
        {
            return ObjectFactory::toWidgetObject(dynamic_cast<QObject*>(this));
        }

        /**
         * @brief onSubObjectCreateFailedEvent 子对象创建失败事件
         * @param classname 类名
         * @return true: 子类已处理 false: 子类未处理
         */
        virtual bool onSubObjectCreateFailedEvent(const QString& classname)
        {
            qWarning() << QStringLiteral("节点%1的对象创建失败!").arg(classname);
            return true;
        }

        /**
         * @brief onLayoutObjecCreatedEvent 布局对象创建事件
         * @param classname 类名
         * @param layout 布局对象
         * @return true: 子类已处理 false: 子类未处理
         */
        virtual bool onLayoutObjectCreatedEvent(const QString& classname, QLayout* layout)
        {
            if (contentWidget()) {
                contentWidget()->setLayout(layout);
                return true;
            }
            return false;
        }

        /**
         * @brief onWidgetObjecCreatedEvent 窗体对象创建事件
         * @param classname 类名
         * @param layout 窗体对象
         * @return true: 子类已处理 false: 子类未处理
         */
        virtual bool onWidgetObjectCreatedEvent(const QString& classname, QWidget* widget) { return false; }

        /**
         * @brief onObjectCreatedEvent QObject对象或子对象创建事件
         * @param classname 类名
         * @param object QObject对象或子对象
         * @return true: 子类已处理 false: 子类未处理
         */
        virtual bool onObjectCreatedEvent(const QString& classname, QObject* object) { return true; }

    private:
        QList<QObject*> m_subObjects;
        QList<QLayout*> m_subLayouts;
        QList<QWidget*> m_subWidgets;
    };

public:
    template <typename T>
    static void registerClass()
    {
        constructors().insert(T::staticMetaObject.className(), &constructorHelper<T>);
    }

    /**
     * @brief toLayoutObject 尝试转换为QLayout对象
     * @param obj 转换对象
     * @return layout对象
     */
    static QLayout* toLayoutObject(QObject* obj)
    {
        return qobject_cast<QLayout*>(obj);
    }

    /**
     * @brief isLayoutObject 是否是Layout对象
     * @param obj 转换对象
     * @return
     */
    static bool isLayoutObject(QObject* obj)
    {
        return toLayoutObject(obj);
    }

    /**
     * @brief toThreadObject 尝试转换为QThread对象
     * @param obj 转换对象
     * @return thread对象
     */
    static QThread* toThreadObject(QObject* obj)
    {
        return qobject_cast<QThread*>(obj);
    }

    /**
     * @brief isThreadObject 是否是thread对象
     * @param obj 转换对象
     * @return
     */
    static bool isThreadObject(QObject* obj)
    {
        return toThreadObject(obj);
    }
    /**
     * @brief toWidgetObject 尝试转换为QWidget对象
     * @param obj 转换对象
     * @return widget对象
     */
    static QWidget* toWidgetObject(QObject* obj)
    {
        return qobject_cast<QWidget*>(obj);
    }

    /**
     * @brief isWidgetObject 是否是widget对象
     * @param obj 转换对象
     * @return
     */
    static bool isWidgetObject(QObject* obj)
    {
        return toWidgetObject(obj);
    }

    /**
     * @brief createObject 根据类名创建对象(通过配置初始化)
     * @param className 类名
     * @param dom_element 配置
     * @return
     */
    static QObject* createObject(const QString& className, const QDomElement& dom_element)
    {
        Constructor constructor = constructors().value(className);
        if (constructor == NULL)
            return NULL;

        QObject* obj = (*constructor)();
        if (obj) {
            //加载属性
            QDomNamedNodeMap attrs = dom_element.attributes();
            for (int i = 0; i < attrs.size(); i++) {
                obj->setProperty(attrs.item(i).toAttr().name().toUtf8().data(), attrs.item(i).toAttr().value());
            }

            //执行配置
            ConfigableObject* configObj = dynamic_cast<ConfigableObject*>(obj);
            if (configObj) {
                configObj->initWithConfig(dom_element);
            }
            if (isThreadObject(obj)) {
                toThreadObject(obj)->start();
            }
            return obj;
        } else {
            qWarning() << QStringLiteral("根据类型%1创建QObject对象失败!").arg(className);
        }

        return Q_NULLPTR;
    }

    /**
     * @brief version 库版本号
     * @return
     */
    static QString version()
    {
        return CONFIGABLEWIDGET_LIB_VERSION;
    }

    /**
     * @brief loadConfigFile 加载配置文件
     * @param config_file_path 配置文件
     * @return
     */
    static bool loadConfigFile(const QString& config_file_path, QDomElement& dom)
    {
        QFile file(config_file_path);
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << QStringLiteral("打开配置文件失败:  %1! 失败原因:%2!").arg(config_file_path).arg(file.errorString());
            return false;
        }

        QString errorMsg;
        QDomDocument dom_doc("mydocument");
        if (!dom_doc.setContent(&file, &errorMsg)) {
            file.close();
            qWarning() << QStringLiteral("解析配置文件失败:  %1! 失败原因:%2!").arg(config_file_path).arg(errorMsg);
            return false;
        }
        file.close();

        dom = dom_doc.documentElement();

        return true;
    }

    /**
     * @brief createObjectFromConfigFile 从配置文件创建对象
     * @param config_file_path 配置文件路径
     * @return QObject对象
     */
    static QObject* createObjectFromConfigFile(const QString& config_file_path)
    {
        QDomElement dom;
        if (loadConfigFile(config_file_path, dom)) {
            const QString tag_name = dom.tagName();
            return createObject(tag_name, dom);
        }
        return Q_NULLPTR;
    }

private:
    typedef QObject* (*Constructor)();

    template <typename T>
    static QObject* constructorHelper()
    {
        return new T();
    }

    static QHash<QString, Constructor>& constructors()
    {
        static QHash<QString, Constructor> instance;
        return instance;
    }
};

//注册可配置对象类函数
#define BEGIN_REGIST_CONFIGABLEOBJECT_FUNC(classname) static int dbfa73cbe0354ecc828a6f1b63f37254##classname = []() {
#define REGIST_CONFIGABLEOBJECT_FUNC(classname) ObjectFactory::registerClass<classname>();
#define END_REGIST_CONFIGABLEOBJECT_FUNC() \
    return 0;                              \
    }                                      \
    ();

//根据类名创建对象
#define createObjectFromFactory(name, config) ObjectFactory::createObject(name, config)

#endif // configablewidgetfactory_H
