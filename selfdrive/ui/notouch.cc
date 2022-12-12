#include <QApplication>
#include <QtWidgets>
#include <QTimer>
#include <QGraphicsScene>
#include <QWidget>
#include <QVBoxLayout>

#include "cereal/messaging/messaging.h"
#include "selfdrive/ui/ui.h"
#include "selfdrive/ui/notouch.h"
#include "selfdrive/ui/qt/qt_window.h"

//class MainWindow : public QWidget {
//  Q_OBJECT
//
//public:
//  explicit MainWindow(QWidget *parent = 0) : QWidget(parent) {
////    main_layout = new QVBoxLayout(this);
////    main_layout->setMargin(0);
//////    QLabel* hello = new QLabel("Hello!");
//////    main_layout->addWidget(hello);
//  };
//
////private:
////  bool eventFilter(QObject *obj, QEvent *event) override;
////  void openSettings(int index = 0, const QString &param = "");
////  void closeSettings();
////
////  Device device;
////
////  QVBoxLayout *main_layout;
////  HomeWindow *homeWindow;
////  SettingsWindow *settingsWindow;
////  OnboardingWindow *onboardingWindow;
//};

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  main_layout = new QVBoxLayout(this);
  main_layout->setMargin(0);
  QLabel* hello = new QLabel("Hello!");
  main_layout->addWidget(hello);

  onroad = new OnroadWindow(this);

  QString route_name = MultiOptionDialog::getSelection(tr("Select a route"), routes, "", this);
  qDebug() << "Selected:" << route_name;

  QString data_dir = QString::fromStdString(Path::log_root());
  replay.reset(new Replay(route_name, {}, {}, uiState()->sm.get(), REPLAY_FLAG_NONE, data_dir));

//
//  homeWindow = new HomeWindow(this);
//  main_layout->addWidget(homeWindow);
//  QObject::connect(homeWindow, &HomeWindow::openSettings, this, &MainWindow::openSettings);
//  QObject::connect(homeWindow, &HomeWindow::closeSettings, this, &MainWindow::closeSettings);
//
//  settingsWindow = new SettingsWindow(this);
//  main_layout->addWidget(settingsWindow);
//  QObject::connect(settingsWindow, &SettingsWindow::closeSettings, this, &MainWindow::closeSettings);
//  QObject::connect(settingsWindow, &SettingsWindow::reviewTrainingGuide, [=]() {
//    onboardingWindow->showTrainingGuide();
//    main_layout->setCurrentWidget(onboardingWindow);
//  });
//  QObject::connect(settingsWindow, &SettingsWindow::showDriverView, [=] {
//    homeWindow->showDriverView(true);
//  });
//
//  onboardingWindow = new OnboardingWindow(this);
//  main_layout->addWidget(onboardingWindow);
//  QObject::connect(onboardingWindow, &OnboardingWindow::onboardingDone, [=]() {
//    main_layout->setCurrentWidget(homeWindow);
//  });
//  if (!onboardingWindow->completed()) {
//    main_layout->setCurrentWidget(onboardingWindow);
//  }
//
//  QObject::connect(uiState(), &UIState::offroadTransition, [=](bool offroad) {
//    if (!offroad) {
//      closeSettings();
//    }
//  });
//  QObject::connect(&device, &Device::interactiveTimout, [=]() {
//    if (main_layout->currentWidget() == settingsWindow) {
//      closeSettings();
//    }
//  });
//
//  // load fonts
//  QFontDatabase::addApplicationFont("../assets/fonts/Inter-Black.ttf");
//  QFontDatabase::addApplicationFont("../assets/fonts/Inter-Bold.ttf");
//  QFontDatabase::addApplicationFont("../assets/fonts/Inter-ExtraBold.ttf");
//  QFontDatabase::addApplicationFont("../assets/fonts/Inter-ExtraLight.ttf");
//  QFontDatabase::addApplicationFont("../assets/fonts/Inter-Medium.ttf");
//  QFontDatabase::addApplicationFont("../assets/fonts/Inter-Regular.ttf");
//  QFontDatabase::addApplicationFont("../assets/fonts/Inter-SemiBold.ttf");
//  QFontDatabase::addApplicationFont("../assets/fonts/Inter-Thin.ttf");
//  QFontDatabase::addApplicationFont("../assets/fonts/JetBrainsMono-Medium.ttf");
//
//  // no outline to prevent the focus rectangle
//  setStyleSheet(R"(
//    * {
//      font-family: Inter;
//      outline: none;
//    }
//  )");
//  setAttribute(Qt::WA_NoSystemBackground);
}

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
//  QWidget w;
  MainWindow w;
  setMainWindow(&w);

//  w.setStyleSheet("background-color: black;");
//
//  // our beautiful UI
//  QVBoxLayout *layout = new QVBoxLayout(&w);
//
//  QGraphicsScene *scene = new QGraphicsScene();
//  StatusBar *status_bar = new StatusBar(0, 0, 1000, 50);
//  scene->addItem(status_bar);
//
//  QGraphicsView *graphics_view = new QGraphicsView(scene);
//  layout->insertSpacing(0, 400);
//  layout->addWidget(graphics_view, 0, Qt::AlignCenter);
//
//  QTimer timer;
//  QObject::connect(&timer, &QTimer::timeout, [=]() {
//    static SubMaster sm({"deviceState", "controlsState", "lateralPlan"});
//
//    bool onroad_prev = sm.allAliveAndValid({"deviceState"}) &&
//                       sm["deviceState"].getDeviceState().getStarted();
//    sm.update(0);
//
//    bool onroad = sm.allAliveAndValid({"deviceState"}) &&
//                  sm["deviceState"].getDeviceState().getStarted();
//
//    if (onroad) {
//      auto cs = sm["controlsState"].getControlsState();
//      UIStatus status = cs.getEnabled() ? STATUS_ENGAGED : STATUS_DISENGAGED;
//      if (cs.getAlertStatus() == cereal::ControlsState::AlertStatus::USER_PROMPT) {
//        status = STATUS_WARNING;
//      } else if (cs.getAlertStatus() == cereal::ControlsState::AlertStatus::CRITICAL) {
//        status = STATUS_ALERT;
//      }
//
//      auto lp = sm["lateralPlan"].getLateralPlan();
//      if (lp.getLaneChangeState() == cereal::LateralPlan::LaneChangeState::PRE_LANE_CHANGE || status == STATUS_ALERT) {
//        status_bar->blinkingColor(bg_colors[status]);
//      } else if (lp.getLaneChangeState() == cereal::LateralPlan::LaneChangeState::LANE_CHANGE_STARTING ||
//                 lp.getLaneChangeState() == cereal::LateralPlan::LaneChangeState::LANE_CHANGE_FINISHING) {
//        status_bar->laneChange(lp.getLaneChangeDirection());
//      } else {
//        status_bar->solidColor(bg_colors[status]);
//      }
//    }
//
//    if ((onroad != onroad_prev) || sm.frame < 2) {
//      Hardware::set_brightness(50);
//      Hardware::set_display_power(onroad);
//    }
//  });
//  timer.start(50);

  return a.exec();
}
