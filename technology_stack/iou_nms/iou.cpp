#include <iostream>
#include <algorithm>

struct bbox
{
	double m_left;
	double m_top;
	double m_width;
	double m_height;
	double m_score = 0.0; // 置信度得分
 
	bbox() {}
	bbox(double left, double top, double width, double height, double score = 0.0) 
	{
		m_left = left;
		m_top = top;
		m_width = width;
		m_height = height;
		m_score = score;
	}
};

double IOU_compute(const bbox& b1, const bbox& b2)
{
	double x_left = std::max(b1.m_left, b2.m_left);
	double y_top = std::min(b1.m_top, b2.m_top);
	double x_right = std::min(b1.m_left + b1.m_width, b2.m_left + b2.m_width);
	double y_bottom = std::max(b1.m_top - b1.m_height, b2.m_top - b2.m_height);
    std::cout << "x_left: " << x_left << ", y_top: " << y_top << ", x_right: " << x_right << ", y_bottom: " << y_bottom << std::endl;

	double w = std::max(0.0, x_right - x_left);
    std::cout << "w: " << w << std::endl;
	double h = std::max(0.0, y_top - y_bottom);
    std::cout << "h: " << h << std::endl;

	double inter = w * h;
	double area1 = b1.m_width * b1.m_height;
	double area2 = b2.m_width * b2.m_height;
	double uni = area1 + area2 - inter;
	if (uni <= 0.0) {
        return 0.0;
    }

	return inter / uni;
}

int main()
{
	// 两个矩形框有部分重叠
	bbox a(2, 2, 3, 3); // 区间 x: [2,5), y: [2,5)
	bbox b(4, 3, 3, 3); // 区间 x: [4,7), y: [3,6)
	float iou = IOU_compute(a, b);
	std::cout << "IOU = " << iou << std::endl;
	double iou1_2 = IOU_compute(b, a);
	std::cout << "IOU = " << iou1_2 << std::endl;

    // 两个矩形框没有重叠
    bbox c(0, 0, 2, 2); // 区间 x: [0,2), y: [0,2)
    bbox d(3, 3, 2, 2); // 区间 x: [3,5), y: [3,5)
    float iou2 = IOU_compute(c, d);
    std::cout << "IOU = " << iou2 << std::endl;
	return 0;
}
