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

	double w = std::max(0.0, x_right - x_left);
	double h = std::max(0.0, y_top - y_bottom);

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
        bbox(4.21716537e+01, 1.28230896e+02, 2.26547668e+02, 6.00434631e+02, 0.5247661),
        bbox(3.18562988e+02, 1.23168472e+02, 4.79000000e+02, 6.05688416e+02, 0.51759845),
        bbox(2.62704697e+01, 1.39430557e+02, 2.20587097e+02, 6.38959656e+02, 0.86075854),
        bbox(4.24965363e+01, 1.42706665e+02, 2.25955185e+02, 6.35671204e+02, 0.9910175),
        bbox(2.37462646e+02, 1.35731537e+02, 4.79000000e+02, 6.31451294e+02, 0.39170712),
        bbox(3.19390472e+02, 1.29295090e+02, 4.79000000e+02, 6.33003845e+02, 0.9297706),
        bbox(3.28933838e+02, 1.22736115e+02, 4.79000000e+02, 6.39000000e+02, 0.5115228),
        bbox(4.44292603e+01, 1.70438187e+02, 2.26841858e+02, 6.39000000e+02, 0.270992),
        bbox(2.17988785e+02, 3.02472412e+02, 4.06062927e+02, 6.29106628e+02, 0.19087596),
        bbox(2.00241089e+02, 3.23755096e+02, 3.96929321e+02, 6.36386108e+02, 0.64201415),
        bbox(2.14310303e+02, 3.23443665e+02, 4.06732849e+02, 6.35775269e+02, 0.879036)
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