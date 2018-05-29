#include <QDialog>

class CQGroupBox;

class CQGroupBoxTest : public QDialog {
  Q_OBJECT

 public:
  CQGroupBoxTest(bool checkable, bool collapse, bool line);
};
