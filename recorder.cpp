#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

bool g_isRecorded = false;
bool g_isFlipped = false;

constexpr int SPACE_ASCII = 32;
constexpr int ESC_ASCII = 27;
constexpr int F_ASCII = 'F';
constexpr int f_ASCII = 'f';

constexpr int DESIRED_WIDTH = 800;
constexpr int DESIRED_HEIGHT = 600;


int main(int argc, char** argv)
{
	cv::Mat buffer;
	cv::VideoCapture camVideoCapture(0);
	cv::VideoWriter outputVideo;
	int key = 0;
	int ret = 0;
	camVideoCapture.set(cv::CAP_PROP_FRAME_WIDTH, DESIRED_WIDTH);
	camVideoCapture.set(cv::CAP_PROP_FRAME_HEIGHT, DESIRED_HEIGHT);

	ret = outputVideo.open(argv[1], cv::VideoWriter::fourcc('H', '2', '6', '4'), 30,
					cv::Size(camVideoCapture.get(cv::CAP_PROP_FRAME_WIDTH), camVideoCapture.get(cv::CAP_PROP_FRAME_HEIGHT)), true);

	if (camVideoCapture.isOpened() != true || ret == false)
	{
		__debugbreak();
	}

	while (camVideoCapture.isOpened() == true)
	{
		camVideoCapture >> buffer;
		key = cv::pollKey() & 0xFF;

		switch (key)
		{
		case F_ASCII:
		case f_ASCII:
			g_isFlipped ^= true;
			break;

		case SPACE_ASCII:
			g_isRecorded ^= true;
			break;

		case ESC_ASCII:
			outputVideo.release();
			camVideoCapture.release();
			break;
		}

		if (g_isFlipped == true)
		{
			cv::flip(buffer, buffer, 1);
		}

		if (g_isRecorded == true)
		{
			outputVideo << buffer;
			cv::circle(buffer, { 50, 50 }, 10, cv::Scalar{ 0, 0, 255 }, -1);
		}

		cv::imshow("record", buffer);
	}

	return 0;
}

