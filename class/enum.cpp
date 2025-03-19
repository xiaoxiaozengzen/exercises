#include <iostream>
#include <string>

enum class RadarIndex {
  FRONT4D,
  FRONT_RIGHT,
  FRONT_LEFT,
  REAR_RIGHT,
  REAR_LEFT,
};

enum class RosMsgType : std::uint8_t {
  PERCEPTION_RESULT,
  FRONT_RADAR,
  FRONT_RIGHT_RADAR,
  FRONT_LEFT_RADAR,
  REAR_RIGHT_RADAR,
  REAR_LEFT_RADAR,
};

int main() {
  RadarIndex radar_index = RadarIndex::FRONT4D;

#if 0
  // 直接输出枚举值会报错，因为枚举没有重载输出运算符
  std::cout << "RadarIndex: " << radar_index << std::endl;
#endif

  // 使用static_cast转换为int类型
  int front_left_radar = static_cast<int>(RosMsgType::FRONT_LEFT_RADAR);
  std::cout << "RosMsgType FRONT_LEFT_RADAR: " << front_left_radar << std::endl;

#if 0
  编译报错:error: cannot convert 'RosMsgType' to 'int' in initialization
  int ret = RosMsgType::FRONT_LEFT_RADAR;
#endif

  // 使用static_cast转换为RosMsgType类型
  RosMsgType msg_type = static_cast<RosMsgType>(3);
  std::cout << "RosMsgType: " << static_cast<int>(msg_type) << std::endl;

  // 超过枚举范围的值，编译不会报错，但是输出的值是未定义的
  RosMsgType msg_type2 = static_cast<RosMsgType>(7);
  std::cout << "RosMsgType: " << static_cast<int>(msg_type2) << std::endl;

  return 0;
}