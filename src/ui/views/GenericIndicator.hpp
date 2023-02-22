#ifndef MOTIV_GENERICINDICATOR_HPP
#define MOTIV_GENERICINDICATOR_HPP


#include <QGraphicsItem>

template <class T, class G> requires std::is_base_of_v<QAbstractGraphicsShapeItem, G>
class GenericIndicator : public G {
public: // constructors
    explicit GenericIndicator(T* element, QGraphicsItem *parent = nullptr);

public: // methods
    void setOnDoubleClick(const std::function<void(T *)>& fn);
    void setOnSelected(const std::function<void(T *)>& fn);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    virtual bool respondToEvent(QPointF) { return true; };

private:
    T* element_;

private: // event handler
    std::function<void(T*)> onDoubleClick_;
    std::function<void(T *element)>  onSelected_;
};


#endif //MOTIV_GENERICINDICATOR_HPP
