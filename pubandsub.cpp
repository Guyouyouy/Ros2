class PerceptionNode : public rclcpp::Node {
public:
    PerceptionNode() : Node("perception_node") {
        camera_pub_ = this->create_publisher<sensor_msgs::msg::Image>("/camera/image", 10);
        lidar_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/lidar/points", 10);
        timer_ = this->create_wall_timer(100ms, [this]() {
            publish_camera_data();
            publish_lidar_data();
        });  
    }
private:
    void publish_camera_data() {
        auto message = sensor_msgs::msg::Image();
        message.header.stamp = this->now();
        message.header.frame_id = "camera_front";
        camera_pub_->publish(message);
    }
    void publish_lidar_data() {
        auto message = sensor_msgs::msg::PointCloud2();
        message.header.stamp = this->now();
        message.header.frame_id = "lidar_top";
        message.height = 1;
        lidar_pub_->publish(message);
    }
};
class LocalizationNode : public rclcpp::Node {
public:
    LocalizationNode() : Node("localization_node") {
        camera_sub_ = this->create_subscription<sensor_msgs::msg::Image>("/camera/image", 10,
            [this](const sensor_msgs::msg::Image::SharedPtr msg) {process_camera_data(msg);});
        lidar_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            "/lidar/points", 10,
            [this](const sensor_msgs::msg::PointCloud2::SharedPtr msg) {process_lidar_data(msg);});
    }
private:
    void process_camera_data(const sensor_msgs::msg::Image::SharedPtr msg) {}
    void process_lidar_data(const sensor_msgs::msg::PointCloud2::SharedPtr msg) {}
};
