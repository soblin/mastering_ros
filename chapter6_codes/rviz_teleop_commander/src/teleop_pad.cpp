#include "teleop_pad.h"
#include <geometry_msgs/Twist.h>

namespace rviz_teleop_commander
{
TeleopPanel::TeleopPanel(QWidget* parent)
  : rviz::Panel(parent)
  , output_topic_editor_(nullptr)
  , output_topic_editor_linear_(nullptr)
  , output_topic_editor_angular_(nullptr)
  , linear_velocity_(0)
  , angular_velocity_(0)
{
  QVBoxLayout* topic_layout = new QVBoxLayout;
  topic_layout->addWidget(new QLabel("Teleop Topic:"));
  output_topic_editor_ = new QLineEdit("");
  topic_layout->addWidget(output_topic_editor_);

  topic_layout->addWidget(new QLabel("Linear Velocity:"));
  output_topic_editor_linear_ = new QLineEdit("");
  topic_layout->addWidget(output_topic_editor_linear_);

  topic_layout->addWidget(new QLabel("Angular Velocity:"));
  output_topic_editor_angular_ = new QLineEdit("");
  topic_layout->addWidget(output_topic_editor_angular_);

  QHBoxLayout* layout = new QHBoxLayout;
  layout->addLayout(topic_layout);
  setLayout(layout);

  QTimer* output_timer = new QTimer(this);

  connect(output_topic_editor_, SIGNAL(editingFinished()), this, SLOT(updateTopic()));
  connect(output_topic_editor_linear_, SIGNAL(editingFinished()), this, SLOT(updateLinearVelocity()));
  connect(output_topic_editor_angular_, SIGNAL(editingFinished()), this, SLOT(updateAngularVelocity()));

  connect(output_timer, SIGNAL(timeout()), this, SLOT(sendVel()));

  output_timer->start(100);
}

void TeleopPanel::updateTopic()
{
  setTopic(output_topic_editor_linear_->text());
}

void TeleopPanel::updateLinearVelocity()
{
  QString input_string = output_topic_editor_linear_->text();
  float lin = input_string.toFloat();
  linear_velocity_ = lin;
}

void TeleopPanel::updateAngularVelocity()
{
  QString input_string = output_topic_editor_angular_->text();
  float ang = input_string.toFloat();
  angular_velocity_ = ang;
}

void TeleopPanel::setTopic(const QString& new_topic)
{
  if (new_topic != output_topic_)
  {
    output_topic_ = new_topic;
    if (output_topic_ == "")
      velocity_publisher_.shutdown();
    else
    {
      velocity_publisher_ = nh_.advertise<geometry_msgs::Twist>(output_topic_.toStdString(), 1);
    }
    Q_EMIT configChanged();
  }
}

void TeleopPanel::sendVel()
{
  if (ros::ok() and velocity_publisher_)
  {
    geometry_msgs::Twist msg;
    msg.linear.x = linear_velocity_;
    msg.linear.y = msg.linear.z = 0;
    msg.angular.x = msg.angular.y = 0;
    msg.angular.z = angular_velocity_;
    velocity_publisher_.publish(msg);
  }
}

void TeleopPanel::save(rviz::Config config) const
{
  rviz::Panel::save(config);
  config.mapSetValue("Topic", output_topic_);
}

void TeleopPanel::load(const rviz::Config& config)
{
  rviz::Panel::load(config);
  QString topic;
  if (config.mapGetString("Topic", &topic))
  {
    output_topic_editor_->setText(topic);
    updateTopic();
  }
}
}  // namespace rviz_teleop_commander

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(rviz_teleop_commander::TeleopPanel, rviz::Panel);
