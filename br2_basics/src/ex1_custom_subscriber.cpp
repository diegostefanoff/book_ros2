#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>

class Ex1CustomSubscriber : public rclcpp::Node {
public:
	Ex1CustomSubscriber() : Node("ex1_custom_subscriber")
	{
		subscriber_ = create_subscription<std_msgs::msg::Int32>("ex1_custom_publisher", 10,
			std::bind(&Ex1CustomSubscriber::callback, this, std::placeholders::_1));
	}

	void callback(const std_msgs::msg::Int32::SharedPtr msg)
	{
		RCLCPP_INFO(this->get_logger(), "Message received: %d.", msg->data);
	}

private:
	rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscriber_;
	std_msgs::msg::Int32 msg_int32_;
};

int main(int argc, char *argv[])
{
	rclcpp::init(argc, argv);

	auto node = std::make_shared<Ex1CustomSubscriber>();

	rclcpp::spin(node);
	rclcpp::shutdown();

	return 0;
}