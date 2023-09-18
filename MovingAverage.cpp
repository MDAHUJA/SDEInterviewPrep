#include <iostream>
#include <vector>

using namespace std; // Add this line

class MovingAverage {
public:
    MovingAverage(int period) : period_(period), sum_(0) {
        // Initialize the circular buffer with zeros
        buffer_.resize(period, 0);
    }

    double addPrice(double price) {
        // Remove the oldest price from the sum
        sum_ -= buffer_[index_];

        // Add the new price to the buffer and the sum
        buffer_[index_] = price;
        sum_ += price;

        // Move to the next position in the circular buffer
        index_ = (index_ + 1) % period_;

        // Calculate and return the moving average
        return sum_ / period_;
    }

private:
    int period_;
    vector<double> buffer_;
    int index_ = 0;
    double sum_;
};

int main() {
    // Create a MovingAverage object with a period of 5
    MovingAverage ma(5);

    // Add price inputs and calculate moving averages
    double prices[] = {10.0, 12.0, 15.0, 14.0, 16.0, 18.0, 20.0};
    for (double price : prices) {
        double avg = ma.addPrice(price);
        cout << "Price: " << price << " Moving Average: " << avg << endl;
    }

    return 0;
}
