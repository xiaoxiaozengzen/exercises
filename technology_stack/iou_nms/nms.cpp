#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

struct bbox
{
	double m_left;
	double m_top;
	double m_width;
	double m_height;
    double m_score; // 置信度得分
 
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

bool compare_score(const bbox& b1, const bbox& b2) {
    return b1.m_score > b2.m_score;
}

std::vector<int> non_max_suppression(const std::vector<bbox>& boxes, double iou_threshold)
{
    std::vector<int> idxs(boxes.size());
    for (size_t i = 0; i < boxes.size(); ++i) idxs[i] = (int)i;

    // 根据得分进行排序
    std::sort(idxs.begin(), idxs.end(), [&](int i, int j){
        return boxes[i].m_score > boxes[j].m_score;
    });

    // 选中的框的索引
    std::vector<int> keep;
    std::deque<int> remain(idxs.begin(), idxs.end());

    keep.push_back(remain.front());
    remain.pop_front();

    while(remain.empty() == false) {
        for(int _i = 0; _i < keep.size(); ++_i) {
            double iou = IOU_compute(boxes[remain.front()], boxes[keep[_i]]);
            if (iou < iou_threshold) {
                // 满足与keep中所有框的IOU阈值，保留该框
                if(_i == keep.size() - 1) {
                    keep.push_back(remain.front());
                }
            } else {
                // 舍弃该框
                break;
            }
        }
        remain.pop_front();
    }

    return keep;
}

int main()
{
    std::vector<bbox> boxes = {
        // Cluster A (重叠密集，靠左上)
        bbox(10, 10, 50, 50, 0.95),
        bbox(12, 14, 48, 48, 0.90),
        bbox(15, 18, 30, 30, 0.85),
        bbox(40, 12, 20, 40, 0.60),

        // Cluster B (中间，部分重叠)
        bbox(200, 200, 50, 50, 0.80),
        bbox(205, 205, 48, 48, 0.78),
        bbox(190, 195, 60, 60, 0.70),
        bbox(300, 220, 80, 40, 0.65),
        bbox(305, 225, 78, 38, 0.62),

        // Scattered / small / edge cases
        bbox(400, 50, 30, 30, 0.60),
        bbox(0, 0, 10, 10, 0.50),        // near origin
        bbox(5, 5, 12, 12, 0.45),        // overlaps small origin box
        bbox(639, 479, 2, 2, 0.40),      // near bottom-right pixel
        bbox(250, 50, 100, 120, 0.55),   // large box
        bbox(255, 60, 90, 100, 0.53)     // overlaps the large box
    };

    double iou_thresh = 0.5;
    std::vector<int> keep = non_max_suppression(boxes, iou_thresh);

    std::cout << "Kept boxes (index, left, top, w, h, score):\n";
    for (int idx : keep) {
        const bbox &b = boxes[idx];
        std::cout << idx << ": " << b.m_left << ", " << b.m_top << ", "
                  << b.m_width << ", " << b.m_height << ", " << b.m_score << '\n';
    }

    return 0;
}