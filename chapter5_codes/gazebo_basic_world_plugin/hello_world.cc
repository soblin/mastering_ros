#include <gazebo/gazebo.hh>

namespace gazebo{
class WorldPluginTutorial : public WorldPlugin {
 public:
  WorldPluginTutorial() : WorldPlugin() {
    std::cout << "Initialized. Hello World!" << std::endl;
  }
  virtual void Load(physics::WorldPtr world, sdf::ElementPtr sdf) override;
};

void WorldPluginTutorial::Load(physics::WorldPtr world, sdf::ElementPtr sdf){}

GZ_REGISTER_WORLD_PLUGIN(WorldPluginTutorial)

}
