#include "TransferMenuItemAction.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QKeyEvent>

TransferMenuItemAction::TransferMenuItemAction(const QString title, const QIcon icon)
    : QWidgetAction(NULL)
{

    this->title = new QLabel(title);
    this->icon = new QIcon(icon);
    this->hoverIcon = NULL;

    container = new QWidget (NULL);
    container->setObjectName(QString::fromUtf8("wContainer"));
    container->installEventFilter(this);
    setupActionWidget();
    setDefaultWidget(container);
}

TransferMenuItemAction::TransferMenuItemAction(const QString title, const QIcon icon, const QIcon hoverIcon)
    : QWidgetAction(NULL)
{
    this->title = new QLabel(title);
    this->icon = new QIcon(icon);
    this->hoverIcon = new QIcon(hoverIcon);

    container = new QWidget (NULL);
    container->setObjectName(QString::fromUtf8("wContainer"));
    container->installEventFilter(this);
    setupActionWidget();
    setDefaultWidget(container);
}

TransferMenuItemAction::~TransferMenuItemAction()
{
    delete title;
    delete iconButton;
    delete icon;
    delete hoverIcon;
    delete container;
}

void TransferMenuItemAction::setupActionWidget()
{
    container->setMinimumHeight(32);
    container->setMaximumHeight(32);
    container->setStyleSheet(QString::fromAscii("#wContainer{margin-left: 20px; padding: 0px;}"));

                                  //"QMenu::separator {height: 1px; margin: 6px 0px 6px 0px; background-color: rgba(0, 0, 0, 0.1);}"
                                  //"QMenu::item:selected {height: 24px; background: #aaaaaa; border-left: 10px solid #aaaaaa; color:#ffffff; }"));

    QHBoxLayout* pLayout = new QHBoxLayout();
    pLayout->setContentsMargins(QMargins(16, 0, 8, 0));
    pLayout->setSpacing(12);

    iconButton = new QPushButton();
    iconButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    iconButton->setText(QString::fromUtf8(""));
    iconButton->setMinimumSize(QSize(24, 24));
    iconButton->setMaximumSize(QSize(24, 24));
    iconButton->setIconSize(QSize(24, 24));
    iconButton->setIcon(*icon);
    iconButton->setFlat(true);
    pLayout->addWidget(iconButton);


    title->setStyleSheet(QString::fromAscii("font-family: Source Sans Pro; font-size: 14px; color: #777777;"));
    //pLabel->setAlignment(Qt::AlignLeft);
    pLayout->addWidget(title);
    pLayout->addItem(new QSpacerItem(10,10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    container->setLayout(pLayout);
}

bool TransferMenuItemAction::eventFilter(QObject *obj, QEvent *event)
{

    if (event->type() == QEvent::Enter)
    {
        container->setStyleSheet(QString::fromUtf8("#wContainer{border: 2px solid #aaaaaa; border-radius: 2px; margin: 0px 8px 0px 8px; padding: 0px; background-color: #aaaaaa;}"));
        title->setStyleSheet(QString::fromAscii("font-family: Source Sans Pro; font-size: 14px; color: #ffffff;"));
        iconButton->setStyleSheet(QString::fromAscii("border: none;"));
        hoverIcon ? iconButton->setIcon(*hoverIcon) : iconButton->setIcon(*icon);
    }

    if (event->type() == QEvent::Leave)
    {
        container->setStyleSheet(QString::fromUtf8("#wContainer{border: none; margin: 0px 0px 0px 0px; padding: 0px; background-color: #ffffff;}"));
        title->setStyleSheet(QString::fromAscii("font-family: Source Sans Pro; font-size: 14px; color: #777777;"));
        iconButton->setStyleSheet(QString::fromAscii("border: none;"));
        iconButton->setIcon(*icon);
    }

    return QObject::eventFilter(obj, event);
}


