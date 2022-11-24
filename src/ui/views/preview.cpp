#include "preview.hpp"

#include "src/ui/colors.hpp"
#include "src/models/filetrace.hpp"

#include <QGraphicsScene>
#include <QRect>
#include <QLabel>

using namespace view;

Preview::Preview(QWidget *parent, FileTrace *trace) : QGraphicsView(parent),
                                                      scene(new QGraphicsScene(this)) {
    setScene(scene);
    scene->addText("Placeholder");
//    const auto slots = trace->getSlots();
//
//    size_t i = 0;
//    for (auto slot : slots) {
//        auto rec = new QRectF();
//        //scene->addRect(rec);
//        ++i;
//    }
}