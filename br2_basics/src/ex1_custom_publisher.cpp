#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>

#include <memory>

using namespace std::chrono_literals;

class Ex1CustomPublisher : public rclcpp::Node {
public:
	Ex1CustomPublisher() : Node("custom_publisher")
	{
		publisher_ = create_publisher<std_msgs::msg::Int32>("custom_publisher_topic", 10);

		timer_ = create_wall_timer(500ms, std::bind(&Ex1CustomPublisher::timer_callback, this));
	}

	void timer_callback()
	{
		msg_int32_.data += 1;
		publisher_->publish(msg_int32_);
	}

private:
	rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
	rclcpp::TimerBase::SharedPtr timer_;
	std_msgs::msg::Int32 msg_int32_;
};

int main(int argc, char *argv[])
{
	rclcpp::init(argc, argv);

	auto node = std::make_shared<Ex1CustomPublisher>();

	rclcpp::spin(node);
	rclcpp::shutdown();

	return 0;
}