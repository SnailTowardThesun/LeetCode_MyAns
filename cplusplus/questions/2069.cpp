/**
 * 2069. 模拟行走机器人 II
 *
 * 题目描述：
 * 给你一个在 XY 平面上的 width x height 的网格，左下角在 (0, 0)，右上角在 (width-1, height-1)。
 * 机器人从 (0, 0) 出发，面朝东方。每一步，机器人可以向前移动一个单位长度或逆时针旋转 90 度。
 * 但机器人不能走出网格，它会一直按照网格的边界行走。
 * 实现 Robot 类：
 * 1. Robot(int width, int height) 初始化一个 width x height 的网格上的机器人
 * 2. void step(int num) 执行 num 步操作
 * 3. vector<int> getPos() 返回机器人当前位置 [x, y]
 * 4. string getDir() 返回机器人当前朝向（"East", "North", "West", "South"）
 *
 * 解题思路：
 * 1. 机器人在网格的边界上行走，形成一个环，周长为 2*(width + height - 2)
 * 2. 使用模运算计算实际需要走的步数，避免重复计算
 * 3. 根据步数判断机器人的位置和朝向
 * 4. 步数计算规则：
 *    - 东边：0 到 width-1 步
 *    - 北边：width 到 width+height-2 步
 *    - 西边：width+height-1 到 2*width+height-3 步
 *    - 南边：2*width+height-2 到 2*(width+height-2) 步
 */

#include <gtest/gtest.h>

#include <string>
#include <vector>

class Robot {
   private:
    int _width{0};
    int _height{0};
    int _current_step{0};

   public:
    Robot(int width, int height) : _width(width), _height(height) {}

    void step(int num) { _current_step = (_current_step + num - 1) % ((_width + _height - 2) * 2) + 1; }

    std::vector<int> getPos() {
        if (_current_step < _width) {  // 东边
            return std::vector<int>{_current_step, 0};
        } else if (_current_step < _width + _height - 1) {  // 北边
            return std::vector<int>{_width - 1, _current_step - _width + 1};
        } else if (_current_step < 2 * _width + _height - 2) {  // 西边
            return std::vector<int>{2 * _width + _height - _current_step - 3, _height - 1};
        } else {  // 南边
            return std::vector<int>{0, 2 * (_width + _height) - _current_step - 4};
        }
    }

    std::string getDir() {
        if (_current_step < _width) {  // 东边
            return "East";
        } else if (_current_step < _width + _height - 1) {  // 北边
            return "North";
        } else if (_current_step < 2 * _width + _height - 2) {  // 西边
            return "West";
        } else {  // 南边
            return "South";
        }
    }
};

/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->step(num);
 * std::vector<int> param_2 = obj->getPos();
 * std::string param_3 = obj->getDir();
 */
TEST(Daily, 2069) {
    Robot robot(3, 4);
    robot.step(3);
    auto param_2 = robot.getPos();
    auto param_3 = robot.getDir();
    std::cout << param_2.size() << std::endl;
    std::cout << param_3 << std::endl;
}
