#include <vector>
#include <algorithm>  // for std::reverse
#include <stdexcept>  // for std::invalid_argument

// lfilter function (simplified)
std::vector<double> lfilter(const std::vector<double>& b, const std::vector<double>& a, const std::vector<double>& x) {
    std::vector<double> y(x.size(), 0.0);
    int N = x.size();
    int M = b.size();
    int L = a.size();

    for (int n = 0; n < N; ++n) {
        for (int m = 0; m < M; ++m) {
            if (n - m >= 0) {
                y[n] += b[m] * x[n - m];
            }
        }
        for (int l = 1; l < L; ++l) {
            if (n - l >= 0) {
                y[n] -= a[l] * y[n - l];
            }
        }
    }
    return y;
}

// filtfilt function
std::vector<double> filtfilt(
    const std::vector<double>& b,
    const std::vector<double>& a,
    const std::vector<double>& x,
    int axis = -1,
    const std::string& padtype = "odd",
    int padlen = 0,
    const std::string& method = "pad",
    int irlen = 0
) {
    // Input validation
    if (method != "pad" && method != "gust") {
        throw std::invalid_argument("Method must be 'pad' or 'gust'.");
    }

    // TODO: Implement padding (if required)

    // Forward filter.
    std::vector<double> y_forward = lfilter(b, a, x);

    // Reverse the forward result.
    std::reverse(y_forward.begin(), y_forward.end());

    // Backward filter.
    std::vector<double> y_backward = lfilter(b, a, y_forward);

    // Reverse the backward result to get the final output.
    std::reverse(y_backward.begin(), y_backward.end());

    // TODO: Remove padding (if required)

    return y_backward;
}
