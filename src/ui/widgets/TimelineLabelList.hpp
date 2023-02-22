#ifndef MOTIV_TIMELINELABELLIST_HPP
#define MOTIV_TIMELINELABELLIST_HPP


#include <QListWidget>

#include "src/ui/TraceDataProxy.hpp"

class TimelineLabelList : public QListWidget {
    Q_OBJECT

public:
    TimelineLabelList(TraceDataProxy *data, QWidget *parent = nullptr);

protected:
    /*
     * NOTE: we override this function to prevent the items from being clicked/activated.
     * this is quite hacky and there might be a better solution.
     */
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    TraceDataProxy *data = nullptr;
};


#endif //MOTIV_TIMELINELABELLIST_HPP
