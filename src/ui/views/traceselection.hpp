#ifndef MOTIV_TRACESELECTION_HPP
#define MOTIV_TRACESELECTION_HPP

#include <QWidget>

namespace view {

// The initial view where one can choose a new file or recent files.
class TraceSelection : public QWidget {
    Q_OBJECT
public:
  TraceSelection(QWidget *parent = nullptr);
  ~TraceSelection();

private:
  QStringList recent;
};

} // namespace view

#endif // MOTIV_TRACESELECTION_HPP