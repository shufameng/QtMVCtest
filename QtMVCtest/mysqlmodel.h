/**
 ** MySqlModel 类
 **
 **
 **
 **
 **
 **
 **
 **/

#ifndef MYSQLMODEL_H
#define MYSQLMODEL_H

#include <QAbstractItemModel>
#include <QtSql>
#include <QTextDocument>

class Table;

class MySqlModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit MySqlModel(QObject *parent = 0);
    virtual ~MySqlModel();

    // 重写
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                    int role = Qt::DisplayRole) const;
    virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value,
                               int role = Qt::EditRole);

    //
public slots:
    int resultCount() const
    { return mResultCount; }

    int pageCount() const
    { return mPageCount; }

    int maxRowPerpage() const
    { return mMaxRowPerpage; }

    void setMaxRowPerpage(const int count);

    int currentPage() const
    { return mCurrentPage; }

    void toNextPage();          /* 下一页 */
    void toPrevPage();          /* 上一页 */
    void toFirstPage();         /* 首页 */
    void toLastPage();          /* 尾页 */
    void toPage(const int page); /* 转到第page页 */

    virtual void setAdvancedKey(Table *key); /* 设置查询关键字 */
    virtual void getRowInfo(Table *key);
    virtual qint64 getRowInfoId(const int row);
    virtual void print(QTextDocument *doc);

protected:
    void setResultCount(const int count);
    void setPageCount(const int count);
    void setCurrentPage(const int num);
    QSqlDatabase getDb();

    bool doSelect();

    // 1.获取查询总结果数,赋值给mResultCount
    // 2.分页查询,获取当前页的结果数据
    virtual bool selectByAdvacedKey();

signals:
    void currentPageChanged(int page);
    void resultCountChanged(int count);
    void pageCountChanged(int count);

protected:
    mutable QSqlQuery   *mQuery;                         /* 保存查询结果的查询器 */
    int                             mRowCount;                      /* 查询器中当前的行数 */
    int                             mColumnCount;               /* 查询器中当前的列数 */

    QVariantList              mHorHeaderData;

    int                             mResultCount;                      /* 查询结果的总条数 */
    int                             mPageCount;                 /* 查询结果的总页数 */
    int                             mMaxRowPerpage;         /* 每页最多显示的查询结果数 */
    int                             mCurrentPage;                       /* 当前显示的页号 */

    Table                    *mAdvancedKey;          /* 查询关键字 */
};

#endif // MYSQLMODEL_H
