#include <CQGroupBoxTest.h>
#include <CQGroupBox.h>
#include <CQApp.h>

#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  bool checkable = false;
  bool collapse  = false;
  bool line      = false;

  for (int i = 1; i < argc; ++i)
    if      (strcmp("-check", argv[i]) == 0)
      checkable = true;
    else if (strcmp("-collapse", argv[i]) == 0)
      collapse = true;
    else if (strcmp("-line", argv[i]) == 0)
      line = true;

  CQGroupBoxTest *test = new CQGroupBoxTest(checkable, collapse, line);

  test->show();

  return app.exec();
}

CQGroupBox *
createGroup(const QString &name, const QString &title=QString(), bool line=false)
{
  CQGroupBox *box = new CQGroupBox(title);
  box->setObjectName(name);

  box->setTitleScale(0.9);

  if (line) {
    box->setMarginTop(24);
    box->setMarginBottom(8);
  }

  QVBoxLayout *layout = new QVBoxLayout(box);

  QPushButton *button1 = new QPushButton("Button One");
  button1->setObjectName("button1");

  QPushButton *button2 = new QPushButton("Button Two");
  button2->setObjectName("button2");

  QPushButton *button3 = new QPushButton("Button Three");
  button3->setObjectName("button3");

  layout->addWidget(button1);
  layout->addWidget(button2);
  layout->addWidget(button3);

  return box;
}

QGroupBox *
createGroupBox(const QString &name, const QString &title=QString())
{
  QGroupBox *box = new QGroupBox(title);
  box->setObjectName(name);

  QVBoxLayout *layout = new QVBoxLayout(box);

  QPushButton *button1 = new QPushButton("Button One");
  button1->setObjectName("button1");

  QPushButton *button2 = new QPushButton("Button Two");
  button2->setObjectName("button2");

  QPushButton *button3 = new QPushButton("Button Three");
  button3->setObjectName("button3");

  layout->addWidget(button1);
  layout->addWidget(button2);
  layout->addWidget(button3);

  return box;
}

CQGroupBoxTest::
CQGroupBoxTest(bool checkable, bool collapse, bool line)
{
  setObjectName("test");

  QGridLayout *layout = new QGridLayout(this);
  layout->setMargin(2); layout->setSpacing(2);

  CQGroupBox *box1 = createGroup("group1", "Group 1", line);

  box1->setCheckable(checkable);
  box1->setCollapsible(collapse);

  box1->setTitleAlignment(Qt::AlignLeft | Qt::AlignTop);
  box1->setHasLineTop(line);
  box1->setHasLineBottom(line);
  box1->setLineTopAlignment(Qt::AlignBottom);
  box1->setLineBottomAlignment(Qt::AlignBottom);

  layout->addWidget(box1, 0, 0);

  CQGroupBox *box2 = createGroup("group2", "Group 2", line);

  box2->setCheckable(checkable);
  box2->setCollapsible(collapse);

  box2->setTitleAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  box2->setHasLineTop(line);
  box2->setHasLineBottom(line);
  box2->setLineTopAlignment(Qt::AlignVCenter);
  box2->setLineBottomAlignment(Qt::AlignVCenter);

  layout->addWidget(box2, 0, 1);

  CQGroupBox *box3 = createGroup("group3", "Group 3", line);

  box3->setCheckable(checkable);
  box3->setCollapsible(collapse);

  box3->setTitleAlignment(Qt::AlignRight | Qt::AlignBottom);
  box3->setHasLineTop(line);
  box3->setHasLineBottom(line);
  box3->setLineTopAlignment(Qt::AlignTop);
  box3->setLineBottomAlignment(Qt::AlignTop);

  box3->setEnabled(false);

  layout->addWidget(box3, 0, 2);

  //---

  CQGroupBox *box4 = createGroup("group4", "", line);

  box4->setCheckable(checkable);
  box4->setCollapsible(collapse);

  box4->setHasLineTop(line);
  box4->setHasLineBottom(line);
  box4->setLineTopAlignment(Qt::AlignBottom);
  box4->setLineBottomAlignment(Qt::AlignBottom);

  layout->addWidget(box4, 1, 0);

  CQGroupBox *box5 = createGroup("group5", "", line);

  box5->setHasLineTop(line);
  box5->setHasLineBottom(line);
  box5->setLineTopAlignment(Qt::AlignVCenter);
  box5->setLineBottomAlignment(Qt::AlignVCenter);

  layout->addWidget(box5, 1, 1);

  CQGroupBox *box6 = createGroup("group6", "", line);

  box6->setHasLineTop(line);
  box6->setHasLineBottom(line);
  box6->setLineTopAlignment(Qt::AlignTop);
  box6->setLineBottomAlignment(Qt::AlignTop);

  layout->addWidget(box6, 1, 2);

  //---

  QGroupBox *box7 = createGroupBox("group7", "Group 7");

  box7->setCheckable(checkable);
//box7->setCollapsible(collapse);

  layout->addWidget(box7, 2, 0);

  QGroupBox *box8 = createGroupBox("group8", "Group 8");

  box8->setStyleSheet(
  "QGroupBox { "
    "font: bold; "
    "border: 0px 0px 0px 0px; "
    "padding: 20px 0px 0px 0px; "
    "margin: 0px 0px 0px 0px; "
    "subcontrol-origin: border; "
    "subcontrol-position: left bottom; "
    "border: 0px solid blue; "
    "border-radius: 5px; "
  "}"
  "QGroupBox::title { "
    "color: #000000; "
    "top: 10px; "
    "left: 10px; "
  "}");

  layout->addWidget(box8, 2, 1);

  QGroupBox *box9 = createGroupBox("group9");

  layout->addWidget(box9, 2, 2);
}
