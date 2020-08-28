#ifndef TELEOP_PAD_H
#define TELEOP_PAD_H

#ifndef Q_MOC_RUN
#include <rviz/panel.h>
#include <ros/ros.h>
#endif

#include <QPainter>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>

class QLineEdit;

namespace rviz_teleop_commander
{
class TeleopPanel : public rviz::Panel
{
  Q_OBJECT
public:
  TeleopPanel(QWidget* parent = 0);

  virtual void load(const rviz::Config& config);
  virtual void save(rviz::Config config) const;

public Q_SLOTS:
  void setTopic(const QString& topic);

protected Q_SLOTS:
  void sendVel();
  void updateLinearVelocity();
  void updateAngularVelocity();
  void updateTopic();

protected:
  QLineEdit* output_topic_editor_ = nullptr;

  QString output_topic_;
  QLineEdit* output_topic_editor_linear_ = nullptr;
  QLineEdit* output_topic_editor_angular_ = nullptr;

  ros::Publisher velocity_publisher_;
  ros::NodeHandle nh_;

  float linear_velocity_ = 0;
  float angular_velocity_ = 0;
};

}  // namespace rviz_teleop_commander
#endif /* TELEOP_PAD_H */
