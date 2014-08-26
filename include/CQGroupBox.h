#ifndef CQGroupBox_H
#define CQGroupBox_H

#include <QWidget>

class CQGroupBoxArea;

class CQGroupBox : public QWidget {
  Q_OBJECT

  Q_PROPERTY(QString title               READ title               WRITE setTitle              )
  Q_PROPERTY(bool    titleBold           READ isTitleBold         WRITE setTitleBold          )
  Q_PROPERTY(double  titleScale          READ titleScale          WRITE setTitleScale         )
  Q_PROPERTY(int     titleAlignment      READ titleAlignment      WRITE setTitleAlignment     )
  Q_PROPERTY(bool    lineTop             READ hasLineTop          WRITE setHasLineTop         )
  Q_PROPERTY(bool    lineBottom          READ hasLineBottom       WRITE setHasLineBottom      )
  Q_PROPERTY(int     lineTopAlignment    READ lineTopAlignment    WRITE setLineTopAlignment   )
  Q_PROPERTY(int     lineBottomAlignment READ lineBottomAlignment WRITE setLineBottomAlignment)
  Q_PROPERTY(int     marginLeft          READ marginLeft          WRITE setMarginLeft         )
  Q_PROPERTY(int     marginRight         READ marginRight         WRITE setMarginRight        )
  Q_PROPERTY(int     marginBottom        READ marginBottom        WRITE setMarginBottom       )
  Q_PROPERTY(int     marginTop           READ marginTop           WRITE setMarginTop          )
  Q_PROPERTY(bool    checkable           READ isCheckable         WRITE setCheckable          )
  Q_PROPERTY(bool    checked             READ isChecked           WRITE setChecked            )

 public:
  CQGroupBox(QWidget *parent=0);
  CQGroupBox(const QString &title, QWidget *parent=0);

  ~CQGroupBox();

  const QString &title() const { return title_; }

  bool isTitleBold() const { return titleBold_; }

  double titleScale() const { return titleScale_; }

  Qt::Alignment titleAlignment() const { return Qt::Alignment(titleAlignment_); }

  bool hasLineTop   () const { return lineTop_   ; }
  bool hasLineBottom() const { return lineBottom_; }

  Qt::Alignment lineTopAlignment   () const { return Qt::Alignment(lineTopAlignment_   ); }
  Qt::Alignment lineBottomAlignment() const { return Qt::Alignment(lineBottomAlignment_); }

  int marginLeft  () const { return marginLeft_  ; }
  int marginRight () const { return marginRight_ ; }
  int marginBottom() const { return marginBottom_; }
  int marginTop   () const { return marginTop_   ; }

  bool isCheckable() const { return checkable_; }

  bool isChecked() const { return checked_; }

  void setTitle(const QString &title);

  void setTitleBold(bool bold);

  void setTitleScale(double scale);

  void setTitleAlignment(int alignment);

  void setHasLineTop   (bool line);
  void setHasLineBottom(bool line);

  void setLineTopAlignment   (int alignment);
  void setLineBottomAlignment(int alignment);

  void setMarginLeft  (int margin);
  void setMarginRight (int margin);
  void setMarginBottom(int margin);
  void setMarginTop   (int margin);

  void setCheckable(bool checkable);

 private:
  void init();

  void setTitleFont();

  void changeEvent(QEvent *e);

  void childEvent(QChildEvent *e);

  bool event(QEvent *e);

  void focusInEvent(QFocusEvent *e);

  void mouseMoveEvent(QMouseEvent *e);
  void mousePressEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);

  void paintEvent(QPaintEvent *e);

  void resizeEvent(QResizeEvent *e);

  QSize minimumSizeHint() const;

  int spaceTop() const;
  int spaceBottom() const;

  void calculateFrame();

  void updateEnabled();

 signals:
  void clicked(bool checked);
  void toggled(bool checked);

 public slots:
  void setChecked(bool checked);

 private:
  CQGroupBoxArea *area_;
  QString         title_;
  bool            titleBold_;
  double          titleScale_;
  int             titleAlignment_;
  bool            lineTop_;
  bool            lineBottom_;
  int             lineTopAlignment_;
  int             lineBottomAlignment_;
  int             marginLeft_;
  int             marginRight_;
  int             marginBottom_;
  int             marginTop_;
  bool            checkable_;
  bool            checked_;
  bool            checkPress_;
  QRect           checkRect_;
  QRect           titleRect_;
  QFont           titleFont_;
  QColor          lineColor_;
  int             dx_, dy_;
};

class CQGroupBoxArea : public QWidget {
 public:
  CQGroupBoxArea(QWidget *parent=0);

  void paintEvent(QPaintEvent *e);
};

#endif
