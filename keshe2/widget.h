#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets>

#include "data.h"
#include "elevator.h"
#include "floor.h"
#include "passenger.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
	Q_OBJECT
		QGridLayout* layoutG;//布局管理器
	QLabel* titles[5];
	QLabel* floorLights[4][21];//四台电梯的楼层指示灯
	QLabel* flags[2][22];//所有楼层的按钮
	QListWidget* list[4];//电梯详细情况显示器
	QLineEdit* getFrom;
	QLineEdit* getTo;
	QLineEdit* getWeight;
	QPushButton* addPassenger;
	QPushButton* pause;

	int timerId = startTimer(500);
	int running;

	void setLight();



public:
	Widget(QWidget* parent = nullptr);
	~Widget();

private:
	Ui::Widget* ui;
	void timerEvent(QTimerEvent* event);

private slots:
	void on_addPassenger_pressed();
	void on_pause_pressed();
};
#endif // WIDGET_H
