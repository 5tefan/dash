#ifndef BITCOIN_QT_GOVERNANCELIST_H
#define BITCOIN_QT_GOVERNANCELIST_H

#include <primitives/transaction.h>
#include <sync.h>
#include <util/system.h>

#include <QMenu>
#include <QTimer>
#include <QWidget>

#define GOVERNANCELIST_UPDATE_SECONDS 10
#define GOVERNANCELIST_FILTER_COOLDOWN_SECONDS 3
#define GOVERNANCELIST_DATEFMT "yyyy-MM-dd hh:mm"

namespace Ui
{
class GovernanceList;
}

class CDeterministicMNList;
class ClientModel;

/** Governance Manager page widget */
class GovernanceList : public QWidget
{
    Q_OBJECT

public:
    explicit GovernanceList(QWidget* parent = 0);
    ~GovernanceList();

    enum {
        COLUMN_HASH,
        COLUMN_TITLE,
        COLUMN_CREATION,
        COLUMN_START,
        COLUMN_END,
        COLUMN_AMOUNT,
        COLUMN_ACTIVE,
        COLUMN_STATUS,
    };

    void setClientModel(ClientModel* clientModel);

private:

    QTimer* timer;
    ClientModel* clientModel;

    Ui::GovernanceList* ui;
    CCriticalSection cs_proposalList;
    bool governanceListChanged;

    QString strCurrentFilter;
    bool fGovernanceFilterUpdated;
    int64_t nTimeGovernanceFilterUpdated;
    int64_t nTimeGovernanceUpdated;

    void updateGovernanceList();

Q_SIGNALS:
    void doubleClicked(const QModelIndex&);

private Q_SLOTS:
    //void proposalLink_clicked();
    void on_filterLineEdit_textChanged(const QString& strFilterIn);

    void handleGovernanceListChanged();
    void updateGovernanceListScheduled();

};
#endif // BITCOIN_QT_GOVERNANCELIST_H
