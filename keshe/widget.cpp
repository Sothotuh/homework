#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    
    layoutG=new QGridLayout;
    layoutG->setHorizontalSpacing(20);
    
    titles[0]=new QLabel("电梯1",this);
    titles[0]->setAlignment(Qt::AlignCenter);
    titles[1]=new QLabel("电梯2",this);
    titles[1]->setAlignment(Qt::AlignCenter);
    titles[2]=new QLabel("电梯3",this);
    titles[2]->setAlignment(Qt::AlignCenter);
    titles[3]=new QLabel("电梯4",this);
    titles[3]->setAlignment(Qt::AlignCenter);
    titles[4]=new QLabel("大楼",this);
    titles[4]->setAlignment(Qt::AlignCenter);
    
    
    layoutG->addWidget(titles[0],0,0,1,2);
    layoutG->addWidget(titles[1],0,2,1,2);
    layoutG->addWidget(titles[2],0,4,1,2);
    layoutG->addWidget(titles[3],0,6,1,2);
    layoutG->addWidget(titles[4],0,8,1,2);
    
    
    for(int ti=20;ti>-1;--ti){
        QString tstr;
        tstr.setNum(ti);
        
        floorLights[0][ti]=new QLabel(tstr,this);
        floorLights[0][ti]->setFrameStyle(QFrame::Box);
        floorLights[0][ti]->setAlignment(Qt::AlignCenter);
        layoutG->addWidget(floorLights[0][ti],(21-ti),0,1,2);
        
        floorLights[1][ti]=new QLabel(tstr,this);
        floorLights[1][ti]->setFrameStyle(QFrame::Box);
        floorLights[1][ti]->setAlignment(Qt::AlignCenter);
        layoutG->addWidget(floorLights[1][ti],(21-ti),2,1,2);
        
        floorLights[2][ti]=new QLabel(tstr,this);
        floorLights[2][ti]->setFrameStyle(QFrame::Box);
        floorLights[2][ti]->setAlignment(Qt::AlignCenter);
        layoutG->addWidget(floorLights[2][ti],(21-ti),4,1,2);
        
        floorLights[3][ti]=new QLabel(tstr,this);
        floorLights[3][ti]->setFrameStyle(QFrame::Box);
        floorLights[3][ti]->setAlignment(Qt::AlignCenter);
        layoutG->addWidget(floorLights[3][ti],(21-ti),6,1,2);
        
        flags[0][ti]=new QLabel("↑",this);
        flags[0][ti]->setFrameStyle(QFrame::Box);
        flags[0][ti]->setAlignment(Qt::AlignCenter);
        layoutG->addWidget(flags[0][ti],(21-ti),8,1,1);
        
        flags[1][ti]=new QLabel("↓",this);
        flags[1][ti]->setFrameStyle(QFrame::Box);
        flags[1][ti]->setAlignment(Qt::AlignCenter);
        layoutG->addWidget(flags[1][ti],(21-ti),9,1,1);
        
    }
    
    list[0]=new QListWidget(this);
    list[0]->setFrameStyle(QFrame::Box);
    layoutG->addWidget(list[0],22,0,4,2);
    list[1]=new QListWidget(this);
    list[1]->setFrameStyle(QFrame::Box);
    layoutG->addWidget(list[1],22,2,4,2);
    list[2]=new QListWidget(this);
    list[2]->setFrameStyle(QFrame::Box);
    layoutG->addWidget(list[2],22,4,4,2);
    list[3]=new QListWidget(this);
    list[3]->setFrameStyle(QFrame::Box);
    layoutG->addWidget(list[3],22,6,4,2);
    
    
    getFrom=new QLineEdit(this);
    getFrom->setValidator(new QIntValidator(0,21,this));
    getTo=new QLineEdit(this);
    getTo->setValidator(new QIntValidator(0,21,this));
    getWeight=new QLineEdit(this);
    getWeight->setValidator(new QIntValidator(10,500,this));
    addPassenger=new QPushButton(this);
    addPassenger->setText("add(&A)");
    pause=new QPushButton(this);
    pause->setText("pause(&P)");
    
    from=new QLabel("从",this);
    from->setAlignment(Qt::AlignRight);
    to=new QLabel("至",this);
    to->setAlignment(Qt::AlignRight);
    weight=new QLabel("重",this);
    weight->setAlignment(Qt::AlignRight);
    
    layoutG->addWidget(from,22,8,1,1);
    layoutG->addWidget(to,23,8,1,1);
    layoutG->addWidget(weight,24,8,1,1);
    
    layoutG->addWidget(getFrom,22,9,1,1);
    layoutG->addWidget(getTo,23,9,1,1);
    layoutG->addWidget(getWeight,24,9,1,1);
    layoutG->addWidget(addPassenger,25,8,1,1);
    layoutG->addWidget(pause,25,9,1,1);
    
    setLayout(layoutG);
    
    connect(getFrom,SIGNAL(returnPressed()),getTo,SLOT(setFocus()));
    connect(getTo,SIGNAL(returnPressed()),getWeight,SLOT(setFocus()));
    connect(getWeight,SIGNAL(returnPressed()),getFrom,SLOT(setFocus()));
    connect(addPassenger,SIGNAL(pressed()),this,SLOT(on_addPassenger_pressed()));
    connect(pause,SIGNAL(pressed()),this,SLOT(on_pause_pressed()));
    
    running=1;
    
    
    
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setLight(){
    for(int ti=0;ti<4;++ti){
        for(int tj=0;tj<21;++tj){
            int tflag=0;
            for(auto it=data::elevators[ti].vect.begin();it!=data::elevators[ti].vect.end();++it){
                if(it->to==tj){
                    tflag=1;
                    break;
                }
            }
            if(tflag==1){
                floorLights[ti][tj]->setStyleSheet("background-color:rgb(0,255,0);");
            }
            else{
                floorLights[ti][tj]->setStyleSheet("background-color:rgb(240,240,240);");
            }
        }
    }
    for(int ti=0;ti<21;++ti){
        if(data::floors[ti].wait(1)){
            flags[0][ti]->setStyleSheet("background-color:rgb(0,255,0);");
        }
        else{
            flags[0][ti]->setStyleSheet("background-color:rgb(240,240,240);");
        }
        if(data::floors[ti].wait(-1)){
            flags[1][ti]->setStyleSheet("background-color:rgb(0,255,0);");
        }
        else{
            flags[1][ti]->setStyleSheet("background-color:rgb(240,240,240);");
        }
    }
}

void Widget::timerEvent(QTimerEvent*event){
    if(event->timerId()==timerId&&running){
        ++data::clock;
        data::elevators[3].run();
        data::elevators[2].run();
        data::elevators[1].run();
        data::elevators[0].run();
        
        setLight();
        
        list[0]->takeItem(0);
        list[0]->insertItem(0,QString::number(data::elevators[0].nowFloor));
        list[1]->takeItem(0);
        list[1]->insertItem(0,QString::number(data::elevators[1].nowFloor));
        list[2]->takeItem(0);
        list[2]->insertItem(0,QString::number(data::elevators[2].nowFloor));
        list[3]->takeItem(0);
        list[3]->insertItem(0,QString::number(data::elevators[3].nowFloor));
        
        
    }
}

void Widget::on_addPassenger_pressed(){
    int from=getFrom->text().toInt();
    int to=getTo->text().toInt();
    int weight=getWeight->text().toInt();
    data::floors[from].add(weight,to);
//    qDebug()<<"pressed";
}

void Widget::on_pause_pressed(){
    running^=1;
}





