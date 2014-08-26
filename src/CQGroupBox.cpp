#include <CQGroupBox.h>
#include <QChildEvent>
#include <QLayout>
#include <QPainter>
#include <QStylePainter>
#include <QStyleOption>
#include <QMouseEvent>

CQGroupBox::
CQGroupBox(QWidget *parent) :
 QWidget(parent), title_()
{
  init();
}

CQGroupBox::
CQGroupBox(const QString &title, QWidget *parent) :
 QWidget(parent), title_(title)
{
  init();
}

CQGroupBox::
~CQGroupBox()
{
}

void
CQGroupBox::
init()
{
  titleBold_      = true;
  titleScale_     = 1.0;
  titleAlignment_ = Qt::AlignLeft | Qt::AlignBottom;

  lineTop_             = false;
  lineBottom_          = true;
  lineTopAlignment_    = Qt::AlignBottom;
  lineBottomAlignment_ = Qt::AlignVCenter;

  marginLeft_   = 4;
  marginRight_  = 4;
  marginTop_    = -1;
  marginBottom_ = -1;

  checkable_  = false;
  checked_    = false;
  checkPress_ = false;

  setTitleFont();

  lineColor_ = palette().color(QPalette::Mid);

  //----

  area_ = new CQGroupBoxArea;

  area_->setParent(this);

  dx_ = 2;
  dy_ = 2;

  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

void
CQGroupBox::
setTitleFont()
{
  titleFont_ = font();

  titleFont_.setPointSizeF(titleFont_.pointSizeF()*titleScale_);

  titleFont_.setBold(titleBold_);
}

void
CQGroupBox::
setTitle(const QString &title)
{
  title_ = title;

  update();
}

void
CQGroupBox::
setTitleBold(bool bold)
{
  titleBold_ = bold;

  setTitleFont();

  update();
}

void
CQGroupBox::
setTitleScale(double scale)
{
  titleScale_ = scale;

  setTitleFont();

  update();
}

void
CQGroupBox::
setTitleAlignment(int alignment)
{
  titleAlignment_ = alignment;

  update();
}

void
CQGroupBox::
setHasLineTop(bool line)
{
  lineTop_ = line;

  update();
}

void
CQGroupBox::
setHasLineBottom(bool line)
{
  lineBottom_ = line;

  update();
}

void
CQGroupBox::
setLineTopAlignment(int alignment)
{
  lineTopAlignment_ = alignment;

  update();
}

void
CQGroupBox::
setLineBottomAlignment(int alignment)
{
  lineBottomAlignment_ = alignment;

  update();
}

void
CQGroupBox::
setMarginLeft(int margin)
{
  marginLeft_ = margin;

  update();
}

void
CQGroupBox::
setMarginRight(int margin)
{
  marginRight_ = margin;

  update();
}

void
CQGroupBox::
setMarginBottom(int margin)
{
  marginBottom_ = margin;

  update();
}

void
CQGroupBox::
setMarginTop(int margin)
{
  marginTop_ = margin;

  update();
}

void
CQGroupBox::
setCheckable(bool checkable)
{
  checkable_ = checkable;

  updateEnabled();

  update();
}

void
CQGroupBox::
setChecked(bool checked)
{
  checked_ = checked;

  if (checkable_)
    updateEnabled();

  emit toggled(isChecked());

  update();
}

void
CQGroupBox::
changeEvent(QEvent *e)
{
  if (e->type() == QEvent::EnabledChange)
    updateEnabled();

  calculateFrame();

  QWidget::changeEvent(e);
}

void
CQGroupBox::
childEvent(QChildEvent *e)
{
  if (e->type() != QEvent::ChildAdded || ! e->child()->isWidgetType())
    return;

  calculateFrame();

  if (checkable_)
    updateEnabled();

  QWidget::childEvent(e);
}

bool
CQGroupBox::
event(QEvent *e)
{
  if      (e->type() == QEvent::KeyPress) {
    QKeyEvent *ke = static_cast<QKeyEvent*>(e);

    if (ke->key() == Qt::Key_Select || ke->key() == Qt::Key_Space) {
      if (checkable_) {
        checkPress_ = true;

        update();

        return true;
      }
    }
  }
  else if (e->type() == QEvent::KeyRelease) {
    QKeyEvent *ke = static_cast<QKeyEvent*>(e);

    if (ke->key() == Qt::Key_Select || ke->key() == Qt::Key_Space) {
      if (checkable_) {
        setChecked(! isChecked());

        checkPress_ = false;

        update();

        return true;
      }
    }
  }

  return QWidget::event(e);
}

void
CQGroupBox::
focusInEvent(QFocusEvent *e)
{
  QWidget::focusInEvent(e);
}

void
CQGroupBox::
mouseMoveEvent(QMouseEvent *e)
{
  if (checkable_) {
    bool inside = checkRect_.contains(e->pos()) || titleRect_.contains(e->pos());

    bool oldCheckPress = checkPress_;

    if      (! checkPress_ && inside)
      checkPress_ = true;
    else if (  checkPress_ && ! inside)
      checkPress_ = false;

    if (checkPress_ != oldCheckPress)
      update();
  }

  QWidget::mouseMoveEvent(e);
}

void
CQGroupBox::
mousePressEvent(QMouseEvent *e)
{
  if (checkable_) {
    bool inside = checkRect_.contains(e->pos()) || titleRect_.contains(e->pos());

    if (inside) {
      checkPress_ = true;

      update();
    }
  }

  QWidget::mousePressEvent(e);
}

void
CQGroupBox::
mouseReleaseEvent(QMouseEvent *e)
{
  if (checkable_) {
    bool inside = checkRect_.contains(e->pos()) || titleRect_.contains(e->pos());

    if (inside) {
      setChecked(! isChecked());

      checkPress_ = false;

      update();
    }
  }

  QWidget::mouseReleaseEvent(e);
}

void
CQGroupBox::
paintEvent(QPaintEvent *)
{
  QPainter p(this);

  QFontMetrics fm(titleFont_);

  int checkSize = (checkable_ ? fm.height() + 4 : 0);

  int textX = 0;

  if      (titleAlignment_ & Qt::AlignRight)
    textX = width() - dx_ - fm.width(title_);
  else if (titleAlignment_ & Qt::AlignHCenter)
    textX = (width() - fm.width(title_) - checkSize)/2 + checkSize;
  else if (titleAlignment_ & Qt::AlignLeft)
    textX = dx_ + checkSize;

  int textY = 0;

  if      (titleAlignment_ & Qt::AlignBottom)
    textY = spaceTop() - fm.descent() - 2;
  else if (titleAlignment_ & Qt::AlignTop)
    textY = fm.ascent() + 2;
  else if (titleAlignment_ & Qt::AlignVCenter)
    textY = spaceTop()/2 + fm.descent() + 2;

  int checkX = textX - checkSize;
  int checkY = textY - fm.ascent()/2;

  if (lineTop_) {
    int lineY;

    if      (lineTopAlignment_ & Qt::AlignTop)
      lineY = 2;
    else if (lineTopAlignment_ & Qt::AlignVCenter)
      lineY = spaceTop()/2;
    else
      lineY = spaceTop() - 2;

    p.setPen(lineColor_);

    p.drawLine(dx_, lineY, width() - 2*dx_, lineY);
  }

  if (title_ != "") {
    p.setFont(titleFont_);

    titleRect_ = QRect(textX - 2, textY - fm.ascent() + fm.descent(),
                       fm.width(title_) + 4, fm.height());

    p.fillRect(titleRect_, QBrush(palette().color(QPalette::Background)));

    if (isEnabled())
      p.setPen(palette().color(QPalette::Active, QPalette::WindowText));
    else
      p.setPen(palette().color(QPalette::Disabled, QPalette::WindowText));

    p.drawText(textX, textY, title_);
  }

  if (lineBottom_) {
    int lineY;

    if      (lineTopAlignment_ & Qt::AlignTop)
      lineY = height() - spaceBottom() + 2;
    else if (lineTopAlignment_ & Qt::AlignVCenter)
      lineY = height() - spaceBottom()/2;
    else
      lineY = height() - 2;

    p.setPen(lineColor_);

    p.drawLine(dx_, lineY, width() - 2*dx_, lineY);
  }

  //------

  if (checkable_) {
    int checkX1    = checkX + 2;
    int checkSize1 = checkSize - 4;
    int checkY1    = checkY - checkSize1/2;

    checkRect_ = QRect(checkX1, checkY1, checkSize1, checkSize1);

    p.fillRect(QRect(checkX1 - 2, checkY1 - 2, checkSize1 + 4, checkSize1 + 4),
               QBrush(palette().color(QPalette::Background)));

    QStylePainter p(this);

    QStyleOptionButton opt;

    opt.initFrom(this);

    opt.rect = checkRect_;

    opt.state |= (isChecked() ? QStyle::State_On : QStyle::State_Off);

    if (checkPress_)
      opt.state |= QStyle::State_Sunken;

#if 0
    if (testAttribute(Qt::WA_Hover) && underMouse()) {
      if (d->hovering)
        opt.state |= QStyle::State_MouseOver;
      else
        opt.state &= ~QStyle::State_MouseOver;
    }

    opt.text = d->text;
    opt.icon = d->icon;
    opt.iconSize = iconSize();
#endif

    p.drawControl(QStyle::CE_CheckBox, opt);
  }
}

void
CQGroupBox::
resizeEvent(QResizeEvent *)
{
}

int
CQGroupBox::
spaceTop() const
{
  if (marginTop_ >= 0)
    return marginTop_;

  if (title_ != "") {
    QFontMetrics fm(titleFont_);

    return fm.height() + 4;
  }
  else
    return 4;
}

int
CQGroupBox::
spaceBottom() const
{
  if (marginBottom_ >= 0)
    return marginBottom_;

  return 4;
}

QSize
CQGroupBox::
minimumSizeHint() const
{
  QFontMetrics fm(titleFont_);

  int baseWidth  = fm.width(title_) + 4;
  int baseHeight = fm.height();

  if (checkable_)
    baseWidth += fm.height() + 4;

  QStyleOptionGroupBox option;

  QSize size = style()->sizeFromContents(QStyle::CT_GroupBox, &option,
                                         QSize(baseWidth, baseHeight), this);

  return size.expandedTo(QWidget::minimumSizeHint());
}

void
CQGroupBox::
calculateFrame()
{
  QLayout *l = layout();
  if (! l) return;

  l->setContentsMargins(marginLeft(), spaceTop(), marginRight(), spaceBottom());
}

void
CQGroupBox::
updateEnabled()
{
  QObjectList childList = children();

  for (int i = 0; i < childList.size(); ++i) {
    QObject *o = childList.at(i);

    if (! o->isWidgetType()) continue;

    QWidget *w = static_cast<QWidget *>(o);

    if (isChecked()) {
//    if (! w->isEnabled()) {
//      if (! w->testAttribute(Qt::WA_ForceDisabled))
          w->setEnabled(true);
//    }
    }
    else {
//    if (w->isEnabled())
        w->setEnabled(false);
    }
  }
}

//-----------

CQGroupBoxArea::
CQGroupBoxArea(QWidget *parent) :
 QWidget(parent)
{
}

void
CQGroupBoxArea::
paintEvent(QPaintEvent *)
{
  //QPainter p(this);

  //p.fillRect(rect(), QBrush(QColor(255,0,0)));
}
